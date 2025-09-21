#include <iostream>
#include <array>

using namespace std;

void balikArray(int* arr, int ukuran) {
    int* awal = arr;
    int* akhir = arr + ukuran - 1;
    while (awal < akhir) {
        int temp = *awal;
        *awal = *akhir;
        *akhir = temp;
        awal++;
        akhir--;
    }
}

void tampilkanArray(const int* arr, int ukuran) {
    for (int i = 0; i < ukuran; ++i) {
        cout << *(arr + i) << " ";
    }
    cout << endl;
}

int main() {
    const int ukuran = 7;
    int data[ukuran];

    for (int i = 0; i < ukuran; ++i) {
        data[i] = (i + 1) * 3;
    }

    cout << "Array sebelum dibalik: ";
    tampilkanArray(data, ukuran);

    balikArray(data, ukuran);

    cout << "Array sesudah dibalik: ";
    tampilkanArray(data, ukuran);

    return 0;
}