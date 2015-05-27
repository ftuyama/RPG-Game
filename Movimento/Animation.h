#ifndef ANIMATION_H
#define ANIMATION_H

#include <allegro.h>

class Animation
{

public:

       Animation();
       ~Animation();

	   BITMAP *animat[4][5];

	   void SetImages (char image1[], char image2[], char image3[], char image4[], char image5[]);

};

#endif