#define USE_CONSOLE
#include <allegro.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

float tempo;
bool GameOver, end;

bool ashield, shield;
int timeshield;

int x, y, tempX, tempY;

char texto[50];
float speed = 1;
int dir = 1; //This will keep track of the circles direction
            //1= up and left, 2 = down and left, 3 = up and right, 4 = down and right

BITMAP *buffer; //This will be our temporary bitmap for double buffering

void iniciar()
{
	srand(time(NULL));
	ashield = false;
	end = false;
	shield = false;
	GameOver = false;
	x = rand() % 600;
	y = rand() % 400;
	x += 20;
	y += 20;
	timeshield = 0;
	speed = 1;
	tempo = 0;
}
void drawtime()
{
	rectfill(buffer, 200, 460, 250, 480, makecol(0, 0, 0));
	textout_ex(buffer, font, itoa(tempo, texto, 10), 220, 470, makecol(255,255,255), -1);
}
void drawlines()
{
	line(buffer,20,20,20,460,makecol(0,0,255));
	line(buffer,20,20,620,20,makecol(0,0,255));
	line(buffer,20,460,620,460,makecol(0,0,255));
	line(buffer,620,20,620,460,makecol(0,0,255));
}
void drawintro()
{
	textout_ex(buffer, font, "Squishy pRayer   by Tuyama.",350,470, makecol(0,255,255), -1);
	textout_ex(buffer, font, "Clique para comecar.",50,10, makecol(255,255,255), -1);
	textout_ex(buffer, font, "Seu objetivo eh desviar da esfera.",350,10, makecol(255,255,255), -1);
	textout_ex(buffer, font, "Tempo de Jogo : .",50,470, makecol(255,255,255), -1);
}
void moveCircle(){

    tempX = x;
    tempY = y;

	for (int i = 0; i<speed; i++)
	{
		if (x==20) dir+=2;
		else if (y==20) dir+=1;
		else if (x==620) dir-=2;
		else if (y==460) dir-=1;
		if (dir == 1){
			--x; --y;
		} else if (dir == 2){
			--x; ++y;
		} else if (dir == 3){
			++x; --y;
		} else if (dir == 4){
			++x; ++y;
		}
	}
    circlefill ( buffer, tempX, tempY, 20, makecol( 0, 0, 0));
    circlefill ( buffer, x, y, 20, makecol( 255, 0, 0));
}    
void doshield()
{
	int mx, my;
	if ((mouse_b &2) && shield == true) 
	{
		ashield = true;
		timeshield = 0;
	}
	if (ashield == true)
	{
		mx = mouse_x;
		my = mouse_y;
		circle(screen, mx, my, 50, makecol(255,0,0));
		timeshield++;
		if (timeshield==200)
		{
			timeshield = 0;
			shield = false;
			ashield = false;
		}
	}
	else
	{
		timeshield++;
		if (timeshield%500==0) 
			shield = true;
	}
	if (!shield)
	{
		rectfill(buffer, 625, 180, 635, 130, makecol(0, 0, 0));
		rectfill(buffer, 625, 180, 635, 130+timeshield/10, makecol(255, 0, 0));
		textout_ex(buffer, font, "ULT.",620,200, makecol(255,0,0), -1);
		circlefill(buffer, 630,230,10, makecol(255,0,0));
	}
	else
	{
		if (ashield == true)
		{
			rectfill(buffer, 625, 180, 635, 130, makecol(0, 0, 0));
			rectfill(buffer, 625, 180, 635, 130+5*timeshield/20, makecol(0, 255, 0));
		}
		else rectfill(buffer, 625, 180, 635, 130, makecol(0, 255, 0));
		textout_ex(buffer, font, "ULT.",620,200, makecol(0,255,0), -1);
		circlefill(buffer, 630,230,10, makecol(0,255,0));
	}
}
void checkGameOver()
{
	float d;
	int mx, my;

	mx = mouse_x;
	my = mouse_y;

	d = sqrt((double)((x-mx)*(x-mx)+(y-my)*(y-my)));

	if (mx > 620 || mx < 20 || my > 460 || my < 20)
		d = 0;
	if (d < 20 && ! ashield)
	{
		stop_midi();
		GameOver = true;
		while (! (mouse_b &1) && !end)
		{
			textout_ex(buffer, font, itoa(tempo, texto, 10), 220, 470, makecol(255,0,0), -1);
			textout_ex(buffer, font, "GAME OVER.",300,300, makecol(255,255,255), -1);
			draw_sprite(screen, buffer, 0, 0);
			if (key[KEY_ESC]) 
				end = true;
			rest(10);
		}
	}
}

void main()
{
    allegro_init();
    install_keyboard();
	install_mouse();
	install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);
    set_color_depth(16);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	MIDI *musica;
    musica = load_midi("dungeon.mid");
start:

	iniciar();
	play_midi(musica,true);
    buffer = create_bitmap( 640, 480); 
	moveCircle();
	drawlines();
	draw_sprite(screen, buffer, 0, 0);

	do
	{
		show_mouse(NULL);
		drawintro();
		drawlines();
		moveCircle();
		show_mouse(buffer);
		draw_sprite(screen, buffer, 0, 0);
		rest(10);
	}while (! (mouse_b &1));
    
    while( !key[KEY_ESC])
	{
		show_mouse(NULL);

		doshield();
		moveCircle();

		checkGameOver();
		if (end == true) goto end;
		if (GameOver == true) goto start;

		drawintro();
		drawtime();
		drawlines();
		show_mouse(buffer);
		draw_sprite(screen, buffer, 0, 0);
		speed+=0.1;
		tempo+=0.1;
		rest(10);
    }
end:
	printf ("GG");

}
END_OF_MAIN();