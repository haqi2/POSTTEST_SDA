#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* next;
};

void push(Node*& top, char data) {
    Node* newNode = new Node{data, top};
    top = newNode;
}

char pop(Node*& top) {
    if (top == nullptr) return '\0';
    Node* temp = top;
    char poppedValue = temp->data;
    top = top->next;
    delete temp;
    return poppedValue;
}

bool areBracketsBalanced(string expr) {
    Node* stackTop = nullptr;

    // 1. Loop setiap karakter dalam `expr`
    for (char c : expr) {
        // 2. Jika karakter adalah kurung buka '(', '{', '[', push ke stack
        if (c == '(' || c == '{' || c == '[') {
            push(stackTop, c);
        }
        // 3. Jika karakter adalah kurung tutup ')', '}', ']'
        else if (c == ')' || c == '}' || c == ']') {
            // a. Apakah stack kosong? Jika ya, berarti tidak ada pasangan buka = tidak seimbang
            if (stackTop == nullptr) {
                return false;
            }
            // b. Pop kurung buka terakhir dari stack.
            char open = pop(stackTop);
            //    Cek apakah kurung tutup cocok dengan kurung buka yang dipop
            if ((c == ')' && open != '(') ||
                (c == '}' && open != '{') ||
                (c == ']' && open != '[')) {
                return false; // Tidak cocok = tidak seimbang
            }
        }
    }
    // 4. Setelah loop selesai, jika stack kosong berarti semua kurung punya pasangan.
    //    Jika masih ada sisa di stack, berarti ada kurung buka yang tidak ditutup.
    return stackTop == nullptr;
}

int main() {
    string expr1 = "{[()]}";
    cout << expr1 << " = " << (areBracketsBalanced(expr1) ? "Seimbang" : "Tidak Seimbang") << endl;
    string expr2 = "{[(])}";
    cout << expr2 << " = " << (areBracketsBalanced(expr2) ? "Seimbang" : "Tidak Seimbang") << endl;
    return 0;
}