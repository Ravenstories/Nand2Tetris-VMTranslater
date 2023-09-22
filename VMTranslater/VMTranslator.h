#include <iostream>
#include <fstream>
#include <map>
#include <bitset>
#include <string>
#include <vector>
#include <sstream>
#include "commandWriter.cpp"

using namespace std;

class VMTranslator {
public:
    VMTranslator(std::ifstream& input, std::ofstream& output) : inputFile(input), commandWriter(output) {}

    void translateVMCommand() {
        string line;

        while (getline(inputFile, line))
        {
            vector <string> tokens = tokenize(line);

            if (tokens.size() == 0)
                continue;
            else
            {
                string command = tokens[0];

                if (command == "push" || command == "pop")
                    commandWriter.writeMemoryAccess(tokens);
                else if (command == "add" || command == "sub" || command == "neg" ||
                         command == "eq"  || command == "gt"  || command == "lt" ||
                         command == "and" || command == "or"  || command == "not")
                    commandWriter.writeArithmetic(tokens);
                /*
                else if (command == "label")
                    writeLabel(tokens[1]);
                else if (command == "goto")
                    writeGoto(tokens[1]);
                else if (command == "if-goto")
                    writeIf(tokens[1]);
                else if (command == "function")
                    writeFunction(tokens[1], tokens[2]);
                else if (command == "return")
                    writeReturn();
                else if (command == "call")
                    writeCall(tokens[1], tokens[2]);
                */
                else
                    continue;
            }
        }
    }


private:
    ifstream& inputFile;
    CommandWriter commandWriter;

    vector<string> tokenize(const string& line)
    {
        vector<string> tokens;
        istringstream tokenizer(line);
        string token;
        while (tokenizer >> token) {
            tokens.push_back(token);
        }
        return tokens;
    }
};