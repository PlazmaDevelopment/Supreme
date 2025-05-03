#ifndef SUPREME_ENVIRONMENT_MANAGER_HPP
#define SUPREME_ENVIRONMENT_MANAGER_HPP

#include <string>
#include <map>
#include <vector>
#include <functional>

namespace Supreme {
    // Çevre değişkeni
    class EnvironmentVariable {
    public:
        std::string name;
        std::string value;
        bool isGlobal;
        bool isReadOnly;
        
        EnvironmentVariable(const std::string& name, const std::string& value, bool isGlobal = false, bool isReadOnly = false)
            : name(name), value(value), isGlobal(isGlobal), isReadOnly(isReadOnly) {}
        
        void setValue(const std::string& value) {
            if (!isReadOnly) {
                this->value = value;
            }
        }
    };
    
    // Çevre yöneticisi
    class EnvironmentManager {
    private:
        std::map<std::string, EnvironmentVariable> variables;
        std::map<std::string, std::function<void(const std::string&)>> onChangeCallbacks;
        
    public:
        // Değişken ekleme
        void addVariable(const std::string& name, const std::string& value, bool isGlobal = false, bool isReadOnly = false) {
            variables[name] = EnvironmentVariable(name, value, isGlobal, isReadOnly);
        }
        
        // Değişken güncelleme
        void updateVariable(const std::string& name, const std::string& value) {
            if (variables.find(name) != variables.end()) {
                variables[name].setValue(value);
                if (onChangeCallbacks.find(name) != onChangeCallbacks.end()) {
                    onChangeCallbacks[name](value);
                }
            }
        }
        
        // Değişken alma
        std::string getVariable(const std::string& name) {
            if (variables.find(name) != variables.end()) {
                return variables[name].value;
            }
            return "";
        }
        
        // Değişken silme
        void removeVariable(const std::string& name) {
            if (variables.find(name) != variables.end() && !variables[name].isReadOnly) {
                variables.erase(name);
            }
        }
        
        // Değişken olayları
        void onVariableChange(const std::string& name, const std::function<void(const std::string&)>& callback) {
            onChangeCallbacks[name] = callback;
        }
        
        // Global değişkenler
        void setGlobalVariable(const std::string& name, const std::string& value) {
            addVariable(name, value, true);
        }
        
        std::string getGlobalVariable(const std::string& name) {
            if (variables.find(name) != variables.end() && variables[name].isGlobal) {
                return variables[name].value;
            }
            return "";
        }
        
        // Okuma-yalnız değişkenler
        void setReadOnlyVariable(const std::string& name, const std::string& value) {
            addVariable(name, value, false, true);
        }
        
        bool isReadOnlyVariable(const std::string& name) {
            if (variables.find(name) != variables.end()) {
                return variables[name].isReadOnly;
            }
            return false;
        }
        
        // Değişken listesi
        std::vector<std::string> getVariableNames() {
            std::vector<std::string> names;
            for (const auto& pair : variables) {
                names.push_back(pair.first);
            }
            return names;
        }
        
        // Değişken kontrolü
        bool hasVariable(const std::string& name) {
            return variables.find(name) != variables.end();
        }
    };
}

#endif // SUPREME_ENVIRONMENT_MANAGER_HPP
