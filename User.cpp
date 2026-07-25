#include "User.h"

User::User() : id(0), name(""), phoneNumber(""), picturePath(""), 
                address(""), email(""), password(""), averageRating(0.0), totalOrders(0) {}

User::User(int id, const std::string& name, const std::string& phoneNumber,
           const std::string& picturePath, const std::string& address,
           const std::string& email, const std::string& password)
    : id(id), name(name), phoneNumber(phoneNumber), picturePath(picturePath),
      address(address), email(email), password(password), averageRating(0.0), totalOrders(0) {}

int User::getId() const { return id; }
std::string User::getName() const { return name; }
std::string User::getPhoneNumber() const { return phoneNumber; }
std::string User::getPicturePath() const { return picturePath; }
std::string User::getAddress() const { return address; }
std::string User::getEmail() const { return email; }
std::string User::getPassword() const { return password; }
const std::vector<int>& User::getOrderHistory() const { return orderHistory; }
double User::getAverageRating() const { return averageRating; }
int User::getTotalOrders() const { return totalOrders; }

void User::setId(int id) { this->id = id; }
void User::setName(const std::string& name) { this->name = name; }
void User::setPhoneNumber(const std::string& phoneNumber) { this->phoneNumber = phoneNumber; }
void User::setPicturePath(const std::string& picturePath) { this->picturePath = picturePath; }
void User::setAddress(const std::string& address) { this->address = address; }
void User::setEmail(const std::string& email) { this->email = email; }
void User::setPassword(const std::string& password) { this->password = password; }

void User::addOrderToHistory(int orderId) {
    orderHistory.push_back(orderId);
    totalOrders++;
}

void User::updateStats(double rating) {
    if (totalOrders > 0) {
        averageRating = (averageRating * (totalOrders - 1) + rating) / totalOrders;
    }
}

void User::display() const {
    std::cout << "ID: " << id 
              << " | Name: " << name 
              << " | Phone: " << phoneNumber
              << " | Email: " << email
              << " | Address: " << address
              << " | Orders: " << totalOrders
              << " | Rating: " << averageRating << "/5\n";
}
