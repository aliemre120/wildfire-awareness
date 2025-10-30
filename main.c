#include <stdio.h>
#include <stdlib.h>
#include "risk.h"
#include "db.h"
#include "string.h"

// This program created for increase awareness about wildfires.

static void flush_line(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}
static void read_line(char *buf, size_t sz)
{
    if (fgets(buf, (int)sz, stdin))
    {
        size_t n = strlen(buf);
        if (n > 0 && buf[n - 1] == '\n')
            buf[n - 1] = '\0';
    }
    else
        buf[0] = '\0';
}

int main()
{
    int language_choice;
    int menu_choice;
    struct risk weather;

    // start the database
    if (!db_init())
    {
        printf("Veritabani baslatilamadi (db_init failed).\n");
        return 1; // if there any error, exit the program
    }

    do
    {
        menu_choice = 0;                                                                                // Reset menu choice for each process.
        printf("Select Language/Dil Secimi\n1.Turkce\n2.English\n3.Exit/Cikis\nChoice/Secim(1,2,3): "); // language selection
        scanf("%d", &language_choice);
        system("cls");
        if (language_choice == 3)
        {
            printf("Exiting the program/Cikis yapiliyor.\n");
            return 0; // Exit the program
        }
        if (language_choice < 1 || language_choice > 3)
        {
            printf("\nInvalid choice. Please try again.\n\n");
            continue; // Restart the loop for valid input
        }

        do
        {
            menu_choice = 0; // Reset menu choice for each process.

            if (language_choice == 1)
            {
                // Display menu in Turkish
                printf("\nTurkce secildi.\n\n");
                printf("**ORMAN YANGINLARI BILGILENDIRME**\n\n");
                printf("1.Orman yanginlari ve yapilmasi gerekenler.\t\t->Dil menusune donmek icin 7'ye basiniz\n");
                printf("2.Yangin riski tahmini.\t\t\t\t\t->Programdan cikmak icin 8'e basiniz.\n");
                printf("3.Yeni bir yangin bildir.\n");
                printf("4.Sonen bir yangini bildir.\n");
                printf("5.Bildirilmis aktif yanginlari goruntule.\n");
                printf("6.Tum bildirilen yanginlari goruntule.\n");
                printf("\n\nMenuden bir numara giriniz: ");
                scanf("%d", &menu_choice);
                flush_line();
                system("cls");
            }
            else if (language_choice == 2)
            {
                // Display menu in English
                printf("\nEnglish selected.\n\n");
                printf("**WILDFIRE AWARENESS**\n\n");
                printf("1.Learn about wildfire and what to do.\t\t\t->Press 7 to go back to the language menu.\n");
                printf("2.Fire risk prediction.\t\t\t\t\t->Press 8 to exit the program.\n");
                printf("3.Report a new Wildfire.\n");
                printf("4.Report an extinguished wildfire.\n");
                printf("5.View reported current Wildfires.\n");
                printf("6.View all reported Wildfires.\n");
                printf("\n\nEnter a number from the menu:");
                scanf("%d", &menu_choice);
                flush_line();
                system("cls");
            }
            if (menu_choice == 8)
            {
                printf("Exiting the program/Cikis yapiliyor.\n");
                return 0; // Exit the program
            }
            if (menu_choice < 1 || menu_choice > 8)
            {
                printf("\nInvalid choice.Please try again.\n\n");
                continue; // Restart the loop if invalid choice
            }
            switch (menu_choice)
            {
            case 1: // Learn about wildfire and what to do
            {
                display_wildfire_informations(language_choice);
                break;
            }
            case 2: // Wildfire risk prediction
            {
                if (language_choice == 1)
                {
                    system("cls");

                    printf("\n YANGIN RISK MATRISI \n\n");
                    printf("-Sicaklik->| 20-25 C  | 26-30 C  | 31-35 C  | 36-40 C   | 41-45 C\n");
                    printf("-Nem (%%)---|----------|----------|----------|-----------|-----------\n");
                    printf(" 10%%-19%%   |   Orta   |   Orta   |  Yuksek  |  Yuksek   |  ASIRI\n");
                    printf(" 20%%-29%%   |  Dusuk   |   Orta   |   Orta   |  Yuksek   |  Yuksek\n");
                    printf(" 30%%-39%%   |  Dusuk   |  Dusuk   |   Orta   |   Orta    |  Orta\n");
                    printf(" 40%%-50%%   |Cok Dusuk |  Dusuk   |  Dusuk   |   Orta    |  Orta\n\n");

                    printf("Orman yangini riski tahmini icin gerekli verileri giriniz:\n");
                    printf("Sicaklik (Celsius 20-45): ");
                    scanf("%f", &weather.temperature);
                    printf("Nem Orani (%%10-%%50): ");
                    scanf("%d", &weather.humidity);
                    system("cls");
                }
                else if (language_choice == 2)
                {
                    system("cls");
                    printf("\n WILDFIRE RISK MATRIX \n\n");
                    printf("Temperature->| 20-25 C  | 26-30 C  | 31-35 C  | 36-40 C  | 41-45 C\n");
                    printf("Humidity (%%)-|----------|----------|----------|----------|-----------\n");
                    printf("   10%%-19%%   | Moderate | Moderate |   High   |  High    | EXTREME\n");
                    printf("   20%%-29%%   |  Low     | Moderate | Moderate |  High    |   High\n");
                    printf("   30%%-39%%   |  Low     |   Low    | Moderate | Moderate | Moderate\n");
                    printf("   40%%-50%%   |Very Low  |   Low    |   Low    | Moderate | Moderate  \n\n");

                    printf("Enter the data for wildfire risk prediction:\n");
                    printf("Temperature (Celsius 20-45): ");
                    scanf("%f", &weather.temperature);
                    flush_line();
                    printf("Humidity (%%10-%%50): ");
                    scanf("%d", &weather.humidity);
                    flush_line();
                    system("cls");
                }

                risk_prediction(&weather, language_choice);
                break;
            }
            case 3:
            { // Report a new wildfire
                char loc[128];
                if (language_choice == 1)
                    printf("Yeni yangin konumu (sehir/ilce vb.): ");
                else
                    printf("New wildfire location (city/district): ");
                read_line(loc, sizeof(loc));
                if (loc[0] == '\0')
                {
                    if (language_choice == 1)
                        printf("Gecersiz konum.\n");
                    else
                        printf("Invalid location.\n");
                    system("pause");
                    system("cls");
                    break;
                }
                int new_id = db_add_fire(loc);
                if (new_id > 0)
                {
                    if (language_choice == 1)
                        printf("Kaydedildi. ID: %d\n", new_id);
                    else
                        printf("Saved. ID: %d\n", new_id);
                }
                else
                {
                    if (language_choice == 1)
                        printf("Kayit basarisiz.\n");
                    else
                        printf("Save failed.\n");
                }
                system("pause");
                system("cls");
                break;
            }
            case 4:
            { // Report an extinguished wildfire
                int id;
                if (language_choice == 1)
                    printf("Sondurulen yangin ID: ");
                else
                    printf("Extinguished wildfire ID: ");
                if (scanf("%d", &id) != 1)
                {
                    flush_line();
                    system("cls");
                    break;
                }
                flush_line();
                bool ok = db_extinguish_fire(id);
                if (ok)
                {
                    if (language_choice == 1)
                        printf("ID %d sonduruldu olarak isaretlendi.\n", id);
                    else
                        printf("ID %d marked as extinguished.\n", id);
                }
                else
                {
                    if (language_choice == 1)
                        printf("Kayit bulunamadi ya da zaten sondurulmus.\n");
                    else
                        printf("No record updated or already extinguished.\n");
                }
                system("pause");
                system("cls");
                break;
            }
            case 5:
            { // View reported current wildfires
                db_list_active(language_choice == 2);
                system("pause");
                system("cls");
                break;
            }
            case 6:
            { // View all reported wildfires
                db_list_all(language_choice == 2);
                system("pause");
                system("cls");
                break;
            }
            }

        } while (menu_choice != 7); // Continue until user chooses to exit or go back to language menu
    } while (1);
    return 0;
}