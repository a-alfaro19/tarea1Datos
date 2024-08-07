//
// Created by andres on 8/6/24.
//

#ifndef SORTER_H
#define SORTER_H

#include <string>
#include <functional>
#include "PagedArray.h"

using namespace std;

class Sorter {
public:
    /**
     * Sort the contents of a file using the specified algorithm
     * @param inputPath The path of the input file
     * @param outputPath The path of the output file
     * @param alg The algorithm to be used
     */
    void sortFile(const string& inputPath, const string& outputPath, const string& alg);

private:
    enum Algoritm { QUICKSORT, INSERTIONSORT, BUBBLESORT, INVALID };

    /**
     * Parse the algorithm string and return the corresponding enum value
     * @param algoritm The algorithm string
     * @return The corresponding enum value
     */
    Algoritm parseAlgoritm(const string& algoritm);

    string algoritmToString(const Algoritm algoritm);

    /**
    * Sort the array using the quicksort algorithm
    * @param pagedArray The array to be sorted
    * @param low The lower bound of the array
    * @param high The upper bound of the array
    */
    void quicksort(PagedArray& pagedArray, int low, int high);

    /**
    * Partition the array and return the pivot index
    * @param pageArray The array to be partitioned
    * @param low The lower bound of the array
    * @param high The upper bound of the array
    * @return The pivot index
    */
    int partition(PagedArray& pageArray, int low, int high);

    void parallelQuicksort(PagedArray& pagedArray, int low, int high, int depth);

    /**
     * Sort the array using the insertion sort algorithm
     * @param pagedArray The array to be sorted
     * @param size The size of the array
     */
    void insertionsort(PagedArray& pagedArray, int size);

    /**
     * Sort the array using the bubble sort algorithm
     * @param pagedArray The array to be sorted
     * @param size The size of the array
     */
    void bubbleSort(PagedArray& pagedArray, int size);

    /**
    * Copy the contents of a file to another file
    * @param inputFilePath The path of the input file
    * @param outputFilePath The path of the output file
    */
    void copyFile(const string& inputFilePath, const string& outputFilePath);

    /**
    * Create a text file with the results of the sorting
    * @param inputFilePath The path of the input file
    * @param outputFilePath The path of the output file
    */
    void createTextFile(const string& inputFilePath, const string& outputFilePath);

    /**
     * Change the extension of a file to .txt
     * @param filePath The path of the file
     * @return The path of the file with the .txt extension
     */
    string changeExtensionToTxt(const string& filePath);

    /**
     * Measure the time it takes to execute a function
     * @param func The function to be executed
     * @return The time it took to execute the function
     */
    double measureTime(const function<void()>& func);

    /**
     * Show a report with the results of the sorting
     * @param elapsedTime The time it took to sort the file
     * @param algorithm The algorithm used to sort the file
     * @param pageFaults The number of page faults that occurred
     * @param pageHits The number of page hits that occurred
     */
    void showReport(double elapsedTime, const string& algorithm, int pageFaults, int pageHits);
};



#endif //SORTER_H
