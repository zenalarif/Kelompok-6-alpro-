#ifndef GYM_H
#define GYM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 100
#define FILE_NAME "data_gym.txt"

// Struktur Data Member
typedef struct {
    int id;
    char nama[50];
    char tipe[20];       // "Harian" atau "Bulanan"
    char tgl_daftar[11]; // Format YYYY-MM-DD
    char tgl_habis[11];  // Format YYYY-MM-DD
    long biaya;
} Member;

// Variabel Global (diakses via gym.c)
extern Member daftarMember[MAX_MEMBERS];
extern int jumlahMember;

// --- Prototype Fungsi ---

// File Handling
void loadData();
void saveData();

// CRUD
void tambahMember();
void tampilkanSemuaMember();
void updateMember();
void hapusMember();

// Fitur Khusus
void cariMember();         // Algoritma Searching (Linear Search)
void urutkanMember();      // Algoritma Sorting (Bubble Sort)
void cekKadaluarsa();      // Cek member expired
void rekapKeuangan();      // Total pemasukan

// Helper
void getTanggalHariIni(char *buffer); // Meminta input tanggal hari ini

#endif