#ifndef EQUIP_H
#define EQUIP_H

#include <allegro.h>

class Equipament
{

public:
       Equipament();
       ~Equipament();
       
	   BITMAP *image;

	   char nome[50];
	   int LVL, HP0, STA, RANGE;
	   int ATK, DEF, SPD, SPC;
	   int custo;

	   void configEquip (int LVL, int HP0, int STA, int ATK, int DEF, int SPD, int SPC, int RANGE, int custo);
	   void showEquip (int X, int Y, BITMAP *mainBITMAP);
};

#endif