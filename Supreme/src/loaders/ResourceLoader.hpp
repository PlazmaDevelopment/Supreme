#ifndef SUPREME_RESOURCE_LOADER_HPP
#define SUPREME_RESOURCE_LOADER_HPP

#include <string>
#include <map>
#include <vector>
#include <functional>

namespace Supreme {
    // Kaynak türü
    enum class ResourceType {
        SCRIPT,
        IMAGE,
        AUDIO,
        VIDEO,
        TEXT,
        BINARY
    };
    
    // Kaynak nesnesi
    class Resource {
    public:
        std::string id;
        std::string path;
        ResourceType type;
        std::string metadata;
        bool isCached;
        
        Resource(const std::string& id, const std::string& path, ResourceType type, const std::string& metadata = "", bool isCached = false)
            : id(id), path(path), type(type), metadata(metadata), isCached(isCached) {}
    };
    
    // Kaynak yükleyici
    class ResourceLoader {
    private:
        std::map<std::string, Resource> resources;
        std::map<std::string, std::function<void(const Resource&)>> onLoadCallbacks;
        
    public:
        // Kaynak yükleme
        void loadResource(const std::string& id, const std::string& path, ResourceType type, const std::string& metadata = "", bool isCached = false) {
            resources[id] = Resource(id, path, type, metadata, isCached);
            if (onLoadCallbacks.find(id) != onLoadCallbacks.end()) {
                onLoadCallbacks[id](resources[id]);
            }
        }
        
        // Kaynak alma
        Resource getResource(const std::string& id) {
            if (resources.find(id) != resources.end()) {
                return resources[id];
            }
            return Resource("", "", ResourceType::SCRIPT);
        }
        
        // Kaynak olayları
        void onResourceLoad(const std::string& id, const std::function<void(const Resource&)>& callback) {
            onLoadCallbacks[id] = callback;
        }
        
        // Kaynak listesi
        std::vector<std::string> getResourceIds() {
            std::vector<std::string> ids;
            for (const auto& pair : resources) {
                ids.push_back(pair.first);
            }
            return ids;
        }
        
        // Kaynak kontrolü
        bool hasResource(const std::string& id) {
            return resources.find(id) != resources.end();
        }
        
        // Kaynak boyutu
        size_t getResourceSize() {
            return resources.size();
        }
        
        // Kaynak temizleme
        void clearResources() {
            resources.clear();
        }
        
        // Önbellek yönetimi
        void setCache(const std::string& id, bool isCached) {
            if (resources.find(id) != resources.end()) {
                resources[id].isCached = isCached;
            }
        }
        
        bool isCached(const std::string& id) {
            if (resources.find(id) != resources.end()) {
                return resources[id].isCached;
            }
            return false;
        }
        
        // Meta veri
        std::string getMetadata(const std::string& id) {
            if (resources.find(id) != resources.end()) {
                return resources[id].metadata;
            }
            return "";
        }
        
        void setMetadata(const std::string& id, const std::string& metadata) {
            if (resources.find(id) != resources.end()) {
                resources[id].metadata = metadata;
            }
        }
    };
}

#endif // SUPREME_RESOURCE_LOADER_HPP
