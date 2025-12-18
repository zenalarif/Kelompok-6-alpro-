#include "header.h"

int main() {
    int pilihan;
    loadData(); // Load data dari file saat program start

    do {
        printf("\n======= Sistem Informasi Administrasi Keanggotaan Fitness =====\n");
        printf("1. Tambah Anggota\n");
        printf("2. Tampilkan Semua Anggota\n");
        printf("3. Cari Anggota\n");
        printf("4. Urutkan Anggota\n");
        printf("5. Update / Perpanjang Member\n");
        printf("6. Hapus Anggota\n");
        printf("7. Cek Status Kadaluarsa\n");
        printf("8. Laporan Keuangan\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
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