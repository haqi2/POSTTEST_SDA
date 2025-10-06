#include <iostream>
#include <string>
using namespace std;

struct Node {
    string document;
    Node* next;
};

void enqueue(Node*& front, Node*& rear, string document) {
    Node* newNode = new Node{document, nullptr};

    // 1. Jika queue kosong (front == nullptr), set front dan rear ke newNode
    if (front == nullptr) {
        front = rear = newNode; // Elemen pertama menjadi sekaligus depan dan belakang antrian
    }
    // 2. Jika tidak kosong, sambungkan rear->next ke newNode, lalu update rear
    else {
        rear->next = newNode;   // Node lama di belakang menunjuk ke node baru
        rear = newNode;         // Pindahkan rear ke node baru (karena sekarang paling akhir)
    }
}

string dequeue(Node*& front, Node*& rear) {
    if (front == nullptr) return ""; // Queue kosong

    // 1. Simpan data dari front node
    string data = front->document;
    Node* temp = front;             // Simpan alamat node depan untuk dihapus nanti
    // 2. Geser front ke front->next (karena elemen depan akan dikeluarkan)
    front = front->next;
    // 3. Jika front menjadi nullptr, berarti queue sekarang kosong → set rear juga ke nullptr
    if (front == nullptr) {
        rear = nullptr;
    }
    // 4. Delete node lama dan return data
    delete temp;
    return data;
}

void processAllDocuments(Node*& front, Node*& rear) {
    // Loop hingga queue kosong, dequeue dan print setiap dokumen
    while (front != nullptr) { // Selama masih ada dokumen di antrian
        cout << "Memproses: " << dequeue(front, rear) << endl;
        // dequeue() mengambil dokumen pertama (FIFO) dan menghapusnya dari antrian
    }
    // Setelah loop, semua dokumen telah diproses dan queue menjadi kosong
}

int main() {
    Node* front = nullptr;
    Node* rear = nullptr;

    enqueue(front, rear, "Document1.pdf");
    enqueue(front, rear, "Report.docx");
    enqueue(front, rear, "Presentation.pptx");

    cout << "Memulai pemrosesan antrian printer:" << endl;
    processAllDocuments(front, rear);

    return 0;
}