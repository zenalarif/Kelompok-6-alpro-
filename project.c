#include <stdio.h>
<<<<<<< HEAD
#include <string.h>
#include <stdlib.h>

#define MAX_MEMBER 100

struct Member {
    char nohp[20];
    char nama[50];
    char paket[30];
    int umur;
};

struct Member dataMember[MAX_MEMBER];
int jumlahMember = 0;

// ======== PROTOTYPE ========
void muatDariFile();
void simpanKeFile();
void tambahMember();
void tampilMember();
void cariMember();
void editMember();
void hapusMember();
void sortByNohp();
void sortByNama();

// ======== LOAD DATA DARI FILE ========
void muatDariFile() {
    FILE *file = fopen("data_gym.txt", "r");
    if (!file) return;

    jumlahMember = 0;
    while (fscanf(file, "%19[^#]#%49[^#]#%29[^#]#%d\n",
           dataMember[jumlahMember].nohp,
           dataMember[jumlahMember].nama,
           dataMember[jumlahMember].paket,
           &dataMember[jumlahMember].umur) == 4)
    {
        if (jumlahMember < MAX_MEMBER) jumlahMember++;
        else break;
    }

    fclose(file);
}

// ======== SAVE DATA KE FILE ========
void simpanKeFile() {
    FILE *file = fopen("data_gym.txt", "w");
    if (!file) {
        printf("Gagal membuka file untuk menyimpan!\n");
        return;
    }

    {
        int i;
        for (i = 0; i < jumlahMember; i++) {
            fprintf(file, "%s#%s#%s#%d\n",
                    dataMember[i].nohp,
                    dataMember[i].nama,
                    dataMember[i].paket,
                    dataMember[i].umur);
        }
    }

    fclose(file);
}

// ======== TAMBAH MEMBER ========
void tambahMember() {
    if (jumlahMember >= MAX_MEMBER) {
        printf("\nData penuh!\n");
        return;
    }

    {
        struct Member m;
        /* input nomor hp, nama, paket, umur */
        printf("\nMasukkan No HP       : ");
        scanf(" %19[^\n]", m.nohp);
        printf("Masukkan Nama        : ");
        scanf(" %49[^\n]", m.nama);
        printf("Masukkan Paket Gym   : ");
        scanf(" %29[^\n]", m.paket);
        printf("Masukkan Umur        : ");
        if (scanf("%d", &m.umur) != 1) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
            printf("Input umur tidak valid.\n");
            return;
        }

        dataMember[jumlahMember++] = m;
        simpanKeFile();
        printf("\nData member berhasil ditambahkan!\n");
    }
}

// ======== TAMPILKAN MEMBER ========
void tampilMember() {
    int i;
    if (jumlahMember == 0) {
        printf("\nBelum ada data!\n");
        return;
    }

    printf("\n=== DATA MEMBER GYM ===\n");
    for (i = 0; i < jumlahMember; i++) {
        printf("\nNo HP   : %s", dataMember[i].nohp);
        printf("\nNama    : %s", dataMember[i].nama);
        printf("\nPaket   : %s", dataMember[i].paket);
        printf("\nUmur    : %d\n", dataMember[i].umur);
    }
}

// ======== CARI MEMBER ========
void cariMember() {
    char cari[20];
    int i;
    printf("\nCari berdasarkan No HP: ");
    scanf(" %19[^\n]", cari);

    for (i = 0; i < jumlahMember; i++) {
        if (strcmp(dataMember[i].nohp, cari) == 0) {
            printf("\nData ditemukan:");
            printf("\nNo HP  : %s", dataMember[i].nohp);
            printf("\nNama   : %s", dataMember[i].nama);
            printf("\nPaket  : %s", dataMember[i].paket);
            printf("\nUmur   : %d\n", dataMember[i].umur);
            return;
        }
    }

    printf("\nData tidak ditemukan!\n");
}

// ======== EDIT MEMBER ========
void editMember() {
    char cari[20];
    int i;
    printf("\nMasukkan No HP yang ingin diedit: ");
    scanf(" %19[^\n]", cari);

    for (i = 0; i < jumlahMember; i++) {
        if (strcmp(dataMember[i].nohp, cari) == 0) {

            printf("\nMasukkan Nama Baru     : ");
            scanf(" %49[^\n]", dataMember[i].nama);
            printf("Masukkan Paket Baru    : ");
            scanf(" %29[^\n]", dataMember[i].paket);
            printf("Masukkan Umur Baru     : ");
            if (scanf("%d", &dataMember[i].umur) != 1) {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
                printf("Input umur tidak valid.\n");
                return;
            }

            simpanKeFile();
            printf("\nData berhasil diperbarui!\n");
            return;
        }
    }

    printf("\nNo HP tidak ditemukan!\n");
}

// ======== HAPUS MEMBER ========
void hapusMember() {
    char cari[20];
    int i, j;
    printf("\nMasukkan No HP yang ingin dihapus: ");
    scanf(" %19[^\n]", cari);

    for (i = 0; i < jumlahMember; i++) {
        if (strcmp(dataMember[i].nohp, cari) == 0) {

            for (j = i; j < jumlahMember - 1; j++) {
                dataMember[j] = dataMember[j + 1];
            }

            jumlahMember--;
            simpanKeFile();

            printf("\nData berhasil dihapus!\n");
            return;
        }
    }

    printf("\nNo HP tidak ditemukan!\n");
}

// ======== SORTING BY NO HP (string) ========
void sortByNohp() {
    int i, j;
    for (i = 0; i < jumlahMember - 1; i++) {
        for (j = i + 1; j < jumlahMember; j++) {
            if (strcmp(dataMember[i].nohp, dataMember[j].nohp) > 0) {
                struct Member temp = dataMember[i];
                dataMember[i] = dataMember[j];
                dataMember[j] = temp;
            }
        }
    }
    printf("\nData berhasil diurutkan berdasarkan Nomor HP!\n");
}

// ======== SORTING BY NAMA ========
void sortByNama() {
    int i, j;
    for (i = 0; i < jumlahMember - 1; i++) {
        for (j = i + 1; j < jumlahMember; j++) {
            if (strcmp(dataMember[i].nama, dataMember[j].nama) > 0) {
                struct Member temp = dataMember[i];
                dataMember[i] = dataMember[j];
                dataMember[j] = temp;
            }
        }
    }
    printf("\nData berhasil diurutkan berdasarkan Nama!\n");
}

// ======== MAIN MENU ========
int main() {
    int pilihan;
    muatDariFile();

    do {
        printf("\n===== ADMINISTRASI MEMBER GYM =====");
        printf("\n1. Tambah Member");
        printf("\n2. Tampilkan Semua Member");
        printf("\n3. Cari Member");
        printf("\n4. Edit Member");
        printf("\n5. Hapus Member");
        printf("\n6. Sort by Nomor HP");
        printf("\n7. Sort by Nama");
        printf("\n8. Keluar");
        printf("\nPilih menu: ");
        if (scanf("%d", &pilihan) != 1) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
            pilihan = 0;
        }

        switch (pilihan) {
            case 1: tambahMember(); break;
            case 2: tampilMember(); break;
            case 3: cariMember(); break;
            case 4: editMember(); break;
            case 5: hapusMember(); break;
            case 6: sortByNohp(); simpanKeFile(); break;
            case 7: sortByNama(); simpanKeFile(); break;
            case 8: printf("\nKeluar...\n"); break;
            default: if (pilihan != 8) printf("\nPilihan tidak valid!\n");
        }

    } while (pilihan != 8);

=======

void dzikir() {
    printf("Subhaanallah\n");
}

int main(){
    for(int i=1; i<=33; i++){
        dzikir();
    }
    
>>>>>>> da1e9e765664cd2549f55dc63b2a3d75af1ac796
    return 0;
}
