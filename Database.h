#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include "Product.h"
#include "User.h"

class Database {
private:
    std::string filename;
    
public:
    Database(const std::string& filename = "database.txt");
    
    // Save/Load Products
    void saveProducts(const std::vector<Product>& products);
    void loadProducts(std::vector<Product>& products);
    
    // Save/Load Users
    void saveUsers(const std::vector<User>& users);
    void loadUsers(std::vector<User>& users);
    
    // Backup
    void createBackup();
    void restoreBackup();
    
private:
    std::string getProductString(const Product& product) const;
    Product parseProductString(const std::string& line) const;
    std::string getUserString(const User& user) const;
    User parseUserString(const std::string& line) const;
};

#endif
