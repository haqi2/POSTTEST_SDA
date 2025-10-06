#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void sortedInsert(Node *&head_ref, int data) {
    Node* newNode = new Node{data, nullptr, nullptr};

    // Kasus 1: List masih kosong
    if (head_ref == nullptr) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }

    // Dapatkan pointer ke head dan tail (karena circular, tail = head->prev)
    Node* head = head_ref;
    Node* tail = head->prev;

    // Kasus 2: Data baru lebih kecil atau sama dengan head → sisipkan di awal
    // Karena list terurut, ini berarti data menjadi elemen terkecil
    if (data <= head->data) {
        newNode->next = head;      // Node baru mengarah ke head lama
        newNode->prev = tail;      // Node baru mengarah ke tail (karena circular)
        tail->next = newNode;      // Tail sekarang mengarah ke node baru
        head->prev = newNode;      // Head lama kini punya prev = node baru
        head_ref = newNode;        // Update head_ref karena elemen terkecil berubah
        return;
    }

    // Kasus tambahan (opsional tapi efisien): Data lebih besar atau sama dengan tail → sisipkan di akhir
    if (data >= tail->data) {
        tail->next = newNode;      // Tail lama mengarah ke node baru
        newNode->prev = tail;      // Node baru mengarah balik ke tail lama
        newNode->next = head;      // Node baru mengarah ke head (menutup lingkaran)
        head->prev = newNode;      // Head kini punya prev = node baru (tail baru)
        // Tidak perlu update head_ref karena head tetap sama
        return;
    }

    // Kasus 3: Cari posisi yang tepat di tengah list
    // Mulai dari head, cari node 'current' sehingga: current->data < data <= current->next->data
    Node* current = head;
    while (current->next != head && current->next->data < data) {
        current = current->next;
    }
    // Sekarang, sisipkan newNode SETELAH current

    // Sambungkan newNode ke node setelah current
    newNode->next = current->next;
    newNode->prev = current;

    // Perbarui koneksi node setelah current agar mengarah balik ke newNode
    current->next->prev = newNode;

    // Sambungkan current ke newNode
    current->next = newNode;
}

void printList(Node *head_ref) {
    if (head_ref == nullptr) {
        cout << "List kosong" << endl;
        return;
    }

    Node *current = head_ref;
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head_ref);
    cout << endl;
}

int main() {
    Node *head = nullptr;

    sortedInsert(head, 30);
    sortedInsert(head, 10);
    sortedInsert(head, 20);
    sortedInsert(head, 40);

    cout << "Circular Doubly Linked List (sorted): ";
    printList(head); // Output: 10 20 30 40

    return 0;
}