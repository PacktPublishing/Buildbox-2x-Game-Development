#ifndef PTPINPUTCONTROLLER_H
#define PTPINPUTCONTROLLER_H

#include <cocos2d.h>

#include "attributes/PTPAttributeAction.h"

class b2RevoluteJoint;
class PTModelLinker;
class PTPObjectAsset;
class PTPObjectButton;
class PTPObjectAssetCharacter;
class PTPScreen;
class PTModelComponentHealth;

enum PTPInputControllerAction {
    PTPInputControllerActionUnknown = 0,
    PTPInputControllerActionMoveUp = 1,
    PTPInputControllerActionMoveDown = 2,
    PTPInputControllerActionMoveRight = 3,
    PTPInputControllerActionMoveLeft = 4,
    PTPInputControllerActionJump = 5,
    PTPInputControllerActionRotateLeft = 6,
    PTPInputControllerActionRotateRight = 7,
    PTPInputControllerActionShoot = 8,
    PTPInputControllerActionMotorCW = 9,
    PTPInputControllerActionMotorCCW = 10,
    PTPInputControllerActionButtonPressed = 11,
    PTPInputControllerActionButtonReleased = 12,
    PTPInputControllerActionSwipeLeft,
    PTPInputControllerActionSwipeRight,
    PTPInputControllerActionSwipeTop,
    PTPInputControllerActionSwipeBottom
};

enum PTPInputControllerKey {
    PTPInputControllerKeyUnknown,
    PTPInputControllerKeyLeft,
    PTPInputControllerKeyRight,
    PTPInputControllerKeyUp,
    PTPInputControllerKeyDown,
    PTPInputControllerKeyShoot,
    PTPInputControllerKeyJump,
    PTPInputControllerKeyMotorCW,
    PTPInputControllerKeyMotorCCW,
    PTPInputControllerKeyRotateLeft,
    PTPInputControllerKeyRotateRight,

    PTPInputControllerKeySelectEnter,
    PTPInputControllerKeySelectUp,
    PTPInputControllerKeySelectDown,
    PTPInputControllerKeySelectLeft,
    PTPInputControllerKeySelectRight,
};

struct PTJointMotorStruct{
    b2RevoluteJoint* joint;
    PTModelLinker* linker;
};

class PTPInputController: public CCObject, public CCKeypadDelegate{

public:
    PTPInputController();
    ~PTPInputController();
    static PTPInputController* shared();
    static void destroy();

    void clear();

    ////////////////////////////////////
    virtual void keyBackClicked();
    virtual void onKeyDown( int keyCode );
    virtual void onKeyUp( int keyCode );
    //////////////

    void keyPressed( PTPInputControllerKey key);
    void keyReleased( PTPInputControllerKey key);

    void touchesBegan(CCSet *touches);
    void touchesMoved(CCSet *touches);
    void touchesEnded(CCSet *touches);

    void applyMoveVectorOnCharacters(CCPoint vector);

    void gamepadAxisMoved( int value, int axis );
    void gamepadButtonPressed( int button );
    void gamepadButtonReleased( int button );

    void buttonJumpPressed(CCObject* sender = NULL) { actionBegin( PTPInputControllerActionJump ); }
    void buttonJumpReleased(CCObject* sender = NULL){ actionEnd( PTPInputControllerActionJump ); }
    void buttonShootPressed(CCObject* sender = NULL) { actionBegin( PTPInputControllerActionShoot ); }
    void buttonShootReleased(CCObject* sender = NULL){ actionEnd( PTPInputControllerActionShoot ); }
    void buttonRotateLeftPressed(CCObject* sender = NULL){ actionBegin( PTPInputControllerActionRotateLeft ); }
    void buttonRotateLeftReleased(CCObject* sender = NULL){ actionEnd( PTPInputControllerActionRotateLeft ); }
    void buttonRotateRightPressed(CCObject* sender = NULL){ actionBegin( PTPInputControllerActionRotateRight );}
    void buttonRotateRightReleased(CCObject* sender = NULL){ actionEnd( PTPInputControllerActionRotateRight ); }

    void buttonMoveRightPressed(CCObject* sender = NULL){ actionBegin( PTPInputControllerActionMoveRight );}
    void buttonMoveRightReleased(CCObject* sender = NULL){ actionEnd( PTPInputControllerActionMoveRight ); }
    void buttonMoveLeftPressed(CCObject* sender = NULL){ actionBegin( PTPInputControllerActionMoveLeft );}
    void buttonMoveLeftReleased(CCObject* sender = NULL){ actionEnd( PTPInputControllerActionMoveLeft ); }
    void buttonMoveUpPressed(CCObject* sender = NULL){ actionBegin( PTPInputControllerActionMoveUp );}
    void buttonMoveUpReleased(CCObject* sender = NULL){ actionEnd( PTPInputControllerActionMoveUp ); }
    void buttonMoveDownPressed(CCObject* sender = NULL){ actionBegin( PTPInputControllerActionMoveDown );}
    void buttonMoveDownReleased(CCObject* sender = NULL){ actionEnd( PTPInputControllerActionMoveDown ); }

    void buttonMotorCWPressed(CCObject* sender = NULL){ actionBegin( PTPInputControllerActionMotorCW ); }
    void buttonMotorCWReleased(CCObject* sender = NULL){ actionEnd( PTPInputControllerActionMotorCW); }
    void buttonMotorCCWPressed(CCObject* sender = NULL){ actionBegin( PTPInputControllerActionMotorCCW); }
    void buttonMotorCCWReleased(CCObject* sender = NULL){ actionEnd( PTPInputControllerActionMotorCCW); }

    void buttonActionPressed(CCObject* sender = NULL){ actionBegin( PTPInputControllerActionButtonPressed, sender); }
    void buttonActionReleased(CCObject* sender = NULL){ actionEnd( PTPInputControllerActionButtonReleased, sender); }

    bool anyCharacterAlive() const;
    void killAllCharacters();
    void addCharacter(PTPObjectAssetCharacter* character);
    void removeCharacter(PTPObjectAssetCharacter* character);

    CCArray* characters();
    CCPoint charactersAveragePosition();
    CCPoint charactersAverageInitialPosition();
    CCPoint charactersAverageScale();
    CCRect charactersBoundingBox();

    PTModelComponentHealth* charactersHealthComponent() const; //Assuming all characters have the same health component

    void showCharacters();
    void hideCharacters();

    int characterZDepth();

    void moveCharactersDelta(float dx, float dy, bool force = true);
    void moveCharacters( float dx, float dy);
    void setCharactersPosition( CCPoint p);
    void addMotor(PTJointMotorStruct motor);
    void removeAllMotors();
    void removeAssociatedMotors(CCArray *objectsForDeletion);

    void addSpawner( PTPObjectAsset* object, PTPInputControllerAction action);
    void removeSpawner( PTPObjectAsset* object );
    void associateSpawnerWithCharacter(PTPObjectAsset* spawner, PTPObjectAsset* character);
    void removeAllSpawners();

    void addKeyBinding( int keyCode, PTPObjectButton *button);
    void removeKeyBinding( int keyCode, PTPObjectButton *button);
    bool handleKeyPressOnScreen( int keyCode, PTPScreen *screenLayer );
    bool handleKeyReleaseOnScreen( int keyCode, PTPScreen *screenLayer );

    void actionSubscribe(PTPInputControllerAction actionId, CCObject *target, PTPActionPointerSender selector, unsigned int senderId = 0);
    void actionUnSubscribe( CCObject* target);

    void broadcastAction(PTPInputControllerAction actionId, unsigned int senderId);


private:
    void actionBegin(PTPInputControllerAction actionId, CCObject* sender = NULL);
    void actionEnd(PTPInputControllerAction actionId, CCObject* sender = NULL);

    CCPoint getActionsResultVector();
    float getActionsResultMotorSpeed(PTJointMotorStruct motor);

    CCArray* _characters;
    typedef std::list<PTPInputControllerAction> PTPInputControllerActionList;
    PTPInputControllerActionList _appliedActions;

    typedef std::list<PTJointMotorStruct> PTJointMotorStructList;
    PTJointMotorStructList _motors;
    typedef std::list<PTPObjectAsset*> PTPObjectAssetList;
    std::map<PTPInputControllerAction, PTPObjectAssetList> _spawnerObjects;

    typedef std::list<PTActionSubscriberStruct> PTActionSubscribersList;
    typedef std::map<PTPInputControllerAction, PTActionSubscribersList> PTActionSubscriptionMap;
    PTActionSubscriptionMap _actionSubscriptions;

    bool _zeroCharacterMode;
    
    CCPoint _characterAveragePosition;

};

#endif // PTPINPUTCONTROLLER_H
