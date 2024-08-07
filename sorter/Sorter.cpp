//
// Created by andres on 8/6/24.
//

#include "Sorter.h"
#include <stdexcept>
#include <thread>
#include <fstream>
#include <iostream>

void Sorter::sortFile(const string& inputPath, const string& outputPath, const string& alg) {
    // Copy the file
    copyFile(inputPath, outputPath);

    // Parse the algorithm
    const Algoritm algoritm = parseAlgoritm(alg);

    // Create the PagedArray
    PagedArray* pagedArray = new PagedArray(outputPath);

    // Sort the file
    const streamsize fileSize = pagedArray->getFileSize();
    const size_t numIntegers = fileSize / sizeof(int);

    const double elapsedTime = measureTime([&]() {
        switch (algoritm) {
            case QUICKSORT:
                quicksort(*pagedArray, 0, numIntegers - 1);
                break;
            case INSERTIONSORT:
                insertionsort(*pagedArray, numIntegers);
                break;
            case BUBBLESORT:
                bubbleSort(*pagedArray, numIntegers);
                break;
            case INVALID:
                throw runtime_error("Invalid algorithm.");
        }
    });

    delete pagedArray;
    showReport(elapsedTime, algoritmToString(algoritm), pagedArray->getPageFaults(), pagedArray->getPageHits());

    // Create the text file
    const string txtFilePath = changeExtensionToTxt(outputPath);
    createTextFile(outputPath, txtFilePath);
}

Sorter::Algoritm Sorter::parseAlgoritm(const string &algoritm) {
    if (algoritm == "QS") return QUICKSORT;
    if (algoritm == "IS") return INSERTIONSORT;
    if (algoritm == "BS") return BUBBLESORT;
    return INVALID;
}

string Sorter::algoritmToString(const Algoritm algoritm) {
    switch (algoritm) {
        case QUICKSORT:
            return "Quicksort";
        case INSERTIONSORT:
            return "Insertion Sort";
        case BUBBLESORT:
            return "Bubble Sort";
        default:
            return "Invalid";
    }
}

void Sorter::quicksort(PagedArray &pagedArray, const int low, const int high) {
    if (low < high) {
        const int pivot = partition(pagedArray, low, high);
        quicksort(pagedArray, low, pivot - 1);
        quicksort(pagedArray, pivot + 1, high);
    }
}

int Sorter::partition(PagedArray& pageArray, const int low, const int high) {
    const int pivot = pageArray[high];
    int x = low - 1;

    for(int y = low; y <= high - 1; y++) {
        if (pageArray[y] < pivot) {
            x++;
            swap(pageArray[x], pageArray[y]);
        }
    }
    swap(pageArray[x + 1], pageArray[high]);
    return x + 1;
}

void Sorter::insertionsort(PagedArray &pagedArray, const int size) {
    for (int i = 1; i <= size; i++) {
        const int key = pagedArray[i];
        int j = i - 1;

        while (j >= 0 && pagedArray[j] > key) {
            pagedArray[j + 1] = pagedArray[j];
            j--;
        }
        pagedArray[j + 1] = key;
    }
}

void Sorter::bubbleSort(PagedArray &pagedArray, const int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (pagedArray[j] > pagedArray[j + 1]) {
                swap(pagedArray[j], pagedArray[j + 1]);
            }
        }
    }
}

void Sorter::copyFile(const string& inputFilePath, const string& outputFilePath) {
    ifstream inputFile(inputFilePath, ios::binary);
    if (!inputFile) {
        throw runtime_error("Cannot open input file.");
    }

    ofstream outputFile(outputFilePath, ios::binary);
    if (!outputFile) {
        throw runtime_error("Cannot open output file.");
    }

    outputFile << inputFile.rdbuf();
    if (!outputFile) {
        throw runtime_error("Error ocurred while copying the file.");
    }
}

void Sorter::createTextFile(const string& inputFilePath, const string& outputFilePath) {
    ifstream inputFile(inputFilePath, ios::binary);
    if (!inputFile) {
        throw runtime_error("Cannot open input file.");
    }

    ofstream textFile(outputFilePath);
    if (!textFile) {
        throw runtime_error("Cannot open text file.");
    }

    vector<int> integers;
    int number;
    while (inputFile.read(reinterpret_cast<char*>(&number), sizeof(int))) {
        integers.push_back(number);
    }

    for (const int& num : integers) {
        textFile << num << ", ";
    }

    inputFile.close();
    textFile.close();
}

string Sorter::changeExtensionToTxt(const string& filePath) {
    string txtFilePath = filePath;
    txtFilePath.replace(txtFilePath.end() - 3, txtFilePath.end(), "txt");
    return txtFilePath;
}

double Sorter::measureTime(const function<void()>& func) {
    const auto start = chrono::high_resolution_clock::now();
    func();
    const auto end = chrono::high_resolution_clock::now();
    const chrono::duration<double> duration = end - start;
    return duration.count();
}

void Sorter::showReport(const double elapsedTime, const string& algorithm, const int pageFaults, const int pageHits) {
    cout << "Time taken to sort the file: " << elapsedTime << " seconds." << endl;
    cout << "Algortim used: " << algorithm << endl;
    cout << "Page faults: " << pageFaults << endl;
    cout << "Page hits: " << pageHits << endl;
}

