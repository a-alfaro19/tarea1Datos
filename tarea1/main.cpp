#include <unordered_map>

#include "Generator.h"

/**
 * Parse the user params into a unordered map
 * @param argc Amount of arguments
 * @param argv Arguments inserted by the user
 * @return A unordered map with the user arguments
 */
unordered_map<string, string> parseArgs(const int argc, char* argv[]) {
    unordered_map<string, string> args;

    for (int i = 1; i < argc -1; i += 2) {
        const string argName = argv[i];
        const string argValue = argv[i+1];
        args[argName] = argValue;
    }
    return args;
}

int main(const int argc, char* argv[]) {
    unordered_map<string, string> args = parseArgs(argc, argv);

    const string sizeInput = args["-size"];
    const string outputInput = args["-output"];

    GENERATOR::Generator::generateBinFile(sizeInput, outputInput);

    return 0;
}
