
package com.secrethq.utils;

import com.audronis.ramblinrover.R;
import java.lang.ref.WeakReference;
import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.EnumSet;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.amazon.ags.api.AGResponseCallback;
import com.amazon.ags.api.AGResponseHandle;
import com.amazon.ags.api.AmazonGamesCallback;
import com.amazon.ags.api.AmazonGamesClient;
import com.amazon.ags.api.AmazonGamesFeature;
import com.amazon.ags.api.AmazonGamesStatus;
import com.amazon.ags.api.leaderboards.LeaderboardsClient;
import com.amazon.ags.api.leaderboards.SubmitScoreResponse;

import android.content.*;

import android.app.Activity;
import android.app.AlertDialog;
import android.net.Uri;

import android.util.Log;

import android.app.UiModeManager;
import android.content.res.Configuration;

public class PTServicesBridge {
	private static PTServicesBridge sInstance;
	private static final String TAG = "PTServicesBridge";

	private static native String getLeaderboardId();
	private static native void warningMessageClicked(boolean accepted);
	
	private static Cocos2dxActivity activity;
	private static WeakReference<Cocos2dxActivity> s_activity;


	private static String urlString;
	private static int scoreValue;

    private static final int RC_SIGN_IN = 9001;	
	private static final int REQUEST_LEADERBOARD = 5000;
	
	public static PTServicesBridge instance() {
		if (sInstance == null)
			sInstance = new PTServicesBridge();
		return sInstance;
	}

	public static void initBridge(Cocos2dxActivity activity, String appId){
		Log.v(TAG, "PTServicesBridge  -- INIT");

		PTServicesBridge.s_activity = new WeakReference<Cocos2dxActivity>(activity);
		PTServicesBridge.activity = activity;

		if(appId == null || appId.length() == 0){
			return;
		}

	}
	
	//reference to the agsClient
	static AmazonGamesClient agsClient;
		 
	static AmazonGamesCallback callback = new AmazonGamesCallback() {
		@Override
		public void onServiceNotReady(AmazonGamesStatus status) {
		    //unable to use service
			Log.e("PTPlayer", "AmazonGames ERROR onServiceNotReady");
		}
		@Override
		public void onServiceReady(AmazonGamesClient amazonGamesClient) {
			agsClient = amazonGamesClient;
		    //ready to use GameCircle
		    Log.d("PTPlayer", "AmazonGames OK onServiceReady");
		}
	};
		
	//leaderboards only
	static EnumSet<AmazonGamesFeature> myGameFeatures = EnumSet.of(
			AmazonGamesFeature.Leaderboards);
	
	public static void onResume( Activity act){
		AmazonGamesClient.initialize(act, callback, myGameFeatures);
	}
	
	public static void onPause( Activity act){
		if (agsClient != null) {
	        agsClient.release();
	    }
	}
	
     public static void openShareWidget( String message ){
            Log.v(TAG, "PTServicesBridge  -- openShareWidget with text:" + message);
            Intent sharingIntent = new Intent(android.content.Intent.ACTION_SEND);
            sharingIntent.setType("text/plain");
            sharingIntent.putExtra(android.content.Intent.EXTRA_TEXT, message);
            PTServicesBridge.activity.startActivity(Intent.createChooser(sharingIntent, "Share" ));
	}
	

	public static void showFacebookPage( final String facebookURL, final String facebookID){
		Log.v(TAG, "Show facebook page for URL: " + facebookURL + " ID: " + facebookID);
		
		PTServicesBridge.s_activity.get().runOnUiThread( new Runnable() {
			public void run() {
				try {
	            	Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse("fb://page/" + facebookID));
	            	PTServicesBridge.activity.startActivity(intent);
	        	} catch(Exception e) {
	        		PTServicesBridge.activity.startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse( facebookURL )));
		        }
			}
		});
	}

	public static void showWarningMessage(final String message){
		Log.v(TAG, "Show warning with message: " + message);
		PTServicesBridge.s_activity.get().runOnUiThread( new Runnable() {
			public void run() {
				AlertDialog.Builder dlgAlert  = new AlertDialog.Builder( PTServicesBridge.activity );

				dlgAlert.setMessage(message);
				dlgAlert.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
			        public void onClick(DialogInterface dialog, int which) {
			            PTServicesBridge.warningMessageClicked( false );
			          }
			      });
				dlgAlert.setPositiveButton("OK", new DialogInterface.OnClickListener() {
			        public void onClick(DialogInterface dialog, int which) {
			        	PTServicesBridge.warningMessageClicked( true ); 
			          }
			      });
				dlgAlert.setCancelable(true);
				dlgAlert.create().show();
			}
		});
		
	}
	
	public static void openUrl( String url ){
		Log.v(TAG, "PTServicesBridge  -- Open URL " + url);

		PTServicesBridge.urlString = url;

		PTServicesBridge.s_activity.get().runOnUiThread( new Runnable() {
			public void run() {
				final Intent intent = new Intent(Intent.ACTION_VIEW).setData(Uri.parse(PTServicesBridge.urlString));
				PTServicesBridge.activity.startActivity(intent);
			}
		});
	}

	public static void showCustomFullScreenAd() {
		Log.e(TAG, "PTServicesBridge  -- showCustomFullScreenAd");
	}

	public static void loadingDidComplete() {
		Log.e(TAG, "PTServicesBridge  -- loadingDidComplete");
	}
	  
	public static void showLeaderboard( ){
		Log.v(TAG, "PTServicesBridge  -- Show Leaderboard ");
		if (agsClient == null) {
			Log.e(TAG, "PTServicesBridge  -- Amazon Games Client NOT READY ");
		}
		try {
			LeaderboardsClient lbClient = agsClient.getLeaderboardsClient();
			lbClient.showLeaderboardsOverlay();   
		} catch (Exception e) {
			 Log.e(TAG, "PTServicesBridge  -- Show Leaderboard FAILED ");
		}
	}

	public static void submitScrore( int score ){
		Log.v(TAG, "PTServicesBridge  -- Submit Score " + score);

		if (agsClient == null) {
			Log.e(TAG, "PTServicesBridge  -- Amazon Games Client NOT READY ");
		}
		try {
			
			// Replace YOUR_LEADERBOARD_ID with an actual leaderboard ID from your game.
			LeaderboardsClient lbClient = agsClient.getLeaderboardsClient();
			
			String leaderboardID = PTServicesBridge.activity.getString(R.string.leaderboard_id);
			AGResponseHandle<SubmitScoreResponse> handle = lbClient.submitScore(leaderboardID, score);
			 
			// Optional callback to receive notification of success/failure.
			handle.setCallback(new AGResponseCallback<SubmitScoreResponse>() {
			    @Override
			    public void onComplete(SubmitScoreResponse result) {
			        if (result.isError()) {
			            // Add optional error handling here.  Not strictly required
			            // since retries and on-device request caching are automatic.
			        } else {
			            // Continue game flow.
			        }
			    }
			});
		} catch (Exception e) {
			Log.e(TAG, "PTServicesBridge  -- Submit Score FAILED");
		}
	}
	
	public static boolean isRunningOnTV(){
		UiModeManager uiModeManager = (UiModeManager)PTServicesBridge.activity.getSystemService( Context.UI_MODE_SERVICE );
		if (uiModeManager.getCurrentModeType() == Configuration.UI_MODE_TYPE_TELEVISION) {
			Log.d("DeviceTypeRuntimeCheck", "Running on a TV Device");
			return true;
		    
		} else {
			Log.d("DeviceTypeRuntimeCheck", "Running on a non-TV Device");
			return false;
		    
		}
	}

	public static void loginGameServices( ){
		Log.v(TAG, "PTServicesBridge  -- Login Game Services ");

	}

	public static boolean isGameServiceAvialable( ){
		Log.v(TAG, "PTServicesBridge  -- Is Game Service Avialable ");

		return false;
	}



	public void  onActivityResult(int requestCode, int responseCode, Intent intent){

	}

	public static String sha1( byte[] data, int length) throws NoSuchAlgorithmException, UnsupportedEncodingException {
		MessageDigest md = MessageDigest.getInstance("SHA-1");
        md.update(data, 0, length);
        byte[] sha1hash = md.digest();
        return convertToHex(sha1hash);
	}
		
    private static String convertToHex(byte[] data) {
        StringBuilder buf = new StringBuilder();
        for (byte b : data) {
            int halfbyte = (b >>> 4) & 0x0F;
            int two_halfs = 0;
            do {
                buf.append((0 <= halfbyte) && (halfbyte <= 9) ? (char) ('0' + halfbyte) : (char) ('a' + (halfbyte - 10)));
                halfbyte = b & 0x0F;
            } while (two_halfs++ < 1);
        }
        return buf.toString();
    }
}
