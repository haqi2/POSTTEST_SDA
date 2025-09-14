#include <iostream>

using namespace std;

int main() {
    const int baris = 3;
    const int kolom = 3;
    int matriks[baris][kolom]; 
    int jumlahDiagonalUtama = 0;
    int jumlahDiagonalSekunder = 0;

    cout << "Masukkan elemen-elemen matriks 3x3:" << endl;
    for (int i = 0; i < baris; ++i) {
        for (int j = 0; j < kolom; ++j) {
            cout << "Matriks[" << i << "][" << j << "]: ";
            cin >> matriks[i][j];
        }
    }

    for (int i = 0; i < baris; ++i) {
        jumlahDiagonalUtama += matriks[i][i];
        jumlahDiagonalSekunder += matriks[i][baris - 1 - i];
    }

    cout << "\nMatriks yang telah diinput:" << endl;
    for (int i = 0; i < baris; ++i) {
        for (int j = 0; j < kolom; ++j) {
            cout << matriks[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nJumlah diagonal utama: " << jumlahDiagonalUtama << endl;
    cout << "Jumlah diagonal sekunder: " << jumlahDiagonalSekunder << endl;

    return 0;
}