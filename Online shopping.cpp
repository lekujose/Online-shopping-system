#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdexcept>

using namespace std;


// Base Class: Product
class Product {
protected:
    int productID;
    string productName;
    double price;
    int quantityInStock;

public:
    Product(int id, string name, double price, int quantity)
        : productID(id), productName(name), price(price), quantityInStock(quantity) {}

    virtual ~Product() {}

    // Display product details
    virtual void displayInfo() const {
        cout << "Product ID: " << productID << "\n"
             << "Name: " << productName << "\n"
             << "Price: Shs " << fixed << setprecision(2) << price << "\n"
             << "Stock: " << quantityInStock << "\n";
    }

    int getProductID() const { return productID; }
    string getProductName() const { return productName; }
    double getPrice() const { return price; }
    int getQuantityInStock() const { return quantityInStock; }

    void reduceStock(int quantity) {
        if (quantity > quantityInStock) {
            throw runtime_error("Insufficient stock available!");
        }
        quantityInStock -= quantity;
    }
};

// Derived Class: ElectronicProduct
class ElectronicProduct : public Product {
    string warranty;

public:
    ElectronicProduct(int id, string name, double price, int quantity, string warrantyPeriod)
        : Product(id, name, price, quantity), warranty(warrantyPeriod) {}

    void displayInfo() const override {
        Product::displayInfo();
        cout << "Warranty: " << warranty << "\n";
    }
};

// Derived Class: ClothingProduct
class ClothingProduct : public Product {
    string size;

public:
    ClothingProduct(int id, string name, double price, int quantity, string size)
        : Product(id, name, price, quantity), size(size) {}

    void displayInfo() const override {
        Product::displayInfo();
        cout << "Size: " << size << "\n";
    }
};

// Shopping Cart Class
class ShoppingCart {
    vector<Product*> items;

public:
    void addProduct(Product* product) {
        items.push_back(product);
        cout << "Product added to cart successfully.\n";
    }

    void displayCart() const {
        if (items.empty()) {
            cout << "Your cart is empty.\n";
            return;
        }

        cout << "\n--- Shopping Cart ---\n";
        for (const auto& item : items) {
            item->displayInfo();
            cout << "----------------------\n";
        }
    }

    void checkout() {
        if (items.empty()) {
            cout << "Your cart is empty. Cannot checkout.\n";
            return;
        }

        double totalAmount = 0.0;
        for (const auto& item : items) {
            totalAmount += item->getPrice();
        }

        cout << "Total Amount: Shs " << fixed << setprecision(2) << totalAmount << "\n";
        cout << "Thank you for your purchase!\n";

        // Clear the cart after checkout
        items.clear();
    }
};

// Function to display main menu
void displayMenu() {
    cout << "\n--- ONLINE SHOPPING SYSTEM ---\n";
    cout << "1. View Products\n";
    cout << "2. Add Product to Cart\n";
    cout << "3. View Cart\n";
    cout << "4. Checkout\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

// Main function
int main() {
    vector<Product*> products;
    ShoppingCart cart;

    // Adding sample products to the product list
    products.push_back(new ElectronicProduct(1, "Laptop", 40000, 5, "2 Years"));
    products.push_back(new ClothingProduct(2, "T-Shirt", 1200, 20, "Medium"));
    products.push_back(new ElectronicProduct(3, "Smartphone", 25000, 10, "1 Year"));

    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\n--- Available Products ---\n";
                for (const auto& product : products) {
                    product->displayInfo();
                    cout << "----------------------\n";
                }
                break;
            }
            case 2: {
                int id;
                cout << "Enter Product ID to add to cart: ";
                cin >> id;

                bool found = false;
                for (auto& product : products) {
                    if (product->getProductID() == id) {
                        cart.addProduct(product);
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Product with ID " << id << " not found.\n";
                }
                break;
            }
            case 3: {
                cart.displayCart();
                break;
            }
            case 4: {
                cart.checkout();
                break;
            }
            case 5: {
                cout << "Exiting the system. Goodbye!\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    } while (choice != 5);

    // Free allocated memory
    for (auto& product : products) {
        delete product;
    }

    return 0;
}
