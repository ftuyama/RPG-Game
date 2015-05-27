#include "Ability.h"

Ability::Ability()
{

}

Ability::~Ability()
{

}

void Ability::setAbilityQ(int CD, int CDE, int cooldown)
{
	CDQ= CD; CDEQ = CDE; cooldownQ = cooldown;
}

void Ability::SetImagesQ( char image1[], char image2[], char image3[], char image4[], char image5[]){
       
   ability[0][0]= load_bitmap(image1, NULL);
   ability[0][1]= load_bitmap(image2, NULL);
   ability[0][2]= load_bitmap(image3, NULL);
   ability[0][3]= load_bitmap(image4, NULL);
   ability[0][4]= load_bitmap(image5, NULL);
       
}