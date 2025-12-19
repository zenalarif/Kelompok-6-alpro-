#include "header.h"

Member daftarMember[MEMBERMAKS];
int jumlahMember = 0;

// Menghitung tgl_habis berdasarkan tgl_daftar + durasi hari
void hitungTanggalOtomatis(char *tglMulai, char *tglHasil, int jumlahHari) {
    int y, m, d;
    struct tm t = {0};

    // Parsing string "YYYY-MM-DD"
    if (sscanf(tglMulai, "%d-%d-%d", &y, &m, &d) != 3) {
        printf("Format tanggal salah!\n");
        return;
    }

    t.tm_year = y - 1900;
    t.tm_mon  = m - 1;
    t.tm_mday = d;

    // Tambah hari
    t.tm_mday += jumlahHari;
    
    // Normalisasi tanggal (misal 32 Jan -> 1 Feb)
    mktime(&t);

    // Tulis hasil ke string
    sprintf(tglHasil, "%04d-%02d-%02d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday);
}

// --- FILE HANDLING ---
void loadData() {
    FILE *fp = fopen(NAMAFILE, "r");
    if (fp == NULL) return;

    jumlahMember = 0;
    // Format baca disesuaikan dengan struct baru
    while (fscanf(fp, "%d|%49[^|]|%14[^|]|%d|%19[^|]|%10[^|]|%10[^|]|%ld\n", 
           &daftarMember[jumlahMember].id, 
           daftarMember[jumlahMember].nama, 
           daftarMember[jumlahMember].noTelepon,
           &daftarMember[jumlahMember].usia,
           daftarMember[jumlahMember].tipeMember, 
           daftarMember[jumlahMember].tglDaftar, 
           daftarMember[jumlahMember].tglHabis, 
           &daftarMember[jumlahMember].biaya) != EOF) {
        jumlahMember++;
    }
    fclose(fp);
}

void saveData() {
    FILE *fp = fopen(NAMAFILE, "w");
    if (fp == NULL) {
        printf("Gagal menyimpan data!\n");
        return;
    }
    for (int i = 0; i < jumlahMember; i++) {
        fprintf(fp, "%d|%s|%s|%d|%s|%s|%s|%ld\n", 
            daftarMember[i].id, 
            daftarMember[i].nama, 
            daftarMember[i].noTelepon,
            daftarMember[i].usia,
            daftarMember[i].tipeMember, 
            daftarMember[i].tglDaftar, 
            daftarMember[i].tglHabis, 
            daftarMember[i].biaya);
    }
    fclose(fp);
    printf("Data berhasil disimpan ke %s.\n", NAMAFILE);
}

// --- CRUD ---
void tambahMember() {
    if (jumlahMember >= MEMBERMAKS) {
        printf("Kapasitas penuh!\n");
        return;
    }

    Member m;
    m.id = (jumlahMember == 0) ? 1 : daftarMember[jumlahMember-1].id + 1;

    printf("================================================================\n");
    printf("||                     TAMPILKAN ANGGOTA                      ||\n");
    printf("================================================================\n");
    printf("Nama Member: ");
    scanf(" %[^\n]s", m.nama);
    
    printf("No Telepon: ");
    scanf(" %[^\n]s", m.noTelepon);

    printf("Usia: ");
    scanf("%d", &m.usia);

    printf("Tanggal Daftar (YYYY-MM-DD): ");
    scanf("%s", m.tglDaftar);

    printf("Tipe (1. Harian / 2. Bulanan): ");
    int pilihan;
    scanf("%d", &pilihan);

    if (pilihan == 1) {
        strcpy(m.tipeMember, "Harian");
        m.biaya = 20000;
        // Harian expired hari itu juga (durasi +0 hari dari tgl daftar)
        hitungTanggalOtomatis(m.tglDaftar, m.tglHabis, 0); 
    } else {
        strcpy(m.tipeMember, "Bulanan");
        m.biaya = 150000;
        // Bulanan expired +30 hari otomatis
        hitungTanggalOtomatis(m.tglDaftar, m.tglHabis, 30);
        printf("-> Expired otomatis diatur ke: %s\n", m.tglHabis);
    }

    daftarMember[jumlahMember] = m;
    jumlahMember++;
    saveData();
}

void tampilkanSemuaMember() {
    printf("========================================================================\n");
    printf("||                     DATA ANGGOTA FITNES JUNISA                       ||\n");
    printf("========================================================================\n");
    if (jumlahMember == 0) {
        printf("Data kosong.\n");
        return;
    }
    // Header tabel disesuaikan
    printf("\n%-3s %-15s %-13s %-3s %-8s %-11s %-11s %-10s\n", 
           "ID", "Nama", "No Telp", "Umur", "Tipe", "Daftar", "Exp", "Biaya");
    printf("----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < jumlahMember; i++) {
        printf("%-3d %-15s %-13s %-3d %-8s %-11s %-11s Rp%-10ld\n", 
            daftarMember[i].id, 
            daftarMember[i].nama, 
            daftarMember[i].noTelepon,
            daftarMember[i].usia,
            daftarMember[i].tipeMember, 
            daftarMember[i].tglDaftar, 
            daftarMember[i].tglHabis, 
            daftarMember[i].biaya);
    }
}

void updateMember() {
    int id, found = 0;
    printf("========================================================================\n");
    printf("||                     DATA ANGGOTA FITNES JUNISA                       ||\n");
    printf("========================================================================\n");
    printf("Masukkan ID member: ");
    scanf("%d", &id);

    for (int i = 0; i < jumlahMember; i++) {
        if (daftarMember[i].id == id) {
            found = 1;
            printf("Member: %s (%s)\n", daftarMember[i].nama, daftarMember[i].tipeMember);
            printf("1. Edit Profil (Nama/Telp/Usia)\n");
            printf("2. Perpanjang Member (+30 Hari)\n");
            printf("Pilihan: ");
            int opsi;
            scanf("%d", &opsi);

            if (opsi == 1) {
                printf("Nama Baru: ");
                scanf(" %[^\n]s", daftarMember[i].nama);
                printf("No Telp Baru: ");
                scanf(" %[^\n]s", daftarMember[i].noTelepon);
                printf("Usia Baru: ");
                scanf("%d", &daftarMember[i].usia);
                printf("Profil berhasil diupdate.\n");
            } 
            else if (opsi == 2) {
                if (strcmp(daftarMember[i].tipeMember, "Bulanan") == 0) {
                    // Perpanjang otomatis menggunakan tgl_habis yang lama sebagai tgl_mulai
                    char tglBaru[11];
                    hitungTanggalOtomatis(daftarMember[i].tglHabis, tglBaru, 30);
                    
                    strcpy(daftarMember[i].tglHabis, tglBaru);
                    daftarMember[i].biaya += 150000; // Tambah biaya ke akumulasi
                    
                    printf("Member diperpanjang hingga: %s\n", daftarMember[i].tglHabis);
                } else {
                    printf("Member Harian tidak bisa diperpanjang.\n");
                }
            }
            saveData();
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

// --- SEARCHING & SORTING ---
void cariMember() {
    char keyword[50];
    int found = 0;
    printf("Masukkan Nama yang dicari: ");
    scanf(" %[^\n]s", keyword);

    printf("\nHasil Pencarian:\n");
    for (int i = 0; i < jumlahMember; i++) {
        if (strstr(daftarMember[i].nama, keyword) != NULL) {
            printf("ID: %d | Nama: %s | Telp: %s | Exp: %s\n", 
                daftarMember[i].id, 
                daftarMember[i].nama,
                daftarMember[i].noTelepon, 
                daftarMember[i].tglHabis);
            found = 1;
        }
    }
    if (!found) printf("Tidak ditemukan.\n");
}

void urutkanMember() {
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

    printf("\n--- Member Kadaluarsa (Per %s) ---\n", today);
    int count = 0;
    for (int i = 0; i < jumlahMember; i++) {
        if (strcmp(daftarMember[i].tglHabis, today) < 0) {
            printf("- %s (Telp: %s) | Exp: %s\n", 
                daftarMember[i].nama, 
                daftarMember[i].noTelepon,
                daftarMember[i].tglHabis);
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
        if (strcmp(daftarMember[i].tipeMember, "Harian") == 0) {
            totalHarian += daftarMember[i].biaya;
        } else {
            totalBulanan += daftarMember[i].biaya;
        }
    }

    printf("\n--- Rekap Keuangan ---\n");
    printf("Pemasukan Member Harian  : Rp %ld\n", totalHarian);
    printf("Pemasukan Member Bulanan : Rp %ld\n", totalBulanan);
    printf("------------------------------\n");
    printf("TOTAL PEMASUKAN GYM      : Rp %ld\n", total);
}