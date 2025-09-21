#include <iostream>

using namespace std;

void tukarNilai(int** a, int** b) {
    int temp = **a;
    **a = **b;
    **b = temp;
}

int main() {
    int x = 10;
    int y = 20;

    cout << "Sebelum pertukaran:" << endl;
    cout << "Nilai x = " << x << endl;
    cout << "Nilai y = " << y << endl;

    int* ptrX = &x;
    int* ptrY = &y;

    tukarNilai(&ptrX, &ptrY);

    cout << "\nSetelah pertukaran:" << endl;
    cout << "Nilai x = " << x << endl;
    cout << "Nilai y = " << y << endl;

    return 0;
}