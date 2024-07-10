#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Node {
public:
    string data;
    Node* next;
    Node* prev;

    Node(string x) : data(x), next(nullptr), prev(nullptr) {}  // constructor
};

class BrowserHistory {
public:
    Node* currentPage;

    BrowserHistory(string homepage) {  // constructor
        currentPage = new Node(homepage);
    }

    void visit(string url) {
        Node* newNode = new Node(url);
        currentPage->next = newNode;
        newNode->prev = currentPage;
        currentPage = newNode;

        // Clear forward history
        Node* temp = currentPage->next;
        while (temp != nullptr) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
        currentPage->next = nullptr;
    }

    string back(int steps) {
        while (steps > 0 && currentPage->prev != nullptr) {
            currentPage = currentPage->prev;
            steps--;
        }
        return currentPage->data;
    }

    string forward(int steps) {
        while (steps > 0 && currentPage->next != nullptr) {
            currentPage = currentPage->next;
            steps--;
        }
        return currentPage->data;
    }
};

int main() {
    // Initialize BrowserHistory with homepage
    BrowserHistory* browserHistory = new BrowserHistory("leetcode.com");
    
    // Test sequence
    vector<string> outputs;
    browserHistory->visit("google.com");       // Visit google.com
    browserHistory->visit("facebook.com");     // Visit facebook.com
    browserHistory->visit("youtube.com");      // Visit youtube.com
    
    outputs.push_back(browserHistory->back(1)); // Back to facebook.com
    outputs.push_back(browserHistory->back(1)); // Back to google.com
    outputs.push_back(browserHistory->forward(1)); // Forward to facebook.com
    browserHistory->visit("linkedin.com");     // Visit linkedin.com
    outputs.push_back(browserHistory->forward(2)); // Cannot move forward any steps
    outputs.push_back(browserHistory->back(2)); // Back to google.com
    outputs.push_back(browserHistory->back(7)); // Back to leetcode.com
    
    // Print the outputs
    for (const string& output : outputs) {
        cout << output << endl;
    }

    // Clean up
    delete browserHistory;

    return 0;
}
