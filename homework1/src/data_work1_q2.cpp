#include <iostream>

using namespace std;

void func(char S[], int n, int index, char current[], int currentSize) {
    
    if (index == n) {
        cout << "(";
        for (int i = 0; i < currentSize; ++i) {
            cout << current[i];
            if (i < currentSize - 1) {
                cout << ",";
            }
        }
        cout << ") ";
        return;
    }

    func(S, n, index + 1, current, currentSize);

    current[currentSize] = S[index];
    func(S, n, index + 1, current, currentSize + 1);
}

int main() {
    char S[] = { 'a', 'b', 'c'};
    int n = sizeof(S) / sizeof(S[0]);

    char current[1000];

    cout << "powerset (S) = { ";
    func(S, n, 0, current, 0);
    cout << "}" << endl;

}