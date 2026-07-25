#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include "Product.h"

class Algorithms {
public:
    // Searching algorithms
    static int linearSearch(const std::vector<Product>& products, const std::string& name);
    static int binarySearch(std::vector<Product>& products, const std::string& name);
    static std::vector<Product> searchByCategory(const std::vector<Product>& products, 
                                                   const std::string& category);
    static std::vector<Product> searchByPriceRange(const std::vector<Product>& products,
                                                     double minPrice, double maxPrice);
    
    // Sorting algorithms
    static void bubbleSort(std::vector<Product>& products, bool ascending = true);
    static void quickSort(std::vector<Product>& products, int low, int high, bool ascending = true);
    static void selectionSort(std::vector<Product>& products, bool ascending = true);
    static void insertionSort(std::vector<Product>& products, bool ascending = true);
    
    // Helper
    static void displaySearchResults(const std::vector<Product>& results);
    
private:
    static int partition(std::vector<Product>& products, int low, int high, bool ascending);
    static void swap(Product& a, Product& b);
};

#endif