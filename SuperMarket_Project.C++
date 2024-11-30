#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;


struct Product {
    string name;
    int quantity;
    float price;
};


void displayProducts();
void adminMenu();
void addProduct();
void editProduct();
void customerMenu();
void buyProduct();

int main() {
    int choice;


    cout << "\t\t\t-----------------------------\n";
    cout << "\t\t\t*          WELCOME          *\n";
    cout << "\t\t\t-----------------------------\n\n";

    // Main menu
    cout << "\t\t----------------------------\n";
    cout << "\t\t*     Super Market Menu    *\n";
    cout << "\t\t----------------------------\n\n";
    cout << "\t\t1) Admin\n";
    cout << "\t\t2) Customer\n";
    cout << "\t\t3) Exit\n";
    cout << "Please select an option: ";
    cin >> choice;

    switch (choice) {
        case 1:
            adminMenu();
            break;
        case 2:
            customerMenu();
            break;
        case 3:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid input. Please try again." << endl;
    }

    return 0;
}

// Function to display the list of products
void displayProducts() {
    ifstream productFile("Product.txt");
    if (!productFile.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    cout << setw(20) << "Product Name"
         << setw(10) << "Quantity"
         << setw(10) << "Price" << endl;
    cout << string(40, '-') << endl;

    string name;
    int quantity;
    float price;
    while (productFile >> name >> quantity >> price) {
        cout << setw(20) << name
             << setw(10) << quantity
             << setw(10) << fixed << setprecision(2) << price << endl;
    }

    productFile.close();
}

// Admin menu
void adminMenu() {
    string email, password;
    cout << "Enter Admin Email: ";
    cin >> email;
    cout << "Enter Admin Password: ";
    cin >> password;

    if (email == "Admin" && password == "Admin@123") {
        int adminChoice;
        cout << "\nWelcome, Admin!\n";
        cout << "\t1) View Product List\n";
        cout << "\t2) Add Product\n";
        cout << "\t3) Edit Product\n";
        cout << "Please select an option: ";
        cin >> adminChoice;

        switch (adminChoice) {
            case 1:
                displayProducts();
                break;
            case 2:
                addProduct();
                break;
            case 3:
                editProduct();
                break;
            default:
                cout << "Invalid input. Returning to main menu." << endl;
        }
    } else {
        cout << "Invalid credentials. Access denied." << endl;
    }
}

// Function to add a new product
void addProduct() {
    ofstream productFile("Product.txt", ios::app);
    if (!productFile.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    Product newProduct;
    cout << "Enter product name: ";
    cin >> newProduct.name;
    cout << "Enter quantity: ";
    cin >> newProduct.quantity;
    cout << "Enter price: ";
    cin >> newProduct.price;

    productFile << newProduct.name << " "
                << newProduct.quantity << " "
                << newProduct.price << endl;

    productFile.close();
    cout << "Product added successfully." << endl;
}

// Function to edit a product
void editProduct() {
    fstream productFile("Product.txt", ios::in | ios::out);
    if (!productFile.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string productName;
    cout << "Enter the product name to edit: ";
    cin >> productName;

    vector<Product> products;
    Product tempProduct;
    bool found = false;

    while (productFile >> tempProduct.name >> tempProduct.quantity >> tempProduct.price) {
        if (tempProduct.name == productName) {
            found = true;
            cout << "Enter new quantity: ";
            cin >> tempProduct.quantity;
            cout << "Enter new price: ";
            cin >> tempProduct.price;
        }
        products.push_back(tempProduct);
    }

    productFile.close();

    if (found) {
        ofstream productFileOut("Product.txt", ios::trunc);
        for (const auto &prod : products) {
            productFileOut << prod.name << " "
                           << prod.quantity << " "
                           << prod.price << endl;
        }
        productFileOut.close();
        cout << "Product updated successfully." << endl;
    } else {
        cout << "Product not found." << endl;
    }
}

// Customer menu
void customerMenu() {
    int customerChoice;
    cout << "\nCustomer Menu:\n";
    cout << "\t1) View Products\n";
    cout << "\t2) Buy Product\n";
    cout << "\t3) Exit\n";
    cout << "Please select an option: ";
    cin >> customerChoice;

    switch (customerChoice) {
        case 1:
            displayProducts();
            break;
        case 2:
            buyProduct();
            break;
        case 3:
            cout << "Exiting customer menu. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid input. Returning to main menu." << endl;
    }
}

// Function to buy products
void buyProduct() {
    fstream productFile("Product.txt", ios::in | ios::out);
    if (!productFile.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string productName;
    int quantityToBuy;
    float totalPrice = 0;
    vector<Product> products;
    Product tempProduct;
    bool found = false;

    cout << "Enter the product name: ";
    cin >> productName;
    cout << "Enter the quantity to buy: ";
    cin >> quantityToBuy;

    while (productFile >> tempProduct.name >> tempProduct.quantity >> tempProduct.price) {
        if (tempProduct.name == productName) {
            found = true;
            if (tempProduct.quantity >= quantityToBuy) {
                tempProduct.quantity -= quantityToBuy;
                totalPrice = quantityToBuy * tempProduct.price;
            } else {
                cout << "Insufficient quantity in stock." << endl;
                return;
            }
        }
        products.push_back(tempProduct);
    }

    productFile.close();

    if (found) {
        ofstream productFileOut("Product.txt", ios::trunc);
        for (const auto &prod : products) {
            productFileOut << prod.name << " "
                           << prod.quantity << " "
                           << prod.price << endl;
        }
        productFileOut.close();

        cout << "Purchase successful. Total price: " << totalPrice << endl;
    } else {
        cout << "Product not found." << endl;
    }
}
