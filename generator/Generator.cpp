//
// Created by andres on 8/6/24.
//

#include "Generator.h"
#include <iostream>
#include <fstream>
#include <thread>

Generator::SizeOption Generator::parseSizeOption(const string& size) {
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

void Generator::generateRandomData(vector<int>& data, const size_t start, const size_t end) {
    random_device randomDevice;
    mt19937 genenerator(randomDevice());
    uniform_int_distribution<> distribution(0, 100);

    for (size_t i = start; i < end; ++i) {
        data[i] = distribution(genenerator);
    }
}

void Generator::writeFile(const string &output, const vector<int>& data) {
    ofstream ofstream(output, ios::binary);

    if (!ofstream) {
        cerr << "Error al abrir el archivo para escribir." << endl;
        return;
    }

    ofstream.write(reinterpret_cast<const char*>(data.data()), static_cast<streamsize>(data.size() * sizeof(int)));
    ofstream.close();

    if (!ofstream.good()) {
        cerr << "Error occurrio al escribir archivo." << endl;

    } else {
        cout << "Archivo creado con éxito: " << output << endl;
    }
}

void Generator::generateBinFile(const string& size, const string& output) {
    // Calculate num of integers
    const size_t fileSize = getFileSize(parseSizeOption(size));
    const size_t numIntegers = fileSize / sizeof(int);

    // Multi threading
    const size_t numThreads = thread::hardware_concurrency();
    vector<thread> threads;
    const size_t chunkSize = numIntegers / numThreads;

    // Data to write
    vector<int> data(numIntegers);

    // Generate random data
    for(size_t i = 0; i < numThreads; ++i) {
        size_t startIdx = i * chunkSize;
        size_t endIdx = (i == numThreads - 1) ? numIntegers : startIdx + chunkSize;
        threads.emplace_back(generateRandomData, ref(data), startIdx, endIdx);
    }

    for(auto& thread : threads) {
        thread.join();
    }

    // Write file
    writeFile(output, data);
}