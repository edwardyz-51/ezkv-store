#include <iostream>
#include <string>
#include <spdlog/spdlog.h>
#include <fmt/format.h>
#include <sstream>
#include <optional>
class parser{
    public:
    enum class CommandType{
        SET,
        GET,
        DELETE
    };
    struct Command {
        CommandType type;
        std::string key;
        std::optional<std::string> value;
    };
    std::optional<Command> parse_command(const std::string& line) {
        std::stringstream ss(line);
        std::string command;
        ss >> command;
        if (command == "SET") {
            std::string key;
            std::string value;
            if (!(ss >> key)) {
                spdlog::error("SET requires a key");
                return std::nullopt;
            }
            if (ss.get() != ' ') {
                spdlog::error("SET requires a space before its value");
                return std::nullopt;
            }
            std::getline(ss, value);
            if (value.empty()) {
                spdlog::error("SET requires a nonempty value");
                return std::nullopt;
            }
            return Command{CommandType::SET, key, value};
        } else if (command == "GET") {
            std::string key;
            std::string remaining;
            if (!(ss >> key)) {
                spdlog::error("GET requires a key");
                return std::nullopt;
            }
            std::getline(ss,remaining);
            if (!remaining.empty()){
                spdlog::error("GET may only take a key");
                return std::nullopt;
            }
            return Command{CommandType::GET, key, std::nullopt};
        } else if (command == "DELETE") {
            std::string key;
            std::string remaining;

            if (!(ss >> key)) {
                spdlog::error("DELETE requires a key");
                return std::nullopt;
            }
            std::getline(ss, remaining);
            if (!remaining.empty()) {
                spdlog::error("DELETE may only take a key");
                return std::nullopt;
            }

            return Command{CommandType::DELETE, key, std::nullopt};
        } else {
            spdlog::error("invalid command");
            return std::nullopt;
        }

    }
};


int main() {
    parser p;
    auto result = p.parse_command("DELETE greeting");
    if (result) {
        spdlog::info(fmt::format("Parsed key='{}'", result->key));
    }
}
