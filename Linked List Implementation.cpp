#include <iostream>
#include <vector>

// Node structure for non-zero elements
struct Node {
    int row, column, value;
    Node *next;

    Node(int r, int c, int v) : row(r), column(c), value(v), next(nullptr) {}
};

// SparseMatrix class to handle the linked list
class SparseMatrix {
private:
    std::vector<Node*> heads; // Array of head pointers for each row
    int rows, cols;

public:
    SparseMatrix(int r, int c) : rows(r), cols(c), heads(r, nullptr) {}

    // Function to insert a new node in a sorted order
    void insert(int r, int c, int value) {
        if (value == 0 || r >= rows || c >= cols) {
            return; // Ignore zero values and invalid positions
        }

        Node* newNode = new Node(r, c, value);
        Node** current = &heads[r]; // Pointer to head pointer of the row

        // Navigate through the list to find the correct position
        while (*current != nullptr && (*current)->column < c) {
            current = &((*current)->next);
        }

        // Insert the new node
        newNode->next = *current;
        *current = newNode;
    }

    // Function to display the compact representation of the matrix
    void displayCompact() {
        std::cout << "Compact representation of the sparse matrix:" << std::endl;
        for (int r = 0; r < rows; ++r) {
            Node* current = heads[r];
            while (current != nullptr) {
                std::cout << "(" << current->row << ", " << current->column << ", " << current->value << ") ";
                current = current->next;
            }
        }
        std::cout << std::endl;
    }

    // Destructor to deallocate memory
    ~SparseMatrix() {
        for (int r = 0; r < rows; ++r) {
            Node* current = heads[r];
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
    }
};

int main() {
    // Create a new Sparse Matrix with dimensions 4x5
    SparseMatrix sparseMatrix(4, 5);

    // Insert some non-zero elements
    sparseMatrix.insert(0, 2, 3);
    sparseMatrix.insert(1, 4, 5);
    sparseMatrix.insert(3, 1, 2);

    // Display the compact representation of the matrix
    sparseMatrix.displayCompact();

    return 0;
}
