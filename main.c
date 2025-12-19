#include "header.h"

int main() {
    int pilihan;
    loadData(); // Load data dari file saat program start

    do {
        printf("\n");
        printf("========================================================\n");
        printf("||        SISTEM ADMINISTRASI FITNESS CENTER           ||\n");
        printf("========================================================\n");
        printf("||  [1] TAMBAH ANGGOTA                                 ||\n");
        printf("||  [2] TAMPILKAN SEMUA ANGGOTA                        ||\n");
        printf("||  [3] CARI ANGGOTA                                   ||\n");
        printf("||  [4] URUTKAN ANGGOTA                                ||\n");
        printf("||  [5] UPDATE / PERPANJANG MEMBER                     ||\n");
        printf("||  [6] HAPUS ANGGOTA                                  ||\n");
        printf("||  [7] CEK STATUS KEDALUWARSA                         ||\n");
        printf("||  [8] LAPORAN KEUANGAN                               ||\n");
        printf("||  [0] KELUAR                                         ||\n");
        printf("========================================================\n");
        printf("||                 JUNISA FITNESS                      ||\n");
        printf("========================================================\n\n");
        printf("PILIH MENU : ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: tambahMember(); break;
            case 2: tampilkanSemuaMember(); break;
            case 3: cariMember(); break;
            case 4: urutkanMember(); break;
            case 5: updateMember(); break;
            case 6: hapusMember(); break;
            case 7: cekKadaluarsa(); break;
            case 8: rekapKeuangan(); break;
            case 0: printf("Aplikasi ditutup.\n"); break;
            default: printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);

    return 0;
}