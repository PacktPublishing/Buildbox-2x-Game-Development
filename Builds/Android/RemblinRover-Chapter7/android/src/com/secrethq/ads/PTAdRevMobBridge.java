package com.secrethq.ads;

import java.lang.ref.WeakReference;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.util.Log;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.LinearLayout.LayoutParams;
import android.widget.RelativeLayout;

import com.revmob.*;
import com.revmob.ads.banner.RevMobBanner;

public class PTAdRevMobBridge {
	private static final String TAG = "PTAdRevMobBridge";
	private static Cocos2dxActivity activity;
	private static WeakReference<Cocos2dxActivity> s_activity;
	private static RevMob remob;
	private static String appid;
	private static ViewGroup view;
	private static RevMobBanner banner;
	private static RelativeLayout.LayoutParams adViewParams;
	
	private static native void interstitialDidFail();
	private static native void bannerDidFail();
	
	static RevMobAdsListener revmobFullscreenListener = new RevMobAdsListener() {
		@Override
		public void onRevMobAdClicked() {
			// TODO Auto-generated method stub
			Log.v(TAG, "onRevMobAdClicked");
		}

		@Override
		public void onRevMobAdDismissed() {
			// TODO Auto-generated method stub
			Log.v(TAG, "onRevMobAdDismiss");		
			
		}
		
		@Override
		public void onRevMobAdDisplayed() {
			// TODO Auto-generated method stub	
			Log.v(TAG, "onRevMobAdDisplayed");
		}

		@Override
		public void onRevMobAdNotReceived(String arg0) {
			// TODO Auto-generated method stub
			Log.v(TAG, "onRevMobAdNotReceived : " + arg0);
			PTAdRevMobBridge.interstitialDidFail();
		}

		@Override
		public void onRevMobAdReceived() {
			Log.v(TAG, "onRevMobAdReceived");
		}

		@Override
		public void onRevMobEulaIsShown() {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void onRevMobEulaWasAcceptedAndDismissed() {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void onRevMobEulaWasRejected() {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void onRevMobSessionIsStarted() {
			// TODO Auto-generated method stub
			Log.v(TAG, "session Is started");
		}

		@Override
		public void onRevMobSessionNotStarted(String arg0) {
			// TODO Auto-generated method stub
			
		}		
	};
	
	static RevMobAdsListener revmobBannerListener = new RevMobAdsListener() {
		@Override
		public void onRevMobAdClicked() {
			// TODO Auto-generated method stub
			Log.v(TAG, "Banner onRevMobAdClicked");
		}

		@Override
		public void onRevMobAdDismissed() {
			// TODO Auto-generated method stub
			Log.v(TAG, "Banner onRevMobAdDismiss");		
			
		}
		
		@Override
		public void onRevMobAdDisplayed() {
			// TODO Auto-generated method stub	
			Log.v(TAG, "Banner onRevMobAdDisplayed");
		}

		@Override
		public void onRevMobAdNotReceived(String arg0) {
			// TODO Auto-generated method stub
			Log.v(TAG, "Banner onRevMobAdNotReceived : " + arg0);
			PTAdRevMobBridge.bannerDidFail();
		}

		@Override
		public void onRevMobAdReceived() {
			Log.v(TAG, "Banner onRevMobAdReceived");
		}

		@Override
		public void onRevMobEulaIsShown() {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void onRevMobEulaWasAcceptedAndDismissed() {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void onRevMobEulaWasRejected() {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void onRevMobSessionIsStarted() {
			// TODO Auto-generated method stub
			Log.v(TAG, "session Is started");
		}

		@Override
		public void onRevMobSessionNotStarted(String arg0) {
			// TODO Auto-generated method stub
			
		}		
	};

	public static void initBridge(Cocos2dxActivity activity){
		Log.v(TAG, "RevMobXBridge  -- INIT");
		
		PTAdRevMobBridge.s_activity = new WeakReference<Cocos2dxActivity>(activity);		
		PTAdRevMobBridge.activity = activity;
		PTAdRevMobBridge.s_activity.get().runOnUiThread( new Runnable() {
			public void run() {
				FrameLayout frameLayout = (FrameLayout)PTAdRevMobBridge.activity.findViewById(android.R.id.content);
		
				adViewParams = new RelativeLayout.LayoutParams(
						RelativeLayout.LayoutParams.WRAP_CONTENT,
						RelativeLayout.LayoutParams.WRAP_CONTENT);
				adViewParams.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
				adViewParams.addRule(RelativeLayout.CENTER_IN_PARENT, RelativeLayout.TRUE);
				
				RelativeLayout layout = new RelativeLayout( PTAdRevMobBridge.activity );
//				layout.setLayoutParams(new LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT));
//				layout.setGravity( Gravity.BOTTOM );
				frameLayout.addView( layout );
		
				PTAdRevMobBridge.view = layout;
			}
		});

	}

	public static void startSession( String appid ){
		if(appid != null){
			Log.v(TAG, "Start Session: " + appid);
			PTAdRevMobBridge.appid = appid;
			PTAdRevMobBridge.s_activity.get().runOnUiThread( new Runnable() {
				public void run() {
					PTAdRevMobBridge.remob = RevMob.start(PTAdRevMobBridge.activity, PTAdRevMobBridge.appid);	
				}
			});			
		}else{
			Log.v(TAG, "Start Session : null ");			
		}
	}

	public static void showFullScreen(){
		Log.v(TAG, "showFullScreen");
		if(PTAdRevMobBridge.remob != null){
			PTAdRevMobBridge.remob.showFullscreen(PTAdRevMobBridge.activity, revmobFullscreenListener);
		}
	}

	public static void showBannerAd(){
		Log.v(TAG, "showBannerAd");
		
		if(PTAdRevMobBridge.remob != null){
			PTAdRevMobBridge.s_activity.get().runOnUiThread( new Runnable() {
				public void run() {
					PTAdRevMobBridge.banner = PTAdRevMobBridge.remob.createBanner( PTAdRevMobBridge.activity, revmobBannerListener );
					if(PTAdRevMobBridge.view != null){
						PTAdRevMobBridge.view.addView( PTAdRevMobBridge.banner, PTAdRevMobBridge.adViewParams );
					}
				}
			});			
		}


	}

	public static void hideBannerAd(){
		Log.v(TAG, "hideBannerAd");
		if(PTAdRevMobBridge.view != null){
			if(PTAdRevMobBridge.view.getChildCount() > 0){
				PTAdRevMobBridge.s_activity.get().runOnUiThread( new Runnable() {
					public void run() {
						PTAdRevMobBridge.view.removeAllViews();
						//RevMobXBridge.banner.hide();
					}
				});
			}
		}
	}

}
