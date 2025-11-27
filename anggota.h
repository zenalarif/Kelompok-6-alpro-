#ifndef ANGGOTA_H
#define ANGGOTA_H

#include <stdio.h>
#include <time.h> 

// Definisi Struktur Data Anggota
typedef struct {
    int id;
    char nama[100];
    char telepon[15];
    time_t tgl_daftar; // Tanggal pendaftaran
    time_t tgl_kadaluarsa; // Tanggal kadaluarsa member
} Anggota;

#define FILENAME "data_anggota_gym.dat"

// deklarari fungsi crud

// Create
void create_anggota(Anggota a);

// Read
void read_all_anggota();
void read_anggota_by_id(int id_target);

// Update
void update_anggota(int id_target, Anggota data_baru);

// Delete
void delete_anggota(int id_target);

// fungsi rekap kadaluarsa
void rekap_kadaluarsa(int hari_batas);

// Fungsi konversi tanggal
char* format_tanggal(time_t timestamp);

#endif