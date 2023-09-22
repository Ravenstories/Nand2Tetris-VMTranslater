#include <iostream>
#include <fstream>
#include <map>
#include <bitset>
#include <string>
#include <vector>
#include <sstream>
#include "CommandWriter.cpp"

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