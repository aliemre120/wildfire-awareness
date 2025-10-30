#include<stdio.h>
#include<stdlib.h>
#include"risk.h"

void display_wildfire_informations(int language)
{
            if(language == 1) // Information in Turkish
            {
                system("cls");
                printf("*ORMAN YANGINLARI VE YAPILMASI GEREKENLER*\n\n");
                printf("\tYuksek sicaklik ve dusuk nem oranina sahip alanlar orman yangini riski tasiyan yerlerdir.\n"
                        "Ozellikle hava sicakliginin 35 derecenin ustunde ve nem orani %%20'den dusuk ise ve alanda cam sise ,sigara\n"
                        "izmariti ve benzeri atiklarin bulunmasi orman yanginini tetikler.Bu yanginlarin cevreye verdigi zararlar\n"
                        "insanoglunun gelecegini tehdit etmekle birlikte bazi canli turlerinin yok olmasina sebep olmaktadir.\n" 
                        "Ayrica Dunya Saglik Orgutu (WHO)'ya gore, \"Orman yangini dumani,PM2.5,NO2, ozon, aromatik hidrokarbonlar\n"
                        "veya kursun gibi tehlikeli hava kirleticilerinin bir karisimidir.Zehirli kirleticilerle havayi \n"
                        "kirletmenin yani sira, orman yanginlari ayni zamanda buyuk miktarda karbondioksit ve diger sera gazlarini\n"
                        "atmosfere salarak iklimi de etkiler.\"\n\n"
                        );
                printf("\tOrman yangini ile karsilastiginizda ilk yapilmasi gereken yangin bolgesinden en az 200 metre uzaklasip\n"
                        "acil durum cagri merkezini arayarak durumu bildirmek olmalidir.Yanginin bulundugu konum ve yangin siddeti acik\n"
                        "ve net olarak bildirilmelidir.Guvenlik acisindan risk teskil etse de eger yangin cok kucuk ve mudahale edilebilecek\n"
                        "duzeyde ise yangin sondurme tupu ile tarafinizca mudahale edilebilir.Bu tarz durumlara karsin evinizde\n"
                        "ve arabanizda mutlaka yangin sondurme tupu bulundurulmasi tavsiye edilir.\n");
                        system("pause");
                        system("cls");
            }
            else if(language == 2) // Information in English
            {
                system("cls");
                printf("*WILDFIRES AND NECESSARY ACTIONS*\n\n");
                printf("\tAreas with high temperatures and low humidity levels are at risk of wildfires.\n"
                        "Especially when the air temperature is above 35 degrees and the humidity is below 20%%, and if there are\n"
                        "items like glass bottles, cigarette butts, or similar waste present, the risk of wildfire increases.\n"
                        "These fires not only threaten the future of humanity but also lead to the extinction of some animal species.\n"
                        "According to the World Health Organization (WHO), \"Wildfire smoke is a mixture of hazardous air pollutants\n"
                        "such as PM2.5, NO2, ozone, aromatic hydrocarbons, or lead. In addition to polluting the air with toxic substances,\n"
                        "wildfires also affect the climate by releasing large amounts of carbon dioxide and other greenhouse gases\n"
                        "into the atmosphere.\"\n\n");
                printf("\tIf you encounter a wildfire, the first thing you should do is move at least 200 meters away from the fire zone\n"
                        "and call the emergency hotline to report the situation. The location and severity of the fire should be clearly\n"
                        "and accurately communicated. Even though it may pose a safety risk, if the fire is small and manageable,\n"
                        "it can be intervened with a fire extinguisher. It is recommended to always keep a fire extinguisher in your home\n"
                        "and vehicle in case of such situations.\n");

                system("pause");
                system("cls");
            }
}
void risk_prediction(struct risk *w ,int language_choice)
{
    float score=0;  

    if(w->temperature > 35) // High temperature
    {
        score += 2; // High temperature effect
    }
    else if(w->temperature >= 27 && w->temperature <= 35) // Moderate temperature
    {
        score += 1;
    }
    else // Low temperature
    {
        score += 0;
    }
    if (w->humidity < 20) // Low humidity
    {
        score += 2;    
    }
    else if(w->humidity >= 20 && w->humidity <= 30) // Moderate humidity
    {
        score += 1;
    }
    else // High humidity
    {
        score += 0;
    }
    
    if(language_choice == 1)// Prediction display in Turkish
    {        
        if(score >= 3) // High risk
        {
            printf("-> Orman yangini riski yuksek!!!\n\n");
        }
        else if(score == 2) // Moderate risk
        {
            printf("-> Orman yangini riski orta derecededir.\n\n");
        }
        else // Low risk
        {
            printf("-> Orman yangini riski dusuktur.\n\n");
        }
    }
    else if(language_choice == 2)// Prediction display in English
    {
        if(score >= 3) // High risk
        {
            printf("-> The wildfire risk is high!!!\n\n");
        }
        else if(score == 2) // Moderate risk
        {
            printf("-> The wildfire risk is moderate.\n\n");
        }
        else // Low risk
        {
            printf("-> The wildfire risk is low.\n\n");
        }
    }
            system("pause");
            system("cls");
}