#ifndef PTMODELGENERALSETTINGS_H
#define PTMODELGENERALSETTINGS_H

#include "PTModel.h"

class PTPAttributeString;
class PTPAttributeSprite;
class PTPAttributeBoolean;
class PTPAttributeFloat;
class PTPAttributePoint;
class PTPAttributeEnum;
class PTPAttributeKey;

typedef enum {
    PTObjectFrameEdgeStatePass = 0,
    PTObjectFrameEdgeStateBlock,
    PTObjectFrameEdgeStateKill,
    PTObjectFrameEdgeStateCount

} PTObjectFrameEdgeState;

typedef enum {
    PTPScreenOrientationLandscape = 0,
    PTPScreenOrientationPortrait,
} PTPScreenOrientation;

typedef enum {
    PTPScreenAdjustmentDefault = 0,
    PTPScreenAdjustmentVertical = 1,
    PTPScreenAdjustmentHorizontal = 2,
} PTPScreenAdjustment;

static float kSimulationTimeScaleMultiplier = 50; // +
static float kFrictionMultiplier = 100; // +
static float kBounceForceMutliplier = 2.0; //+
static float kRestitutionMultiplier = 100; //+
static float kVeclocityScaleMultiplier = 100; //+
static float kUpForceMultiplier = 4.0; // +
static float kRotationScaleMultiplier = 100; //+
static float kRotationLeftRightMultiplier = 100; // +
static float kPlatformFrictionMultiplier = 40; //+
static float kCharacterFriction = 100; // +
static float kGameSpeedMultiplier = 25; // +
static float kMoveSpeedMultiplier = 3; // +

class PTModelGeneralSettings : public PTModel {
public:
    PTModelGeneralSettings();
    ~PTModelGeneralSettings();

    static PTModelGeneralSettings* shared();

    inline unsigned int lastIdNumber() const { return _lastIdNumber; }
    inline void setLastIdNumber(unsigned int id) { _lastIdNumber = id; }

    void setScreenAdjustment( PTPScreenAdjustment value);
    PTPScreenAdjustment screenAdjustment();

    void setOrientation( PTPScreenOrientation );
    PTPScreenOrientation orientation();

    void setGameplayAngleDirection(float);
    float gameplayAngleDirection();
    CCPoint gameplayDirection();

    float gameSpeedMin();
    void setGameSpeedMin( float );

    float gameSpeedMax();
    void setGameSpeedMax( float );

    float gameSpeedCurrent();
    void setGameSpeedCurrent( float );

    float gameSpeedIncrease();
    void setGameSpeedIncrease( float );

    float sidesDeletionThreshold();
    void setSidesDeletionThreshold( float );

    float backDeletionThreshold();
    void setBackDeletionThreshold( float );

    float extraDeletionThreshold();

    virtual void initWithDictionary( CCDictionary *dict );
    virtual cocos2d::CCDictionary *getDictionary();

    CCString versionNumber();
    void setVersionNumber(const CCString &);
    CCString applicationName();
    void setApplicationName(const CCString &);
    CCString comments();
    void setComments(const CCString &);
    CCString resetText();
    void setResetText(const CCString &);

    CCString buildDate() const;
    void setBuildDate(const CCString &date);

    // hot keys
    int moveUpKey();
    void setMoveUpKey(int);

    int moveDownKey();
    void setMoveDownKey(int);

    int moveLeftKey();
    void setMoveLeftKey(int);

    int moveRightKey();
    void setMoveRightKey(int);

    int motorCWKey();
    void setMotorCWKey(int);

    int motorCCWKey();
    void setMotorCCWKey(int);

    int rotateLeftKey();
    void setRotateLeftKey(int);

    int rotateRightKey();
    void setRotateRightKey(int);

    int shootKey();
    void setShootKey(int);

    int jumpKey();
    void setJumpKey(int);

    bool isKeyMapped( int );

    PTPAttributeSprite *iconAttribute;

    CCPoint moveSpeed() const;
    void setMoveSpeed(float x, float y);
    void setFixedRotation( bool fixedRotation );
    bool isFixedRotation() const;
    void setFixedPosition( bool fixedPosition );
    bool isFixedPosition() const;
    bool isForcedMovement() const;
    void setForcedMovement( bool value );
    CCPoint upForce() const;
    void setUpForce( CCPoint value);
    float upForceDuration() const;
    void setUpForceDuration(float value);
    float upForceCounter() const;
    void setUpForceCounter(float value);
    void setJumpGroundThreshold( float value );
    float jumpGroundThreshold();
    float leftLeanForce() const;
    void setLeftLeanForce(float value);
    float rightLeanForce() const;
    void setRightLeanForce(float value);
    float simulationTimeScale();
    void setSimulationTimeScale( float value);
    CCPoint characterFriction();
    void setCharacterFriction( CCPoint value);
    float friction();
    void setFriction( float value );
    float velocityScale();
    void setVelocityScale( float value  );

    void setRestitution( float );
    float restitution() const;

    void setScoreMultiplier( float );
    float scoreMultiplier() const;

    void setPlatformFriction( float );
    float platformFriction() const;

    bool autoImageDirection();
    void setAutoImageDirection( bool autoImageDirection );

    void setBounceForce( CCPoint value);
    CCPoint bounceForce();

    bool isUpForceFromGround();
    void setUpForceFromGround( bool upForceFromGround );

    float rotationScale();
    void setRotationScale( float rotationScale );

    void setGravity( CCPoint value);
    CCPoint gravity();

    void setObjectFrameRect( CCRect rect );
    CCRect objectFrameRect();

    PTObjectFrameEdgeState objectFrameEdgeState( int edgeIndex );
    void setObjectFrameEdgeState(int edgeIndex, PTObjectFrameEdgeState state);

    static PTModel * create() {
        return new PTModelGeneralSettings();
    }

    CCString scoreType;
    CCString shareScreen;

    PTPAttributeString *gamePresetName;
    CCString *ibVersion() const;
    void setIbVersion(CCString *ibVersion);

    void setDesignResolution( float width, float height );
    void setDesignResolution( CCSize );
    CCSize designResolution();

    bool isTrial();
    void setTrial( bool value );

    float gameOverDelay();

#ifdef __QT__
    static QStringList supportedPlatformsList();
#endif
    const char* platformValue(const std::string &platform, const std::string &key) const;
    void setPlatformValue(const std::string &platform, const std::string &key, const std::string &value);
    void removePlatformValue(const std::string &platform, const std::string &key);

    std::list<std::string> adBannersList(const std::string &platform) const;
    std::list<std::string> adInterstitialsList(const std::string &platform) const;

    void dumpAttributes();

private:
    unsigned int _lastIdNumber;

    CCString *_ibVersion;

    PTPScreenOrientation _orientation;
    PTPScreenAdjustment _screenAdjustment;
    PTPAttributeFloat *_gameplayAngleDirection;

    bool _trial;

    CCSize _designResolution;

    PTPAttributePoint *_gravityAttribute;
    PTPAttributePoint *_moveSpeedAttribute;
    PTPAttributePoint *_bounceForceAttribute;
    PTPAttributePoint *_upForceAttribute;
    PTPAttributeFloat *_upForceDurationAttribute;
    PTPAttributeFloat *_upForceCounterAttribute;
    PTPAttributeFloat *_jumpGroundThreshold;
    PTPAttributeFloat *_leftLeanForceAttribute;
    PTPAttributeFloat *_rightLeanForceAttribute;
    PTPAttributeFloat *_simulationTimeScaleAttribute;
    PTPAttributeFloat *_frictionAttribute;
    PTPAttributePoint *_characterFrictionAttribute;
    PTPAttributeFloat *_velocityScaleAttribute;
    PTPAttributeFloat *_rotationScaleAttribute;
    PTPAttributeFloat *_restitutionAttribute;
    PTPAttributeFloat *_platformFriction;
    PTPAttributeFloat *_scoreMultiplierAttribute;

    PTPAttributeFloat *_backDeletionThreshold;
    PTPAttributeFloat *_sidesDeletionThreshold;

    CCRect _objectFrameRect;

    PTObjectFrameEdgeState _objectFrameEdgeState[ 4 ];
    PTPAttributeBoolean *_upForceFromGroundAttribute;
    PTPAttributeBoolean *_fixedRotationAttribute;
    PTPAttributeBoolean *_fixedPositionAttribute;
    PTPAttributeBoolean *_forcedPositionAttribute;
    PTPAttributeBoolean *_autoImageDirectionAttribute;

    PTPAttributeString *_versionNumberAttribute;
    PTPAttributeString *_applicationNameAttribute;
    PTPAttributeString *_commentsAttribute;
    PTPAttributeString *_resetTextAttribute;
    PTPAttributeString *_buildDateAttribute;

    PTPAttributeKey *_moveUpKeyAttribute;
    PTPAttributeKey *_moveDownKeyAttribute;
    PTPAttributeKey *_moveLeftKeyAttribute;
    PTPAttributeKey *_moveRightKeyAttribute;
    PTPAttributeKey *_motorCWKeyAttribute;
    PTPAttributeKey *_motorCCWKeyAttribute;
    PTPAttributeKey *_rotateLeftKeyAttribute;
    PTPAttributeKey *_rotateRightKeyAttribute;
    PTPAttributeKey *_shootKeyAttribute;
    PTPAttributeKey *_jumpKeyAttribute;

    PTPAttributeFloat *_gameSpeedMin;
    PTPAttributeFloat *_gameSpeedMax;
    PTPAttributeFloat *_gameSpeedCurrent;
    PTPAttributeFloat *_gameSpeedIncrease;

    CCDictionary* _platformSpecificValues;

    friend class PTSettingsWindow;
};

#endif // PTMODELGENERALSETTINGS_H
