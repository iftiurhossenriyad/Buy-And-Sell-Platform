#ifndef PLATFORM_H
#define PLATFORM_H

#include "DataStructures.h"
#include "Algorithms.h"
#include "Database.h"
#include <map>

class Platform {
private:
    DataStructures data;
    Database db;
    int nextProductId;
    int nextUserId;
    int currentUserId;  // Current logged-in user
    bool isAdmin;
    
public:
    Platform();
    ~Platform();
    
    // Authentication
    void login(bool adminLogin = false);
    void registerUser();
    void logout();
    bool authenticateUser(int userId, const std::string& password);
    
    // Main menus
    void showMainMenu();
    void showUserMenu();
    void showAdminMenu();
    
    // Product operations
    void addProduct();
    void viewProducts();
    void searchProduct();
    void sortProducts();
    void deleteProduct();
    void restoreProduct();
    void viewRecycleBin();
    
    // User operations
    void addUser();
    void viewUsers();
    void viewUserProfile();
    void updateUserInfo();
    
    // Admin operations
    void viewSalesReport();
    void manageUsers();
    void manageProducts();
    
    // Database operations
    void saveData();
    void loadData();
    void createBackup();
    void restoreBackup();
    
private:
    // Helper methods
    void clearScreen() const;
    void waitForEnter() const;
    void displayHeader(const std::string& title) const;
    int generateProductId();
    int generateUserId();
    std::string getInput(const std::string& prompt) const;
    double getDoubleInput(const std::string& prompt) const;
    int getIntInput(const std::string& prompt) const;
};

#endif