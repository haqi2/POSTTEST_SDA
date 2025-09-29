#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct ItemGame {
    string nama;
    int jumlah;
    string tipe;
};

struct Node {
    ItemGame item;
    Node* next;
    Node* prev;
};

void AF(Node*& head, const ItemGame& itemBaru);
void AL(Node*& head, const ItemGame& itemBaru);
void AM(Node*& head, const ItemGame& itemBaru, int posisi);
void DF(Node*& head);
void DL(Node*& head);
void DM(Node*& head, int posisi);
void UM(Node*& head, int posisi, const ItemGame& itemUpdate);
void disp(Node* head);
void dispReverse(Node* head);
ItemGame inputitem();
void gunakanItem(Node*& head, const string& namaItem);
void cariItem(Node* head, const string& namaCari);

const int DIGIT_TERAKHIR_NIM = 81;

int main() {
    Node* head = nullptr;
    int pilih, posisi;
    ItemGame itemBaru;

    cout << "\n";
    cout << "+--------------------------------------------------+\n";
    cout << "|             GAME INVENTORY MANAGEMENT             |\n";
    cout << "|---------------------------------------------------|\n";
    cout << "| [BENYAMIN HAQIE]                                  |\n";
    cout << "|   [2409106081]                                    |\n";
    cout << "+--------------------------------------------------+\n";

    do {
        cout << "+---------------------------+\n";
        cout << "|           MENU            |\n";
        cout << "+---------------------------+\n";
        cout << "| 1. Tambah Item di Awal    |\n";
        cout << "| 2. Tambah Item di Akhir   |\n"; 
        cout << "| 3. Sisipkan Item          |\n";
        cout << "| 4. Buang Item Terakhir    |\n";
        cout << "| 5. Gunakan Item           |\n";
        cout << "| 6. Cari Item              |\n";
        cout << "| 7. Tampilkan Inventory    |\n";
        cout << "| 8. Reverse Inventory      |\n";
        cout << "| 0. Keluar                 |\n";
        cout << "+---------------------------+\n";
        cout << "Pilih (0-8): ";
        cin >> pilih;

        switch (pilih) {
            case 1:
                itemBaru = inputitem();
                AF(head, itemBaru);
                break;
            case 2:
                itemBaru = inputitem();
                AL(head, itemBaru);
                break;
            case 3:
                itemBaru = inputitem();
                cout << "Posisi sisip (default: " << DIGIT_TERAKHIR_NIM + 1 << "): ";
                cin >> posisi;
                if (posisi <= 0) posisi = DIGIT_TERAKHIR_NIM + 1;
                AM(head, itemBaru, posisi);
                break;
            case 4:
                DL(head);
                break;
            case 5: {
                cout << "Nama item yang ingin digunakan: ";
                cin.ignore();
                string nama;
                getline(cin, nama);
                gunakanItem(head, nama);
                break;
            }
            case 6: {
                cout << "Nama item yang dicari ?: ";
                cin.ignore();
                string namaCari;
                getline(cin, namaCari);
                cariItem(head, namaCari);
                break;
            }
            case 7:
                disp(head);
                break;
            case 8:
                dispReverse(head);
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

void AF(Node*& head, const ItemGame& itemBaru) {
    Node* baru = new Node{itemBaru, head, nullptr};
    if (head != nullptr) {
        head->prev = baru;
    }
    head = baru;
    cout << "\n>> Item \"" << itemBaru.nama << "\" berhasil ditambahkan di awal.\n\n";
}

void AL(Node*& head, const ItemGame& itemBaru) {
    Node* baru = new Node{itemBaru, nullptr, nullptr};
    if (head == nullptr) {
        head = baru;
        cout << "\n>> Item pertama \"" << itemBaru.nama << "\" berhasil ditambahkan.\n\n";
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = baru;
    baru->prev = temp;
    cout << "\n>> Item \"" << itemBaru.nama << "\" berhasil ditambahkan di akhir.\n\n";
}

void AM(Node*& head, const ItemGame& itemBaru, int posisi) {
    if (posisi <= 1) {
        AF(head, itemBaru);
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
    Node* baru = new Node{itemBaru, temp->next, temp};
    if (temp->next != nullptr) {
        temp->next->prev = baru;
    }
    temp->next = baru;
    cout << "\n>> Item \"" << itemBaru.nama << "\" berhasil disisipkan di posisi " << posisi << ".\n\n";
}

void DF(Node*& head) {
    if (head == nullptr) {
        cout << "\n>> Inventory kosong!\n\n";
        return;
    }
    Node* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    }
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
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->prev->next = nullptr;
    delete temp;
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
    for (int i = 1; i < posisi && temp != nullptr; i++) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "\n>> Posisi tidak valid!\n\n";
        return;
    }
    temp->prev->next = temp->next;
    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    }
    delete temp;
    cout << "\n>> Item di posisi " << posisi << " berhasil dihapus.\n\n";
}

void UM(Node*& head, int posisi, const ItemGame& itemUpdate) {
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
    temp->item = itemUpdate;
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

void dispReverse(Node* head) {
    if (head == nullptr) {
        cout << "\n>> Inventory kosong.\n\n";
        return;
    }

    Node* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    cout << "\n";
    cout << "+---------------------------------------+\n";
    cout << "|           REVERSE INVENTORY           |\n";
    cout << "+---------------------------------------+\n";
    int no = 1;
    for (Node* temp = tail; temp != nullptr; temp = temp->prev) {
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
    while (temp != nullptr && temp->item.nama != namaItem) {
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

        if (temp->prev != nullptr) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next;
        }
        if (temp->next != nullptr) {
            temp->next->prev = temp->prev;
        }
        delete temp;
    }
    cout << "\n";
}

void cariItem(Node* head, const string& namaCari) {
    if (head == nullptr) {
        cout << "\n>> Inventory kosong.\n\n";
        return;
    }

    Node* temp = head;
    while (temp != nullptr) {
        if (temp->item.nama == namaCari) {
            cout << "\n+---------------------------------------+\n";
            cout << "|               DETAIL ITEM               |\n";
            cout << "+-----------------------------------------+\n";
            cout << "Nama: " << temp->item.nama << "\n";
            cout << "Jumlah: " << temp->item.jumlah << "\n";
            cout << "Tipe: " << temp->item.tipe << "\n";
            cout << "+---------------------------------------+\n\n";
            return;
        }
        temp = temp->next;
    }

    cout << "\n>> Item \"" << namaCari << "\" tidak ditemukan!\n\n";
}