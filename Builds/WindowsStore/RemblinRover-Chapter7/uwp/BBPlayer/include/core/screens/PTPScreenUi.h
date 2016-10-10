#ifndef PTPSCREENUI_H
#define PTPSCREENUI_H

#include "PTPScreen.h"
class PTPObjectCharacterSelector;


class PTPScreenUi : public PTPScreen
{
public:
    enum SwitchAndPauseMode
    {
        SwitchAndPause,
        SwitchAndUnpause,
        SwitchAndKeep
    };

    PTPScreenUi();
    ~PTPScreenUi();

    static cocos2d::CCScene* scene( bool isLoading = false );

    CREATE_FUNC( PTPScreenUi );

    virtual bool init();
    virtual void update(float dt);

    virtual void draw();
    virtual void visit();

    void setIsLoadingScreen( bool );
    bool isLoadingScreen() const { return _isLoadingScreen; }

    void pauseButtonAction(CCObject* pSender);
    void restartButtonAction(CCObject* pSender);
    void restartCheckpointButtonAction(CCObject* pSender);
    void continueButtonAction(CCObject* pSender);
    void backButtonAction(CCObject* pSender);
    void backToButtonAction(CCObject* pSender);
    void resetButtonAction(CCObject* pSender);
    void resetWarningMessageClicked( bool yes );
    void reviewButtonAction(CCObject* pSender);
    void shareButtonAction(CCObject* pSender);
    void gameServicesButtonAction(CCObject* pSender);

    virtual void keyBackClicked();
    virtual void onKeyDown( int keyCode );
    virtual void onKeyUp( int keyCode );

    virtual void onBackFromChildScreen();

    void fullscreenAction(CCObject *pSender);
    void windowedAction(CCObject* pSender);

    void unlockChatracterButtonUpdate();

    void switchScreen(const CCString &link, unsigned levelId = 0, bool restart = false, SwitchAndPauseMode pauseMode = SwitchAndKeep, bool saveScores = false);

    void setButtonsEnabled(bool state);
    inline bool areButtonsEnabled() const { return _buttonsEnableState; }

protected:
    void setFullscreenMode( bool value );
    virtual void onButtonPressed(PTModelObjectButton *button);

private:
    PTPObjectCharacterSelector* getCharacetrSelectorObject();

    void initUnlockCharacterButton();
    void unlockCharacterAction( CCObject *sender);

    void registerButtonActions();

    bool _isLoadingScreen;
    int _drawCounter;
    bool _takingScreenshotMode;

    PTPObjectButton* _windowedButton;
    PTPObjectButton* _fullscreenButton;

    bool _buttonsEnableState;
};

#endif // PTPSCREENUI_H
