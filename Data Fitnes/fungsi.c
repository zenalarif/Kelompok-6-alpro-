#include "gym.h"

Member daftarMember[MAX_MEMBERS];
int jumlahMember = 0;

// --- FILE HANDLING ---
void loadData() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) return; // File belum ada, abaikan

    jumlahMember = 0;
    while (fscanf(fp, "%d|%49[^|]|%19[^|]|%10[^|]|%10[^|]|%ld\n", 
           &daftarMember[jumlahMember].id, 
           daftarMember[jumlahMember].nama, 
           daftarMember[jumlahMember].tipe, 
           daftarMember[jumlahMember].tgl_daftar, 
           daftarMember[jumlahMember].tgl_habis, 
           &daftarMember[jumlahMember].biaya) != EOF) {
        jumlahMember++;
    }
    fclose(fp);
}

void saveData() {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("Gagal menyimpan data!\n");
        return;
    }
    for (int i = 0; i < jumlahMember; i++) {
        fprintf(fp, "%d|%s|%s|%s|%s|%ld\n", 
            daftarMember[i].id, 
            daftarMember[i].nama, 
            daftarMember[i].tipe, 
            daftarMember[i].tgl_daftar, 
            daftarMember[i].tgl_habis, 
            daftarMember[i].biaya);
    }
    fclose(fp);
    printf("Data berhasil disimpan ke %s.\n", FILE_NAME);
}

// --- CRUD ---
void tambahMember() {
    if (jumlahMember >= MAX_MEMBERS) {
        printf("Kapasitas penuh!\n");
        return;
    }

    Member m;
    // Auto Increment ID sederhana
    m.id = (jumlahMember == 0) ? 1 : daftarMember[jumlahMember-1].id + 1;

    printf("\n--- Tambah Anggota ---\n");
    printf("Nama Member: ");
    scanf(" %[^\n]s", m.nama);
    
    printf("Tipe (1. Harian / 2. Bulanan): ");
    int pilihan;
    scanf("%d", &pilihan);

    printf("Tanggal Daftar (YYYY-MM-DD): ");
    scanf("%s", m.tgl_daftar);

    if (pilihan == 1) {
        strcpy(m.tipe, "Harian");
        m.biaya = 20000;
        strcpy(m.tgl_habis, m.tgl_daftar); // Expired hari itu juga
    } else {
        strcpy(m.tipe, "Bulanan");
        m.biaya = 150000;
        
        // Logika sederhana penambahan bulan (manual input untuk akurasi di C basic)
        printf("Masukkan Tanggal Habis (misal +30 hari) (YYYY-MM-DD): ");
        scanf("%s", m.tgl_habis);
    }

    daftarMember[jumlahMember] = m;
    jumlahMember++;
    saveData();
}

void tampilkanSemuaMember() {
    if (jumlahMember == 0) {
        printf("Data kosong.\n");
        return;
    }
    printf("\n%-4s %-20s %-10s %-12s %-12s %-10s\n", "ID", "Nama", "Tipe", "Daftar", "Exp", "Biaya");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < jumlahMember; i++) {
        printf("%-4d %-20s %-10s %-12s %-12s Rp%-10ld\n", 
            daftarMember[i].id, 
            daftarMember[i].nama, 
            daftarMember[i].tipe, 
            daftarMember[i].tgl_daftar, 
            daftarMember[i].tgl_habis, 
            daftarMember[i].biaya);
    }
}

void updateMember() {
    int id, found = 0;
    printf("Masukkan ID member yang akan diedit: ");
    scanf("%d", &id);

    for (int i = 0; i < jumlahMember; i++) {
        if (daftarMember[i].id == id) {
            printf("Nama Baru: ");
            scanf(" %[^\n]s", daftarMember[i].nama);
            printf("Perpanjang Tanggal Habis (YYYY-MM-DD): ");
            scanf("%s", daftarMember[i].tgl_habis);
            saveData();
            printf("Data berhasil diupdate.\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("ID tidak ditemukan.\n");
}

void hapusMember() {
    int id, found = 0;
    printf("Masukkan ID member yang akan dihapus: ");
    scanf("%d", &id);

    for (int i = 0; i < jumlahMember; i++) {
        if (daftarMember[i].id == id) {
            // Geser elemen setelahnya ke kiri
            for (int j = i; j < jumlahMember - 1; j++) {
                daftarMember[j] = daftarMember[j + 1];
            }
            jumlahMember--;
            saveData();
            printf("Member berhasil dihapus.\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("ID tidak ditemukan.\n");
}

// --- ALGORITMA SEARCHING (Linear Search) ---
void cariMember() {
    char keyword[50];
    int found = 0;
    printf("Masukkan Nama yang dicari: ");
    scanf(" %[^\n]s", keyword);

    printf("\nHasil Pencarian:\n");
    for (int i = 0; i < jumlahMember; i++) {
        // Mencari substring nama
        if (strstr(daftarMember[i].nama, keyword) != NULL) {
            printf("ID: %d | Nama: %s | Tipe: %s | Exp: %s\n", 
                daftarMember[i].id, 
                daftarMember[i].nama, 
                daftarMember[i].tipe, 
                daftarMember[i].tgl_habis); // <--- Menampilkan tanggal habis
            // ---------------------------
            found = 1;
        }
    }
    if (!found) printf("Tidak ditemukan.\n");
}

// --- ALGORITMA SORTING (Bubble Sort) ---
void urutkanMember() {
    // Sort berdasarkan Nama (Ascending)
    for (int i = 0; i < jumlahMember - 1; i++) {
        for (int j = 0; j < jumlahMember - i - 1; j++) {
            if (strcmp(daftarMember[j].nama, daftarMember[j+1].nama) > 0) {
                Member temp = daftarMember[j];
                daftarMember[j] = daftarMember[j+1];
                daftarMember[j+1] = temp;
            }
        }
    }
    printf("Data berhasil diurutkan berdasarkan Nama.\n");
    tampilkanSemuaMember();
}

// --- FITUR KHUSUS ---
void cekKadaluarsa() {
    char today[11];
    printf("Masukkan Tanggal Hari Ini (YYYY-MM-DD): ");
    scanf("%s", today);

    printf("\n--- Member Kadaluarsa ---\n");
    int count = 0;
    for (int i = 0; i < jumlahMember; i++) {
        // strcmp string tanggal format YYYY-MM-DD bekerja secara kronologis
        if (strcmp(daftarMember[i].tgl_habis, today) < 0) {
            printf("- %s (Exp: %s)\n", daftarMember[i].nama, daftarMember[i].tgl_habis);
            count++;
        }
    }
    if (count == 0) printf("Tidak ada member yang kadaluarsa.\n");
}

void rekapKeuangan() {
    long total = 0;
    long totalHarian = 0;
    long totalBulanan = 0;

    for (int i = 0; i < jumlahMember; i++) {
        total += daftarMember[i].biaya;
        if (strcmp(daftarMember[i].tipe, "Harian") == 0) {
            totalHarian += daftarMember[i].biaya;
        } else {
            totalBulanan += daftarMember[i].biaya;
        }
    }

    printf("\n--- Rekap Keuangan ---\n");
    printf("Total Pemasukan Harian  : Rp %ld\n", totalHarian);
    printf("Total Pemasukan Bulanan : Rp %ld\n", totalBulanan);
    printf("------------------------------\n");
    printf("TOTAL KESELURUHAN       : Rp %ld\n", total);
}