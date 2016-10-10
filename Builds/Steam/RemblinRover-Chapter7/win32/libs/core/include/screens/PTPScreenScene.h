#ifndef PTPSCREENSCENE_H
#define PTPSCREENSCENE_H

#include "PTPScreen.h"

#include <unordered_set>
#include <box2D/Box2D.h>

class PTPScreenUi;
class PTPInputController;
class PTPObjectAssetPowerup;
class PTPObjectAssetTeleport;
class PTPObjectAssetMirror;
class PTPGameFieldCamera;
class PTModelGeneralSettings;
class PTModelLevelSection;
class PTPObjectAsset;
class PTPObject;
class PTModelObject;
class PTPObjectGeneralSettings;

struct PTPScreenSceneAssetCreation {
    PTPObjectAsset* asset;
    float32 assetLinearDamping;
    b2Vec2 assetLinearVelocity;
    PTPObjectAsset *parent;
};

struct PTPScreenSceneCreationQueue {
    CCPoint position;
    CCArray *objects;
    int index;
    PTModelLevelSection *model;
    CCArray* createdObjects;
};

class PTPScreenScene : public PTPScreen
{
public:
    PTPScreenScene();
    ~PTPScreenScene();

    static cocos2d::CCScene* scene();

    CREATE_FUNC( PTPScreenScene );

    virtual bool init();
    virtual void update(float dt);
    virtual void updateCameraObjects( float dt );

    virtual void visit();

    void cameraShake( float cameraShake );
    void cameraFlash( float cameraFlash );

    void loadBackgroundObjects();

    virtual bool isBannerWillShow();

    virtual void pressHilightedButton();
    virtual void hilightButton(int direction);

    void addAsset( PTPObjectAsset *asset, CCNode *sender );
    CCArray *getAssetsList();

    bool updateObjectCreationQueue();

    PTPGameFieldCamera* camera();

    void deleteAsset(PTModelObject* assetModel);

    virtual void onBackFromChildScreen();

    void resetGameplay();
    void setDebugMode(bool enable);

    PTPInputController* inputController();

    void submitScoreAndUpdateBestScores();

    virtual void activatePowerup( PTModelAssetPowerup* powerup, bool aboveCharacter = true);
    PTPObjectAssetPowerup* activePowerup( CCString type,  PTPObject *sender);
    std::list<PTPObjectAssetPowerup*> powerupList(CCString type);

    void setPowerupMagnetMode( bool enabled );
    void setPowerupKillAllEnemy();
    void setPowerupCheckPoint( CCPoint point, int levelSectionId );
    void setPowerupNextCheckPoint();

    void resetPowerups();

    void scheduleGameRestart();

    b2World* world();

    virtual void onEnter();
    virtual void onKeyDown( int keyCode );
    virtual void onKeyUp( int keyCode );
    virtual void keyBackClicked();
    virtual void setTouchEnabled( bool enabled );

    void setGameSpeedSlowDown( float factor );

    void setGameOverMode( bool gameOverMode );
    bool isGameOverMode();
    void setPauseMode( bool pauseMode );
    bool isPauseMode();

    void pauseButtonAction( CCObject *sender );
    void backButttonAction( CCObject *pSender );
    void restartButtonAction( CCObject *sender );
    void endGameAction();

    PTPScreenUi *currentUI() const;

    void scheduleCloneObject(PTPObjectAsset *asset, PTPObjectAsset *parent);

    std::list<PTPObjectAssetTeleport *> teleportList( float groupId );

    void switchToNewUI();
    void loadOriginalUi();

    void restart();

    void switchScene(const CCString &link, bool pause = false, bool restart = false, bool saveScores = false);

    void removeShaderEffect(PTPObject *effect);

protected:
    float addLevelSection(  PTModelLevelSection *model, float position ); // return width of added level section
    PTPObjectAsset* createAsset(PTModelObject* assetModel, int levelSectionModelId, CCPoint levelSectionPosition, bool characterVerification = true );
    PTPObjectAsset* createAsset(PTModelObject* assetModel, PTPObjectAsset *parent);

    virtual void onButtonPressed(PTModelObjectButton *button);

    virtual PTModelScreen *getModelForKey(const char *key);

    PTPGameFieldCamera *_camera;
    PTModelGeneralSettings* _generalSettings;
    PTPObjectGeneralSettings* _generalSettingsObject;
    b2World *_world;

    CCArray *_backgroundObjects;

private:
    void checkForDeletion(PTPObject *obj);
    void checkIsCharacterCreated( unsigned int modelId ); // we checking is character created durign scene inititalization if not we will grab his position from Start Scene
    PTModelLevelSection *getLevelSectionByDistance( float d );
    std::vector<std::size_t> levelSectionIndicesByDistance( float d, bool cooledDown); //return indices of level section that cooled down and not
    void levelSectionCooldownUpdate();
    void addStartLevelSection();

    void killAllEnemyOnObject( CCNode * );
    void resetPowerupsOnObject( CCNode * );

    void pauseAnimations();
    void resumeAnimations();

    void setNodeAnimationsState(CCNode *node, bool pause);

    PTPInputController* _inputController;

    CCArray *_levelSectionModels;
    float _levelSectionCurentLength;

    float _levelSectionLength;

    CCScene *_debugScene;
    PTPScreenUi *_uiScreen;

    bool _pauseMode;
    bool _gameOverMode;

    //powerups
    bool _powerupMagnetMode;
    bool _scheduleGameRestart;

    float _gameSpeedslowDownFactor;
    float _gameOverDelay;

    float _cameraShake;
    float _cameraFlash;
    float _cameraFlashDuration;
    CCSprite *_cameraFlashSprite;
    float _simulationTimeAccumulator;

    std::vector<PTPScreenSceneAssetCreation> _assetCreationList;
    std::vector<PTPScreenSceneCreationQueue> objectCreationList;

    std::vector<PTPObjectAssetMirror*> _shaderEffectList;

    std::unordered_set<std::string> _unpausedUiList;

    friend class PTPScreenUi;
};

#endif // PTPSCREENSCENE_H
