#include "anggota.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

// Fungsi utilitas untuk membersihkan input buffer setelah scanf
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Fungsi untuk menerima input data anggota dari pengguna
void input_anggota(Anggota *a) {
    printf("Masukkan ID Anggota: ");
    if (scanf("%d", &a->id) != 1) { clear_input_buffer(); return; }
    
    printf("Masukkan Nama Anggota: ");
    clear_input_buffer(); // Bersihkan buffer sebelum membaca string
    if (scanf("%99[^\n]", a->nama) != 1) { clear_input_buffer(); return; }
    
    printf("Masukkan Telepon: ");
    clear_input_buffer();
    if (scanf("%14[^\n]", a->telepon) != 1) { clear_input_buffer(); return; }

    // Set tanggal daftar dan kadaluarsa
    a->tgl_daftar = time(NULL); // Tanggal daftar: hari ini
    
    int bulan_member;
    printf("Lama Membership (dalam bulan): ");
    if (scanf("%d", &bulan_member) != 1) { clear_input_buffer(); return; }

    // Hitung tanggal kadaluarsa (sederhana: 30 hari/bulan)
    // Dikalikan 30 hari * 24 jam * 60 menit * 60 detik
    long detik_tambahan = (long)bulan_member * 30 * 24 * 60 * 60; 
    a->tgl_kadaluarsa = a->tgl_daftar + detik_tambahan;
}

// Fungsi untuk menampilkan Menu Utama
void tampilkan_menu() {
    printf("\n\n=== SISTEM MANAJEMEN DATA ANGGOTA GYM ===\n");
    printf("1. Tambah Anggota Baru\n");
    printf("2. Tampilkan Semua Anggota\n");
    printf("3. Cari Detail Anggota (by ID)\n");
    printf("4. Perbarui Data Anggota\n");
    printf("5. Hapus Anggota\n");
    printf("6. Anggota Akan Kadaluarsa (7 Hari)\n");
    printf("7. Keluar\n");
    printf("Pilihan Anda: ");
}

int main() {
    int pilihan;
    int id_target;
    Anggota a_input;

    while (1) {
        tampilkan_menu();
        if (scanf("%d", &pilihan) != 1) {
             clear_input_buffer();
             continue;
        }

        switch (pilihan) {
            case 1: // CREATE
                printf("\n--- Tambah Anggota Baru ---\n");
                input_anggota(&a_input);
                create_anggota(a_input);
                break;
            case 2: // READ ALL
                printf("\n--- Daftar Semua Anggota ---\n");
                read_all_anggota();
                break;
            case 3: // READ BY ID
                printf("\n--- Cari Detail Anggota ---\n");
                printf("Masukkan ID Anggota: ");
                if (scanf("%d", &id_target) != 1) { clear_input_buffer(); break; }
                read_anggota_by_id(id_target);
                break;
            case 4: // UPDATE
                printf("\n--- Perbarui Data Anggota ---\n");
                printf("Masukkan ID Anggota yang ingin diperbarui: ");
                if (scanf("%d", &id_target) != 1) { clear_input_buffer(); break; }
                
                printf("Masukkan Data Baru (ID akan tetap: %d):\n", id_target);
                input_anggota(&a_input);
                a_input.id = id_target; // Pastikan ID data baru sama dengan target
                update_anggota(id_target, a_input);
                break;
            case 5: // DELETE
                printf("\n--- Hapus Anggota ---\n");
                printf("Masukkan ID Anggota yang ingin dihapus: ");
                if (scanf("%d", &id_target) != 1) { clear_input_buffer(); break; }
                delete_anggota(id_target);
                break;
            case 6: // REKAP KADALUARSA
                rekap_kadaluarsa(7); // Panggil fungsi rekap untuk 7 hari
                break;
            case 7:
                printf("\nProgram selesai. Sampai jumpa!\n");
                return 0;
            default:
                printf("\nOpsi tidak valid. Silakan coba lagi.\n");
        }
    }
    return 0;
}