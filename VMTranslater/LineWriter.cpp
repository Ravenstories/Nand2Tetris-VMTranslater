#include <iostream>
#include <fstream>
#include <map>
#include <bitset>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class LineWriter {
public:
	LineWriter(std::ofstream& output) : outputFile(output), labelCounter(0) {}

	void writeArithmetic(vector<string> tokens)
	{
		string aCommand = tokens[0];

		outputFile << "@SP" << endl;
		outputFile << "AM=M-1" << endl;

		if (aCommand == "neg") {
			outputFile << "M=-M" << endl;
			return;
		}
		if (aCommand == "not") {
			outputFile << "M=!M" << endl;
			return;
		}

		outputFile << "D=M" << endl;
		outputFile << "A=A-1" << endl;

		if (aCommand == "add") {
			outputFile << "M=M+D" << endl;
		}
		else if (aCommand == "sub") {
			outputFile << "M=M-D" << endl;
		}
		else if (aCommand == "and") {
			outputFile << "M=M&D" << endl;
		}
		else if (aCommand == "or") {
			outputFile << "M=M|D" << endl;
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
			if (segment == "constant")
			{
				outputFile << "@" << value << endl;
				outputFile << "D=A" << endl;
			}
			outputFile << "@SP" << std::endl;
			outputFile << "A=M" << std::endl;
			outputFile << "M=D" << std::endl;
			outputFile << "@SP" << std::endl;
			outputFile << "M=M+1" << std::endl;

		}
		else if (command == "pop")
		{
			if (segment == "local")
			{
				popSegment("LCL", value);
			}
			else if (segment == "argument")
			{
				popSegment("ARG", value);
			}
			else if (segment == "this")
			{
				popSegment("THIS", value);
			}
			else if (segment == "that")
			{
				popSegment("THAT", value);
			}
			else if (segment == "temp")
			{
				popSegment("R5", value);
			}
			else if (segment == "pointer")
			{
				popSegment("R3", value);
			}
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
		string trueLabel = "TRUE" + to_string(labelCounter);
		string falseLabel = "FALSE" + to_string(labelCounter);
		string continueLabel = "CONTINUE" + to_string(labelCounter);

		outputFile << "D=M-D" << endl;

		outputFile << "@" << falseLabel << endl;
		outputFile << "D;" << jumpCondition(aCommand) << endl;
		outputFile << "@SP" << endl;
		outputFile << "A=M-1" << endl;
		outputFile << "M=-1" << endl;

		outputFile << "@" << continueLabel << endl;
		outputFile << "0;JMP" << endl;

		outputFile << "(" << falseLabel << ")" << endl;
		outputFile << "@SP" << endl;
		outputFile << "A=M-1" << endl;
		outputFile << "M=0" << endl;
		outputFile << "(" << continueLabel << ")" << endl;

		labelCounter++; // Increment the label counter
	}

	string jumpCondition(const string& aCommand) {
		if (aCommand == "eq") {
			return "JNE";
		}
		else if (aCommand == "lt") {
			return "JGE";
		}
		else {
			return "JLE";
		}
	}

	void popSegment(const string& segment, const string& index) {
		outputFile << "@" << segment << endl;
		outputFile << "D=M" << endl;
		outputFile << "@" << index << endl;
		outputFile << "D=D+A" << endl;
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