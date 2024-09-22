#include "matriks.h"

double A[M][N];
double B[M][N];
double C[M][N];

int main() {
    int pilihan;
    int baris, kolom, jumlahElemen;

    do {
        cout << "\n<---------- Program Operasi Lanjutan Matriks ---------->\n";
        cout << "--------------------------------------------------------\n";
        cout << "\nPilihan Menu :\n";
        cout << "1. Eliminasi dengan metode Gauss-Jordan\n";
        cout << "2. Menghitung invers matriks dengan metode Gauss-Jordan\n";
        cout << "0. Keluar\n";
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;

        switch(pilihan) {
            case 1:
                cout << "Masukkan jumlah baris : ";
                cin >> baris;
                cout << "Masukkan jumlah kolom : ";
                cin >> kolom;
                jumlahElemen = createMatrix(baris, kolom, A);
                eliminasiGaussJordan(baris, kolom, A);
                break;
            case 2:
                cout << "Masukkan ukuran matriks (n x n): ";
                cin >> baris;
                kolom = baris;
                jumlahElemen = createMatrix(baris, kolom, A);
                createIdentityMatrix(baris, B);  // Membuat matriks identitas
                inversGaussJordan(baris, A);
                break;
            case 0:
                cout << "Terima kasih telah menggunakan program ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                break;
        }
    } while(pilihan != 0);

    return 0;
}