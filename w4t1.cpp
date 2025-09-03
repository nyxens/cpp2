#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
using namespace std;
using namespace std::chrono;
typedef vector<vector<int>> matrix;
matrix normal(const matrix &A,const matrix &B,int ar,int ac,int br,int bc,int size){
    matrix C(size,vector<int>(size,0));
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            int sum = 0;
            for(int k = 0; k < size; k++){
                sum += A[ar + i][ac + k] * B[br + k][bc + j];
            }
            C[i][j] = sum;
        }
    }
    return C;
}
matrix add(const matrix &A,const matrix &B,int ar,int ac,int br,int bc,int size){
    matrix C(size,vector<int>(size));
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            C[i][j] = A[ar+i][ac+j] + B[br+i][bc+j];
    return C;
}
matrix subtract(const matrix &A,const matrix &B,int ar,int ac,int br,int bc,int size){
    matrix C(size,vector<int>(size));
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            C[i][j] = A[ar+i][ac+j] - B[br+i][bc+j];
    return C;
}
matrix strassen(const matrix &A,const matrix &B,int ar,int ac,int br,int bc,int size){
    if(size <= 64){
        return normal(A,B,ar,ac,br,bc,size);
    }
    int k = size / 2;
    matrix M1 = strassen(add(A,A,ar,ac,ar+k,ac+k,k),add(B,B,br,bc,br+k,bc+k,k),0,0,0,0,k);
    matrix M2 = strassen(add(A,A,ar+k,ac,ar+k,ac+k,k),B,0,0,br,bc,k);
    matrix M3 = strassen(A,subtract(B,B,br,bc+k,br+k,bc+k,k),ar,ac,0,0,k);
    matrix M4 = strassen(A,subtract(B,B,br+k,bc,br,bc,k),ar+k,ac+k,0,0,k);
    matrix M5 = strassen(add(A,A,ar,ac,ar,ac+k,k),B,0,0,br+k,bc+k,k);
    matrix M6 = strassen(subtract(A,A,ar+k,ac,ar,ac,k),add(B,B,br,bc,br,bc+k,k),0,0,0,0,k);
    matrix M7 = strassen(subtract(A,A,ar,ac+k,ar+k,ac+k,k),add(B,B,br+k,bc,br+k,bc+k,k),0,0,0,0,k);
    matrix C(size,vector<int>(size));
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j+k] = M3[i][j] + M5[i][j];                      
            C[i+k][j] = M2[i][j] + M4[i][j];                      
            C[i+k][j+k] = M1[i][j] + M3[i][j] - M2[i][j] + M6[i][j];
        }
    }
    return C;
}
void fillrand(matrix &A){
    int n = A.size();
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            A[i][j] = rand() % 100;
}
int main(){
    vector<int> sizes ={2,4,8,16,64,128,256,512,1024};
    srand(time(0));
    ofstream fout("matrix.dat");
    fout << "# Size Normal Strassen\n";
    for(int n: sizes){
        matrix a(n,vector<int>(n)),b(n,vector<int>(n)),c;
        fillrand(a); 
        b = a;

        auto t1 = high_resolution_clock::now();
        c = normal(a,b,0,0,0,0,n);
        auto t2 = high_resolution_clock::now();
        auto bf = duration_cast<milliseconds>(t2 - t1).count();

        t1 = high_resolution_clock::now();
        c = strassen(a,b,0,0,0,0,n);
        t2 = high_resolution_clock::now();
        auto sm = duration_cast<milliseconds>(t2 - t1).count();

        fout << n << " " << bf << " " << sm << "\n";
    }
    fout.close();
    cout << "Data written to matrix.dat\n";
    return 0;
}
