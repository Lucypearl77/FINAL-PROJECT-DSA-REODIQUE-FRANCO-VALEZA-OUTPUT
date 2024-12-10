#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Node structure for the Binary Search Tree
struct Node {
    int orderId;
    string itemName;
    double price;
    Node* left;
    Node* right;

    Node(int id, string name, double price) : orderId(id), itemName(name), price(price), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class
class ShoppingCart {
private:
    Node* root;
    int itemCount; // Track the number of items in the cart
    const int MAX_ITEMS = 5; // Maximum allowed items

    // Helper function to insert an item
    Node* insert(Node* node, int orderId, string itemName, double price) {
        if (node == nullptr) {
            return new Node(orderId, itemName, price);
        }
        if (price < node->price) {
            node->left = insert(node->left, orderId, itemName, price);
        } else {
            node->right = insert(node->right, orderId, itemName, price);
        }
        return node;
    }

    // Helper function for searching an item
    Node* search(Node* node, int orderId) {
        if (node == nullptr || node->orderId == orderId) {
            return node;
        }
        if (orderId < node->orderId) {
            return search(node->left, orderId);
        }
        return search(node->right, orderId);
    }

    // Helper function to find the minimum value node
    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Helper function to delete a node
    Node* deleteNode(Node* node, int orderId) {
        if (node == nullptr) {
            return node;
        }
        if (orderId < node->orderId) {
            node->left = deleteNode(node->left, orderId);
        } else if (orderId > node->orderId) {
            node->right = deleteNode(node->right, orderId);
        } else {
            // Node with only one child or no child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: Get the in-order successor (smallest in the right subtree)
            Node* temp = findMin(node->right);
            node->orderId = temp->orderId;
            node->itemName = temp->itemName;
            node->price = temp->price;

            // Delete the in-order successor
            node->right = deleteNode(node->right, temp->orderId);
        }
        return node;
    }

    // Helper function for pre-order traversal
    void preOrderTraversal(Node* node, string& result) {
        if (node == nullptr) return;
        result += "Php " + to_string(node->price) + ", ";
        preOrderTraversal(node->left, result);
        preOrderTraversal(node->right, result);
    }

    // Helper function for in-order traversal
    void inOrderTraversal(Node* node, string& result) {
        if (node == nullptr) return;
        inOrderTraversal(node->left, result);
        result += "Php " + to_string(node->price) + ", ";
        inOrderTraversal(node->right, result);
    }

    // Helper function for post-order traversal
    void postOrderTraversal(Node* node, string& result) {
        if (node == nullptr) return;
        postOrderTraversal(node->left, result);
        postOrderTraversal(node->right, result);
        result += "Php " + to_string(node->price) + ", ";
    }

public:
    ShoppingCart() : root(nullptr), itemCount(0) {}

    // Public method to add an item to the cart
    void addItem(int orderId, string itemName, double price) {
        if (itemCount >= MAX_ITEMS) {
            cout << "The cart is full! You can only have up to " << MAX_ITEMS << " items." << endl;
            return;
        }
        root = insert(root, orderId, itemName, price);
        itemCount++;
        cout << "Item '" << itemName << "' added to cart for Php " << fixed << setprecision(2) << price << endl;
    }

    // Public method to search for an item
    void searchItem(int orderId) {
        Node* found = search(root, orderId);
        if (found != nullptr) {
            cout << "Item found: " << endl;
            cout << "Order ID: " << found->orderId << endl;
            cout << "Item Name: " << found->itemName << endl;
            cout << "Price: Php " << fixed << setprecision(2) << found->price << endl;
        } else {
            cout << "Item with Order ID " << orderId << " not found." << endl;
        }
    }

    // Public method to delete an item
    void deleteItem(int orderId) {
        if (root == nullptr) {
            cout << "The cart is empty!" << endl;
            return;
        }
        root = deleteNode(root, orderId);
        cout << "Item with Order ID " << orderId << " has been deleted from the cart." << endl;
        itemCount--; // Decrease the item count
    }

    // Public method to display items in a specified traversal order
    void displayItems(string traversalType) {
        if (root == nullptr) {
            cout << "The cart is empty!" << endl;
            return;
        }
        string result;
        if (traversalType == "Pre-order") {
            preOrderTraversal(root, result);
        } else if (traversalType == "In-order") {
            inOrderTraversal(root, result);
        } else if (traversalType == "Post-order") {
            postOrderTraversal(root, result);
        } else {
            cout << "Invalid traversal type!" << endl;
            return;
        }
        // Remove the trailing ", " and display the result
        if (!result.empty()) result.pop_back(), result.pop_back();
        cout << traversalType << ": " << result << endl;
    }
};

int main() {
    ShoppingCart cart;
    int choice, orderId;
    string itemName, traversalType;
    double price;

    cout << "Welcome to the Shopping Cart System!" << endl;

    while (true) {
        cout << "\nMenu:" << endl;
        cout << "1. Add an item to the cart" << endl;
        cout << "2. Display cart items (Pre-order, In-order, Post-order)" << endl;
        cout << "3. Search for an item" << endl;
        cout << "4. Delete an item from the cart" << endl;
        cout << "5. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter order ID: ";
                cin >> orderId;
                cout << "Enter item name: ";
                cin.ignore();
                getline(cin, itemName);
                cout << "Enter item price: ";
                cin >> price;
                cart.addItem(orderId, itemName, price);
                break;
            case 2:
                cout << "Enter traversal type (Pre-order, In-order, Post-order): " << endl;
                cin.ignore();
                getline(cin, traversalType);
                cart.displayItems(traversalType);
                break;
            case 3:
                cout << "Enter the Order ID to search: ";
                cin >> orderId;
                cart.searchItem(orderId);
                break;
            case 4:
                cout << "Enter the Order ID to delete: ";
                cin >> orderId;
                cart.deleteItem(orderId);
                break;
            case 5:
                cout << "Exiting the system. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
