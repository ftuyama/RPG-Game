#ifndef ABILITY_H
#define ABILITY_H

#include <allegro.h>

class Ability
{

public:
       Ability();
       ~Ability();

	   BITMAP *ability[4][5];
       
	   int CDQ, CDEQ, cooldownQ;
	   int CDW, CDEW, cooldownW;
	   int CQE, CDEE, cooldownE;
	   int CQR, CDER, cooldownR;

	   void setAbilityQ (int CD, int CDE, int cooldown);
	   void SetImagesQ ( char image1[], char image2[], char image3[], char image4[], char image5[]);

};

#endif