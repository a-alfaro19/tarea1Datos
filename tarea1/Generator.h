//
// Created by andres on 7/26/24.
//

#ifndef GENERATOR_H
#define GENERATOR_H
#include <string>
#include <random>
#include <iostream>
#include <fstream>

using namespace std;

namespace GENERATOR {

    enum SizeOption { SMALL, MEDIUM, LARGE, INVALID };

    /**
     * Parse the user size input into a SizeOption type,
     *
     * @param size User size input
     * @return Input SizeOption equivalent
     */
    static SizeOption parseSizeOption(const string& size);

    class Generator {

    private:
        /**
         * Converts the file SizeOption into his equivalent in bytes,
         *
         * @param size The select SizeOption
         * @return The file size in bytes
         */
        static size_t getFileSize(SizeOption size);

        /**
         * Generate a random number.
         *
         * @return A random integer
         */
        static int generateRandomInt();

        /**
         * Writes a given amount of Integers in a given file.
         *
         * @param ofstream Ofstream to write on the file
         * @param numInteger Num of integers to write in the file
         */
        static void writeFile(ofstream& ofstream, size_t numInteger);

    public:
        static void generateBinFile(const string& size, const string& output);

    };

} // GENERATOR

#endif //GENERATOR_H
