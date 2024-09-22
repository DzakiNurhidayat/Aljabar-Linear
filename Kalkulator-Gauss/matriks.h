#ifndef MATRIKS_H
#define MATRIKS_H

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const int M = 100;
const int N = 100;

extern double A[M][N];
extern double B[M][N];
extern double C[M][N];

int createMatrix(int baris, int kolom, double matrix[M][N]);
void printMatrix(int baris, int kolom, double matrix[M][N]);
void createIdentityMatrix(int n, double matrix[M][N]);

// Modul Utama 
void eliminasiGaussJordan(int baris, int kolom, double matrix[M][N]);
void inversGaussJordan(int n, double matrix[M][N]);


// Modul Pendukung / Sub Modul
void findLeadingOnes(int baris, int kolom, double matrix[M][N], int pivotRows[M], int pivotCols[N], int &pivotCount);
void makeZeros(int baris, int kolom, double matrix[M][N], int pivotRows[M], int pivotCols[N], int pivotCount);
bool isTrivial(int baris, int kolom, double matrix[M][N]);
void determineFinalEquations(int baris, int kolom, double matrix[M][N], int pivotRows[M], int pivotCols[N], int pivotCount);
void applyOperationsToIdentity(int n, double matrix[M][N], double identity[M][N]);
bool isReducedRowEchelonForm(int baris, int kolom, double matrix[M][N]);

#endif /* MATRIKS_H */