#include "DataStructures.h"
#include <iostream>
#include <algorithm>

DataStructures::DataStructures() {
    // Initialize with some sample data
    productList.reserve(100);
    userList.reserve(50);
}

void DataStructures::addProduct(const Product& product) {
    productList.push_back(product);
    std::cout << "Product added successfully! ID: " << product.getId() << "\n";
}

void DataStructures::removeProduct(int id) {
    auto it = std::find_if(productList.begin(), productList.end(),
        [id](const Product& p) { return p.getId() == id && !p.getIsDeleted(); });
    
    if (it != productList.end()) {
        // Mark as deleted and push to stack
        it->setIsDeleted(true);
        deletedProducts.push(*it);
        std::cout << "Product moved to recycle bin.\n";
    } else {
        std::cout << "Product not found or already deleted.\n";
    }
}

void DataStructures::restoreProduct() {
    if (deletedProducts.empty()) {
        std::cout << "Recycle bin is empty.\n";
        return;
    }
    
    Product restored = deletedProducts.top();
    deletedProducts.pop();
    
    // Find and restore in product list
    auto it = std::find_if(productList.begin(), productList.end(),
        [restored](const Product& p) { return p.getId() == restored.getId(); });
    
    if (it != productList.end()) {
        it->setIsDeleted(false);
        std::cout << "Product restored: " << it->getName() << "\n";
    }
}

void DataStructures::viewAllProducts() const {
    std::cout << "\n=== All Products ===\n";
    bool found = false;
    for (const auto& product : productList) {
        if (!product.getIsDeleted()) {
            product.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No products available.\n";
    }
}

std::vector<Product>& DataStructures::getProductList() {
    return productList;
}

const std::vector<Product>& DataStructures::getProductList() const {
    return productList;
}

void DataStructures::addToOrderQueue(const Product& product) {
    orderQueue.push(product);
    std::cout << "Order added to queue: " << product.getName() << "\n";
}

void DataStructures::processNextOrder() {
    if (orderQueue.empty()) {
        std::cout << "No orders to process.\n";
        return;
    }
    
    Product order = orderQueue.front();
    orderQueue.pop();
    std::cout << "Processing order: " << order.getName() 
              << " (ID: " << order.getId() << ")\n";
}

void DataStructures::viewOrderQueue() const {
    if (orderQueue.empty()) {
        std::cout << "Order queue is empty.\n";
        return;
    }
    
    std::queue<Product> temp = orderQueue;
    std::cout << "\n=== Order Queue ===\n";
    int position = 1;
    while (!temp.empty()) {
        std::cout << position++ << ". ";
        temp.front().display();
        temp.pop();
    }
}

void DataStructures::addUser(const User& user) {
    userList.push_back(user);
    std::cout << "User added successfully!\n";
}

void DataStructures::viewAllUsers() const {
    std::cout << "\n=== All Users ===\n";
    if (userList.empty()) {
        std::cout << "No users registered.\n";
        return;
    }
    for (const auto& user : userList) {
        user.display();
    }
}

std::vector<User>& DataStructures::getUserList() {
    return userList;
}

const std::vector<User>& DataStructures::getUserList() const {
    return userList;
}

void DataStructures::viewRecycleBin() const {
    std::cout << "\n=== Recycle Bin ===\n";
    if (deletedProducts.empty()) {
        std::cout << "Recycle bin is empty.\n";
        return;
    }
    
    std::stack<Product> temp = deletedProducts;
    while (!temp.empty()) {
        temp.top().display();
        temp.pop();
    }
    std::cout << "Total deleted: " << deletedProducts.size() << "\n";
}

int DataStructures::getDeletedCount() const {
    return deletedProducts.size();
}