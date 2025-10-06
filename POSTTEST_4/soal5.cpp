#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

// Fungsi bantu untuk menyisipkan di akhir (digunakan di main)
void insertEnd(Node *&head_ref, int data) {
    Node *newNode = new Node{data, nullptr, nullptr};

    if (head_ref == nullptr) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }

    Node *tail = head_ref->prev;
    newNode->next = head_ref;
    newNode->prev = tail;
    head_ref->prev = newNode;
    tail->next = newNode;
}

// Fungsi utama: menukar head dan tail dalam circular doubly linked list
void exchangeHeadAndTail(Node *&head_ref) {
    // Tidak perlu tukar jika list kosong atau hanya 1 node
    if (head_ref == nullptr || head_ref->next == head_ref) {
        return; 
    }

    Node* head = head_ref;
    Node* tail = head->prev;        // Tail adalah node sebelum head (karena circular)
    Node* head_next = head->next;   // Node setelah head
    Node* tail_prev = tail->prev;   // Node sebelum tail

    // Kasus khusus: hanya ada 2 node (head <-> tail)
    if (head_next == tail) {
        // Cukup tukar peran: hubungkan tail ke head dan sebaliknya
        tail->next = head;
        tail->prev = head;
        head->next = tail;
        head->prev = tail;
        head_ref = tail; // Update head menjadi tail lama
        return;
    }

    // Kasus umum: 3 node atau lebih
    // 1. Sambungkan node sebelum tail (tail_prev) ke head,
    //    karena head akan menjadi tail baru
    tail_prev->next = head;
    head->prev = tail_prev;

    // 2. Sambungkan tail ke node setelah head (head_next),
    //    karena tail akan menjadi head baru
    tail->next = head_next;
    head_next->prev = tail;

    // 3. Hubungkan head (sekarang di posisi akhir) dan tail (sekarang di posisi awal)
    //    secara langsung untuk menutup lingkaran
    head->next = tail;
    tail->prev = head;

    // 4. Update head_ref ke tail lama, karena sekarang jadi head
    head_ref = tail;
}

// Fungsi untuk mencetak list
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

// Program utama
int main() {
    Node *head = nullptr;

    insertEnd(head, 1);
    insertEnd(head, 2);
    insertEnd(head, 3);
    insertEnd(head, 4);
    insertEnd(head, 5);

    cout << "List sebelum ditukar: ";
    printList(head); 

    exchangeHeadAndTail(head);

    cout << "List setelah ditukar head dan tail: ";
    printList(head); // Output: 5 2 3 4 1

    return 0;
}