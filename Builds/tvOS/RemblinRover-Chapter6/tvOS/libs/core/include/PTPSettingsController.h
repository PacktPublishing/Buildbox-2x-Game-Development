#ifndef PTPSETTINGSCONTROLLER_H
#define PTPSETTINGSCONTROLLER_H

#include <cocos2d.h>
#include <map>

class PTModelAssetPowerup;

struct PTPowerupRefillStruct {
   time_t startTime;
   int refillDuration;
   unsigned int id;
   int maxRefils;

};

class PTPSettingsController: public cocos2d::CCObject {

public:
    PTPSettingsController();
    virtual ~PTPSettingsController();
    static PTPSettingsController* shared();
    static void resetShared();

    void setPowerupInventoryAmount(PTModelAssetPowerup* powerup, int amount);
    int powerupInventoryAmount( PTModelAssetPowerup* powerup);

    int powerupRefillTime( unsigned int id );
    void scheduleRefillTimer( unsigned int id, int minutes, int maxRefills );

    virtual void save();
    virtual void load();
    void reset();
    void resetInventory();

    void setRemoveAds( bool );
    bool removeAds();

    void setFullscreen( bool value);
    bool isFullscreen();

    void setLowPerformanceMode( bool value);
    bool isLowPerformanceMode();

    inline void setMuteEffectsSound(bool state) { _muteEffectsSound = state; }
    inline bool isMuteEffectsSound() const { return _muteEffectsSound; }

    inline void setMuteBackgroundSound(bool state) { _muteBackgroundSound = state; }
    inline bool isMuteBackgroundSound() const { return _muteBackgroundSound; }

    void loadDefaultInventoryMap();

    int screenPlayed( cocos2d::CCString name );
    void setScreenPlayed( cocos2d::CCString name );


    void unlockCharacter(unsigned int characterIndex);
    void lockCharacter(unsigned int characterIndex);
    bool isCharacterLocked(unsigned int characterIndex);

    void setSelectedCharacter( int index );
    int selectedCharacter();

protected:
    typedef std::map<unsigned int, PTPowerupRefillStruct> PTPowerupRefillMap;
    PTPowerupRefillMap _powerupRefillsMap;

private:
    void update(float dt);
    typedef std::map<unsigned int, int> PTPowerupInventoryMap;
    PTPowerupInventoryMap _inventoryMap;

    typedef std::map<unsigned int, bool> PTCharacterUnlockMap;
    PTCharacterUnlockMap _characterUnlockMap;

    bool _removeAds;
    bool _muteSound;
    bool _lowPerformanceMode;
    bool _fullscreen;

    bool _muteEffectsSound;
    bool _muteBackgroundSound;

    int _selectedCharacterId;
};

#endif // PTPSETTINGSCONTROLLER_H
