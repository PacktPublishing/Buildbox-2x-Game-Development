package com.secrethq.store.util;

import java.util.Map;
import java.util.Set;

import android.app.Activity;
import android.util.Log;

import android.widget.Toast;

import com.secrethq.store.PTStoreBridge;

import com.amazon.device.iap.PurchasingListener;
import com.amazon.device.iap.PurchasingService;
import com.amazon.device.iap.model.FulfillmentResult;
import com.amazon.device.iap.model.Product;
import com.amazon.device.iap.model.Receipt;
import com.amazon.device.iap.model.UserData;

/**
 * This is a sample of how an application may handle InAppPurchasing. The major
 * functions includes
 * <ul>
 * <li>Simple user and purchase history management</li>
 * <li>Grant Orange purchases</li>
 * <li>Enable/disable purchases from GUI</li>
 * <li>Save persistent order data into SQLite Database and SharedPreference</li>
 * </ul>
 * 
 * 
 */
public class SampleIapManager {
	public static enum PurchaseStatus {
        PAID, FULFILLED, UNAVAILABLE, UNKNOWN
    }

    private static final String TAG = "SampleIAPManager";

    final private Activity mainActivity;
    private UserIapData userIapData;

    public SampleIapManager(final Activity mainActivity) {
        this.mainActivity = mainActivity;
    }

    /**
     * Method to set the app's amazon user id and marketplace from IAP SDK
     * responses.
     * 
     * @param newAmazonUserId
     * @param newAmazonMarketplace
     */
    public void setAmazonUserId(final String newAmazonUserId, final String newAmazonMarketplace) {
        // Reload everything if the Amazon user has changed.
        if (newAmazonUserId == null) {
            // A null user id typically means there is no registered Amazon
            // account.
            if (userIapData != null) {
                userIapData = null;
            }
        } else if (userIapData == null || !newAmazonUserId.equals(userIapData.getAmazonUserId())) {
            // If there was no existing Amazon user then either no customer was
            // previously registered or the application has just started.

            // If the user id does not match then another Amazon user has
            // registered.
            userIapData = reloadUserData(newAmazonUserId, newAmazonMarketplace);
        }
    }

    /**
     * This method contains the business logic to fulfill the customer's
     * purchase based on the receipt received from InAppPurchase SDK's
     * {@link PurchasingListener#onPurchaseResponse} or
     * {@link PurchasingListener#onPurchaseUpdates} method.
     * 
     * 
     * @param receipt
     * @param userData
     */
    public void handleConsumablePurchase(final Receipt receipt, final UserData userData) {
        try {
            if (receipt.isCanceled()) {
                revokeConsumablePurchase(receipt, userData);
            } else {
                if (receiptAlreadyFulfilled(receipt.getReceiptId(), userData)) {
                    // if the receipt was fulfilled before, just notify Amazon
                    // Appstore it's Fulfilled again.
                    PurchasingService.notifyFulfillment(receipt.getReceiptId(), FulfillmentResult.FULFILLED);
                    return;
                }

                grantConsumablePurchase(receipt, userData);
            }
            return;
        } catch (final Throwable e) {
            showMessage("Purchase cannot be completed, please retry");
        }
    }

    /**
     * Method to handle Entitlement Purchase
     *
     * @param receipt
     * @param userData
     */
    private void handleEntitlementPurchase(final Receipt receipt, final UserData userData) {
        try {
            if (receipt.isCanceled()) {
                // Check whether this receipt is to revoke a entitlement
                // purchase
                revokeEntitlement(receipt, userData.getUserId());
            } else {

                grantEntitlementPurchase(receipt, userData);
            }
            return;
        } catch (final Throwable e) {
            showMessage("Purchase cannot be completed, please retry");
        }

    }

    /**
     * Method to handle the receipt
     * 
     * @param receipt
     * @param userData
     */
    public void handleReceipt(final Receipt receipt, final UserData userData) {
        switch (receipt.getProductType()) {
        case CONSUMABLE:
            // try to do your application logic to fulfill the customer purchase
            handleConsumablePurchase(receipt, userData);
            break;
        case ENTITLED:
            // check entitled sample app to know how to handle entitled
            // purchases
            handleEntitlementPurchase(receipt, userData);
            break;
        case SUBSCRIPTION:
            // check subscription sample app to know how to handle subscription
            // purchases
            break;
        }

    }

    /**
     * Show purchase failed message for specified sku
     * 
     * @param sku
     */
    public void purchaseFailed(final String sku) {
        showMessage("Purchase failed!");
    }

    /**
     * App logic for handle "eat orange" operation
     * 
     * @return
     */
    public boolean consumePurchase( String storeId ) {
        if (userIapData == null) {
            showMessage("user not logged in to amazon marketplace!");
        }

        // following sample code is a simple implementation, please
        // implement your own granting logic thread-safe, transactional and
        // robust

        // TODO logic to increase consumed and decrease remaining

        return true;
    }

    /**
     * returns the userIapData
     * 
     * @return
     */
    public UserIapData getUserIapData() {
        return this.userIapData;
    }

    /**
     * Private method to revoke a consumable purchase from the customer.
     * 
     * If your application supports "Revoke Consumable Purchases" feature,
     * please implement your application-specific logic to handle the revocation
     * of consumable purchase. i.e. try to revoke the items issued to customer
     * in last purchase. <br>
     * <b>Be careful with the revocation logic:</b>
     * <ul>
     * <li>For example: if you give 10 items as part of a consumable purchase,
     * and the customer has consumed 5 items, it might not be possible to fully
     * revoke items since customer does not have enough items in their account.</li>
     * <li>The cancelled receipt object can be returned by
     * getPurchaseUpdatesResponse multiple times. So, always check if the
     * receipt id was previously revoked before attempting to revoke.</li>
     * </ul>
     * 
     * 
     * @param receipt
     * @param userData
     */
    private void revokeConsumablePurchase(final Receipt receipt, final UserData userData) {
        // TODO: implement your application-specific logic to handle the
        // consumable purchase.

    }

    /**
     * Private method to revoke an entitlement purchase from the customer
     *
     * Please implement your application-specific logic to handle the revocation
     * of an entitlement purchase.
     *
     *
     * @param receipt
     * @param userId
     */
    private void revokeEntitlement(final Receipt receipt, final String userId) {
        String receiptId = receipt.getReceiptId();
        //final EntitlementRecord record;
        if (receiptId == null) {
            // The revoked receipt's receipt id may be null on older devices.
        //    record = dataSource.getLatestEntitlementRecordBySku(userId, receipt.getSku());
        //    receiptId = record.getReceiptId();
        } else {
        //    record = dataSource.getEntitlementRecordByReceiptId(receiptId);
        }
        //if (record == null) {
            // No purchase record for the entitlement before, do nothing.
        //    return;
        //}
        //if (record.getCancelDate() == EntitlementRecord.DATE_NOT_SET || record.getCancelDate() > System
        //        .currentTimeMillis()) {
        //    final long cancelDate = receipt.getCancelDate() != null ? receipt.getCancelDate().getTime() : System
        //        .currentTimeMillis();
        //    dataSource.cancelEntitlement(receiptId, cancelDate);
        //} else {
            // Already canceled, do nothing
        //    return;
        //}

    }

    /**
     * Load the user data from SharedPreference.
     * 
     * @param amazonUserId
     * @param amazonMarketplace
     * @return
     */
    private UserIapData reloadUserData(final String amazonUserId, final String amazonMarketplace) {
        // TODO Load User Iap Data
        // userIapData.getAmazonUserId()

        final UserIapData userIapData = new UserIapData(amazonUserId, amazonMarketplace);
        return userIapData;
    }

    /**
     * This method contains the business logic to fulfill the customer's
     * purchase, based on the receipt received from InAppPurchase SDK's
     * {@link PurchasingListener#onPurchaseResponse} or
     * {@link PurchasingListener#onPurchaseUpdates} method.
     * 
     * 
     * @param receiptId
     * @param userData
     */
    private void grantConsumablePurchase(final Receipt receipt, final UserData userData) {
        try {
            // following sample code is a simple implementation, please
            // implement your own granting logic thread-safe, transactional and
            // robust

            // create the purchase information in your app/your server,
            // And grant the purchase to customer - give one orange to customer
            // in this case
//            createPurchase(receipt.getReceiptId(), userData.getUserId());

            if (updatePurchaseStatus(receipt.getReceiptId(), PurchaseStatus.PAID, PurchaseStatus.FULFILLED)) {
                Log.i(TAG, "Successfuly update purchase from PAID->FULFILLED for receipt id " + receipt.getReceiptId());
                // update the status to Amazon Appstore. Once receive Fulfilled
                // status for the purchase, Amazon will not try to send the
                // purchase receipt to application any more
                PurchasingService.notifyFulfillment(receipt.getReceiptId(), FulfillmentResult.FULFILLED);

                PTStoreBridge.purchaseDidComplete( receipt.getSku() );
            } else {
                // Update purchase status in SQLite database failed - Status
                // already changed.
                // Usually means the same receipt was updated by another
                // onPurchaseResponse or onPurchaseUpdatesResponse callback.
                // simply swallow the error and log it in this sample code
                Log.w(TAG, "Failed to update purchase from PAID->FULFILLED for receipt id " + receipt.getReceiptId()
                           + ", Status already changed.");
            }

        } catch (final Throwable e) {
            // If for any reason the app is not able to fulfill the purchase,
            // add your own error handling code here.
            // Amazon will try to send the consumable purchase receipt again
            // next time you call PurchasingService.getPurchaseUpdates api
            Log.e(TAG, "Failed to grant consumable purchase, with error " + e.getMessage());
        }

    }

    /**
     * This method contains the business logic to fulfill the customer's
     * purchase based on the receipt received from InAppPurchase SDK's
     * {@link PurchasingListener#onPurchaseResponse} or
     * {@link PurchasingListener#onPurchaseUpdates} method.
     *
     *
     * @param receiptId
     * @param userData
     */
    private void grantEntitlementPurchase(final Receipt receipt, final UserData userData) {
        try {
            // Actual entitlement granting logic: Save the entitlement purchase
            // record to database so it can be loaded by
            // refreshLevel2Availability() method later,
            // then notify Amazon Appstore.
            PurchasingService.notifyFulfillment(receipt.getReceiptId(), FulfillmentResult.FULFILLED);

            PTStoreBridge.purchaseDidComplete( receipt.getReceiptId() );
        } catch (final Throwable e) {
            // If for any reason the app is not able to fulfill the purchase,
            // add your own error handling code here.
            Log.e(TAG, "Failed to grant entitlement purchase, with error " + e.getMessage());
        }
    }


    /**
     * We strongly recommend verifying the receipt on your own server side
     * first. The server side verification ideally should include checking with
     * Amazon RVS (Receipt Verification Service) to verify the receipt details.
     * 
     * @see <a href=
     *      "https://developer.amazon.com/appsandservices/apis/earn/in-app-purchasing/docs/rvs"
     *      >Appstore's Receipt Verification Service</a>
     * 
     * @param receiptId
     * @return
     */
    private boolean verifyReceiptFromYourService(final String receiptId, final UserData userData) {
        // TODO Add your own server side accessing and verification code
        return true;
    }

    /**
     * Developer should implement de-duplication logic based on the receiptId
     * received from Amazon Appstore. The receiptId is a unique identifier for
     * every purchase, but the same purchase receipt can be pushed to your app
     * multiple times in the event of connectivity issue while calling
     * notifyFulfillment. So if the given receiptId was tracked and fulfilled by
     * the app before, you should not grant the purchase content to the customer
     * again, otherwise you are giving the item for free.
     * 
     * 
     * @param receiptId
     * @param userData
     * @return
     */
    private boolean receiptAlreadyFulfilled(final String receiptId, final UserData userData) {
        // TODO Following is a simple de-duplication logic implementation using
        // local SQLite database. We strongly recommend that you save purchase
        // information and implement the de-duplication logic on your server
        // side.

        return false;
    }

    /**
     * This sample app includes a simple SQLite implementation for save purchase
     * detail locally.
     * 
     * We strongly recommend that you save purchase information on a server.
     * 
     * @param receiptId
     *            receipt to update
     * @param fromStatus
     *            the current purchase status
     * @param toStatus
     *            the new purchase status
     */
    private boolean updatePurchaseStatus(final String receiptId,
            final PurchaseStatus fromStatus,
            final PurchaseStatus toStatus) {
        // TODO replace with your own implementation

        return true;
    }

    /**
     * Sample logic to create the purchase record.
     * 
     * Create and save the purchase information from app's local SQLite database
     * 
     * @param receiptId
     *            the purchase's receipt id
     * @param userId
     *            the user id for the purchase
     */
    private void createPurchase(final String receiptId, final String userId) {
        // TODO Add your own logic to save those purchase information either in
        // your own server side or in app's local data

    }

    /**
     * Show message on UI
     *
     * @param message
     */
    public void showMessage(final String message) {
        Toast.makeText(mainActivity, message, Toast.LENGTH_LONG).show();
    }

}
