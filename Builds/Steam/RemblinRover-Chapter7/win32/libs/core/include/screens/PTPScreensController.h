#ifndef PTPScreensController_H
#define PTPScreensController_H

#include <cocos2d.h>
#include <vector>

using namespace cocos2d;

class PTPScreenScene;
class PTPScreenUi;
class PTPAttributeAction;

class PTPScreensController {
public:
    enum SwitchResult {
        NotSwitched,
        SceneSwitched,
        UiSwitched
    };

    static PTPScreensController* shared();
    static void resetShared();

    CCScene* currentScene();

    PTPScreenScene* currentScreenScene();
    PTPScreenUi* currentScreenUi();

    inline const CCString& currentScreenSceneKey() const { return _currentScreenSceneKey; }
    inline CCString currentScreenUiKey() const { return _currentScreenUiIt != _uiStack.end() ? *_currentScreenUiIt : CCString(); }

    bool switchNextScreen(const CCString &link, bool fromUi = false, bool saveScores = false);
    bool switchNextUi(const CCString &link, bool fromScene = false);

    bool switchToOrigianlUi();
    bool switchToPreviousUi();

    SwitchResult switchScreen(const CCString &sceneKey, const CCString &uiKey, bool saveScores = false);

    unsigned int levelSectionDestinationId();
    void setLevelSectionDestinationId( unsigned int id );
    unsigned int nextLevelSectionDestinationId( unsigned int startLevelSectionId );

    void setCurrentScreenSceneKey(CCString key);

private:
    PTPScreensController();
    ~PTPScreensController();

    PTPAttributeAction* findSceneAction(const CCString &link);
    PTPAttributeAction* findUiAction(const CCString &link);

private:
    static PTPScreensController *_instance;

    CCString _currentScreenSceneKey;

    std::vector<CCString> _uiStack;
    std::vector<CCString>::iterator _currentScreenUiIt;

    CCScene *_currentScene;

    unsigned int _levelSectionDestinationId;
};

#endif // PTPScreensController_H
