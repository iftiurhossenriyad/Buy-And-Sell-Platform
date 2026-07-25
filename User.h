#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <vector>

class User {
private:
    int id;
    std::string name;
    std::string phoneNumber;
    std::string picturePath;
    std::string address;
    std::string email;
    std::string password;
    std::vector<int> orderHistory;  // Order IDs
    double averageRating;
    int totalOrders;

public:
    User();
    User(int id, const std::string& name, const std::string& phoneNumber,
         const std::string& picturePath = "", const std::string& address = "",
         const std::string& email = "", const std::string& password = "");
    
    // Getters
    int getId() const;
    std::string getName() const;
    std::string getPhoneNumber() const;
    std::string getPicturePath() const;
    std::string getAddress() const;
    std::string getEmail() const;
    std::string getPassword() const;
    const std::vector<int>& getOrderHistory() const;
    double getAverageRating() const;
    int getTotalOrders() const;
    
    // Setters
    void setId(int id);
    void setName(const std::string& name);
    void setPhoneNumber(const std::string& phoneNumber);
    void setPicturePath(const std::string& picturePath);
    void setAddress(const std::string& address);
    void setEmail(const std::string& email);
    void setPassword(const std::string& password);
    
    // Order methods
    void addOrderToHistory(int orderId);
    void updateStats(double rating);
    
    // Display
    void display() const;
};

#endif