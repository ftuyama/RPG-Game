#include "Animation.h"

Animation::Animation()
{

}

Animation::~Animation()
{

}

void Animation::SetImages( char image1[], char image2[], char image3[], char image4[], char image5[])
{

   animat[0][0]= load_bitmap(image1, NULL);
   animat[0][1]= load_bitmap(image2, NULL);
   animat[0][2]= load_bitmap(image3, NULL);
   animat[0][3]= load_bitmap(image4, NULL);
   animat[0][4]= load_bitmap(image5, NULL);
       
}