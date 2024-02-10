//Bismillahirrahmanirrahim.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int jpeg_kontrol(void *ptr);
int son(void *blok);


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Kullanım: ./recover <adli fotoğraflar>\n");
        return 1;
    }
    char *yol = argv[1];
    FILE *dosya = fopen(yol, "r");
    if (dosya == NULL)
    {
        printf("Dosya bulunamadı.\n");
        return 1;
    }
    int dsay = 0;
    void *geçici = malloc(512);
    FILE *yeni;
    int yazılıyor = 0;
    int durum = fread(geçici, 512, 1, dosya);
    while (durum > 0)
    {
        if (jpeg_kontrol(geçici))
        {
            if (yazılıyor)
            {
                fclose(yeni);
            }
            char yeyol[8];
            sprintf(yeyol, "%03u.jpg", dsay);
            yeni = fopen(yeyol, "a");
            fwrite(geçici, 512, 1, yeni);
            dsay++;
            yazılıyor = 1;
        }
        else
        {
            if (yazılıyor)
            {
                fwrite(geçici, 512, 1, yeni);
            }
        }
        durum = fread(geçici, 512, 1, dosya);
    }
    fclose(yeni);
    free(geçici);
}

int jpeg_kontrol(void *blok)
{
    unsigned char baş[] = {0xff, 0xd8, 0xff};
    int ilk3 = memcmp(blok, baş, 3);
    unsigned char *kar = blok;
    if (ilk3 == 0 && kar[3] >= 224 && kar[3] <= 239)
    {
        return 1;
    }
    return 0;
}