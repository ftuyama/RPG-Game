#define USE_CONSOLE
#include <allegro.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int x = 320;
int y = 240;

float raddius;

int tempX = 100;
int tempY = 100;
int t = 0;

int dir = 1; //This will keep track of the circles direction
//1= up and left, 2 = down and left, 3 = up and right, 4 = down and right

void moveCircle(){

	tempX = x;
	tempY = y;

	dir = rand() % 4 + 1;

	if (dir == 1 && x != 20 && y != 20){

		--x;
		--y;

	} else if (dir == 2 && x != 20 && y != 460){

		--x;
		++y;

	} else if (dir == 3 && x != 620 && y != 20){

		++x;
		--y;

	} else if (dir == 4 && x != 620 && y != 460){

		++x;
		++y;

	}

	acquire_screen();
	circlefill ( screen, tempX, tempY, 20, makecol( 0, 0, 0));
	circlefill ( screen, x, y, 20, makecol( 255, 0, 0));
	release_screen();

	rest(10);

}    

void main()
{
	char radius[50];
	srand(time(NULL));
	allegro_init();
	install_keyboard();
	set_color_depth(32);
	set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);

	line(screen, 320 , 0, 320, 480, makecol(255,255,0 ));
    line(screen, 0 , 240, 640, 240, makecol(255,255,0 ));
	circle (screen, 320,240,300, makecol(0,0,255));
	circle (screen, 320,240,200, makecol(0,0,255));
	circle (screen, 320,240,100, makecol(0,0,255));
	textout_ex(screen, font, "Probabilistic Machine by Tuyama",50,10, makecol(255,0,0), -1);

	while( !key[KEY_ESC]){

		moveCircle();
		raddius = sqrt((double)((x-320)*(x-320)+(y-240)*(y-240)));
		textout_ex(screen, font, "radius: ", 30, 30, makecol(255,0,0), -1);
		if (t%100==0)
		{
			rectfill(screen, 90, 25, 150, 40, makecol(0, 0, 0));
			textout_ex(screen, font, itoa(raddius, radius, 10), 100, 30, makecol(255,0,0), -1);
		}
		t+=1;

	}    
}

END_OF_MAIN();