package com.secrethq.ads;

import java.lang.ref.WeakReference;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.google.android.gms.ads.AdView;
import com.heyzap.sdk.ads.HeyzapAds;
import com.heyzap.sdk.ads.InterstitialAd;
import com.heyzap.sdk.ads.VideoAd;
import com.heyzap.sdk.ads.IncentivizedAd;
import com.heyzap.sdk.ads.BannerAdView;
import com.heyzap.sdk.ads.HeyzapAds.BannerListener;
import com.heyzap.sdk.ads.HeyzapAds.BannerError;
import com.heyzap.sdk.ads.HeyzapAds.OnStatusListener;
import com.heyzap.sdk.ads.HeyzapAds.OnIncentiveResultListener;

import android.util.Log;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.RelativeLayout;

public class PTAdHeyzapBridge {
	private static native String bannerId();
	private static native String interstitialId();
	private static native void interstitialDidFail();
	private static native void bannerDidFail();
	private static native void rewardVideoComplete();
	
	private static final String TAG = "PTAdHeyzapBridge";
	private static Cocos2dxActivity activity;
	private static WeakReference<Cocos2dxActivity> s_activity;
	private static 	BannerAdView bannerAdView;
	
	private static boolean isBannerScheduledForShow = false;
	
	public static void initBridge(Cocos2dxActivity activity){
		Log.v(TAG, "PTAdHeyzapBridge -- INIT");
		PTAdHeyzapBridge.s_activity = new WeakReference<Cocos2dxActivity>(activity);	
		PTAdHeyzapBridge.activity = activity;
		
		PTAdHeyzapBridge.initBanner();
		PTAdHeyzapBridge.initInterstitial();
    	PTAdHeyzapBridge.initVideo();
	}

	public static void initBanner(){
		Log.v(TAG, "PTAdHeyzapBridge -- Init Banner");
		
		PTAdHeyzapBridge.s_activity.get().runOnUiThread( new Runnable() {
            public void run() {
            	PTAdHeyzapBridge.bannerAdView = new BannerAdView(PTAdHeyzapBridge.activity);
            	
            	FrameLayout frameLayout = (FrameLayout)PTAdHeyzapBridge.activity.findViewById(android.R.id.content);
        		RelativeLayout layout = new RelativeLayout( PTAdHeyzapBridge.activity );
        		frameLayout.addView( layout );
        		
        		RelativeLayout.LayoutParams adViewParams = new RelativeLayout.LayoutParams(
        				AdView.LayoutParams.WRAP_CONTENT,
        				AdView.LayoutParams.WRAP_CONTENT);
        		adViewParams.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
        		adViewParams.addRule(RelativeLayout.CENTER_IN_PARENT, RelativeLayout.TRUE);
        		
        		layout.addView(PTAdHeyzapBridge.bannerAdView, adViewParams);
        		PTAdHeyzapBridge.bannerAdView.setVisibility( View.INVISIBLE );
            	
        		// Add a listener.
            	PTAdHeyzapBridge.bannerAdView.setBannerListener(new BannerListener() {
        	        @Override
        	        public void onAdClicked(BannerAdView b) {
        	            // The ad has been clicked by the user.
        	        }

        	        @Override
        	        public void onAdLoaded(BannerAdView b) {
        	            // The ad has been loaded.
        	        	Log.v(TAG, "PTAdHeyzapBridge -- Banner onAdLoaded ");
        	        	PTAdHeyzapBridge.bannerAdView.setVisibility( PTAdHeyzapBridge.isBannerScheduledForShow ? View.VISIBLE : View.INVISIBLE );
        	        }

        	        @Override
        	        public void onAdError(BannerAdView b, BannerError bannerError) {
        	            // There was an error loading the ad.
        	        	Log.v(TAG, "PTAdHeyzapBridge -- Banner onAdError : " + bannerError.getErrorMessage());
        	        	bannerDidFail();
        	        }
        	    });
            	
            	PTAdHeyzapBridge.bannerAdView.load();
            }
        });
	}

	public static void initInterstitial(){
		Log.v(TAG, "PTAdHeyzapBridge -- Init Interstitial");		
		
		InterstitialAd.setOnStatusListener(new OnStatusListener() {
		    @Override
		    public void onShow(String tag) {
		        // Ad is now showing
		    }

		    @Override
		    public void onClick(String tag) {
		        // Ad was clicked on. You can expect the user to leave your application temporarily.
		    }

		    @Override
		    public void onHide(String tag) {
		        // Ad was closed. The user has returned to your application.
		    }

		    @Override
		    public void onFailedToShow(String tag) {
		        // Display was called but there was no ad to show
		    }

		    @Override
		    public void onAvailable(String tag) {
		        // An ad has been successfully fetched
		    }

		    @Override
		    public void onFailedToFetch(String tag) {
		        // No ad was able to be fetched
		    	Log.v(TAG, "PTAdHeyzapBridge -- Interstitial onFailedToFetch : " + tag);
		    	interstitialDidFail();
		    }

			@Override
			public void onAudioFinished() {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void onAudioStarted() {
				// TODO Auto-generated method stub
				
			}
		});
				
	}
	
	public static void initVideo() {
		IncentivizedAd.setOnIncentiveResultListener(new OnIncentiveResultListener() {
		    @Override
		    public void onComplete(String tag) {
		    	Log.v(TAG, "PTAdHeyzapBridge -- IncentivizedAd Complete ");
		    	
		        // Give the player their reward
		    	rewardVideoComplete();
		    }

		    @Override
		    public void onIncomplete(String tag) {
		        // Don't give the player their reward, and tell them why
		    	Log.v(TAG, "PTAdHeyzapBridge -- IncentivizedAd InComplete ");
		    }
		});
		
		PTAdHeyzapBridge.s_activity.get().runOnUiThread( new Runnable() {
            public void run() {
            	// As early as possible, and after showing a rewarded video, call fetch
        		IncentivizedAd.fetch();
            }
        });
	}
	
	public static void showRewardedVideo(){
		Log.v(TAG, "PTAdHeyzapBridge -- showRewardedVideo");
		
		PTAdHeyzapBridge.s_activity.get().runOnUiThread( new Runnable() {
            public void run() {
            	if (IncentivizedAd.isAvailable()) {
        		    IncentivizedAd.display(PTAdHeyzapBridge.activity);
        		}
            }
        });
		
	}
		
	public static void startSession( String sdkKey ){
        if(sdkKey != null){
            Log.v(TAG, "PTAdHeyzapBridge -- Start Session: " + sdkKey);

            try {
            	HeyzapAds.start(sdkKey, PTAdHeyzapBridge.activity);
			} catch (Exception e) {
				// TODO: handle exception
				Log.v(TAG, "PTAdHeyzapBridge -- Start Session FAILED : " + e.getMessage());
			}
    		
            Log.v(TAG, "Heyzap SDK Version : " + HeyzapAds.getVersion());

        }else{
            Log.v(TAG, "Start Session : null ");
        }
    }

	public static void showFullScreen(){
		Log.v(TAG, "PTAdHeyzapBridge -- showFullScreen");
		
		PTAdHeyzapBridge.s_activity.get().runOnUiThread( new Runnable() {
            public void run() {
            	// InterstitialAds are automatically fetched from our server
        		InterstitialAd.display(PTAdHeyzapBridge.activity);
            }
        });
	}

	public static void showBannerAd(){
		Log.v(TAG, "PTAdHeyzapBridge -- showBannerAd");
		
		isBannerScheduledForShow = true;
		
		PTAdHeyzapBridge.s_activity.get().runOnUiThread( new Runnable() {
            public void run() {
                if(PTAdHeyzapBridge.bannerAdView != null){
                	PTAdHeyzapBridge.bannerAdView.setVisibility(View.VISIBLE);
            		// Load the banner ad.
            		PTAdHeyzapBridge.bannerAdView.load();
                }
            }
        });
	}

	public static void hideBannerAd(){
		Log.v(TAG, "PTAdHeyzapBridge -- hideBannerAd");
		
		isBannerScheduledForShow = false;
		
		PTAdHeyzapBridge.s_activity.get().runOnUiThread( new Runnable() {
            public void run() {
                if(PTAdHeyzapBridge.bannerAdView != null){
                	PTAdHeyzapBridge.bannerAdView.setVisibility(View.INVISIBLE);
                }
            }
        });
	}

	public static boolean isBannerVisible() {	
		return (PTAdHeyzapBridge.bannerAdView.getVisibility() == View.VISIBLE);
	}

	public static boolean isRewardedVideoAvialable(){	
		return IncentivizedAd.isAvailable();
	}
}
