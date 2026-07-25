#include "Database.h"
#include <fstream>
#include <sstream>
#include <iostream>

Database::Database(const std::string& filename) : filename(filename) {}

void Database::saveProducts(const std::vector<Product>& products) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file for writing.\n";
        return;
    }
    
    for (const auto& product : products) {
        file << getProductString(product) << "\n";
    }
    file.close();
    std::cout << "Products saved successfully.\n";
}

void Database::loadProducts(std::vector<Product>& products) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "No existing database found. Starting fresh.\n";
        return;
    }
    
    products.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            Product p = parseProductString(line);
            products.push_back(p);
        }
    }
    file.close();
    std::cout << "Loaded " << products.size() << " products from database.\n";
}

void Database::saveUsers(const std::vector<User>& users) {
    std::ofstream file("users.txt");
    if (!file.is_open()) {
        std::cout << "Error opening users file for writing.\n";
        return;
    }
    
    for (const auto& user : users) {
        file << getUserString(user) << "\n";
    }
    file.close();
    std::cout << "Users saved successfully.\n";
}

void Database::loadUsers(std::vector<User>& users) {
    std::ifstream file("users.txt");
    if (!file.is_open()) {
        std::cout << "No existing users database found.\n";
        return;
    }
    
    users.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            User u = parseUserString(line);
            users.push_back(u);
        }
    }
    file.close();
    std::cout << "Loaded " << users.size() << " users from database.\n";
}

std::string Database::getProductString(const Product& product) const {
    std::stringstream ss;
    ss << product.getId() << "|"
       << product.getName() << "|"
       << product.getPrice() << "|"
       << product.getCategory() << "|"
       << product.getSellerName() << "|"
       << (product.getIsDeleted() ? 1 : 0) << "|"
       << product.getAverageRating() << "|"
       << product.getTotalRatings() << "|"
       << product.getDescription();
    return ss.str();
}

Product Database::parseProductString(const std::string& line) const {
    std::stringstream ss(line);
    std::string idStr, name, priceStr, category, seller, deletedStr, ratingStr, totalStr, description;
    
    std::getline(ss, idStr, '|');
    std::getline(ss, name, '|');
    std::getline(ss, priceStr, '|');
    std::getline(ss, category, '|');
    std::getline(ss, seller, '|');
    
    // Handle optional fields (for backward compatibility with old format)
    bool deleted = false;
    double rating = 0.0;
    int totalRatings = 0;
    description = "";
    
    if (std::getline(ss, deletedStr, '|') && !deletedStr.empty()) {
        try {
            deleted = (deletedStr == "1");
            if (std::getline(ss, ratingStr, '|') && !ratingStr.empty()) {
                rating = std::stod(ratingStr);
                if (std::getline(ss, totalStr, '|') && !totalStr.empty()) {
                    totalRatings = std::stoi(totalStr);
                    std::getline(ss, description, '|');
                }
            }
        } catch (const std::exception&) {
            // Ignore parsing errors for optional fields
        }
    }
    
    try {
        int id = std::stoi(idStr);
        double price = std::stod(priceStr);
        
        Product product(id, name, price, category, seller);
        product.setIsDeleted(deleted);
        product.setAverageRating(rating);
        product.setTotalRatings(totalRatings);
        product.setDescription(description);
        return product;
    } catch (const std::exception&) {
        // Return empty product on parse error
        return Product();
    }
}

std::string Database::getUserString(const User& user) const {
    std::stringstream ss;
    ss << user.getId() << "|"
       << user.getName() << "|"
       << user.getPhoneNumber() << "|"
       << user.getPicturePath() << "|"
       << user.getAddress() << "|"
       << user.getEmail() << "|"
       << user.getPassword();
    return ss.str();
}

User Database::parseUserString(const std::string& line) const {
    std::stringstream ss(line);
    std::string idStr, name, phone, picture, address, email, password;
    
    std::getline(ss, idStr, '|');
    std::getline(ss, name, '|');
    std::getline(ss, phone, '|');
    std::getline(ss, picture, '|');
    std::getline(ss, address, '|');
    std::getline(ss, email, '|');
    
    // Handle optional password field (for backward compatibility)
    password = "password123";  // Default password if not found
    if (!std::getline(ss, password, '|')) {
        password = "password123";
    }
    if (password.empty()) {
        password = "password123";
    }
    
    try {
        int id = std::stoi(idStr);
        return User(id, name, phone, picture, address, email, password);
    } catch (const std::exception&) {
        // Return empty user on parse error
        return User();
    }
}

void Database::createBackup() {
    std::ifstream srcProducts(filename);
    std::ofstream dstProducts("backup_" + filename);
    if (srcProducts.is_open() && dstProducts.is_open()) {
        dstProducts << srcProducts.rdbuf();
    }

    std::ifstream srcUsers("users.txt");
    std::ofstream dstUsers("backup_users.txt");
    if (srcUsers.is_open() && dstUsers.is_open()) {
        dstUsers << srcUsers.rdbuf();
    }

    std::cout << "Backup created successfully.\n";
}

void Database::restoreBackup() {
    std::ifstream srcProducts("backup_" + filename);
    if (srcProducts.is_open()) {
        std::ofstream dstProducts(filename);
        dstProducts << srcProducts.rdbuf();
    } else {
        std::cout << "No product backup found.\n";
    }

    std::ifstream srcUsers("backup_users.txt");
    if (srcUsers.is_open()) {
        std::ofstream dstUsers("users.txt");
        dstUsers << srcUsers.rdbuf();
    } else {
        std::cout << "No user backup found.\n";
    }

    std::cout << "Backup restore completed.\n";
}