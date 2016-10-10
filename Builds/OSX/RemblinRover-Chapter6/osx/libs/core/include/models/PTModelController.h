#ifndef PTMODELCONTROLLER_H
#define PTMODELCONTROLLER_H

#include "cocos2d.h"
#include <map>

using namespace cocos2d;

class QLocalServer;
class PTModel;
class PTModelSprite;
class PTModelSound;
class PTNodeUIStart;
class PTNodeScene;
class PTNodeUI;
class PTModelLevelSection;
class PTModelObjectButton;
class PTModelScreen;

typedef PTModel *(*CreatePTModelFn)(void);

typedef enum{
    PTModelControllerDataTypeAttributes = 0,
    PTModelControllerDataTypeConnections = 1,

} PTModelControllerDataType;

class PTModelController {
public:    
    static PTModelController *shared();
    static void resetShared();

    PTModelController &operator=(const PTModelController &) { return *this; }

    static unsigned int nextId();

    void addModel( PTModel *model );
    void insertModel( unsigned int index, PTModel *model );
    unsigned int indexOfModel( PTModel *model ) const;
    void removeModel( PTModel *model );

    CCArray *getModelArray( const std::string &className );
    void setModelArray( const std::string &className, CCArray *array );

    PTModel *getModel( const std::string &className );
    PTModel *getModel( unsigned int id );

    void saveSpriteToFile( PTModelSprite *model );
    void loadSpriteFromFile( PTModelSprite *model );
    void copySpriteFile(PTModelSprite *original, PTModelSprite *copy);
    bool deleteSpriteFile( PTModelSprite *model );

    PTModel *createModel( const std::string &className );

    PTModelSprite *getSpriteById( int id );

    bool updateLoadingQueue( const char* resourceFolder );
    void loadFromFile( CCString fileName );

    bool isChanged() const;

    // returns true no previous sessions were found
    bool isEmpty() const;

    bool loadDataForClass( CCString *fileName, PTModelControllerDataType dataType );

    int fileLoadingProgress();

    void stopAllBackgroundMusic();
    void stopAllSounds();

    void clean();

    int bigIbVersion() const;

    CCDictionary* data();

    void toggleUpdateObjects(bool state, bool updateObjects = true);
    inline bool isUpdateObjectsEnabled() const { return _updateObjectsState; }

    void removeInvalidObjects();

    //QT specific part
#ifdef __QT__
    static QString rootTempDirPath();

    void initDefaultModelSet();
    QString initWorkingFolder();

    void setupDefaultScene(const QVariantMap &settings, const QString &gamePreset);

    QString saveSoundFile( PTModelSound *model, const QString &sourceFilePath );
    QString getSoundFileName( PTModelSound *model );
    bool deleteSoundFile( PTModelSound *model );
    bool isEmptySoundFile( PTModelSound *model );

    bool isWorkDirEmpty();
    QStringList getSessionsList();

    void copyPath(QString src, QString dst);
    QString getWorkingPath( ) { return _workingPath; }
    QString savedFilePath;
    bool loadFromFile( QString fileName, bool isTemplate = false );
    bool saveToFile( QString fileName );
    bool saveSession(bool isAutoSave = true);

    bool isLoading();
    void setIsLoading(bool);

    bool writeDataForClass( CCString *className, PTModelControllerDataType dataType );


    QString errorString() const;
    void clearErrorString();

    bool loadExistingSession();
    bool loadExistingSession( const QString & );

    void removeSessionFolder( QString uid );

    bool compressFilesToArhive(QString basePath, QStringList filesList, QString archiveName );

    void checkSpriteFiles();

    void onModelChange(QString className);


    void perform1xto20conversion();
    void convertUiButtons();
    void convertUiButtons(PTNodeUI *node);
    void convertUiSoundButtons(PTModelScreen *model, std::vector<PTModelObjectButton*> &onButtons, std::vector<PTModelObjectButton*> &offButtons);
    void convertUnitAssets();

    void connectAttributes(PTModel *outputNode, const CCString &outputLink, PTModel *inputNode, const CCString &inputLink);
#endif

private:
    // Model Controller is singleton object so there is no ability to create this object explicitly.
    // Use PTModelController::shared() method to get access to singleton instance instead.
    explicit PTModelController( );
    virtual ~PTModelController( );

    void init();

    void addClass(const std::string &className, CreatePTModelFn pfnCreate);

    void splitVersionNumbers(const char* veriosnString, int *v1, int *v2, int *v3) const;

#ifdef __QT__
    bool compressWorkingFiles( QString fileName );
    void workingFiles( QString path, QStringList &list );

    // remove folder of current session
    void removeWorkingFolder();

    void checkAtlasFiles();
    void checkFontFiles();

    //For setupDefaultScene
    void setupDefaultNodes(PTNodeUIStart **startNode, PTNodeScene **sceneNode, PTNodeUI **gameUiNode, bool fromExisting, bool hasPause);
    void setupDefaultGameUi(PTNodeUI *gameUiNode, bool fromExisting, bool hasPause);
    void setupMainMenu(PTNodeScene *sceneNode, PTNodeUI **mainMenuUi, bool hasInfoScreen, bool hasCoinShop);
    PTNodeUI* setupCompleteUi();
    PTNodeUI* setupWorldsUi();
    PTNodeUI* setupInfoScreen(PTNodeScene *sceneNode, PTNodeUI *mainMenuUi);
    void setupCoinShop(PTNodeScene *sceneNode, PTNodeUI *mainMenuUi, PTNodeUI *infoScreen);
    void setupPauseScreen(PTNodeUI *gameUiNode, PTNodeUI *mainMenuUi, PTNodeUI *worldsUi);
    void setupGameOverScreen(PTNodeUI *gameUiNode, PTNodeUI *mainMenuUi, PTNodeUI *worldsUi);
    PTModelLevelSection* setupStartSection(PTNodeScene *sceneNode, bool fromExisting);
    void setupDefaultCharacter(PTModelLevelSection *section);
    void setupDefaultPlatform(PTModelLevelSection *section);
    void setupNextScreenJump(PTNodeScene *sceneNode, PTModelLevelSection *section);
    void setupMultipleWorlds(QList<PTNodeScene*> &sceneNodes, QList<PTNodeUI*> &completeUiNodes, qulonglong count,
                             PTNodeScene *sceneNode, PTNodeUI *completeUiNode, PTNodeUI *gameUiNode, bool singleUi);
    PTNodeScene* setupEndScene(PTNodeUI *completeUiNode, const CCPoint &scenePos, float uiPosX);
    void setupWorldsUi2(PTNodeUI *worldsUi, PTNodeUI *mainMenuUi, const QList<PTNodeScene*> &sceneNodes);
#endif

    cocos2d::CCDictionary *_data;
    typedef std::map<std::string, CreatePTModelFn> PTModelFactoryMap;
    PTModelFactoryMap _factoryMap;
    bool _isEmpty;

    typedef std::map<unsigned int, PTModel*> PTModelIdMap;
    PTModelIdMap _modelIdMap;

    int _fileLoadCounter;
    int _fileSectionLoadCounter;
    int _fileLoadingMode; // 0 - loading data, 1 - loading connections, 2 - loading complete
    int _fileLoadingProgress;

    bool _updateObjectsState;

#ifdef __QT__
    QString _workingPath;
    QStringList _ignoreList;
    QString _errorString;

    QMap<QString, bool> _changeModelMap;
    bool _isLoading;

    QLocalServer *m_localServer;

    //PATCH SECTION
    void pathForObjectSorting();  // since BBox 1.0.9
    void patchForFileLoading( QFileInfo inputFileInfo ); // since BBox 1.0.14
    void patchForJoystick(); // since BBox 1.1
    void patchForCharacterBulletsCollisionType(); // since BBox 1.1
    void patchForDestroyType(); //since BBox 1.1
    void patchReviewLinks();
    void patchLogicItems(); // since BBox 1.3.4
    void patchOldAdsSettings();
    void patchConvertWakeupSleepToComponents(); //in bbox2 all wakeup and sleep is a component now (since 2.0)

    void assignIndexForLevelSections();

    void applyPatches();
    void applyBackgroundsPatch();
    void applyAirDragPowerupPatch(); //invert AirDrag value inside powerup (since 2.0)
#endif




};



#endif // PTMODELCONTROLLER_H
