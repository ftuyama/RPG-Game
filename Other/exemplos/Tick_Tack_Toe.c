#define USE_CONSOLE
#include <allegro.h>
#include <stdio.h>

int x = 100;
int y = 100;

int tempX = 100;
int tempY = 100;

int dir = 1; //This will keep track of the circles direction
//1= up and left, 2 = down and left, 3 = up and right, 4 = down and right

void moveCircle(){

	tempX = x;
	tempY = y;

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

	} else { 

		dir = rand() % 4 + 1;

	}    

	acquire_screen();
	circlefill ( screen, tempX, tempY, 20, makecol( 0, 0, 0));
	circlefill ( screen, x, y, 20, makecol( 128, 255, 0));
	release_screen();

	rest(10);

}    

void main()
{
	allegro_init();
	install_keyboard();
	set_color_depth(32);
	set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);

	while( !key[KEY_ESC]){

		moveCircle();

	}    
}

END_OF_MAIN();