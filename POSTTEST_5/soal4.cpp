#include <iostream>
using namespace std;

// Struktur Node untuk Binary Tree
struct Node {
    int data;
    Node* left;
    Node* right;

    // Constructor
    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// Fungsi insert untuk membangun tree
Node* insert(Node* root, int val) {
    if (root == nullptr) {
        return new Node(val);
    }
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else if (val > root->data) {
        root->right = insert(root->right, val);
    }
    return root;
}

/**
 * @brief Fungsi untuk melakukan post-order traversal pada tree.
 * @param root Pointer ke node root dari tree.
 * @logic
 * 1. Jika node saat ini adalah nullptr, kembalikan (base case).
 * 2. Rekursif ke subtree kiri.
 * 3. Rekursif ke subtree kanan.
 * 4. Cetak data node saat ini.
 */
void postOrderTraversal(Node* root) {
    if (root == nullptr) {
        return; // Base case: node kosong, tidak perlu diproses
    }
    postOrderTraversal(root->left);  // Kunjungi subtree kiri
    postOrderTraversal(root->right); // Kunjungi subtree kanan
    cout << root->data << " ";       // Cetak data node saat ini (urutan: kiri → kanan → akar)
}

int main() {
    Node* root = nullptr;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    cout << "Post-order traversal dari tree adalah: ";
    postOrderTraversal(root); // Harusnya output: 20 40 30 60 80 70 50
    cout << endl;
    return 0;
}