package com.secrethq.store;

import java.util.HashSet;
import java.util.Set;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.secrethq.store.util.*;
import com.secrethq.utils.PTServicesBridge;

import com.amazon.device.iap.PurchasingService;
import com.amazon.device.iap.model.RequestId;


public class PTStoreBridge {
	private static boolean readyToPurchase;
	
	private static final String TAG = "PTStoreBridge";
	
    private static native String licenseKey();
    public static native void purchaseDidComplete( String productId );
    public static native void purchaseDidCompleteRestoring(String productId);
    public static native boolean isProductConsumible( String productId );

    private static SampleIapManager sampleIapManager;

    /**
     * Call {@link PurchasingService#getProductData(Set)} to get the product
     * availability
     */
    protected void onStart() {

//        Log.d(TAG, "onStart: call getProductData " );
//
//        final Set<String> productSkus = new HashSet<String>();
//        productSkus.add( "com.amazon.example.iap.consumable" );
//        productSkus.add( "com.amazon.example.iap.entitlement" );
//        productSkus.add( "com.amazon.example.iap.subscription" );
//
//        PurchasingService.getProductData(productSkus);
    }

    /**
     * Calls {@link PurchasingService#getUserData()} to get current Amazon
     * user's data and {@link PurchasingService#getPurchaseUpdates(boolean)} to
     * get recent purchase updates
     */
    protected void onResume() {

//        Log.d(TAG, "onResume: call getUserData");
//        PurchasingService.getUserData();

//        Log.d(TAG, "onResume: getPurchaseUpdates");
//        PurchasingService.getPurchaseUpdates(false);
    }
    
	static public void initBridge(Cocos2dxActivity activity){
        sampleIapManager = new SampleIapManager(activity);

        final SamplePurchasingListener purchasingListener = new SamplePurchasingListener(sampleIapManager);

        Log.d(TAG, "onCreate: registering PurchasingListener");
        PurchasingService.registerListener(activity.getApplicationContext(), purchasingListener);

        Log.d(TAG, "IS_SANDBOX_MODE:" + PurchasingService.IS_SANDBOX_MODE);
        
        Log.d(TAG, "onResume: call getUserData");
        PurchasingService.getUserData();

        Log.d(TAG, "onResume: getPurchaseUpdates");
        PurchasingService.getPurchaseUpdates(false);  
        
        Log.d(TAG, "onStart: call getProductData " );

        final Set<String> productSkus = new HashSet<String>();
        productSkus.add( "com.amazon.example.iap.consumable" );
        productSkus.add( "com.amazon.example.iap.entitlement" );
        productSkus.add( "com.amazon.example.iap.subscription" );

        PurchasingService.getProductData(productSkus);
	}
	
	static public void purchase( String storeId ){
        final RequestId requestId = PurchasingService.purchase( storeId );
        Log.d(TAG, "onBuyOrangeClick: requestId (" + requestId + ")");
	}
	
	static public void consumePurchase( String storeId ){
        try {
            sampleIapManager.consumePurchase( storeId );
            Log.d(TAG, "consuming Purchase");

        } catch (final RuntimeException e) {
        	sampleIapManager.showMessage("Unknow error when eat Orange");
        }
	}
}
