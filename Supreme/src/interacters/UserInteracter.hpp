#ifndef SUPREME_USER_INTERACTER_HPP
#define SUPREME_USER_INTERACTER_HPP

#include <string>
#include <map>
#include <vector>
#include <functional>

namespace Supreme {
    // Kullanıcı girişi türü
    enum class InputType {
        TEXT,
        NUMBER,
        BOOLEAN,
        DATE,
        TIME,
        COLOR,
        FILE
    };
    
    // Kullanıcı olayı
    class UserEvent {
    public:
        std::string name;
        std::string value;
        InputType type;
        std::string metadata;
        
        UserEvent(const std::string& name, const std::string& value, InputType type, const std::string& metadata = "")
            : name(name), value(value), type(type), metadata(metadata) {}
    };
    
    // Kullanıcı etkileşim yöneticisi
    class UserInteracter {
    private:
        std::map<std::string, std::function<void(const UserEvent&)>> eventHandlers;
        std::map<std::string, std::string> userInputs;
        
    public:
        // Kullanıcı girişi alma
        std::string getUserInput(const std::string& name) {
            if (userInputs.find(name) != userInputs.end()) {
                return userInputs[name];
            }
            return "";
        }
        
        // Kullanıcı girişi ayarlama
        void setUserInput(const std::string& name, const std::string& value) {
            userInputs[name] = value;
            if (eventHandlers.find(name) != eventHandlers.end()) {
                eventHandlers[name](UserEvent(name, value, InputType::TEXT));
            }
        }
        
        // Olay yönetimi
        void onUserEvent(const std::string& name, const std::function<void(const UserEvent&)>& callback) {
            eventHandlers[name] = callback;
        }
        
        // Kullanıcı girişi listesi
        std::vector<std::string> getUserInputNames() {
            std::vector<std::string> names;
            for (const auto& pair : userInputs) {
                names.push_back(pair.first);
            }
            return names;
        }
        
        // Kullanıcı girişi kontrolü
        bool hasUserInput(const std::string& name) {
            return userInputs.find(name) != userInputs.end();
        }
        
        // Kullanıcı girişi temizleme
        void clearUserInputs() {
            userInputs.clear();
        }
        
        // Meta veri
        std::string getMetadata(const std::string& name) {
            if (eventHandlers.find(name) != eventHandlers.end()) {
                return eventHandlers[name].target_type().name();
            }
            return "";
        }
        
        // Kullanıcı girişi türü
        InputType getInputType(const std::string& name) {
            if (eventHandlers.find(name) != eventHandlers.end()) {
                return InputType::TEXT;
            }
            return InputType::TEXT;
        }
        
        // Kullanıcı girişi güncelleme
        void updateUserInput(const std::string& name, const std::string& value) {
            setUserInput(name, value);
        }
        
        // Kullanıcı girişi silme
        void removeUserInput(const std::string& name) {
            if (userInputs.find(name) != userInputs.end()) {
                userInputs.erase(name);
            }
        }
    };
}

#endif // SUPREME_USER_INTERACTER_HPP
