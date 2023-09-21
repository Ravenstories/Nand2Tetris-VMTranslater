#include <iostream>
#include <fstream>
#include <map>
#include <bitset>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

//enum commands{ add, sub, neg, eq, gt, lt, and, or, not, push, pop, label, goto_, if_, function, return_, call };

/*
	Notes to self. Handle the following:
	Token 0 push / pop 
	Token 1 constant / local / argument / this / that / pointer / temp / static
	Token 2 int / string / label
*/

class VMTranslator {
    public:
        VMTranslator(std::ifstream& input, std::ofstream& output) : inputFile(input), outputFile(output) {}

        void translateVMCommand() {
            string line;
            while (getline(inputFile, line))
            {
				vector <string> tokens = tokenize(line);

                if (tokens.size() == 0) {
					continue;
                }
                else
                {
					string command = tokens[0];
                    
					if (command == "push" || command == "pop")
						writeMemoryAccess(tokens);
                    else if (command == "add" || command == "sub" || command == "neg" ||
                             command == "eq"  || command == "gt"  || command == "lt"  ||
                             command == "and" || command == "or"  || command == "not" )
                        writeArithmetic(tokens);
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
		ofstream& outputFile;

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
        
        //writeArithmetic
        
		void writeArithmetic(vector<string> tokens)
        {
            
            
        }
		void writeMemoryAccess(vector<string> tokens)
		{
            if (tokens[0] == "push")
            {
                
                

            }
			else if (tokens[0] == "pop")
			{

			}
			else
			{
				cout << "Error: Invalid command" << endl;
			}

            
            if (tokens[1] == "constant") {
                // Push a constant value onto the stack
                outputFile << "@" << tokens[2] << std::endl;
                outputFile << "D=A" << std::endl;
            }

            outputFile << "@SP" << std::endl;
            outputFile << "A=M" << std::endl;
            outputFile << "M=D" << std::endl;
            outputFile << "@SP" << std::endl;
            outputFile << "M=M+1" << std::endl;
            
        }
        
        /*
        void translatePush(const std::string& segment, const std::string& value) {
        }

        void translatePop(){}
        
        void translateAdd() {
            outputFile << "@SP" << std::endl;
            outputFile << "A=M-1" << std::endl;
            outputFile << "D=M" << std::endl;
            outputFile << "A=A-1" << std::endl;
            outputFile << "M=M+D" << std::endl;
            outputFile << "@SP" << std::endl;
            outputFile << "M=M-1" << std::endl;
        }
        
		void translateSub() {
			outputFile << "@SP" << std::endl;
			outputFile << "A=M-1" << std::endl;
			outputFile << "D=M" << std::endl;
			outputFile << "A=A-1" << std::endl;
			outputFile << "M=M-D" << std::endl;
			outputFile << "@SP" << std::endl;
			outputFile << "M=M-1" << std::endl;
		}
        */
        
        
};



int main()
{
    // Open the input file
    string inputFileName = "input.asm";
    // Create the output file
    string outputFileName = "output.txt";

    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    string line;

    VMTranslator translator(inputFile, outputFile);
    /*
    translator.translateVMCommand("push constant 7");
    translator.translateVMCommand("push constant 8");
    translator.translateVMCommand("add");
    */

    inputFile.clear();
    inputFile.seekg(0);

    std::cout << "Assembly successfully assembled to " << outputFileName << endl;

    return 0;
}