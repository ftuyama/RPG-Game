#include "Monster.h"
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

Monster::Monster()
{
	moviment = respawn = STA = 0;

	leftDone= false; rightDone= false;
	upDone= false; downDone= false;

	direction = DOWN;
	Stage = 0;
}

Monster::~Monster(){

}

void Monster::SetImagesLeft( char image1[], char image2[], char image3[]){
       
   images[0][0]= load_bitmap(image1, NULL);
   images[0][1]= load_bitmap(image2, NULL);
   images[0][2]= load_bitmap(image3, NULL);
   
   leftDone= true;
       
}

void Monster::SetImagesRight(char image1[], char image2[], char image3[]){

   images[1][0]= load_bitmap(image1, NULL);
   images[1][1]= load_bitmap(image2, NULL);
   images[1][2]= load_bitmap(image3, NULL);
   
   rightDone= true;

}

void Monster::SetImagesUp(char image1[], char image2[], char image3[]){

   images[2][0]= load_bitmap(image1, NULL);
   images[2][1]= load_bitmap(image2, NULL);
   images[2][2]= load_bitmap(image3, NULL);
   
   upDone= true;

}
       
void Monster::SetImagesDown(char image1[], char image2[], char image3[]){

   images[3][0]= load_bitmap(image1, NULL);
   images[3][1]= load_bitmap(image2, NULL);
   images[3][2]= load_bitmap(image3, NULL);
   
   downDone= true;

}

bool Monster::CheckImages(){
   if( rightDone && leftDone && upDone && downDone)
       return true;
   return false;         
                        
}
       
int Monster::GetX(){
    return x;
}
       
int Monster::GetY(){
    return y;
}

void Monster::SetX( int newValue){
    x = newValue;
}

void Monster::SetY( int newValue){
    y = newValue;
}

int Monster::GetHelpNumber (int Stage){
	int HelpNumber;
	if (Stage == 1 || Stage == 3)  HelpNumber = 0;
	else if (Stage == 0) HelpNumber = 1;
	else if (Stage == 2) HelpNumber = 2;
	else HelpNumber  = 0;
	return HelpNumber;
}
void Monster::MoveOnX( int newDirection, BITMAP* tempBitmap, BITMAP* mainBitmap, BITMAP* cena){
   direction = newDirection;
   draw_sprite( tempBitmap, cena, 0, 0);
   int HelpNumber = GetHelpNumber(Stage);
    if( CheckImages()){
		if( direction == LEFT){
			x -= 10;
			DrawNewSprite( tempBitmap, images[0][HelpNumber]);
			if (Stage == 3) Stage = 0;
			else Stage++;

			draw_sprite( cena, tempBitmap, 0, 0);

		} else {
			x += 10;
			DrawNewSprite( tempBitmap, images[1][HelpNumber]);
			if (Stage == 3) Stage = 0;
			else Stage++;

			draw_sprite( cena, tempBitmap, 0, 0);

		}
    }

}

void Monster::MoveOnY( int newDirection, BITMAP* tempBitmap, BITMAP* mainBitmap, BITMAP* cena){
   direction = newDirection;
   draw_sprite( tempBitmap, cena, 0, 0);
   int HelpNumber = GetHelpNumber(Stage);
   if( CheckImages()){
	   if( direction == UP){
		   y -= 10;
		   DrawNewSprite( tempBitmap, images[2][HelpNumber]);
		   if (Stage == 3) Stage = 0;
		   else Stage++;

		   draw_sprite( cena, tempBitmap, 0, 0);

	   } else {
		   y += 10;
		   DrawNewSprite( tempBitmap, images[3][HelpNumber]);
		   if (Stage == 3) Stage = 0;
		   else Stage++;

		   draw_sprite( cena, tempBitmap, 0, 0);
	   }
    }
}


void Monster::EraseOldSprite( BITMAP* tempBitmap)
{
    draw_sprite( tempBitmap, tempBitmap, GetX(), GetY());
}

void Monster::printStatus (BITMAP* mainBitmap)
{
	char palavra[50];
	float Life = (float)HP/(float)HP0;
	draw_sprite(mainBitmap, status, GetX()-35, GetY()-45);

	if (Life>0.6) rectfill(mainBitmap, GetX()+23, GetY()-23, GetX()+23+36*Life, GetY()-16, makecol(0, 255, 0));
	else if (Life>0.4) rectfill(mainBitmap, GetX()+23, GetY()-23, GetX()+23+36*Life, GetY()-16, makecol(255, 255, 0));
	else if (Life>0) rectfill(mainBitmap, GetX()+23, GetY()-23, GetX()+23+36*Life, GetY()-16, makecol(255, 0, 0));

	textout_ex(mainBitmap, font, nome, GetX()-7, GetY()-35, makecol(60,60,200), -1);
	textout_ex(mainBitmap, font, itoa(HP ,palavra,10), GetX()-7, GetY()-22, makecol(0,0,0), -1);

}
void Monster::DrawNewSprite( BITMAP* tempBitmap, BITMAP* spriteToDraw){

    draw_sprite( tempBitmap, spriteToDraw, GetX(), GetY());
	printStatus (tempBitmap);

}
void Monster::Show(BITMAP* mainBitmap){

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

void Monster::ShowStats(int X, int Y, BITMAP* mainBitmap){
	char palavra[50];

	draw_sprite(mainBitmap, face, X-120, Y-35);
	textout_ex(mainBitmap, font, nome,X+50,Y-30, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(LVL,palavra,10), X+100,Y, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(HP0,palavra,10), X+100,  Y+35, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(HP ,palavra,10), X+70, Y+35, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(ATK,palavra,10), X-20, Y+110, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(DEF,palavra,10), X-20, Y+140, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(SPD,palavra,10), X-20, Y+170, makecol(0,0,0), -1);
	textout_ex(mainBitmap, font, itoa(SPC,palavra,10), X-20, Y+200, makecol(0,0,0), -1);

}