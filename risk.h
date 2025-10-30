#ifndef RISK_H
#define RISK_H

struct risk
{
   float temperature;
   int humidity;
};
void display_wildfire_informations(int language);
void risk_prediction(struct risk *weather ,int language_choice);

#endif // RISK_H