#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <vector>
#include <stack>
#include <queue>
#include "Product.h"
#include "User.h"

class DataStructures {
private:
    std::vector<Product> productList;      // Main storage for products
    std::stack<Product> deletedProducts;   // Stack for deleted products (recycle bin)
    std::queue<Product> orderQueue;        // Queue for order processing
    std::vector<User> userList;            // Storage for users

public:
    DataStructures();
    
    // Product management
    void addProduct(const Product& product);
    void removeProduct(int id);
    void restoreProduct();  // Restore last deleted product from stack
    void viewAllProducts() const;
    std::vector<Product>& getProductList();
    const std::vector<Product>& getProductList() const;
    
    // Order management (Queue)
    void addToOrderQueue(const Product& product);
    void processNextOrder();
    void viewOrderQueue() const;
    
    // User management
    void addUser(const User& user);
    void viewAllUsers() const;
    std::vector<User>& getUserList();
    const std::vector<User>& getUserList() const;
    
    // Recycle bin
    void viewRecycleBin() const;
    int getDeletedCount() const;
};

#endif