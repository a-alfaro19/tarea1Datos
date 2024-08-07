//
// Created by andres on 8/6/24.
//

#include "PagedArray.h"

PagedArray::PagedArray(const string& filePath)
: binFile(filePath, ios::binary | ios::in | ios::out), pageFaults(0), pageHits(0) {
    if (!binFile) {
        throw runtime_error("Cannot open file");
    }

    // Load the first 4 pages into the page table
    for (int i = 0; i < NUM_PAGES; i++) {
        Page page;
        loadPage(i, page);
        pageTable[i] = page;
        lruList.push_front(i);
    }
}

PagedArray::~PagedArray() {
    for (auto& entry : pageTable) {
        if (entry.second.dirty) {
            writePage(entry.second);
        }
    }

    if (binFile.is_open()) {
        binFile.close();
    }
}

int &PagedArray::operator[](const int index) {
    const int pageIndex = index / PAGE_SIZE;
    const int offset = index % PAGE_SIZE;

    if (pageTable.find(pageIndex) != pageTable.end()) { // If the page is in the page table
        pageHits++;
        updateLRU(pageIndex);
        pageTable[pageIndex].dirty = true;
        return pageTable[pageIndex].data[offset];
    }

    pageFaults++;
    if (pageTable.size() >= NUM_PAGES) { // If the page table is full, remove the least recently used page
        const int lruPageIndex = lruList.back();
        lruList.pop_back();
        if (pageTable[lruPageIndex].dirty) {
            writePage(pageTable[lruPageIndex]);
        }
        pageTable.erase(lruPageIndex);
    }

    Page newPage;
    loadPage(pageIndex, newPage);
    pageTable[pageIndex] = newPage;
    updateLRU(pageIndex);
    pageTable[pageIndex].dirty = true;
    return pageTable[pageIndex].data[offset];
}

streamsize PagedArray::getFileSize() {
    binFile.seekg(0, ios::end);
    return binFile.tellg();
}

int PagedArray::getPageFaults() const {
    return pageFaults;
}

int PagedArray::getPageHits() const {
    return pageHits;
}

void PagedArray::loadPage(const int pageIndex, Page& targetPage) {
    targetPage.index = pageIndex;
    targetPage.dirty = false;

    const auto offset = static_cast<streamoff>(pageIndex * PAGE_SIZE * sizeof(int));

    binFile.seekg(offset, ios::beg);

    binFile.read(reinterpret_cast<char*>(targetPage.data), PAGE_SIZE * sizeof(int));

    if (binFile.fail()) {
        throw runtime_error("Error reading file");
    }
}

void PagedArray::writePage(Page& page) {
    const auto offset = static_cast<streamoff>(page.index * PAGE_SIZE * sizeof(int));

    binFile.seekp(offset, ios::beg);
    binFile.write(reinterpret_cast<char*>(page.data), PAGE_SIZE * sizeof(int));
    page.dirty = false;

    if (binFile.fail()) {
        throw runtime_error("Error writing to file");
    }
}

void PagedArray::updateLRU(const int pageIndex) {
    lruList.remove(pageIndex);
    lruList.push_front(pageIndex);
}