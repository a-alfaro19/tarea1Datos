//
// Created by andres on 8/6/24.
//

#ifndef GENERATOR_H
#define GENERATOR_H
#include <string>
#include <vector>
#include <random>

using namespace std;

class Generator {
public:
    /**
     * Generates a bin file of a givne size in a given path.
     *
     * @param size Size of the file.
     * @param output Output path of the generated file
     */
    static void generateBinFile(const string& size, const std::string& output);

private:
    enum SizeOption { SMALL, MEDIUM, LARGE, INVALID };

    /**
     * Parse the user size input into a SizeOption type,
     *
     * @param size User size input
     * @return Input SizeOption equivalent
     */
    static SizeOption parseSizeOption(const string& size);

    /**
     * Converts the file SizeOption into his equivalent in bytes,
     *
     * @param size The select SizeOption
     * @return The file size in bytes
     */
    static size_t getFileSize(SizeOption size);

    /**
     * Writes a given amount of Integers in a given file.
     *
     * @param output Output path of the file
     * @param data Data to write on file
     */
    static void writeFile(const string& output, const vector<int>& data);

    /**
     * Inserts random integers in a specific range of a given vector.
     *
     * @param data Vector where to insert the random integers
     * @param start Index of the vector where to start inserting integers
     * @param end Index og the vector where to stop inseting integers
     */
    static void generateRandomData(vector<int>& data, size_t start, size_t end);
};



#endif //GENERATOR_H
