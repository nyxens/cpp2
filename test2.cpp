#include <iostream>
#include <vector>
using namespace std;
typedef vector<vector<int>> matrix;
matrix add(const matrix &A, const matrix &B) {
    int n = A.size();
    matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
} 
matrix subtract(const matrix &A, const matrix &B) {
    int n = A.size();
    matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}
matrix strassen(const matrix &A, const matrix &B) {
    int n = A.size();
    matrix C(n, vector<int>(n));
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }
    int k = n / 2;
    matrix A11(k, vector<int>(k)), A12(k, vector<int>(k)), A21(k, vector<int>(k)), A22(k, vector<int>(k));
    matrix B11(k, vector<int>(k)), B12(k, vector<int>(k)), B21(k, vector<int>(k)), B22(k, vector<int>(k));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }
    matrix M1 = strassen(add(A11, A22), add(B11, B22));
    matrix M2 = strassen(add(A21, A22), B11);
    matrix M3 = strassen(A11, subtract(B12, B22));
    matrix M4 = strassen(A22, subtract(B21, B11));
    matrix M5 = strassen(add(A11, A12), B22);
    matrix M6 = strassen(subtract(A21, A11), add(B11, B12));
    matrix M7 = strassen(subtract(A12, A22), add(B21, B22));

    matrix C11 = add(subtract(add(M1, M4), M5), M7);
    matrix C12 = add(M3, M5);
    matrix C21 = add(M2, M4);
    matrix C22 = add(subtract(add(M1, M3), M2), M6);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    return C;
}

void printMatrix(const matrix &A) {
    for (auto &row : A) {
        for (auto val : row)
            cout << val << " ";
        cout << "\n";
    }
}

int main() {
    matrix A = {{1, 2, 3, 4},
                {5, 6, 7, 8},
                {9, 10, 11, 12},
                {13, 14, 15, 16}};

    matrix B = {{16, 15, 14, 13},
                {12, 11, 10, 9},
                {8, 7, 6, 5},
                {4, 3, 2, 1}};

    matrix C = strassen(A, B);

    cout << "Result of Strassen's multiplication:\n";
    printMatrix(C);

    return 0;
}
