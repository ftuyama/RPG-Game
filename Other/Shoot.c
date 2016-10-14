#define USE_CONSOLE
#include <allegro.h>
#include <stdio.h>
 
int x = 10;
int y = 10;
int shoot = 0;
int u = -1;
int v = -1;
int velx = 0;
int vely = 0;

void main()
{
	allegro_init();
	install_keyboard();
	set_color_depth(32);
 
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
 
	triangle(screen, 320, 40, 147, 340, 493, 340, makecol(255, 255, 0));
	triangle(screen, 230, 190, 320, 340, 410, 190,makecol(0,0,0));

	BITMAP *PAP;
	PAP=load_bitmap("C:\\Users\\Felipe\\Trivia\\06\\Achyos.bmp", NULL);/*logo do P@P em bitmap*/
	draw_sprite(screen,PAP,150,100);


	while(!key[KEY_ESC])
    {      
		clear_keybuf();
        acquire_screen();
        
        textout_ex( screen, font, " ", x, y, makecol( 0, 0, 0), makecol( 0, 0, 0) );
		textout_ex( screen, font, " ", u, v, makecol( 0, 0, 0), makecol( 0, 0, 0) );
        
		if (key[KEY_UP]) { --y; vely = -10; }     
        else if (key[KEY_DOWN]) { ++y; vely = +10; }        
        else if (key[KEY_RIGHT]) { ++x; velx = +10; }     
        else if (key[KEY_LEFT]){ --x; velx = -10; } 
		
		if (key[KEY_W]) shoot = 1;
		if (shoot == 1)
		{
			u+=velx;
			v+=vely;
		}


        textout_ex( screen, font, "@", x, y, makecol( 255, 0, 0), makecol( 0, 0, 0) );
		textout_ex( screen, font, "*", u, v, makecol( 255, 255, 0), makecol( 0, 0, 0) );
        
        release_screen();
        rest(50);
	}
}
 
END_OF_MAIN();