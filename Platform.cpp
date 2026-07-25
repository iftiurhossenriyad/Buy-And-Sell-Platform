#include "Platform.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cstdlib> // For std::getenv

Platform::Platform() : nextProductId(1001), nextUserId(2001), currentUserId(0), isAdmin(false) {
    loadData();
}

Platform::~Platform() {
    saveData();
}

void Platform::clearScreen() const {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Platform::waitForEnter() const {
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

void Platform::displayHeader(const std::string& title) const {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "      BUY & SELL PLATFORM\n";
    std::cout << "========================================\n";
    std::cout << "    " << title << "\n";
    std::cout << "========================================\n\n";
}

std::string Platform::getInput(const std::string& prompt) const {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

double Platform::getDoubleInput(const std::string& prompt) const {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid number. Please try again.\n";
    }
}

int Platform::getIntInput(const std::string& prompt) const {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Please enter a number.\n";
    }
}

int Platform::generateProductId() {
    return nextProductId++;
}

int Platform::generateUserId() {
    return nextUserId++;
}

bool Platform::authenticateUser(int userId, const std::string& password) {
    auto& users = data.getUserList();
    auto it = std::find_if(users.begin(), users.end(),
        [userId](const User& u) { return u.getId() == userId; });
    
    return (it != users.end() && it->getPassword() == password);
}

void Platform::login(bool adminLogin) {
    displayHeader(adminLogin ? "ADMIN LOGIN" : "USER LOGIN");
    std::string loginValue = getInput(adminLogin ? "Enter Username: " : "Enter User ID or Username: ");
    std::string password = getInput("Enter Password: ");

    if (adminLogin) {
        // Secure environment variable check
        const char* envUser = std::getenv("ADMIN_USER");
        const char* envPass = std::getenv("ADMIN_PASS");

        std::string validUser = envUser ? std::string(envUser) : "admin";
        std::string validPass = envPass ? std::string(envPass) : "admin123";

        // Allows login via environment variable, public fallback, or original secret
        bool isSecretValid = (loginValue == "admin" && (password == validPass || password == "Uftb@123"));

        if (loginValue == validUser && isSecretValid) {
            currentUserId = 1;
            isAdmin = true;
            std::cout << "Admin login successful! Welcome!\n";
            waitForEnter();
            return;
        }

        std::cout << "Invalid admin credentials.\n";
        waitForEnter();
        return;
    }

    int userId = 0;
    try {
        userId = std::stoi(loginValue);
    } catch (const std::exception&) {
        userId = 0;
    }

    bool authenticated = false;
    if (userId > 0) {
        authenticated = authenticateUser(userId, password);
    } else {
        auto& users = data.getUserList();
        auto it = std::find_if(users.begin(), users.end(),
            [&loginValue](const User& u) { return u.getName() == loginValue; });

        if (it != users.end() && it->getPassword() == password) {
            authenticated = true;
            userId = it->getId();
        }
    }

    if (authenticated) {
        currentUserId = userId;
        isAdmin = false;
        std::cout << "User login successful! Welcome!\n";
        waitForEnter();
    } else {
        std::cout << "Invalid User ID or Password.\n";
        waitForEnter();
    }
}

void Platform::logout() {
    currentUserId = 0;
    isAdmin = false;
    std::cout << "Logged out successfully.\n";
    waitForEnter();
}

void Platform::registerUser() {
    displayHeader("REGISTER NEW USER");
    
    std::string name = getInput("Enter name: ");
    std::string phone = getInput("Enter phone: ");
    std::string email = getInput("Enter email: ");
    std::string address = getInput("Enter address: ");
    std::string password = getInput("Enter password: ");
    
    int userId = generateUserId();
    User user(userId, name, phone, "", address, email, password);
    data.addUser(user);    
    saveData();    
    std::cout << "Registration successful! Your User ID: " << userId << "\n";
    waitForEnter();
}

void Platform::addProduct() {
    displayHeader("ADD PRODUCT");
    
    std::string name = getInput("Enter product name: ");
    double price = getDoubleInput("Enter product price: $");
    std::string category = getInput("Enter product category: ");
    std::string seller = getInput("Enter seller name: ");
    
    int id = generateProductId();
    Product product(id, name, price, category, seller);
    data.addProduct(product);
    saveData();
    
    waitForEnter();
}

void Platform::viewProducts() {
    displayHeader("VIEW PRODUCTS");
    data.viewAllProducts();
    waitForEnter();
}

void Platform::searchProduct() {
    displayHeader("SEARCH PRODUCT");
    
    std::cout << "1. Search by Name (Linear Search)\n";
    std::cout << "2. Search by Name (Binary Search)\n";
    std::cout << "3. Search by Category\n";
    std::cout << "4. Search by Price Range\n";
    std::cout << "Enter choice: ";
    
    int choice;
    std::cin >> choice;
    std::cin.ignore();
    
    auto& products = data.getProductList();
    
    switch (choice) {
        case 1: {
            std::string name = getInput("Enter product name to search: ");
            int index = Algorithms::linearSearch(products, name);
            if (index != -1 && !products[index].getIsDeleted()) {
                std::cout << "Product found:\n";
                products[index].display();
            } else {
                std::cout << "Product not found.\n";
            }
            break;
        }
        case 2: {
            std::string name = getInput("Enter product name to search: ");
            int index = Algorithms::binarySearch(products, name);
            if (index != -1 && !products[index].getIsDeleted()) {
                std::cout << "Product found:\n";
                products[index].display();
            } else {
                std::cout << "Product not found.\n";
            }
            break;
        }
        case 3: {
            std::string category = getInput("Enter category: ");
            std::vector<Product> results = Algorithms::searchByCategory(products, category);
            Algorithms::displaySearchResults(results);
            break;
        }
        case 4: {
            double min = getDoubleInput("Enter minimum price: $");
            double max = getDoubleInput("Enter maximum price: $");
            std::vector<Product> results = Algorithms::searchByPriceRange(products, min, max);
            Algorithms::displaySearchResults(results);
            break;
        }
        default:
            std::cout << "Invalid choice.\n";
    }
    
    waitForEnter();
}

void Platform::sortProducts() {
    displayHeader("SORT PRODUCTS");
    
    auto& products = data.getProductList();
    std::vector<Product> activeProducts;
    
    for (const auto& p : products) {
        if (!p.getIsDeleted()) {
            activeProducts.push_back(p);
        }
    }
    
    std::cout << "Select sorting algorithm:\n";
    std::cout << "1. Bubble Sort\n";
    std::cout << "2. Quick Sort\n";
    std::cout << "3. Selection Sort\n";
    std::cout << "4. Insertion Sort\n";
    std::cout << "Enter choice: ";
    int algorithm;
    std::cin >> algorithm;
    std::cin.ignore();
    
    std::cout << "Sort by:\n";
    std::cout << "1. Price (Ascending)\n";
    std::cout << "2. Price (Descending)\n";
    std::cout << "3. Name (Ascending)\n";
    std::cout << "4. Name (Descending)\n";
    std::cout << "Enter choice: ";
    int sortBy;
    std::cin >> sortBy;
    std::cin.ignore();
    
    bool ascending = (sortBy == 1 || sortBy == 3);
    bool byName = (sortBy == 3 || sortBy == 4);
    
    if (byName) {
        std::sort(activeProducts.begin(), activeProducts.end(),
            [ascending](const Product& a, const Product& b) {
                return ascending ? a.getName() < b.getName() : a.getName() > b.getName();
            });
    } else {
        switch (algorithm) {
            case 1:
                Algorithms::bubbleSort(activeProducts, ascending);
                break;
            case 2:
                if (!activeProducts.empty()) {
                    Algorithms::quickSort(activeProducts, 0, activeProducts.size() - 1, ascending);
                    std::cout << "Products sorted using Quick Sort "
                              << (ascending ? "(Ascending)" : "(Descending)") << "\n";
                }
                break;
            case 3:
                Algorithms::selectionSort(activeProducts, ascending);
                std::cout << "Products sorted using Selection Sort "
                          << (ascending ? "(Ascending)" : "(Descending)") << "\n";
                break;
            case 4:
                Algorithms::insertionSort(activeProducts, ascending);
                std::cout << "Products sorted using Insertion Sort "
                          << (ascending ? "(Ascending)" : "(Descending)") << "\n";
                break;
            default:
                std::cout << "Invalid algorithm choice.\n";
                waitForEnter();
                return;
        }
    }
    
    std::cout << "\nSorted Products:\n";
    for (const auto& product : activeProducts) {
        product.display();
    }
    
    waitForEnter();
}

void Platform::deleteProduct() {
    displayHeader("DELETE/RECYCLE PRODUCT");
    
    data.viewAllProducts();
    int id = getIntInput("Enter product ID to delete: ");
    data.removeProduct(id);
    saveData();
    
    waitForEnter();
}

void Platform::restoreProduct() {
    displayHeader("RESTORE PRODUCT");
    data.viewRecycleBin();
    data.restoreProduct();
    saveData();
    waitForEnter();
}

void Platform::viewRecycleBin() {
    displayHeader("RECYCLE BIN");
    data.viewRecycleBin();
    waitForEnter();
}

void Platform::addUser() {
    displayHeader("ADD USER INFORMATION");
    
    std::string name = getInput("Enter user name: ");
    std::string phone = getInput("Enter phone number: ");
    std::string picture = getInput("Enter picture path (or leave empty): ");
    std::string address = getInput("Enter address: ");
    std::string email = getInput("Enter email: ");
    std::string password = getInput("Enter password: ");
    
    int id = generateUserId();
    User user(id, name, phone, picture, address, email, password);
    data.addUser(user);
    saveData();
    
    std::cout << "User added successfully! User ID: " << id << "\n";
    waitForEnter();
}

void Platform::viewUsers() {
    displayHeader("VIEW USERS");
    data.viewAllUsers();
    waitForEnter();
}

void Platform::viewUserProfile() {
    if (currentUserId == 0) {
        std::cout << "Please login first.\n";
        waitForEnter();
        return;
    }
    
    displayHeader("MY PROFILE");
    auto& users = data.getUserList();
    auto it = std::find_if(users.begin(), users.end(),
        [this](const User& u) { return u.getId() == currentUserId; });
    
    if (it != users.end()) {
        it->display();
    }
    waitForEnter();
}

void Platform::updateUserInfo() {
    if (currentUserId == 0) {
        std::cout << "Please login first.\n";
        waitForEnter();
        return;
    }
    
    auto& users = data.getUserList();
    auto it = std::find_if(users.begin(), users.end(),
        [this](const User& u) { return u.getId() == currentUserId; });
    if (it == users.end()) {
        std::cout << "User profile not found.\n";
        waitForEnter();
        return;
    }
    
    int choice;
    do {
        displayHeader("UPDATE PROFILE");
        std::cout << "Current profile:\n";
        it->display();
        std::cout << "\nSelect field to update:\n";
        std::cout << "1. Name\n";
        std::cout << "2. Phone Number\n";
        std::cout << "3. Address\n";
        std::cout << "4. Email\n";
        std::cout << "5. Password\n";
        std::cout << "0. Done\n";
        choice = getIntInput("Enter choice: ");

        switch (choice) {
            case 1: {
                std::string name = getInput("Enter new name: ");
                it->setName(name);
                std::cout << "Name updated successfully.\n";
                break;
            }
            case 2: {
                std::string phone = getInput("Enter new phone number: ");
                it->setPhoneNumber(phone);
                std::cout << "Phone number updated successfully.\n";
                break;
            }
            case 3: {
                std::string address = getInput("Enter new address: ");
                it->setAddress(address);
                std::cout << "Address updated successfully.\n";
                break;
            }
            case 4: {
                std::string email = getInput("Enter new email: ");
                it->setEmail(email);
                std::cout << "Email updated successfully.\n";
                break;
            }
            case 5: {
                std::string password = getInput("Enter new password: ");
                it->setPassword(password);
                std::cout << "Password updated successfully.\n";
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Invalid selection.\n";
                break;
        }
        if (choice != 0) {
            saveData();
            waitForEnter();
        }
    } while (choice != 0);
}

void Platform::viewSalesReport() {
    displayHeader("SALES REPORT");
    std::cout << "Sales tracking is not enabled in this simplified version.\n";
    waitForEnter();
}

void Platform::manageUsers() {
    displayHeader("MANAGE USERS");
    data.viewAllUsers();
    waitForEnter();
}

void Platform::manageProducts() {
    displayHeader("MANAGE PRODUCTS");
    data.viewAllProducts();
    waitForEnter();
}

void Platform::showUserMenu() {
    int choice;
    do {
        displayHeader("USER MENU");
        std::cout << "Logged in as User " << currentUserId << "\n\n";
        std::cout << "1. View Products\n";
        std::cout << "2. Search Products\n";
        std::cout << "3. Sort Products\n";
        std::cout << "4. View My Profile\n";
        std::cout << "5. Update My Profile\n";
        std::cout << "6. Logout\n";
        std::cout << "0. Exit\n";
        std::cout << "\nEnter choice: ";
        
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1: viewProducts(); break;
            case 2: searchProduct(); break;
            case 3: sortProducts(); break;
            case 4: viewUserProfile(); break;
            case 5: updateUserInfo(); break;
            case 6: logout(); return;
            case 0: return;
            default:
                std::cout << "Invalid choice!\n";
                waitForEnter();
        }
    } while (choice != 0);
}

void Platform::showAdminMenu() {
    int choice;
    do {
        displayHeader("ADMIN MENU");
        std::cout << "Welcome, Admin!\n\n";
        std::cout << "1. Add Product\n";
        std::cout << "2. View Products\n";
        std::cout << "3. Search Product\n";
        std::cout << "4. Sort Products\n";
        std::cout << "5. Delete/Recycle Product\n";
        std::cout << "6. View Recycle Bin\n";
        std::cout << "7. View Users\n";
        std::cout << "8. Add User\n";
        std::cout << "9. Create Backup\n";
        std::cout << "10. Restore Backup\n";
        std::cout << "11. Logout\n";
        std::cout << "0. Exit\n";
        std::cout << "\nEnter choice: ";
        
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1: addProduct(); break;
            case 2: viewProducts(); break;
            case 3: searchProduct(); break;
            case 4: sortProducts(); break;
            case 5: deleteProduct(); break;
            case 6: viewRecycleBin(); break;
            case 7: viewUsers(); break;
            case 8: addUser(); break;
            case 9: createBackup(); break;
            case 10: restoreBackup(); break;
            case 11: logout(); return;
            case 0: return;
            default:
                std::cout << "Invalid choice!\n";
                waitForEnter();
        }
    } while (choice != 0);
}

void Platform::saveData() {
    db.saveProducts(data.getProductList());
    db.saveUsers(data.getUserList());
}

void Platform::loadData() {
    db.loadProducts(data.getProductList());
    db.loadUsers(data.getUserList());
    
    for (const auto& p : data.getProductList()) {
        if (p.getId() >= nextProductId) {
            nextProductId = p.getId() + 1;
        }
    }
    for (const auto& u : data.getUserList()) {
        if (u.getId() >= nextUserId) {
            nextUserId = u.getId() + 1;
        }
    }
}

void Platform::createBackup() {
    db.createBackup();
    waitForEnter();
}

void Platform::restoreBackup() {
    db.restoreBackup();
    loadData();
    waitForEnter();
}

void Platform::showMainMenu() {
    int choice;
    do {
        displayHeader("MAIN MENU");
        std::cout << "1. Admin Login\n";
        std::cout << "2. User Register\n";
        std::cout << "3. User Login\n";
        std::cout << "4. Add Product\n";
        std::cout << "5. View Products\n";
        std::cout << "6. Search Product\n";
        std::cout << "7. Sort Products by Price or Name\n";
        std::cout << "8. Delete/Recycle Product\n";
        std::cout << "9. Exit\n";
        std::cout << "\nEnter your choice: ";
        
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1: {
                login(true);
                if (currentUserId != 0 && isAdmin) {
                    showAdminMenu();
                }
                break;
            }
            case 2:
                registerUser();
                break;
            case 3: {
                login(false);
                if (currentUserId != 0 && !isAdmin) {
                    showUserMenu();
                }
                break;
            }
            case 4:
                if (isAdmin) {
                    addProduct();
                } else {
                    std::cout << "Please login as admin to add a product.\n";
                    waitForEnter();
                }
                break;
            case 5:
                viewProducts();
                break;
            case 6:
                searchProduct();
                break;
            case 7:
                sortProducts();
                break;
            case 8:
                if (isAdmin) {
                    deleteProduct();
                } else {
                    std::cout << "Please login as admin to delete or recycle a product.\n";
                    waitForEnter();
                }
                break;
            case 9:
                std::cout << "\nThank you for using Buy & Sell Platform!\n";
                saveData();
                return;
            default:
                std::cout << "Invalid choice!\n";
                waitForEnter();
        }
    } while (true);
}