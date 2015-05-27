#include "equip.h"

Equipament::Equipament()
{
	LVL = 1;
	HP0 = STA = ATK = DEF = SPD = SPC = 0;
	custo = 0;
}

Equipament::~Equipament()
{

}

void Equipament::configEquip (int LVL, int HP0, int STA, int ATK, int DEF, int SPD, int SPC, int RANGE, int custo)
{
	this->LVL = LVL; this->HP0 = HP0; this->STA = STA; this->custo = custo;
	this->ATK = ATK; this->DEF = DEF; this->SPD = SPD; this->SPC = SPC;
	this->RANGE = RANGE;
}
void Equipament::showEquip(int X, int Y, BITMAP* mainBitmap)
{
	char palavra[50];
	draw_sprite(mainBitmap, image, X, Y);
	textout_ex(mainBitmap, font, nome, X+50,Y-10, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(custo,palavra,10), X+50,Y+10, makecol(20,125,0), -1);
	textout_ex(mainBitmap, font, "HP", X+80,Y+10, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(HP0,palavra,10), X+110,Y+10, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, "STA", X+130,Y+10, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(STA,palavra,10), X+160,Y+10, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, "ATK", X+80,Y+20, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(ATK,palavra,10), X+110,Y+20, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, "DEF", X+130,Y+20, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(DEF,palavra,10), X+160,Y+20, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, "SPD", X+80,Y+30, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(SPD,palavra,10), X+110,Y+30, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, "SPC", X+130,Y+30, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(SPC,palavra,10), X+160,Y+30, makecol(0,0,0), -1);

}
