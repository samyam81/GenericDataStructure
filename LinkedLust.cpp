#include <iostream>

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& data) : data(data), next(nullptr) {}
    };

    Node* head;
    size_t size;

public:
    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList() {
        clear();
    }

    void addFront(const T& item) {
        Node* newNode = new Node(item);
        newNode->next = head;
        head = newNode;
        size++;
    }

    void removeFront() {
        if (isEmpty()) {
            std::cerr << "List is empty. Cannot remove front.\n";
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    const T& getFront() const {
        if (isEmpty()) {
            throw std::out_of_range("List is empty. Cannot get front.");
        }
        return head->data;
    }

    bool isEmpty() const {
        return size == 0;
    }

    size_t getSize() const {
        return size;
    }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }
};
