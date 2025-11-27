#include "anggota.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* format_tanggal(time_t timestamp) {
    // time_t 0 akan diabaikan (untuk menghindari tanggal 1970)
    if (timestamp == 0) {
        return strdup("N/A"); 
    }
    
    // Alokasi memori untuk menyimpan string tanggal (DD-MM-YYYY)
    char *date_str = (char*)malloc(11 * sizeof(char)); 
    if (date_str == NULL) {
        perror("Gagal alokasi memori");
        return strdup("Error");
    }

    struct tm *local_time;
    local_time = localtime(&timestamp);
    
    // Format ke DD-MM-YYYY
    strftime(date_str, 11, "%d-%m-%Y", local_time);
    return date_str;
}

// --- C (CREATE) ---

void create_anggota(Anggota a) {
    FILE *file = fopen(FILENAME, "ab");
    if (file == NULL) {
        perror("Error: Gagal membuka file untuk menulis");
        return;
    }

    fwrite(&a, sizeof(Anggota), 1, file);
    printf("\nData Anggota (ID %d) berhasil ditambahkan.\n", a.id);
    
    fclose(file);
}

// read

void read_all_anggota() {
    Anggota a;
    FILE *file = fopen(FILENAME, "rb");
    int counter = 0;

    if (file == NULL) {
        printf("\n Belum ada data Anggota yang tersimpan.\n");
        return;
    }

    printf("\n========================================================================================\n");
    printf("| ID  | Nama (100) | Telepon (15) | Tgl Daftar | Tgl Kadaluarsa |\n");
    printf("========================================================================================\n");

    while (fread(&a, sizeof(Anggota), 1, file) == 1) {
        char *daftar_str = format_tanggal(a.tgl_daftar);
        char *kadaluarsa_str = format_tanggal(a.tgl_kadaluarsa);

        printf("| %-3d | %-10s | %-12s | %-10s | %-14s |\n", 
               a.id, a.nama, a.telepon, daftar_str, kadaluarsa_str);
        
        free(daftar_str);
        free(kadaluarsa_str);
        counter++;
    }
    printf("========================================================================================\n");

    if (counter == 0) {
         printf("   (Tidak ada data yang tersedia)\n");
         printf("========================================================================================\n");
    }

    fclose(file);
}

void read_anggota_by_id(int id_target) {
    Anggota a;
    FILE *file = fopen(FILENAME, "rb");
    bool ditemukan = false;

    if (file == NULL) {
        printf("\nBelum ada data Anggota.\n");
        return;
    }

    while (fread(&a, sizeof(Anggota), 1, file) == 1) {
        if (a.id == id_target) {
            ditemukan = true;
            char *daftar_str = format_tanggal(a.tgl_daftar);
            char *kadaluarsa_str = format_tanggal(a.tgl_kadaluarsa);

            printf("\n--- DETAIL ANGGOTA (ID %d) ---\n", id_target);
            printf("Nama: %s\n", a.nama);
            printf("Telepon: %s\n", a.telepon);
            printf("Tanggal Daftar: %s\n", daftar_str);
            printf("Tanggal Kadaluarsa: %s\n", kadaluarsa_str);
            printf("------------------------------\n");

            free(daftar_str);
            free(kadaluarsa_str);
            break;
        }
    }

    if (!ditemukan) {
        printf("\nAnggota dengan ID %d tidak ditemukan.\n", id_target);
    }
    fclose(file);
}


// update

void update_anggota(int id_target, Anggota data_baru) {
    Anggota a;
    FILE *file = fopen(FILENAME, "r+b"); // r+b: Read dan Write Binary
    
    if (file == NULL) {
        perror("Error: Gagal membuka file");
        return;
    }

    int ditemukan = 0;

    while (fread(&a, sizeof(Anggota), 1, file) == 1) {
        if (a.id == id_target) {
            ditemukan = 1;
            long posisi_awal_struct = ftell(file) - sizeof(Anggota);
            fseek(file, posisi_awal_struct, SEEK_SET);
            fwrite(&data_baru, sizeof(Anggota), 1, file);
            
            printf("\nData Anggota (ID %d) berhasil diperbarui.\n", id_target);
            break; 
        }
    }

    if (!ditemukan) {
        printf("\nAnggota dengan ID %d tidak ditemukan. Gagal update.\n", id_target);
    }

    fclose(file);
}

// delete

void delete_anggota(int id_target) {
    Anggota a;
    FILE *file_asli = fopen(FILENAME, "rb");
    FILE *file_temp = fopen("temp.dat", "wb"); 
    
    if (file_asli == NULL || file_temp == NULL) {
        perror("Error: Gagal membuka file");
        if (file_asli) fclose(file_asli);
        if (file_temp) fclose(file_temp);
        return;
    }

    int ditemukan = 0;

    while (fread(&a, sizeof(Anggota), 1, file_asli) == 1) {
        if (a.id == id_target) {
            ditemukan = 1;
        } else {
            fwrite(&a, sizeof(Anggota), 1, file_temp);
        }
    }

    fclose(file_asli);
    fclose(file_temp);

    if (ditemukan) {
        remove(FILENAME);             
        rename("temp.dat", FILENAME); 
        printf("\nData Anggota (ID %d) berhasil dihapus.\n", id_target);
    } else {
        remove("temp.dat"); 
        printf("\nAnggota dengan ID %d tidak ditemukan. Gagal hapus.\n", id_target);
    }
}

void rekap_kadaluarsa(int hari_batas) {
    Anggota a;
    FILE *file = fopen(FILENAME, "rb");
    int counter = 0;

    if (file == NULL) {
        printf("\nBelum ada data Anggota yang tersimpan.\n");
        return;
    }
    time_t now = time(NULL);
    time_t batas_waktu = now + (long)hari_batas * 24 * 60 * 60; 

    printf("\n\n--- REKAP ANGGOTA AKAN KADALUARSA DALAM %d HARI ---\n", hari_batas);
    printf("========================================================================\n");
    printf("| ID  | Nama (100) | Telepon (15) | Tgl Kadaluarsa | Sisa Hari |\n");
    printf("========================================================================\n");

    while (fread(&a, sizeof(Anggota), 1, file) == 1) {
        if (a.tgl_kadaluarsa > now && a.tgl_kadaluarsa <= batas_waktu) {
            double detik_tersisa = difftime(a.tgl_kadaluarsa, now);
            int hari_tersisa = (int)(detik_tersisa / (24 * 60 * 60)) + 1;
            char *kadaluarsa_str = format_tanggal(a.tgl_kadaluarsa);

            printf("| %-3d | %-10s | %-12s | %-14s | %-9d |\n", 
                   a.id, a.nama, a.telepon, kadaluarsa_str, hari_tersisa);
            
            free(kadaluarsa_str);
            counter++;
        }
    }
    printf("========================================================================\n");

    if (counter == 0) {
         printf("   (Tidak ada anggota yang akan kadaluarsa dalam %d hari.)\n", hari_batas);
         printf("========================================================================\n");
    }

    fclose(file);
}