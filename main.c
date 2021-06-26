#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define LONGSTR 1000
#define SHORTSTR 100
#define MAXHEWAN 10

typedef struct
{
    char id_hewan[SHORTSTR];
    char jenis[SHORTSTR];
    char nama[SHORTSTR];
    char ras[SHORTSTR];
    char kelamin[SHORTSTR];
    char keterangan_lain[LONGSTR];
} Hewan;

typedef struct 
{
    char nama_lengkap[SHORTSTR];
    char alamat[LONGSTR];
    char no_telp[SHORTSTR];
    Hewan hewan[MAXHEWAN];
} Owner;

typedef struct
{
    char id_cust[SHORTSTR];
    char tgl_checkin[SHORTSTR];
    char durasi[SHORTSTR];
    char total_biaya[SHORTSTR];
} DataPenitipan;

void tampilkan_menu()
{
    printf("Sistem pengelolaan tempat penitipan hewan\n");
    printf("==========================================");

    printf("Menu:\n");
    printf("1. Check-in\n");
    printf("2. Check-out\n");
    printf("3. Cari data penitipan\n");
    printf("4. Ubah data\n");
}

void create_custID()
{

}

void create_petID(char *petID)
{
    int i;
    //ascii number (48, 57)
    //ascii upper alphabet (65, 90)
    
    srand(time(NULL));

    //generate 3 random number
    for (i = 1; i <= 3; ++i)
    {
        petID[i-1] = ( rand() % (57 - 48 + 1) ) + 48; //random number 0-9
    }

    for (i = 4; i <= 6; ++i)
    {
        petID[i-1] = ( rand() % (90 - 65 + 1) ) + 65; //random uppercase alphabet 
    }
}

void check_in()
{
    Owner customer;
    DataPenitipan order;

    printf("Check-in Penitipan\n");
    printf("--------------------\n");

    printf("Data Owner\n");
    printf("-----------\n");
    printf("Nama Lengkap: ");
    scanf("%s ", customer.nama_lengkap);
    printf("Alamat Rumah: ");
    scanf("%s ", customer.alamat);
    printf("No Telp: ");
    scanf("%s ", customer.no_telp);

    printf("Data Hewan\n");
    printf("------------\n");
    printf("Nama: ");
    scanf("%s ", customer.hewan->nama);
    printf("Jenis: ");
    scanf("%s ", customer.hewan->jenis);
    printf("Jenis Kelamin: ");
    scanf("%s ", customer.hewan->kelamin);
    printf("Jenis Ras: ");
    scanf("%s ", customer.hewan->ras);
}

int main()
{
    char petID[6];
    // char menu;
    // do
    // {
    //     switch (menu)
    //     {
    //     case 1:
            
    //         break;
        
    //     default:
    //         break;
    //     }
    // } while (menu != 5);
    create_petID(petID);
    printf("%s \n", petID);
    
    return 0;
}