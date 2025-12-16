#include "gym.h"

int main() {
    int pilihan;
    loadData(); // Muat data dari file saat program mulai

    do {
        printf("\n=== SISTEM MANAJEMEN GYM ===\n");
        printf("1. Tambah Anggota\n");
        printf("2. Tampilkan Semua Anggota\n");
        printf("3. Cari Anggota (Searching)\n");
        printf("4. Urutkan Anggota by Nama (Sorting)\n");
        printf("5. Update Data Anggota\n");
        printf("6. Hapus Anggota\n");
        printf("7. Cek Member Kadaluarsa\n");
        printf("8. Rekap Keuangan\n");
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
            case 0: printf("Terima kasih!\n"); break;
            default: printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);

    return 0;
}