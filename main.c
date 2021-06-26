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
    int jml_hewan;
    Hewan hewan[MAXHEWAN];
} Owner;

typedef struct
{
    char id_cust[SHORTSTR];
    char tgl_checkin[SHORTSTR];
    int durasi;
    long int total_biaya;
} DataPenitipan;

Owner customer;

// sequential files pointer
FILE *fcust;
FILE *fhewan;
FILE *forder;

// untuk menghilangkan sisa input
void clearinputbuffer()
{
    while(getchar() != '\n');
}

// tampilan menu
void tampilkan_menu()
{
    printf("Sistem pengelolaan tempat penitipan hewan\n");
    printf("==========================================\n");

    printf("Menu:\n");
    printf("1. Check-in\n");
    printf("2. Check-out\n");
    printf("3. Keluar\n");
}

// ID generator ex: A3B5H7
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
            ID[i-1] = ( rand() % (90 - 65 + 1) ) + 65; //random alphabet
    }
}

// mengambil tanggal dari sistem lokal
void get_date(char *tgl)
{
    int day, month, year;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    day = tm.tm_mday;
    month = tm.tm_mon+1;
    year = tm.tm_year+1900;
    snprintf(tgl, sizeof(tgl), "%d-%d-%d", day, month,year);
}

void check_in()
{
    int i;
    int jml_hewan;

    DataPenitipan order;

    printf("Check-in Penitipan\n");
    printf("--------------------\n\n");

    // input data pemilik hewan
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
    customer.jml_hewan = jml_hewan;
    clearinputbuffer();

    create_ID(customer.hewan[0].id_hewan);

    // input data hewan-hewan
    for (i = 1; i <= jml_hewan; ++i)
    {
        printf("Data Hewan %d\n", i);
        printf("------------\n");
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
        
        // Rekam ke file hewan.txt
        fhewan = fopen("data\\hewan.txt", "a");
        if (fhewan != NULL)
        {
            fprintf(fhewan, "%s\t%s\t%s\t%s\t%s\t%d\t%s\n",
            customer.hewan[0].id_hewan, customer.hewan[i-1].jenis, customer.hewan[i-1].nama,
            customer.hewan[i-1].ras, customer.hewan[i-1].kelamin, customer.hewan[i-1].umur, 
            customer.hewan[i-1].keterangan_lain);
        }
        else
            printf("Error opening data hewan.\n");
        fclose(fhewan);
    }

    // Rekam data pemilik hewan ke file customer.txt
    fcust = fopen("data\\customer.txt", "a");
    if (fcust != NULL)
    {
        fprintf(fcust, "%s\t%s\t%s\t%s\t%d\n", customer.nama_lengkap, customer.alamat, customer.no_telp, customer.hewan[0].id_hewan, customer.jml_hewan);
    }
    else
        printf("Error opening data customer.\n");
    fclose(fcust);

    // ID Customer
    create_ID(order.id_cust);
    // tanggal check-in
    get_date(order.tgl_checkin);
    // lama penitipan
    printf("Durasi Penitipan: ");
    scanf("%d", &order.durasi);
    clearinputbuffer();
    // Hitung total biaya
    order.total_biaya = order.durasi * (BIAYAINAP * jml_hewan);

    // Rekam ke file order
    forder = fopen("data\\order.txt", "a");
    if (forder != NULL)
    {
        fprintf(forder, "%s\t%s\t%d\t%ld\n", order.id_cust, order.tgl_checkin, 
        order.durasi, order.total_biaya);    
    }
    else
        printf("Error opening data order.\n");
    fclose(forder);
}

// konsolidasi file untuk mencari informasi customer berdasarkan nama
int cari_customer(char *nama_cust)
{
    int test = 0;
    int found = 0;

    if ((fcust = fopen("data\\customer.txt", "r")) != NULL)
    {
        fscanf(fcust, "%[^\t] %[^\t] %[^\t] %[^\t] %d\n", customer.nama_lengkap, customer.alamat, customer.no_telp, customer.hewan[0].id_hewan, &customer.jml_hewan);
        if (strcmp(nama_cust, customer.nama_lengkap) == 0)
                found = 1;

        while ((found == 0) && !feof(fcust))
        {
            fscanf(fcust, "%[^\t] %[^\t] %[^\t] %[^\t] %d\n", customer.nama_lengkap, customer.alamat, customer.no_telp, customer.hewan[0].id_hewan, &customer.jml_hewan);
            if (strcmp(nama_cust, customer.nama_lengkap) == 0)
                found = 1;
        }

        fclose(fcust);

        if (found == 1)
        {
            return 1;
        }
        else
            return -1;
    }
    else
        printf("Gagal membuka file customer.txt\n");
}

// melakukan konsolidasi file untuk mencari informasi hewan berdasarkan ID
void cari_hewan(char *cari)
{
    int i = 0;
    char ID[SHORTSTR];
    char junk[5];

    if ((fhewan = fopen("data\\hewan.txt", "r")) != NULL)
    {          
        while (!feof(fhewan))
        {
            fscanf(fhewan, "%[^\t] %[^\t] %[^\t] %[^\t] %[^\t] %d %[^\n] %[\n]",
            ID, customer.hewan[i].jenis, customer.hewan[i].nama,
            customer.hewan[i].ras, customer.hewan[i].kelamin, &customer.hewan[i].umur, 
            customer.hewan[i].keterangan_lain, junk);
            
            if ((strcmp(cari, ID) == 0) && (i < customer.jml_hewan))
            {
                ++i;
            }     
        }
    }
    else
        printf("Gagal membuka file customer.txt\n");
    fclose(fhewan);
}

// maaf bu yg ini masih error baru kepikiran harus hapus data customer setelah selesai inap
void hapus_data(char *name_cari)
{
    // menghapus data customer setelah selesai penitipan
    // pointer file sementara untuk salin bagian selain ID yang dicari
    FILE *ftemp = fopen("data\\temp.txt", "w");
    char current_name[SHORTSTR];
    int is_finish = 0;
    char buff[LONGSTR]; //menyimpan barisan rekaman data utk sementara
    fcust = fopen("data\\customer.txt", "a");

    if (fcust != NULL)
    {
        fscanf(fcust, "%[^\t]", current_name);
        while (!feof(fcust))
        {
            if (strcmp(current_name, name_cari) != 0)
            {
                fgets(buff, LONGSTR, fcust);
                fputs(buff, ftemp);
            }
            fscanf(fcust, "%[^\t]", current_name);
        }
        is_finish = 1;
    }
    else
        printf("Error opening data customer.\n");
    
    // salin kembali file temp ke file customer setelah menghilangkan data
    if (is_finish == 1)
    {
        while (!feof(fcust))
        {
            fgets(buff, LONGSTR, ftemp);
            fputs(buff, fcust);
        }
    }

    fclose(fcust);
    fclose(ftemp);
}

void check_out()
{
    int i;
    char nama_cust[SHORTSTR];
    char is_selesai;

    printf("Check-out Penitipan\n");
    printf("----------------------\n");
    printf("Masukkan nama lengkap customer: ");
    scanf("%[^\n]%*c", nama_cust);

    if (cari_customer(nama_cust) == 1)
    {
        printf("Informasi Penitipan:\n");
        printf("--------------\n");
        cari_hewan(customer.hewan[0].id_hewan);
        for (i = 0; i < customer.jml_hewan; ++i)
        {
            printf("Jenis: %s\n", customer.hewan[i].jenis);
            printf("Nama: %s\n", customer.hewan[i].nama);
            printf("--------------\n");
        }

        printf("Apakah selesai check-out? (y/n): ");
        scanf("%c", &is_selesai);
        if (is_selesai == 'y')
        {
            // bagian menghapus data customer
            // hapus_data(customer.nama_lengkap); (masih error)
        }
    }
    else
        printf("Customer tidak ditemukan\n");
}

int main()
{
    int menu;
    do
    {
        printf("\n");
        tampilkan_menu();
        printf("\nPilih Menu: ");
        scanf("%d", &menu);
        clearinputbuffer();

        switch (menu)
        {
        case 1:
            check_in();
            break;
        case 2:
            check_out();
            break;
        case 3:
            printf("Keluar...\n");
            break;
        default:
            printf("pilihan menu tidak ada.");
            break;
        }
    } while (menu != 3);
    
    return 0;
}