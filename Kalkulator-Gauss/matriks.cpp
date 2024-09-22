#include "matriks.h"

const double epsilon = 1e-9; // Toleransi untuk menganggap angka sebagai nol

int createMatrix(int baris, int kolom, double matrix[M][N]) {
    int jumlahElemen = 0;
    for (int i = 1; i <= baris; i++) {
        for (int j = 1; j <= kolom; j++) {
            cout << "Masukkan Angka pada [" << i << "][" << j << "] : ";
            cin >> matrix[i][j];
            jumlahElemen++;
        }
    }
    return jumlahElemen;
}

void printMatrix(int baris, int kolom, double matrix[M][N]) {
    for (int i = 1; i <= baris; i++) {
        for (int j = 1; j <= kolom; j++) {
            cout << setw(10) << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void createIdentityMatrix(int n, double matrix[M][N]) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            matrix[i][j] = (i == j) ? 1 : 0;
        }
    }
}

void findLeadingOnes(int baris, int kolom, double matrix[M][N], int pivotRows[M], int pivotCols[N], int &pivotCount) {
    pivotCount = 0;
    for (int i = 1, j = 1; i <= baris && j <= kolom; j++) {
        int maxRow = i;
        for (int k = i + 1; k <= baris; k++) {
            if (abs(matrix[k][j]) > abs(matrix[maxRow][j])) {
                maxRow = k;
            }
        }
        
        if (abs(matrix[maxRow][j]) > epsilon) {
            if (i != maxRow) {
                for (int l = 1; l <= kolom; l++) {
                    swap(matrix[i][l], matrix[maxRow][l]);
                }
            }
            
            double pivot = matrix[i][j];
            for (int l = 1; l <= kolom; l++) {
                matrix[i][l] /= pivot;
            }
            
            pivotCols[pivotCount] = j;
            pivotRows[pivotCount] = i;
            pivotCount++;
            i++;
        }
    }
}

void makeZeros(int baris, int kolom, double matrix[M][N], int pivotRows[M], int pivotCols[N], int pivotCount) {
    for (int p = 0; p < pivotCount; p++) {
        int col = pivotCols[p];
        int row = pivotRows[p];

        // Normalisasi pivot menjadi 1
        double pivotValue = matrix[row][col];
        if (abs(pivotValue) > epsilon) {
            for (int j = 1; j <= kolom; j++) {
                matrix[row][j] /= pivotValue;
            }
        }

        // Mengeliminasi elemen di atas dan di bawah pivot
        for (int i = 1; i <= baris; i++) {
            if (i != row) {  // Lewati baris pivot
                double factor = matrix[i][col];
                for (int j = 1; j <= kolom; j++) {
                    matrix[i][j] -= factor * matrix[row][j];
                    if (abs(matrix[i][j]) < epsilon) matrix[i][j] = 0;  // Perbaikan presisi
                }
            }
        }
    }
}

bool isReducedRowEchelonForm(int baris, int kolom, double matrix[M][N]) {
    int leadingOne = 1;
    for (int i = 1; i <= baris; i++) {
        while (leadingOne <= kolom && abs(matrix[i][leadingOne]) < epsilon) {
            leadingOne++;
        }
        if (leadingOne > kolom) return true;
        if (abs(matrix[i][leadingOne] - 1) > epsilon) return false;
        for (int j = 1; j <= baris; j++) {
            if (j != i && abs(matrix[j][leadingOne]) > epsilon) return false;
        }
    }
    return true;
}

bool isTrivial(int baris, int kolom, double matrix[M][N]) {
    for (int i = 1; i <= baris; i++) {
        bool allZero = true;
        for (int j = 1; j < kolom; j++) {
            if (abs(matrix[i][j]) > epsilon) {
                allZero = false;
                break;
            }
        }
        if (allZero && abs(matrix[i][kolom]) > epsilon) {
            return false; // Sistem tidak konsisten
        }
    }
    return true; // Sistem konsisten (mungkin memiliki solusi parametrik)
}

void determineFinalEquations(int baris, int kolom, double matrix[M][N], int pivotRows[M], int pivotCols[N], int pivotCount) {
    bool isBasic[N] = {false};
    for (int i = 0; i < pivotCount; i++) {
        isBasic[pivotCols[i]] = true;
    }
    
    cout << "Solusi Sistem Persamaan adalah:\n";
    char param = 'r';
    for (int i = 1; i < kolom; i++) {
        cout << "x" << i << " = ";
        if (isBasic[i]) {
            int row = -1;
            for (int j = 0; j < pivotCount; j++) {
                if (pivotCols[j] == i) {
                    row = pivotRows[j];
                    break;
                }
            }
            
            bool hasNonZeroTerm = false;
            for (int j = 1; j < kolom; j++) {
                if (!isBasic[j] && abs(matrix[row][j]) > epsilon) {
                    if (hasNonZeroTerm) cout << (matrix[row][j] < 0 ? " - " : " + ");
                    else if (matrix[row][j] < 0) cout << "-";
                    if (abs(abs(matrix[row][j]) - 1) > epsilon) cout << abs(matrix[row][j]);
                    cout << param;
                    param++;
                    hasNonZeroTerm = true;
                }
            }
            
            double constantTerm = matrix[row][kolom];
            if (abs(constantTerm) > epsilon) {
                if (hasNonZeroTerm) cout << (constantTerm < 0 ? " - " : " + ");
                else if (constantTerm < 0) cout << "-";
                cout << abs(constantTerm);
            } else if (!hasNonZeroTerm) {
                cout << "0";
            }
        } else {
            cout << param;
            param++;
        }
        cout << endl;
    }
}

void applyOperationsToIdentity(int n, double matrix[M][N], double identity[M][N]) {
    for (int i = 1; i <= n; i++) {
        if (abs(matrix[i][i]) < epsilon) {
            cout << "Matriks tidak memiliki invers.\n";
            return;
        }
        
        double pivot = matrix[i][i];
        for (int j = 1; j <= n; j++) {
            matrix[i][j] /= pivot;
            identity[i][j] /= pivot;
        }
        
        for (int k = 1; k <= n; k++) {
            if (k != i) {
                double factor = matrix[k][i];
                for (int j = 1; j <= n; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                    identity[k][j] -= factor * identity[i][j];
                }
            }
        }
    }
}

// Fungsi eliminasi Gauss-Jordan untuk melakukan eliminasi hingga RREF
void eliminasiGaussJordan(int baris, int kolom, double matrix[M][N]) {
    cout << "===== Eliminasi Gauss Jordan =====\n";
    
    cout << "\nMatriks Augmented Awal:\n";
    printMatrix(baris, kolom, matrix);
    
    int pivotRows[M], pivotCols[N], pivotCount;
    findLeadingOnes(baris, kolom, matrix, pivotRows, pivotCols, pivotCount);
    
    // Membuat leading ones dan mengeliminasi elemen di atas dan di bawah
    makeZeros(baris, kolom, matrix, pivotRows, pivotCols, pivotCount);

    // Memastikan matriks sudah dalam bentuk eselon baris tereduksi
    if (!isReducedRowEchelonForm(baris, kolom, matrix)) {
        cout << "Peringatan: Matriks mungkin belum dalam bentuk eselon baris tereduksi.\n";
    }
    
    cout << "\nMatriks Setelah Eliminasi Gauss-Jordan:\n";
    printMatrix(baris, kolom, matrix);
    
    if (isTrivial(baris, kolom, matrix)) {
        determineFinalEquations(baris, kolom, matrix, pivotRows, pivotCols, pivotCount);
    } else {
        cout << "Sistem persamaan tidak konsisten.\n";
    }
}

void inversGaussJordan(int n, double matrix[M][N]) {
    cout << "============Invers Metode Gauss Jordan============\n";
    
    cout << "\nMatriks Awal:\n";
    printMatrix(n, n, matrix);
    
    double identity[M][N];
    createIdentityMatrix(n, identity);
    
    applyOperationsToIdentity(n, matrix, identity);
    
    cout << "\nMatriks Invers adalah:\n";
    printMatrix(n, n, identity);
}