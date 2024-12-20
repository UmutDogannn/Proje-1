#include <stdio.h>
#include <string.h>
#define kota 6144
#define ücret 0.011719
#define mb 1024
float aşım_ücreti;
float upload = 0;
float download = 0;

void kotaAsımı(int kullanlan_download) {
    float aşım;
    aşım = kullanlan_download - kota;
    if (aşım > 0) {
        aşım_ücreti = (float)aşım * ücret;
    }
}

void istenenAY(const char *filename, const char *kelime) {
    int gün;
    float upload1 = 0, download1 = 0;
    FILE *adsl = fopen(filename, "r");
    if (adsl == NULL) {
        printf("Dosya açılamadı\n");
    }

    char karakter[256];
    while (fgets(karakter, sizeof(karakter), adsl)) {
        if (strncmp(karakter, kelime, strlen(kelime)) == 0) {
            if (sscanf(karakter, "%s %d %f %f", karakter, &gün, &upload1, &download1) == 4) {
                upload += upload1;
                download += download1;
            }
        }
    }
    kotaAsımı(download);
    fclose(adsl);
}

int main() {
    char ay_adı[20];
    printf("Hangi ayin faturasini istiyorusunuz: \n");
    scanf("%s", ay_adı);
    printf("%s 2012 faturaniz olusturulmustur\n ", ay_adı);
    istenenAY("adsl.txt",ay_adı);
    FILE *dosya;
    dosya = fopen("fatura.txt", "w");
    fprintf(dosya, "%s 2012\nToplam yukleme(upload): %.2f GB\nToplam indirme(download): %.2f GB\nKota asim ucreti: %.2f", ay_adı, upload/mb, download/mb, aşım_ücreti);
    return 1;
}