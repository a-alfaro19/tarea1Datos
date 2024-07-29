//
// Created by andres on 7/26/24.
//

#include "Generator.h"


namespace GENERATOR {

    SizeOption parseSizeOption(const string& size) {
        if (size == "SMALL") return SMALL;
        if (size == "MEDIUM") return MEDIUM;
        if (size == "LARGE") return LARGE;
        return INVALID;
    }

    size_t Generator::getFileSize(const SizeOption size) {
        switch (size) {
            case SMALL: return 512 * 1024 * 1024;
            case MEDIUM: return 1024 * 1024 * 1024;
            case LARGE: return 2048 * 1024 * 1024;
            default: return 0;
        }
    }

    int Generator::generateRandomInt() {
        random_device randomDevice;
        mt19937 genenerator(randomDevice());
        uniform_int_distribution<> distribution;

        return distribution(genenerator);
    }

    void Generator::writeFile(ofstream& ofstream, const size_t numInteger) {
        for (size_t i = 0; i < numInteger; ++i) {
            int randomInt = generateRandomInt();
            ofstream.write(reinterpret_cast<const char*>(&randomInt), sizeof(randomInt));
        }
    }

    void Generator::generateBinFile(const string& size, const string& output) {
        const size_t fileSize = getFileSize(parseSizeOption(size));
        const size_t numIntegers = fileSize / sizeof(int);


        ofstream outputFile(output, ios::binary | ios::trunc);

        if (!outputFile) {
            std::cerr << "Error al abrir el archivo para escribir." << std::endl;
        }

        writeFile(outputFile, numIntegers);
        outputFile.close();

        if (!outputFile) {
            cerr << "Error al escribir en el archivo." << endl;
        } else {
            cout << "Archivo creado con éxito: " << output << endl;
        }
    }

} // GENERATOR