#include "Algorithms.h"
#include <iostream>
#include <algorithm>
#include <cctype>

int Algorithms::linearSearch(const std::vector<Product>& products, const std::string& name) {
    std::string searchLower = name;
    std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
    
    for (size_t i = 0; i < products.size(); i++) {
        std::string productLower = products[i].getName();
        std::transform(productLower.begin(), productLower.end(), productLower.begin(), ::tolower);
        if (productLower.find(searchLower) != std::string::npos && !products[i].getIsDeleted()) {
            return i;
        }
    }
    return -1;
}

int Algorithms::binarySearch(std::vector<Product>& products, const std::string& name) {
    // First sort by name (for binary search)
    std::sort(products.begin(), products.end(), 
        [](const Product& a, const Product& b) {
            return a.getName() < b.getName();
        });
    
    int left = 0, right = products.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (products[mid].getName() == name && !products[mid].getIsDeleted()) {
            return mid;
        }
        if (products[mid].getName() < name) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

std::vector<Product> Algorithms::searchByCategory(const std::vector<Product>& products, 
                                                     const std::string& category) {
    std::vector<Product> results;
    std::string categoryLower = category;
    std::transform(categoryLower.begin(), categoryLower.end(), categoryLower.begin(), ::tolower);
    
    for (const auto& product : products) {
        std::string prodCategory = product.getCategory();
        std::transform(prodCategory.begin(), prodCategory.end(), prodCategory.begin(), ::tolower);
        if (prodCategory == categoryLower && !product.getIsDeleted()) {
            results.push_back(product);
        }
    }
    return results;
}

std::vector<Product> Algorithms::searchByPriceRange(const std::vector<Product>& products,
                                                      double minPrice, double maxPrice) {
    std::vector<Product> results;
    for (const auto& product : products) {
        if (product.getPrice() >= minPrice && product.getPrice() <= maxPrice && 
            !product.getIsDeleted()) {
            results.push_back(product);
        }
    }
    return results;
}

void Algorithms::bubbleSort(std::vector<Product>& products, bool ascending) {
    int n = products.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            bool condition = ascending ? (products[j] > products[j + 1]) 
                                       : (products[j] < products[j + 1]);
            if (condition && !products[j].getIsDeleted() && !products[j+1].getIsDeleted()) {
                swap(products[j], products[j + 1]);
            }
        }
    }
    std::cout << "Products sorted using Bubble Sort " 
              << (ascending ? "(Ascending)" : "(Descending)") << "\n";
}

void Algorithms::quickSort(std::vector<Product>& products, int low, int high, bool ascending) {
    if (low < high) {
        int pi = partition(products, low, high, ascending);
        quickSort(products, low, pi - 1, ascending);
        quickSort(products, pi + 1, high, ascending);
    }
}

int Algorithms::partition(std::vector<Product>& products, int low, int high, bool ascending) {
    Product pivot = products[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (!products[j].getIsDeleted()) {
            bool condition = ascending ? (products[j] < pivot) : (products[j] > pivot);
            if (condition) {
                i++;
                swap(products[i], products[j]);
            }
        }
    }
    swap(products[i + 1], products[high]);
    return i + 1;
}

void Algorithms::selectionSort(std::vector<Product>& products, bool ascending) {
    int n = products.size();
    for (int i = 0; i < n - 1; i++) {
        int extremeIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (!products[j].getIsDeleted()) {
                bool condition = ascending ? (products[j] < products[extremeIdx]) 
                                           : (products[j] > products[extremeIdx]);
                if (condition) {
                    extremeIdx = j;
                }
            }
        }
        if (extremeIdx != i && !products[i].getIsDeleted()) {
            swap(products[i], products[extremeIdx]);
        }
    }
}

void Algorithms::insertionSort(std::vector<Product>& products, bool ascending) {
    int n = products.size();
    for (int i = 1; i < n; i++) {
        Product key = products[i];
        int j = i - 1;
        
        while (j >= 0 && !products[j].getIsDeleted()) {
            bool condition = ascending ? (products[j] > key) : (products[j] < key);
            if (condition) {
                products[j + 1] = products[j];
                j--;
            } else {
                break;
            }
        }
        products[j + 1] = key;
    }
}

void Algorithms::swap(Product& a, Product& b) {
    Product temp = a;
    a = b;
    b = temp;
}

void Algorithms::displaySearchResults(const std::vector<Product>& results) {
    if (results.empty()) {
        std::cout << "No products found.\n";
        return;
    }
    
    std::cout << "\n=== Search Results ===\n";
    std::cout << "Found " << results.size() << " product(s):\n";
    for (const auto& product : results) {
        product.display();
    }
}