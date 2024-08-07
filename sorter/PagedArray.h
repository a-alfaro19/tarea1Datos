//
// Created by andres on 8/6/24.
//

#ifndef PAGEDARRAY_H
#define PAGEDARRAY_H

#include <list>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

class PagedArray {
public:
    /**
     * Constructor
     *
     * @param filePath The path to the binary file to be accessed.
     */
    PagedArray(const string& filePath);

    /**
     * Destructor
     */
    ~PagedArray();

    /**
     * Overloaded subscript operator to access and modify elements at a specified index.
     *
     * @param index The index of the element to be accessed.
     * @return A reference to the integer at the specified index.
     */
    int& operator[](int index);

    /**
    * Returns the size of the file in bytes.
    *
    * @return The size of the file in bytes.
    */
    streamsize getFileSize();

    /**
     * Returns the number of page faults that have occurred.
     *
     * @return The number of page faults.
     */
    int getPageFaults() const;

    /**
     * Returns the number of page hits that have occurred.
     *
     * @return The number of page hits.
     */
    int getPageHits() const;

    static const int PAGE_SIZE = 1024; // Size of a page
    static const int NUM_PAGES = 4; // Number of pages in the page table

private:
    /**
    * Represents a page in the PagedArray.
    */
    struct Page {
     int data[PAGE_SIZE]; // Data stored in the page
     int index;
     bool dirty; // Flag to indicate if the page has been modified
    };

    /**
     * Loads a page from the file into the specified Page object.
     *
     * @param pageIndex The index of the page to be loaded.
     * @param targetPage The Page object where the data will be loaded.
     */
    void loadPage(int pageIndex, Page& targetPage);

    /**
     * Writes the contents of a Page object to the file.
     *
     * @param page The Page object to be written to the file.
     */
    void writePage(Page& page);

    /**
     * Updates the Least Recently Used (LRU) list with the specified page index.
     *
     * @param pageIndex The index of the page to be updated in the LRU list.
     */
    void updateLRU(int pageIndex);

    fstream binFile; // Binary file stream
    unordered_map<int, Page> pageTable; // Page table
    list<int> lruList; // Least Recently Used list
    int pageFaults; // Number of page faults
    int pageHits; // Number of page hits
};



#endif //PAGEDARRAY_H
