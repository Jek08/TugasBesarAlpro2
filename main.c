#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define LONGSTR 1000
#define SHORTSTR 100
#define MAXHEWAN 10
#define BIAYAINAP 50000

typedef struct
{
    char id_hewan[SHORTSTR];
    char jenis[SHORTSTR];
    char nama[SHORTSTR];
    char ras[SHORTSTR];
    char kelamin[SHORTSTR];
    int umur;
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
    int durasi;
    long int total_biaya;
} DataPenitipan;

FILE *fcust;
FILE *fhewan;
FILE *forder;

void clearinputbuffer()
{
    while(getchar() != '\n');
}

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

void create_ID(char *ID)
{
    int i;
    //ascii number (48, 57)
    //ascii upper alphabet (65, 90)
    
    srand(time(NULL));

    //generate 3 random number
    for (i = 1; i <= 6; ++i)
    {
        if (i % 2 == 0)
            ID[i-1] = ( rand() % (57 - 48 + 1) ) + 48; //random number 0-9
        else if(i % 2 != 0)
            ID[i-1] = ( rand() % (90 - 65 + 1) ) + 65;
    }
}

void get_date(char *tgl)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
}

void check_in()
{
    int i;
    int jml_hewan;

    Owner customer;
    DataPenitipan order;

    printf("Check-in Penitipan\n");
    printf("--------------------\n");

    printf("Data Owner\n");
    printf("-----------\n");
    printf("Nama Lengkap: ");
    scanf("%[^\n]%*c", customer.nama_lengkap);
    printf("Alamat Rumah: ");
    scanf("%[^\n]%*c", customer.alamat);
    printf("No Telp: ");
    scanf("%[^\n]%*c", customer.no_telp);
    printf("Jumlah hewan yang dititipkan: ");
    scanf("%d", &jml_hewan);
    clearinputbuffer();

    for (i = 1; i <= jml_hewan; ++i)
    {
        printf("Data Hewan %d\n", i);
        printf("------------\n");
        create_ID(customer.hewan[i-1].id_hewan);
        printf("Nama: ");
        scanf("%[^\n]%*c", customer.hewan[i-1].nama);
        printf("Jenis: ");
        scanf("%[^\n]%*c", customer.hewan[i-1].jenis);
        printf("Jenis Kelamin: ");
        scanf("%[^\n]%*c", customer.hewan[i-1].kelamin);
        printf("Umur: ");
        scanf("%d", &customer.hewan[i-1].umur);
        clearinputbuffer();
        printf("Jenis Ras: ");
        scanf("%[^\n]%*c", customer.hewan[i-1].ras);
        printf("Keterangan lain: ");
        scanf("%[^\n]%*c", customer.hewan[i-1].keterangan_lain);

        // Data penitipan
        // ID Customer
        create_ID(order.id_cust);
        // tanggal check-in
        get_date(order.tgl_checkin);
        // lama penitipan
        printf("Durasi Penitipan: ");
        scanf("%d", &order.durasi);
        clearinputbuffer();
        // Hitung total biaya
        order.total_biaya = order.durasi * BIAYAINAP;

        // Rekam data ke file
        // Rekam ke file customer
        fcust = fopen("data\\customer.txt", "w");
        if (fcust != NULL)
        {
            fprintf(fcust, "%s\t%s\t%s\n", &customer.nama_lengkap, &customer.alamat, &customer.no_telp);
        }
        else
            printf("Error opening data file.");
        fclose(fcust);
        
        // Rekam ke file hewan
        fhewan = fopen("data\\hewan.txt", "w");
        fprintf(fhewan, "%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
        customer.hewan[i-1].id_hewan, customer.hewan[i-1].jenis, customer.hewan[i-1].nama,
        customer.hewan[i-1].ras, customer.hewan[i-1].kelamin, customer.hewan[i-1].umur, 
        customer.hewan[i-1].keterangan_lain);
        fclose(fhewan);
        
        // Rekam ke file order
        forder = fopen("data\\order.txt", "w");
        fprintf(forder, "%s\t%s\t%d\t%ld\n", order.id_cust, order.tgl_checkin, order.durasi,
        order.total_biaya);
    }
}

int main()
{
    char *tgl;
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

    check_in();
    
    return 0;
}