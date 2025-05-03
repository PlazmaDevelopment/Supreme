#ifndef SUPREME_HPP
#define SUPREME_HPP

#include "enviroment/EnvironmentManager.hpp"
#include "storages/StorageManager.hpp"
#include "scriptparsers/ScriptParser.hpp"
#include "loaders/ResourceLoader.hpp"
#include "interacters/UserInteracter.hpp"

namespace Supreme {
    // Supreme motoru
    class Supreme {
    private:
        EnvironmentManager environment;
        StorageManager storage;
        ScriptParser scriptParser;
        ResourceLoader resourceLoader;
        UserInteracter userInteracter;
        
    public:
        // Çevre yönetimi
        void addVariable(const std::string& name, const std::string& value, bool isGlobal = false, bool isReadOnly = false) {
            environment.addVariable(name, value, isGlobal, isReadOnly);
        }
        
        std::string getVariable(const std::string& name) {
            return environment.getVariable(name);
        }
        
        // Depolama yönetimi
        void addStorage(const std::string& key, const std::string& value, StorageType type, const std::string& metadata = "") {
            storage.addStorage(key, value, type, metadata);
        }
        
        std::string getStorage(const std::string& key) {
            return storage.getStorage(key);
        }
        
        // Betik yönetimi
        void addCommand(const std::string& name, const std::vector<std::string>& arguments, ScriptLanguage language, const std::string& metadata = "") {
            scriptParser.addCommand(name, arguments, language, metadata);
        }
        
        void executeScript(const std::string& script) {
            scriptParser.executeScript(script);
        }
        
        // Kaynak yönetimi
        void loadResource(const std::string& id, const std::string& path, ResourceType type, const std::string& metadata = "", bool isCached = false) {
            resourceLoader.loadResource(id, path, type, metadata, isCached);
        }
        
        Resource getResource(const std::string& id) {
            return resourceLoader.getResource(id);
        }
        
        // Kullanıcı etkileşimi
        void setUserInput(const std::string& name, const std::string& value) {
            userInteracter.setUserInput(name, value);
        }
        
        std::string getUserInput(const std::string& name) {
            return userInteracter.getUserInput(name);
        }
        
        // Olay yönetimi
        void onVariableChange(const std::string& name, const std::function<void(const std::string&)>& callback) {
            environment.onVariableChange(name, callback);
        }
        
        void onStorageChange(const std::string& key, const std::function<void(const std::string&)>& callback) {
            storage.onStorageChange(key, callback);
        }
        
        void onCommand(const std::string& name, const std::function<void(const ScriptCommand&)>& callback) {
            scriptParser.onCommand(name, callback);
        }
        
        void onResourceLoad(const std::string& id, const std::function<void(const Resource&)>& callback) {
            resourceLoader.onResourceLoad(id, callback);
        }
        
        void onUserEvent(const std::string& name, const std::function<void(const UserEvent&)>& callback) {
            userInteracter.onUserEvent(name, callback);
        }
        
        // Durum yönetimi
        bool isRunning() const {
            return true; // Default olarak çalışır durumda
        }
        
        void update(float deltaTime) {
            // Tüm sistemlerin güncellenmesi
        }
    };
}

#endif // SUPREME_HPP
