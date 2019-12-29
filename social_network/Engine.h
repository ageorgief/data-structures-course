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
public:
    Engine();
    void start();
};

Engine::Engine() {}

void Engine::start() {
    while (true) {
        std::string inputString = input.read();
        commandResult = parser.parse(inputString);
       
        if (commandResult.isError()) {
            std::string errorMessage = commandResult.getErrorMessage();
            output.print(errorMessage);
        }
        else {
            std::string commandExecutionMessage = commandResult.getCommand()->execute();
            output.print(commandExecutionMessage);
        }
    }
}
#endif // !ENGINE_H

