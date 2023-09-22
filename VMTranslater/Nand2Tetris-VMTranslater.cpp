#include "VMTranslator.h"

using namespace std;

int main()
{
    // Open the input file
    string inputFileName = "input.txt";
    // Create the output file
    string outputFileName = "output.txt";

    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    VMTranslator translator(inputFile, outputFile);
    
    translator.translateVMCommand();

    inputFile.clear();
    inputFile.seekg(0);

    inputFile.close();
    outputFile.close();

    std::cout << "Assembly successfully assembled to " << outputFileName << endl;

    return 0;
}