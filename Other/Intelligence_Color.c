#define USE_CONSOLE
#include <allegro.h>
#include <stdio.h>

void main()
{
	int color[4], myset[4], pix, d;
	BITMAP * caixa;
	allegro_init();
	install_keyboard();
	set_color_depth(32);
 
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
 

	myset[0] = 130;
	myset[1] = 195;
	myset[2] = 195;
	caixa = load_bitmap( "Default.bmp", NULL);
	for (int y = 0; y < caixa->h; y++)
         for (int x = 0; x < caixa->w; x++)
		{
			d = 0;
			pix = getpixel(caixa, x, y);
			color[0] = getr(pix);
			color[1] = getg(pix);
			color[2] = getb(pix);
			for (int i = 0; i<3; i++)
				d+=(color[i]-myset[i])*(color[i]-myset[i]);
			if (d<100)
			  putpixel(caixa, x, y, 0);
		}

	draw_sprite(screen, caixa, 0, 0);

	while(!key[KEY_ESC])    
        rest(50);
}
 
END_OF_MAIN();