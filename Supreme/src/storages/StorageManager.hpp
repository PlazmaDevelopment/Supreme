#ifndef SUPREME_STORAGE_MANAGER_HPP
#define SUPREME_STORAGE_MANAGER_HPP

#include <string>
#include <map>
#include <vector>
#include <functional>

namespace Supreme {
    // Depolama türü
    enum class StorageType {
        MEMORY,
        FILE,
        DATABASE,
        CLOUD
    };
    
    // Depolama nesnesi
    class StorageObject {
    public:
        std::string key;
        std::string value;
        StorageType type;
        std::string metadata;
        
        StorageObject(const std::string& key, const std::string& value, StorageType type, const std::string& metadata = "")
            : key(key), value(value), type(type), metadata(metadata) {}
    };
    
    // Depolama yöneticisi
    class StorageManager {
    private:
        std::map<std::string, StorageObject> storage;
        std::map<std::string, std::function<void(const std::string&)>> onChangeCallbacks;
        
    public:
        // Depolama ekleme
        void addStorage(const std::string& key, const std::string& value, StorageType type, const std::string& metadata = "") {
            storage[key] = StorageObject(key, value, type, metadata);
        }
        
        // Depolama güncelleme
        void updateStorage(const std::string& key, const std::string& value) {
            if (storage.find(key) != storage.end()) {
                storage[key].value = value;
                if (onChangeCallbacks.find(key) != onChangeCallbacks.end()) {
                    onChangeCallbacks[key](value);
                }
            }
        }
        
        // Depolama alma
        std::string getStorage(const std::string& key) {
            if (storage.find(key) != storage.end()) {
                return storage[key].value;
            }
            return "";
        }
        
        // Depolama silme
        void removeStorage(const std::string& key) {
            if (storage.find(key) != storage.end()) {
                storage.erase(key);
            }
        }
        
        // Depolama olayları
        void onStorageChange(const std::string& key, const std::function<void(const std::string&)>& callback) {
            onChangeCallbacks[key] = callback;
        }
        
        // Depolama türü
        StorageType getStorageType(const std::string& key) {
            if (storage.find(key) != storage.end()) {
                return storage[key].type;
            }
            return StorageType::MEMORY;
        }
        
        // Meta veri
        std::string getMetadata(const std::string& key) {
            if (storage.find(key) != storage.end()) {
                return storage[key].metadata;
            }
            return "";
        }
        
        // Depolama listesi
        std::vector<std::string> getStorageKeys() {
            std::vector<std::string> keys;
            for (const auto& pair : storage) {
                keys.push_back(pair.first);
            }
            return keys;
        }
        
        // Depolama kontrolü
        bool hasStorage(const std::string& key) {
            return storage.find(key) != storage.end();
        }
        
        // Depolama boyutu
        size_t getStorageSize() {
            return storage.size();
        }
        
        // Depolama temizleme
        void clearStorage() {
            storage.clear();
        }
    };
}

#endif // SUPREME_STORAGE_MANAGER_HPP
