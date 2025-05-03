#ifndef SUPREME_SCRIPT_PARSER_HPP
#define SUPREME_SCRIPT_PARSER_HPP

#include <string>
#include <vector>
#include <map>
#include <functional>

namespace Supreme {
    // Betik dil türü
    enum class ScriptLanguage {
        WHOLF,
        PYTHON,
        JAVASCRIPT,
        LUA,
        RUBY
    };
    
    // Betik komutu
    class ScriptCommand {
    public:
        std::string name;
        std::vector<std::string> arguments;
        ScriptLanguage language;
        std::string metadata;
        
        ScriptCommand(const std::string& name, const std::vector<std::string>& arguments, ScriptLanguage language, const std::string& metadata = "")
            : name(name), arguments(arguments), language(language), metadata(metadata) {}
    };
    
    // Betik parser
    class ScriptParser {
    private:
        std::vector<ScriptCommand> commands;
        std::map<std::string, std::function<void(const ScriptCommand&)>> commandHandlers;
        
    public:
        // Betik ekleme
        void addCommand(const std::string& name, const std::vector<std::string>& arguments, ScriptLanguage language, const std::string& metadata = "") {
            commands.push_back(ScriptCommand(name, arguments, language, metadata));
        }
        
        // Betik ayrıştırma
        std::vector<ScriptCommand> parseScript(const std::string& script) {
            // Betik ayrıştırma işlemleri
            return commands;
        }
        
        // Komut olayları
        void onCommand(const std::string& name, const std::function<void(const ScriptCommand&)>& callback) {
            commandHandlers[name] = callback;
        }
        
        // Betik yürütme
        void executeScript(const std::string& script) {
            auto parsedCommands = parseScript(script);
            for (const auto& command : parsedCommands) {
                if (commandHandlers.find(command.name) != commandHandlers.end()) {
                    commandHandlers[command.name](command);
                }
            }
        }
        
        // Betik dil türü
        ScriptLanguage getLanguage(const std::string& script) {
            // Dil türü tespiti
            return ScriptLanguage::WHOLF;
        }
        
        // Meta veri
        std::string getMetadata(const std::string& script) {
            // Meta veri alma
            return "";
        }
        
        // Komut listesi
        std::vector<std::string> getCommandNames() {
            std::vector<std::string> names;
            for (const auto& command : commands) {
                names.push_back(command.name);
            }
            return names;
        }
        
        // Komut kontrolü
        bool hasCommand(const std::string& name) {
            for (const auto& command : commands) {
                if (command.name == name) {
                    return true;
                }
            }
            return false;
        }
        
        // Betik temizleme
        void clearCommands() {
            commands.clear();
        }
    };
}

#endif // SUPREME_SCRIPT_PARSER_HPP
