#include "Character.h"
#include "Ability.h"
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

Character::Character()
{
	LVL = 1; HP0 = 10 + rand() % 5; MP = 0;
	ATK = 10 + rand() % 5; DEF = 10 + rand() % 5;
	SPD = 10 + rand() % 5; SPC = 10 + rand() % 5;
	LUCK = 5-(ATK+DEF+SPD+SPC+HP0-50)/5;
	HP = HP0; STA = 0; MONEY = 0; RANGE = 100;

	leftDone= false; rightDone= false;
	upDone= false; downDone= false;

	armored = sworded = othered = false;

	direction = DOWN;
	Stage = 0;
}

Character::~Character(){

}

void Character::SetImagesLeft( char image1[], char image2[], char image3[]){
       
   images[0][0]= load_bitmap(image1, NULL);
   images[0][1]= load_bitmap(image2, NULL);
   images[0][2]= load_bitmap(image3, NULL);
   
   leftDone= true;
       
}

void Character::SetImagesRight(char image1[], char image2[], char image3[]){

   images[1][0]= load_bitmap(image1, NULL);
   images[1][1]= load_bitmap(image2, NULL);
   images[1][2]= load_bitmap(image3, NULL);
   
   rightDone= true;

}

void Character::SetImagesUp(char image1[], char image2[], char image3[]){

   images[2][0]= load_bitmap(image1, NULL);
   images[2][1]= load_bitmap(image2, NULL);
   images[2][2]= load_bitmap(image3, NULL);
   
   upDone= true;

}
       
void Character::SetImagesDown(char image1[], char image2[], char image3[]){

   images[3][0]= load_bitmap(image1, NULL);
   images[3][1]= load_bitmap(image2, NULL);
   images[3][2]= load_bitmap(image3, NULL);
   
   downDone= true;

}

bool Character::CheckImages(){
   if( rightDone && leftDone && upDone && downDone)
       return true;
   return false;         
                        
}
       
int Character::GetX(){
    return x;
}
       
int Character::GetY(){
    return y;
}

void Character::SetX( int newValue){
    x = newValue;
}

void Character::SetY( int newValue){
    y = newValue;
}

int Character::GetHelpNumber (int Stage){
	int HelpNumber;
	if (Stage == 1 || Stage == 3)  HelpNumber = 0;
	else if (Stage == 0) HelpNumber = 1;
	else if (Stage == 2) HelpNumber = 2;
	return HelpNumber;
}
void Character::MoveOnX( int newDirection, BITMAP* tempBitmap, BITMAP* mainBitmap, BITMAP* cena){
   direction = newDirection;
   draw_sprite( tempBitmap, cena, 0, 0);
   int HelpNumber = GetHelpNumber(Stage);
    if( CheckImages())
	{
		if( direction == LEFT){
			x -= 5+SPD/10;
			DrawNewSprite( tempBitmap, images[0][HelpNumber]);
			if (Stage == 3) Stage = 0;
			else Stage++;

			draw_sprite( mainBitmap, tempBitmap, 0, 0);

		} else 
		{
			x += 5+SPD/10;
			DrawNewSprite( tempBitmap, images[1][HelpNumber]);
			if (Stage == 3) Stage = 0;
			else Stage++;

			draw_sprite( mainBitmap, tempBitmap, 0, 0);

		}
    }

}

void Character::MoveOnY( int newDirection, BITMAP* tempBitmap, BITMAP* mainBitmap, BITMAP* cena){
   direction = newDirection;
   draw_sprite( tempBitmap, cena, 0, 0);
   int HelpNumber = GetHelpNumber(Stage);
   if( CheckImages()){
	   if( direction == UP)
	   {
		   y -= 5+SPD/10;
		   DrawNewSprite( tempBitmap, images[2][HelpNumber]);
		   if (Stage == 3) Stage = 0;
		   else Stage++;

		   draw_sprite( mainBitmap, tempBitmap, 0, 0);

	   } else 
	   {
		   y += 5+SPD/10;
		   DrawNewSprite( tempBitmap, images[3][HelpNumber]);
		   if (Stage == 3) Stage = 0;
		   else Stage++;

		   draw_sprite( mainBitmap, tempBitmap, 0, 0);
	   }
    }
}


void Character::EraseOldSprite( BITMAP* tempBitmap)
{
    draw_sprite( tempBitmap, tempBitmap, GetX(), GetY());
}

void Character::printStatus (BITMAP* mainBitmap)
{
	char palavra[50];
	float Life = (float)HP/(float)HP0;
	float CoolQ = (float)habil.cooldownQ/(float)habil.CDQ;

	draw_sprite(mainBitmap, status, GetX()-35, GetY()-45);

	if (Life>0.6) rectfill(mainBitmap, GetX()+16, GetY()-23, GetX()+16+52*Life, GetY()-17, makecol(0, 255, 0));
	else if (Life>0.4) rectfill(mainBitmap, GetX()+16, GetY()-23, GetX()+16+52*Life, GetY()-17, makecol(255, 255, 0));
	else if (Life>0) rectfill(mainBitmap, GetX()+16, GetY()-23, GetX()+16+52*Life, GetY()-17, makecol(255, 0, 0));

	textout_ex(mainBitmap, font, itoa(LVL ,palavra,10), GetX()+17, GetY()-35, makecol(200,0,0), -1);
	textout_ex(mainBitmap, font, itoa(HP ,palavra,10), GetX()+50, GetY()-35, makecol(0,220,0), -1);
	
	if (MP!=0) rectfill(mainBitmap, GetX()+16, GetY()-15, GetX()+16+52*MP/(10*LVL), GetY()-13, makecol(0, 0, 255));
	
	if (habil.cooldownQ < habil.CDEQ) circlefill(mainBitmap, GetX()-21, GetY()-18, 5, makecol(0, 0, 255));
	else if (CoolQ<1) circlefill(mainBitmap, GetX()-21, GetY()-18, 5*CoolQ, makecol(255, 0, 0));
	else circlefill(mainBitmap, GetX()-21, GetY()-18, 5, makecol(0, 255, 0));

}
void Character::DrawNewSprite( BITMAP* tempBitmap, BITMAP* spriteToDraw){

    draw_sprite( tempBitmap, spriteToDraw, GetX(), GetY());
	printStatus (tempBitmap);

}
void Character::Show(BITMAP* mainBitmap){

	int HelpNumber = GetHelpNumber(Stage);
	printStatus (mainBitmap);
    if( CheckImages())
	{
		if (direction == UP) draw_sprite( mainBitmap, images[2][HelpNumber], GetX(), GetY());
		else if (direction == LEFT) draw_sprite( mainBitmap, images[0][HelpNumber], GetX(), GetY());
		else if (direction == RIGHT) draw_sprite( mainBitmap, images[1][HelpNumber], GetX(), GetY());
		else if (direction == DOWN) draw_sprite( mainBitmap, images[3][HelpNumber], GetX(), GetY());
	}

}

void Character::ShowStats(int X, int Y, BITMAP* mainBitmap)
{
	char palavra[50];
	draw_sprite(mainBitmap, face, X-120, Y-35);
	textout_ex(mainBitmap, font, nome, X-100,Y-50, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(LVL,palavra,10), X+100,Y, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(HP0,palavra,10), X+100,  Y+35, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(HP ,palavra,10), X+70, Y+35, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(ATK,palavra,10), X-20, Y+110, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(DEF,palavra,10), X-20, Y+140, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(SPD,palavra,10), X-20, Y+170, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(SPC,palavra,10), X-20, Y+200, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, "CH: 1/", X+60, Y+170, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(15/LUCK,palavra,10), X+115, Y+170, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(MONEY	,palavra,10), X+50, Y+135, makecol(0,255,0), -1);
	if (armored) draw_sprite(mainBitmap, armor.image, X+50, Y-45);
	if (sworded) draw_sprite(mainBitmap, sword.image, X, Y-45);
	if (othered) draw_sprite(mainBitmap, other.image, X+100, Y-45);

}