#include <iostream>
#include <string>
#include <limits>   
#include <algorithm> 
using namespace std;


struct ItemGame {
    string nama;
    int jumlah;
    string tipe;
};

struct Node {
    ItemGame item;
    Node* next;
};

void AF(Node*& head, const ItemGame& d);           
void AL(Node*& head, const ItemGame& d);          
void AM(Node*& head, const ItemGame& d, int posisi); 
void DF(Node*& head);                             
void DL(Node*& head);                              
void DM(Node*& head, int posisi);                 
void UM(Node*& head, int posisi, const ItemGame& dBaru); 
void disp(Node* head);                             
ItemGame inputitem();                              
void gunakanItem(Node*& head, const string& namaItem); 


const int DIGIT_TERAKHIR_NIM = 81; 


int main() {
    Node* head = nullptr;
    int pilih, posisi;
    ItemGame d;

    cout << "\n";
    cout << "+--------------------------------------------------+\n";
    cout << "|             GAME INVENTORY MANAGEMENT             |\n";
    cout << "|---------------------------------------------------|\n";
    cout << "| [BENYAMIN HAQIE]                                  |\n"; 
    cout << "|   [2409106081]                                    |\n"; 
    cout << "+--------------------------------------------------+\n";

    do {
        cout << "\n";
        cout << "+---------------------------+\n";
        cout << "|           MENU            |\n";
        cout << "+---------------------------+\n";
        cout << "| 1. Tambah Item Baru       |\n";
        cout << "| 2. Sisipkan Item          |\n";
        cout << "| 3. Buang Item Terakhir    |\n";
        cout << "| 4. Gunakan Item           |\n";
        cout << "| 5. Tampilkan Inventory    |\n";
        cout << "| 0. Keluar                 |\n";
        cout << "+---------------------------+\n";
        cout << "Pilih (0-5): ";
        cin >> pilih;

        switch (pilih) {
            case 1:
                d = inputitem();
                AF(head, d);
                break;
            case 2:
                d = inputitem();
                cout << "Posisi sisip (default: " << DIGIT_TERAKHIR_NIM + 1 << "): ";
                cin >> posisi;
                if (posisi <= 0) posisi = DIGIT_TERAKHIR_NIM + 1;
                AM(head, d, posisi);
                break;
            case 3:
                DL(head);
                break;
            case 4: { 
                cout << "Nama item yang ingin digunakan: ";
                cin.ignore();
                string nama; 
                getline(cin, nama);
                gunakanItem(head, nama);
                break;
            } 
            case 5:
                disp(head);
                break;
            case 0:
                cout << "\n>> Terima kasih telah bermain! <<\n";
                break;
            default:
                cout << "\n>> Pilihan tidak valid. Silakan coba lagi. <<\n";
        }
    } while (pilih != 0); 


    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}


ItemGame inputitem() {
    ItemGame item;
    cout << "\n--- INPUT DATA ITEM ---\n";
    cout << "Nama Item: ";
    cin.ignore();
    getline(cin, item.nama);
    cout << "Tipe: ";
    getline(cin, item.tipe);
    item.jumlah = DIGIT_TERAKHIR_NIM;

    cout << "Jumlah: "; 
    int inputJumlah;
    while (!(cin >> inputJumlah)) {
        cout << "Input tidak valid. Masukkan angka: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (inputJumlah > 0) {
        item.jumlah = inputJumlah;
    }

    return item;
}

void AF(Node*& head, const ItemGame& d) {
    Node* baru = new Node{d, head};
    head = baru;
    cout << "\n>> Item \"" << d.nama << "\" berhasil ditambahkan di awal.\n\n";
}

void AL(Node*& head, const ItemGame& d) {
    Node* baru = new Node{d, nullptr};
    if (head == nullptr) {
        head = baru;
        cout << "\n>> Item pertama \"" << d.nama << "\" berhasil ditambahkan.\n\n";
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = baru;
    cout << "\n>> Item \"" << d.nama << "\" berhasil ditambahkan di akhir.\n\n";
}

void AM(Node*& head, const ItemGame& d, int posisi) {
    if (posisi <= 1) {
        AF(head, d);
        return;
    }
    Node* temp = head;
    for (int i = 1; i < posisi - 1 && temp != nullptr; i++) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "\n>> Posisi tidak valid!\n\n";
        return;
    }
    Node* baru = new Node{d, temp->next};
    temp->next = baru;
    cout << "\n>> Item \"" << d.nama << "\" berhasil disisipkan di posisi " << posisi << ".\n\n";
}

void DF(Node*& head) {
    if (head == nullptr) {
        cout << "\n>> Inventory kosong!\n\n";
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
    cout << "\n>> Item pertama berhasil dibuang.\n\n";
}

void DL(Node*& head) {
    if (head == nullptr) {
        cout << "\n>> Inventory kosong!\n\n";
        return;
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        cout << "\n>> Item terakhir berhasil dibuang.\n\n";
        return;
    }
    Node* temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
    cout << "\n>> Item terakhir berhasil dibuang.\n\n";
}

void DM(Node*& head, int posisi) {
    if (head == nullptr) {
        cout << "\n>> Inventory kosong!\n\n";
        return;
    }
    if (posisi <= 1) {
        DF(head);
        return;
    }
    Node* temp = head;
    for (int i = 1; i < posisi - 1 && temp->next != nullptr; i++) {
        temp = temp->next;
    }
    if (temp->next == nullptr) {
        cout << "\n>> Posisi tidak valid!\n\n";
        return;
    }
    Node* hapus = temp->next;
    temp->next = hapus->next;
    delete hapus;
    cout << "\n>> Item di posisi " << posisi << " berhasil dihapus.\n\n";
}

void UM(Node*& head, int posisi, const ItemGame& dBaru) {
    if (head == nullptr) {
        cout << "\n>> Inventory kosong!\n\n";
        return;
    }
    Node* temp = head;
    for (int i = 1; i < posisi && temp != nullptr; i++) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "\n>> Posisi tidak valid!\n\n";
        return;
    }
    cout << "\n>> Item lama: " << temp->item.nama << " (" << temp->item.jumlah << ")\n";
    temp->item = dBaru;
    cout << ">> Item berhasil diubah.\n\n";
}

void disp(Node* head) {
    if (head == nullptr) {
        cout << "\n>> Inventory kosong.\n\n";
        return;
    }
    cout << "\n";
    cout << "+---------------------------------------+\n";
    cout << "|               INVENTORY                |\n";
    cout << "+---------------------------------------+\n";
    int no = 1;
    for (Node* temp = head; temp != nullptr; temp = temp->next) {
        cout << no++ << ". " << temp->item.nama 
            << " | Jumlah: " << temp->item.jumlah 
            << " | Tipe: " << temp->item.tipe << "\n";
    }
    cout << "+---------------------------------------+\n\n";
}

void gunakanItem(Node*& head, const string& namaItem) {
    if (head == nullptr) {
        cout << "\n>> Inventory kosong!\n\n";
        return;
    }

    Node* temp = head;
    Node* prev = nullptr;

    while (temp != nullptr && temp->item.nama != namaItem) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "\n>> Item \"" << namaItem << "\" tidak ditemukan!\n\n";
        return;
    }

    temp->item.jumlah--;
    cout << "\n>> Menggunakan item \"" << namaItem << "\". Sisa: " << temp->item.jumlah << "\n";

    if (temp->item.jumlah <= 0) {
        cout << ">> Item \"" << namaItem << "\" habis dan dihapus dari inventory.\n";

        if (prev == nullptr) {
            head = temp->next;
        } else {
            prev->next = temp->next;
        }
        delete temp;
    }
    cout << "\n";
}