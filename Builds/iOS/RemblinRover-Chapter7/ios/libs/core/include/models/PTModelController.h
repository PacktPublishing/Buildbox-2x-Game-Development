#ifndef PTMODELCONTROLLER_H
#define PTMODELCONTROLLER_H

#include <unordered_map>
#include <string>
#include <vector>
#include <functional>
#include <limits>
#include <algorithm>

#include <cocos2d.h>

class PTModel;

template <typename StringType>
inline const char* toCString(const StringType &str) { return str; }

template <>
inline const char* toCString<std::string>(const std::string &str) { return str.c_str(); }

template <>
inline const char* toCString<cocos2d::CCString>(const cocos2d::CCString &str) { return str.getCString(); }

class PTModelController
{
public:
    enum DataType
    {
        Attributes,
        Connections
    };

    enum LoadFileStatus
    {
        LoadFileSuccess,
        LoadFileNotFound,
        LoadFileError
    };

    static PTModelController* shared();
    static void resetShared();

    void addFactory(const char *className, std::function<PTModel*()> createFunc);

    PTModel* createModel(const char *className);

    void addModel(PTModel *model, std::size_t index = std::numeric_limits<std::size_t>::max());
    void removeModel(PTModel *model);

    PTModel* getModel(std::size_t id) const;
    PTModel* getFirstModel(const char *className) const;
    std::vector<PTModel*> getModels(const char *className) const;

    bool hasModel(PTModel *model) const;
    std::size_t modelIndex(PTModel *model) const;

    void modelIdChanged(PTModel *model, std::size_t oldId);

    virtual void modelChanged(PTModel *model);

    inline bool hasChanges() const { return _changesState; }
    inline void setChangesState(bool hasChanges) { _changesState = hasChanges; }

    inline unsigned int lastModelId() const { return _lastModelId; }
    inline unsigned int nextModelId() { return ++_lastModelId; }
    inline void setLastModelid(unsigned int id) { _lastModelId = id; }

    bool loadDirectory(const char *path);
    LoadFileStatus loadFile(const char *path, DataType type);

    std::size_t loadProgress() const;

    inline const std::string& loadError() const { return _loadError; }
    inline void clearLoadError() { _loadError.clear(); }

    void toggleUpdateObjects(bool state, bool updateObjects = true);
    inline bool isUpdateObjectsEnabled() const { return _updateObjectsState; }

    static void ibVersion(int &big, int &major, int &minor);

    static inline int bigIbVersion() { int big = 0, major = 0, minor = 0; ibVersion(big, major, minor); return big; }
    static inline int majorIbVersion() { int big = 0, major = 0, minor = 0; ibVersion(big, major, minor); return major; }
    static inline int minorIbVersion() { int big = 0, major = 0, minor = 0; ibVersion(big, major, minor); return minor; }

    void clean();

    /***************************Templates***************************/
    template <typename StringType>
    void addFactory(const StringType &className, std::function<PTModel*()> createFunc) { addFactory(toCString(className), createFunc); }

    template <typename StringType>
    PTModel* createModel(const StringType &className) { return createModel(toCString(className)); }

    template <typename StringType>
    PTModel* getFirstModel(const StringType &className) const { return getFirstModel(toCString(className)); }

    template <typename StringType>
    std::vector<PTModel*> getModels(const StringType &className) const { return getModels(toCString(className)); }

    template <typename StringType, typename Compare>
    void sortModels(const StringType &className, Compare compare) {
        std::unordered_map<std::string, std::vector<PTModel*>>::iterator it = _nameModelMap.find(toCString(className));

        if (it != _nameModelMap.end()) {
            std::sort(it->second.begin(), it->second.end(), compare);
        }
    }

    template <typename StringType>
    bool loadDirectory(const StringType &path) { return loadDirectory(toCString(path)); }

    template <typename StringType>
    LoadFileStatus loadFile(const StringType &path, DataType type) { return loadFile(toCString(path), type); }

protected:
    PTModelController();
    virtual ~PTModelController();

    void loadDictionary(cocos2d::CCDictionary *dict, DataType type);

private:
    void initFactory();

    void modelAdded(PTModel *model);
    void modelRemoved(PTModel *model);

protected:
    static PTModelController *_instance;

    std::unordered_map<std::string, std::function<PTModel*()>> _factoryMap;

    std::unordered_map<std::string, std::vector<PTModel*>> _nameModelMap;
    std::unordered_map<std::size_t, PTModel*> _idModelMap;

    std::string _loadError;

private:
    class LoadProgress;

    bool _changesState;
    unsigned int _lastModelId;

    LoadProgress *_loadProgress;

    bool _updateObjectsState;
};

#endif // PTMODELCONTROLLER_H
