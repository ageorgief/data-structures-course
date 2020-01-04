#ifndef ENGINE_H
#define ENGINE_H

#include "Input.h"
#include "ParseCommandResult.h"
#include "Parser.h"
#include "Output.h"

class Engine {
private:
    Input input;
    Output output;
    Parser parser;
    ParseCommandResult commandResult;
    DataStorage storage;
public:
    Engine();
    void start();
};

Engine::Engine() {}

void Engine::start() {
    storage.loadData();
    while (true) {
        std::string inputString = input.read();
        commandResult = parser.parse(inputString);
       
        if (commandResult.isError()) {
            std::string errorMessage = commandResult.getErrorMessage();
            output.print(errorMessage);
        }
        else {
            std::string commandExecutionMessage = commandResult.getCommand()->execute(storage);
            output.print(commandExecutionMessage);
            storage.writeUsersDataToFile();
        }
    }
}
#endif // !ENGINE_H

