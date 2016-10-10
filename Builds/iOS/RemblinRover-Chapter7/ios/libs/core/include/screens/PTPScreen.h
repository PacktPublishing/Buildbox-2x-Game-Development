#ifndef PTPSCREEN_H
#define PTPSCREEN_H

#include <cocos2d.h>

#include "attributes/PTPAttribute.h"

#define kRootLayerItemTag 0
#define kRootCCMenuItemTag 100

class PTModelScreen;
class PTPScreenScene;
class PTModelObjectButton;
class PTModelAssetPowerup;
class PTSoundController;
class PTModelObjectLabel;
class PTPObjectButton;
class PTModelObject;

class PTPScreen : public CCLayer
{
public:
	PTPScreen();
    ~PTPScreen();
    virtual bool init();
    static cocos2d::CCScene* scene();
    static PTPScreen *getRunningScreen();

    CREATE_FUNC( PTPScreen );

    bool load(const char* key);
    PTPObjectButton* getButton( const char* key );
    std::vector<PTPObjectButton*> getButtons(const std::string &key) const { return getButtons(key.c_str()); }
    std::vector<PTPObjectButton*> getButtons(const CCString &key) const { return getButtons(key.getCString()); }
    std::vector<PTPObjectButton*> getButtons(const char *key) const;
    PTModelObjectLabel* getLabel( const char* key);

    void update(float dt);

    virtual void onKeyUp( int keyCode );

    virtual void stopBackgroundMusic();
    virtual void playBackgroundMusic();

    virtual void visit();

    virtual void reset();
    virtual void removeAds();

    virtual void pressHilightedButton();
    virtual void hilightButton(int direction);
    virtual void hilightDefaultButton();


    virtual void deleteObject(PTModelObject *model);
    void hideAds();
    virtual void showAds();

    virtual bool isBannerWillShow();
    bool isBannerWillShow(const char* screenModelName);
    bool isInterstitialWillShow();
    bool isInterstitialWillShow(const char* screenModelName);

    virtual PTPScreenScene *parentScreenScene();
    virtual void onBackToParentScreen();
    virtual void defaultBackActionHandler();

    virtual void onEnter();

    virtual void removeFromParent();

    void setUiLayerVisible( bool );
    void setChildrenButtonsEnabled( bool );

    void ignoreNextInterstitial();

    virtual void activatePowerup( PTModelAssetPowerup* powerup, bool aboveCharacter = true);

    void addChildScreen(PTPScreen *);
    PTPScreen *getChildScreen();
    static PTPScreen *getTopScreen();

    PTModelScreen* model();

    CCString getGameOverSwitchName();

    void powerupButtonAction(CCObject* sender);
    void purchaseButtonAction(CCObject* sender);

protected:
    PTModelScreen* _model;

    void assignActionToButtons(const char* buttonId, CCObject* target, SEL_MenuHandler selector);
    void assignActionsToButtons(const char* buttonId, CCObject* target, SEL_MenuHandler selectedSelector, SEL_MenuHandler unselectedSelector);

    virtual void buttonAction(CCObject* pSender);
    virtual void onButtonPressed(PTModelObjectButton *button);
    void callScheduledButton(float);

    void restorePurchasesButtonAction(CCObject* pSender);
    virtual void gameServicesButtonAction(CCObject* pSender);

    virtual PTModelScreen *getModelForKey(const char *key);

    void hideUiChildren();

    std::map<PTModelObject*, CCNode*> _objectMap;

    CCNode *_uiNode;
    float _uiNodeUnhideTimeOut;
    float _uiNodeScheduleForUnhide;

    void switchToScene( CCScene* );

    bool _ignoreNextInterstitialShow;

    void setAnimationState( PTPAnimationState state );

    CCString _gameOverSwitchName;

private:
    PTSoundController *_soundController;

    CCLabelBMFont *_distanceSessionLabel;
    CCLabelBMFont *_distanceBestLabel;

    CCLabelBMFont *_coinsSessionLabel;
    CCLabelBMFont *_coinsTotalLabel;

    PTModelObjectButton *_scheduledButton;

    PTPAnimationState _animationState;
    float _currentTime;
};

#endif // PTPSCREEN_H
