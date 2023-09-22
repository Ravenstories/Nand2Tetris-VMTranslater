#include <iostream>
#include <fstream>
#include <map>
#include <bitset>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CommandWriter {
public:
	CommandWriter() = default;
    CommandWriter(std::ofstream& output) : outputFile(output), labelCounter(0) {}

    void writeArithmetic(vector<string> tokens)
    {
		string aCommand = tokens[0];
		outputFile << "@SP" << endl;
		outputFile << "AM=M-1" << endl;		// A -> y

		if (aCommand == "neg") {
			outputFile << "M=-M" << endl;
			return;
		}
		if (aCommand == "not") {
			outputFile << "M=!M" << endl;
			return;
		}

		// Binary operations: D contains y, A points to x.
		outputFile << "D=M" << endl;		// D = y
		outputFile << "A=A-1" << endl; 	// A -> x

		if (aCommand == "add") {					// [SP-1] <- result
			outputFile << "M=M+D" << endl;
		}
		else if (aCommand == "sub") {
			outputFile << "M=M-D" << endl;
		}
		else if (aCommand == "and") {
			outputFile << "M=D&M" << endl;
		}
		else if (aCommand == "or") {
			outputFile << "M=D|M" << endl;
		}
		else if (aCommand == "eq" || aCommand == "lt" || aCommand == "gt") {
			compare(aCommand);
		}
		// Decrementing the stack pointer:
		//outputFile << "@SP" << endl;
		//outputFile << "M=M-1" << endl;
    }
	
    void writeMemoryAccess(vector<string> tokens)
    {
		string command = tokens[0];
		string segment = tokens[1];
		string value = tokens[2];

        if (command == "push")
        {
			if (segment == "constant") {
				outputFile << "@" << value << endl;
				outputFile << "D=A" << endl;			// D = constant.
			}
			else if (segment == "local") {
			
			}
			else if (segment == "argument") {
			
			}
			outputFile << "@SP" << std::endl;
			outputFile << "A=M" << std::endl;
			outputFile << "M=D" << std::endl;
			outputFile << "@SP" << std::endl;
			outputFile << "M=M+1" << std::endl;

        }
        else if (command == "pop")
        {
			
        }
        else
        {
            cout << "Error: Invalid command" << endl;
        }
    }

private:
    ofstream& outputFile;
	int labelCounter;

	void compare(const string& aCommand) {
		outputFile << "D=M-D" << endl;            
		outputFile << "@TRUE" << labelCounter << endl;
		outputFile << "D;" << jumpCondition(aCommand) << endl;
		outputFile << "D=0" << endl;               
		outputFile << "@END" << labelCounter << endl;
		outputFile << "0;JMP" << endl;          
		outputFile << "(TRUE" << labelCounter << ")" << endl;
		outputFile << "D=-1" << endl;              
		outputFile << "(END" << labelCounter << ")" << endl;
		labelCounter++;
	}

	string jumpCondition(const string& aCommand) {
		if (aCommand == "eq") {
			return "JEQ";
		}
		else if (aCommand == "lt") {
			return "JLT";
		}
		else { 
			return "JGT";
		}
	}

	void popSegment(const string& segment, const string& index) {
		outputFile << "@" << index << endl;
		outputFile << "D=A" << endl;           
		outputFile << "@" << segment << endl;
		outputFile << "D=M+D" << endl;         
		outputFile << "@R13" << endl;  
		outputFile << "M=D" << endl;
		outputFile << "@SP" << endl;
		outputFile << "AM=M-1" << endl;
		outputFile << "D=M" << endl;
		outputFile << "@R13" << endl;  
		outputFile << "A=M" << endl;
		outputFile << "M=D" << endl;   
	}

};