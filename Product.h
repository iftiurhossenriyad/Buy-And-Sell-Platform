#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>
#include <vector>

class Product {
private:
    int id;
    std::string name;
    double price;
    std::string category;
    std::string sellerName;
    bool isDeleted;
    double averageRating;
    int totalRatings;
    std::string description;

public:
    Product();
    Product(int id, const std::string& name, double price, 
            const std::string& category, const std::string& sellerName);
    
    // Getters
    int getId() const;
    std::string getName() const;
    double getPrice() const;
    std::string getCategory() const;
    std::string getSellerName() const;
    bool getIsDeleted() const;
    double getAverageRating() const;
    int getTotalRatings() const;
    std::string getDescription() const;
    
    // Setters
    void setId(int id);
    void setName(const std::string& name);
    void setPrice(double price);
    void setCategory(const std::string& category);
    void setSellerName(const std::string& sellerName);
    void setIsDeleted(bool deleted);
    void setDescription(const std::string& description);
    void setAverageRating(double rating);
    void setTotalRatings(int totalRatings);
    
    // Rating methods
    void addRating(int rating);
    
    // Display
    void display() const;
    
    // Comparison operators for sorting
    bool operator<(const Product& other) const;
    bool operator>(const Product& other) const;
};

#endif
