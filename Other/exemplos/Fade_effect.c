#define USE_CONSOLE
#include <allegro.h>

void highcolor_fade_in(BITMAP *bmp_orig, int speed)
{
   BITMAP *bmp_buff;

    if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H)))
    {
        int a;
        if (speed <= 0) speed = 16;
        
        for (a = 0; a < 256; a+=speed)
        {
            clear(bmp_buff);
            set_trans_blender(0,0,0,a);
            draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
            vsync();
            blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
        }
        destroy_bitmap(bmp_buff);
    } 

    blit(bmp_orig, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
}

void highcolor_fade_out(int speed)
{
    BITMAP *bmp_orig, *bmp_buff;

    if ((bmp_orig = create_bitmap(SCREEN_W, SCREEN_H)))
    {
        if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H)))
        {
            int a;
            blit(screen, bmp_orig, 0,0, 0,0, SCREEN_W, SCREEN_H);
            if (speed <= 0) speed = 16;
        
            for (a = 255-speed; a > 0; a-=speed)
            {
                clear(bmp_buff);
                set_trans_blender(0,0,0,a);
                draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
                vsync();
                blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
            }
            destroy_bitmap(bmp_buff);
        }
        destroy_bitmap(bmp_orig);
    }

    rectfill(screen, 0,0, SCREEN_W,SCREEN_H, makecol(0,0,0));
}

int main(void)
{
    BITMAP *tmp;

    allegro_init();
    install_keyboard();

    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);

    /* set up a temp bitmap to so we can fade back later */
    if (!(tmp = create_bitmap(SCREEN_W, SCREEN_H))) exit(1);
    
    /* create a test screen */
    rectfill(screen, 0,0, SCREEN_W,SCREEN_H, makecol(255,255,255));
    circlefill(screen, 75,75, 25, makecol(255,0,0));

    /* save this test screen so we can fade_in to it later */
    blit(screen, tmp, 0,0, 0,0, SCREEN_W, SCREEN_H);
    readkey();
    
    highcolor_fade_out(16);
    readkey();

    highcolor_fade_in(tmp, 16);
    readkey();

    destroy_bitmap(tmp);
    return 0;
}
END_OF_MAIN()
