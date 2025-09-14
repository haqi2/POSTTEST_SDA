#include <iostream>
#include <string>

using namespace std;

struct Mahasiswa {
    string nama;
    int nim;
    double ipk;
};

int main() {
    const int jumlahMahasiswa = 5;
    Mahasiswa mhs[jumlahMahasiswa];
    for (int i = 0; i < jumlahMahasiswa; ++i) {
        cout << "Masukkan data mahasiswa ke-" << i + 1 << endl;
        cout << "Nama: ";
        getline(cin >> ws, mhs[i].nama);
        cout << "NIM: ";
        cin >> mhs[i].nim;
        cout << "IPK: ";
        cin >> mhs[i].ipk;
    }

    int indeksTertinggi = 0;
    for (int i = 1; i < jumlahMahasiswa; ++i) {
        if (mhs[i].ipk > mhs[indeksTertinggi].ipk) {
            indeksTertinggi = i;
        }
    }

    cout << "\nMahasiswa dengan IPK tertinggi:" << endl;
    cout << "Nama: " << mhs[indeksTertinggi].nama << endl;
    cout << "NIM: " << mhs[indeksTertinggi].nim << endl;
    cout << "IPK: " << mhs[indeksTertinggi].ipk << endl;

    return 0;
}