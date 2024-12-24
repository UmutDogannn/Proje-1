#include <stdio.h>
#include <string.h>
// Tanımlanan sabitler
#define KOTA 6144       // Kota değeri (MB)
#define UCRET 0.011719  // Kota aşımı ücret birim fiyatı (TL/MB)
#define MB 1024         // 1 GB = 1024 MB
// Global değişkenler
float asimUcreti;       // Kota aşımı ücretini saklar
float upload = 0;       // Toplam yükleme (upload) miktarını saklar
float download = 0;     // Toplam indirme (download) miktarını saklar
// Kota aşımı ücretini hesaplayan fonksiyon
void kotaAsimi(int kullanilanDownland) {
    float asim; // Kota aşım miktarını tutar
    asim = kullanilanDownland - KOTA; // Kota aşımı hesaplanır
    if (asim > 0) { // Kota aşıldıysa
        asimUcreti = asim * UCRET; // Aşım ücreti hesaplanır
    }
}
// Dosyadan belirtilen aya ait verileri okuyan fonksiyon
void istenenAY(const char *filename, const char *kelime) {
    int gun; // Gün bilgisi
    float upload1 = 0, download1 = 0; // Geçici upload ve download değerleri
    char karakter[64]; // Dosyadan okunan satırları saklar
    // Dosyayı açma
    FILE *adsl = fopen(filename, "r");
    if (adsl == NULL) { // Dosya açılamadıysa hata mesajı basılır
        printf("Dosya acilamadi\n");
        return;
    }
    // Dosyadaki satırları okuma
    while (fgets(karakter, sizeof(karakter), adsl)) {
        // Satırın başı aranan kelimeyle eşleşiyorsa
        if (strncmp(karakter, kelime, strlen(kelime)) == 0) {
            // Satırdaki bilgileri ayrıştırma
            if (sscanf(karakter, "%s %d %f %f", karakter, &gun, &upload1, &download1) == 4) {
                upload += upload1;   // Yükleme miktarını toplar
                download += download1; // İndirme miktarını toplar
            }
        }
    }
    // Kota aşımını hesaplama
    kotaAsimi(download);
    fclose(adsl);
}
int main() {
    char ayAdi[20]; // Kullanıcıdan alınacak ay ismi
    // Kullanıcıdan fatura oluşturulacak ayı isteme
    printf("Hangi ayin faturasini istiyorusunuz: \n");
    scanf("%s", ayAdi);
    printf("%s 2012 faturaniz olusturulmustur\n ", ayAdi);
    // Belirtilen aya ait verileri işlemeye başlama
    istenenAY("adsl.txt", ayAdi);
    // Fatura dosyasını oluşturma ve yazma
    FILE *dosya;
    dosya = fopen("fatura.txt", "w");
    fprintf(dosya, "%s 2012\nToplam yukleme(upload): %.2f GB\nToplam indirme(download): %.2f GB\nKota asim ucreti: %.2f",
            ayAdi, upload / MB, download / MB, asimUcreti);
    return 0;
}
