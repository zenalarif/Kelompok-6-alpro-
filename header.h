#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Library manipulasi tanggal otomatis

#define MEMBERMAKS 100
#define NAMAFILE "dataFitnes.txt"

// Struktur Data
typedef struct {
    int id;
    char nama[50];
    char noTelepon[15]; 
    int usia;            
    char tipeMember[20];  // "Harian" atau "Bulanan"
    char tglDaftar[11]; // Format YYYY-MM-DD
    char tglHabis[11]; 
    long biaya;
} Member;

// Variabel Global
extern Member daftarMember[MEMBERMAKS];
extern int jumlahMember;

// File Handling
void loadData();
void saveData();

// Helper Date
void hitungTanggalOtomatis(char *tglMulai, char *tglHasil, int jumlahHari);

// CRUD
void tambahMember();
void tampilkanSemuaMember();
void updateMember();
void hapusMember();

// Fitur Tambahan
void cariMember();         
void urutkanMember();      
void cekKadaluarsa();      
void rekapKeuangan();      

#endif