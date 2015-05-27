#ifndef MONSTER_H
#define MONSTER_H

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

#include <allegro.h>

class Monster
{

public:
       Monster();
       ~Monster();
       
	   BITMAP * face, *status;
	   char nome[50];
	   int LVL, HP, HP0, STA;
	   int ATK, DEF, SPD, SPC;
	   int moviment, respawn;

       // The following 4 methods will be used to set the images for the different stages of movement

       void SetImagesLeft( char image1[], char image2[], char image3[]);
       void SetImagesRight( char image1[], char image2[], char image3[]);
       void SetImagesUp( char image1[], char image2[], char image3[]);
       void SetImagesDown( char image1[], char image2[], char image3[]);
       
       //To keep the program from crashing, this function will be used before 
       //calling any movement methods
       bool CheckImages();

       int GetX();
       void SetX( int newValue);
       void MoveOnX( int newValue, BITMAP* tempBitmap, BITMAP* mainBitmap, BITMAP* cena);
       
       int GetY();
       void SetY( int newValue);
       void MoveOnY( int newValue, BITMAP* tempBitmap, BITMAP* mainBitmap, BITMAP* cena);
       
	   int Stage;
	   int GetHelpNumber( int Stage);
       void EraseOldSprite( BITMAP* tempBitmap);
       void DrawNewSprite( BITMAP* tempBitmap, BITMAP* spriteToDraw); 
       
	   void printStatus (BITMAP* bitmap);
       void Show(BITMAP* mainBitmap); 

	   void ShowStats (int X, int Y, BITMAP* mainBitmap);

       
private:
        bool leftDone, rightDone;
        bool upDone, downDone;
        
        int direction, x, y;
        
        //This will contain all the images, [0][0-2] will be left movements, [1][0-2] right
        //[2][0-2] upwards, and [3][0-2] downwards
        BITMAP *images[4][3]; 
};

#endif