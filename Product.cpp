#include "Product.h"
#include <iomanip>

Product::Product() : id(0), name(""), price(0.0), category(""), 
                      sellerName(""), isDeleted(false), averageRating(0.0), 
                      totalRatings(0), description("") {}

Product::Product(int id, const std::string& name, double price, 
                 const std::string& category, const std::string& sellerName)
    : id(id), name(name), price(price), category(category), 
      sellerName(sellerName), isDeleted(false), averageRating(0.0), 
      totalRatings(0), description("") {}

int Product::getId() const { return id; }
std::string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
std::string Product::getCategory() const { return category; }
std::string Product::getSellerName() const { return sellerName; }
bool Product::getIsDeleted() const { return isDeleted; }
double Product::getAverageRating() const { return averageRating; }
int Product::getTotalRatings() const { return totalRatings; }
std::string Product::getDescription() const { return description; }

void Product::setId(int id) { this->id = id; }
void Product::setName(const std::string& name) { this->name = name; }
void Product::setPrice(double price) { this->price = price; }
void Product::setCategory(const std::string& category) { this->category = category; }
void Product::setSellerName(const std::string& sellerName) { this->sellerName = sellerName; }
void Product::setIsDeleted(bool deleted) { isDeleted = deleted; }
void Product::setDescription(const std::string& description) { this->description = description; }
void Product::setAverageRating(double rating) { averageRating = rating; }
void Product::setTotalRatings(int total) { totalRatings = total; }

void Product::addRating(int rating) {
    if (rating >= 1 && rating <= 5) {
        if (totalRatings > 0) {
            averageRating = (averageRating * totalRatings + rating) / (totalRatings + 1);
        } else {
            averageRating = rating;
        }
        totalRatings++;
    }
}

void Product::display() const {
    std::cout << "ID: " << id 
              << " | Name: " << name 
              << " | Price: $" << std::fixed << std::setprecision(2) << price
              << " | Category: " << category
              << " | Seller: " << sellerName
              << " | Rating: " << std::fixed << std::setprecision(1) << averageRating << "/5 (" << totalRatings << ")"
              << (isDeleted ? " [DELETED]" : "") << "\n";
}

bool Product::operator<(const Product& other) const {
    return this->price < other.price;
}

bool Product::operator>(const Product& other) const {
    return this->price > other.price;
}
