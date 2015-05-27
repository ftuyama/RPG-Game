#define USE_CONSOLE
#include <allegro.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "luta.h"
#include "Character.h"
#include "Monster.h"

using namespace std;
bool P, f5buy;
int FPS = 10, slot, fase, matriz[1280][640];
int color[4], myset[4], pix, d;
char palavra[50];
BITMAP *fase1, *fase2;
BITMAP *buffer, *background, *saida;
BITMAP *cena, *capa, *pause, *buyscreen;
BITMAP *PvPon, *PvPoff, *P1, *P2;
Luta sistemaluta;
Character myChar, myChar2;
Monster slime[5], boss1, *slot1, *slot2;
Equipament armor[7], sword[7], other[7];
MIDI *title, *city, *mercado, *boss;

void ConfigurarFase(BITMAP *afase, int r, int g, int b)
{
	myset[0] = r; myset[1] = g; myset[2] = b;
	for (int y = 0; y < afase->h; y++)
         for (int x = 0; x < afase->w; x++)
		{
			d = 0;
			pix = getpixel(afase, x, y);
			color[0] = getr(pix);
			color[1] = getg(pix);
			color[2] = getb(pix);
			for (int i = 0; i<3; i++)
				d+=(color[i]-myset[i])*(color[i]-myset[i]);
			if (d<100) matriz[x][y] = 0;
			
			if (d<100) putpixel(afase,x,y,0);
			
		}
}
void Setup()
{
	 myChar.habil.setAbilityQ (120,30,120);
	 myChar2.habil.setAbilityQ (120,0,120);

	 P = f5buy = true;
	 slot = fase = 1;
	 slot1 = slot2 = NULL;

	 P1 = load_bitmap( "Imagens\\P1.bmp", NULL);
	 P2 = load_bitmap( "Imagens\\P2.bmp", NULL);
	 PvPon = load_bitmap( "Imagens\\PvPon.bmp", NULL);
	 PvPoff = load_bitmap( "Imagens\\PvPoff.bmp", NULL);
	 saida = load_bitmap( "Imagens\\exit.bmp", NULL);
	 title = load_midi("Musica\\title.mid");
	 city = load_midi("Musica\\city.mid");
	 boss = load_midi("Musica\\boss.mid");
	 mercado = load_midi("Musica\\mercado.mid");

	 for (int i=0; i<1280; i++)
		 for (int j=0; j<640; j++)
			 matriz[i][j] = 1;
	 cena = create_bitmap(1280,640);
     buffer = create_bitmap(1280,640);
	 buyscreen = load_bitmap( "Imagens\\trade.bmp",NULL);
	 pause = load_bitmap( "Imagens\\pause.bmp",NULL);
	 capa = load_bitmap( "Imagens\\capa.bmp", NULL);
	 fase1 = load_bitmap( "Imagens\\fase1.bmp", NULL);
	 fase2 = load_bitmap( "Imagens\\fase2.bmp", NULL);

	 //void configEquip (int LVL, int HP0, int STA, int ATK, int DEF, int SPD, int SPC, int RANGE, int custo);
	 armor[0].image = load_bitmap( "Itens\\armor0.bmp", NULL); 
	 strcpy (armor[0].nome, "Leather Armor"); armor[0].configEquip(1,5,1,0,2,0,0,0,10);
	 armor[1].image = load_bitmap( "Itens\\armor1.bmp", NULL); 
	 strcpy (armor[1].nome, "Chain Armor"); armor[1].configEquip(2,10,2,0,5,0,0,0,20);
	 armor[2].image = load_bitmap( "Itens\\armor2.bmp", NULL); 
	 strcpy (armor[2].nome, "Plate Armor"); armor[2].configEquip(3,15,3,0,8,0,0,0,30);
	 armor[3].image = load_bitmap( "Itens\\armor3.bmp", NULL); 
	 strcpy (armor[3].nome, "Golden Armor"); armor[3].configEquip(4,20,4,0,10,0,0,0,40);

	 sword[0].image = load_bitmap( "Itens\\sword0.bmp", NULL); 
	 strcpy (sword[0].nome, "Knife"); sword[0].configEquip(1,0,1,2,0,5,0,0,5);
	 sword[1].image = load_bitmap( "Itens\\sword1.bmp", NULL); 
	 strcpy (sword[1].nome, "Normal Sword"); sword[1].configEquip(2,0,3,5,2,2,0,0,10);
	 sword[2].image = load_bitmap( "Itens\\sword2.bmp", NULL); 
	 strcpy (sword[2].nome, "Rapier Sword"); sword[2].configEquip(3,0,10,10,5,15,0,0,35);
	 sword[3].image = load_bitmap( "Itens\\sword3.bmp", NULL); 
	 strcpy (sword[3].nome, "OP Sword"); sword[3].configEquip(4,5,10,13,13,7,0,5,40);

	 other[0].image = load_bitmap( "Itens\\other0.bmp", NULL); 
	 strcpy (other[0].nome, "Normal Shield"); other[0].configEquip(1,5,2,0,5,0,0,0,10);
	 other[1].image = load_bitmap( "Itens\\other1.bmp", NULL); 
	 strcpy (other[1].nome, "Boot"); other[1].configEquip(1,2,5,0,0,5,0,0,10);
	 other[2].image = load_bitmap( "Itens\\other2.bmp", NULL); 
	 strcpy (other[2].nome, "Bow"); other[2].configEquip(1,0,2,5,0,5,0,20,10);
	 other[3].image = load_bitmap( "Itens\\other3.bmp", NULL); 
	 strcpy (other[3].nome, "OP other"); other[3].configEquip(4,5,10,13,13,7,0,5,40);

	 strcpy (boss1.nome, "Goro");
	 boss1.face = load_bitmap( "boss1\\face.bmp", NULL);
	 boss1.SetImagesLeft( "boss1\\left1.bmp", "boss1\\left2.bmp", "boss1\\left3.bmp");
	 boss1.SetImagesRight( "boss1\\right1.bmp", "boss1\\right2.bmp", "boss1\\right3.bmp");
	 boss1.SetImagesUp( "boss1\\up1.bmp", "boss1\\up2.bmp", "boss1\\up3.bmp");
	 boss1.SetImagesDown( "boss1\\down1.bmp", "boss1\\down2.bmp", "boss1\\down3.bmp");
	 boss1.status = load_bitmap( "Imagens\\status2.bmp", NULL);
	 boss1.LVL = 5; boss1.HP = boss1.HP0 = 50; 
	 boss1.ATK = 25; boss1.DEF = 30; boss1. SPD = 20; boss1.SPC = 15;
	 boss1.SetX(600); boss1.SetY(250);

	 for (int i = 0; i<5; i++)
	 {
		 strcpy (slime[i].nome, "Slime");
		 slime[i].face = load_bitmap( "slime\\face.bmp", NULL);
		 slime[i].SetImagesLeft( "slime\\left1.bmp", "slime\\left2.bmp", "slime\\left3.bmp");
		 slime[i].SetImagesRight( "slime\\right1.bmp", "slime\\right2.bmp", "slime\\right3.bmp");
		 slime[i].SetImagesUp( "slime\\up1.bmp", "slime\\up2.bmp", "slime\\up3.bmp");
		 slime[i].SetImagesDown( "slime\\down1.bmp", "slime\\down2.bmp", "slime\\down3.bmp");
		 slime[i].status = load_bitmap( "Imagens\\status2.bmp", NULL);
		 slime[i].LVL = 1; slime[i].HP = slime[i].HP0 = 5 + rand() % 5;
		 slime[i].ATK = 5 + rand() % 5; slime[i].DEF = 5 + rand() % 5;
		 slime[i]. SPD = 10 + rand() % 5; slime[i].SPC = 5 + rand() % 5;
	 }
	 slime[0].SetX(600); slime[0].SetY(400);
	 slime[1].SetX(550); slime[1].SetY(255);
	 slime[2].SetX(675); slime[2].SetY(135);
	 slime[3].SetX(900); slime[3].SetY(275);
	 slime[4].SetX(255); slime[4].SetY(150);
	
	 strcpy (myChar.nome, "Lance");
	 myChar.face = load_bitmap( "Char1\\face.bmp", NULL);
	 myChar.habil.SetImagesQ ("Char1\\Q\\Q0.bmp","Char1\\Q\\Q1.bmp","Char1\\Q\\Q2.bmp","Char1\\Q\\Q3.bmp","Char1\\Q\\Q4.bmp");
     myChar.SetImagesLeft( "Char1\\left1.bmp", "Char1\\left2.bmp", "Char1\\left3.bmp");
     myChar.SetImagesRight( "Char1\\right1.bmp", "Char1\\right2.bmp", "Char1\\right3.bmp");
     myChar.SetImagesUp( "Char1\\up1.bmp", "Char1\\up2.bmp", "Char1\\up3.bmp");
     myChar.SetImagesDown( "Char1\\down1.bmp", "Char1\\down2.bmp", "Char1\\down3.bmp");
	 myChar.AtkAnim.SetImages ("Itens\\fist\\0.bmp","Itens\\fist\\1.bmp","Itens\\fist\\2.bmp","Itens\\fist\\3.bmp","Itens\\fist\\4.bmp");
	 myChar.status = load_bitmap( "Imagens\\status.bmp", NULL);
	 myChar.SetX(200); myChar.SetY(250);
	 
	 strcpy (myChar2.nome, "Kirito");
	 myChar2.face = load_bitmap( "Char2\\face.bmp", NULL);
	 myChar2.habil.SetImagesQ ("Char2\\Q\\Q0.bmp","Char2\\Q\\Q1.bmp","Char2\\Q\\Q2.bmp","Char2\\Q\\Q3.bmp","Char2\\Q\\Q4.bmp");
	 myChar2.SetImagesLeft( "Char2\\left1.bmp", "Char2\\left2.bmp", "Char2\\left3.bmp");
     myChar2.SetImagesRight( "Char2\\right1.bmp", "Char2\\right2.bmp", "Char2\\right3.bmp");
     myChar2.SetImagesUp( "Char2\\up1.bmp", "Char2\\up2.bmp", "Char2\\up3.bmp");
     myChar2.SetImagesDown( "Char2\\down1.bmp", "Char2\\down2.bmp", "Char2\\down3.bmp");
	 myChar2.AtkAnim.SetImages ("Itens\\fist\\0.bmp","Itens\\fist\\1.bmp","Itens\\fist\\2.bmp","Itens\\fist\\3.bmp","Itens\\fist\\4.bmp");
	 myChar2.status = load_bitmap( "Imagens\\status.bmp", NULL);
	 myChar2.SetX(400); myChar2.SetY(250);

	 play_midi(title,true);
	 draw_sprite(screen, capa, 0, 0);
	 ConfigurarFase(fase1,130,195,195);
}

void Combat()
{
	if (myChar.habil.cooldownQ < myChar.habil.CDQ) myChar.habil.cooldownQ++;
	if (myChar2.habil.cooldownQ < myChar2.habil.CDQ) myChar2.habil.cooldownQ++;

	if (sistemaluta.PvP) sistemaluta.checkCombat (&myChar, &myChar2, cena);
	if (fase == 1)
	{
		for (int i = 0; i<5; i++)
		{
			sistemaluta.checkMCombat (&myChar, &slime[i], cena);
			sistemaluta.checkMCombat (&myChar2, &slime[i], cena);
		}
		for (int i = 0; i<5; i++)
		{
			if (slime[i].respawn>300) {
				slime[i].HP = slime[i].HP0;
				slime[i].respawn = 0;
			}
			else
			{
				if (slime[i].HP<=0) 
					slime[i].respawn++;
			}
		}
	}
	if (fase == 2)
	{
		sistemaluta.checkMCombat (&myChar, &boss1, cena);
		sistemaluta.checkMCombat (&myChar2, &boss1, cena);
	}
}
/************* Movimento das Entidades ****************/
void moveMonster()
{
	int move;
	if (fase == 1)
	{
		for (int i = 0; i<5; i++)
		{
			if (slime[i].HP>0) {
				if (slime[i].moviment==10)
				{
					move = 1 + rand() % 4;
					switch (move)
					{
					case 1: slime[i].MoveOnX( LEFT, buffer, screen, cena); break;
					case 2: slime[i].MoveOnX( RIGHT, buffer, screen, cena); break;
					case 3: slime[i].MoveOnY( UP, buffer, screen, cena); break;
					case 4: slime[i].MoveOnY( DOWN, buffer, screen, cena); break;
					}
					slime[i].moviment = 0;
				}
				else 
				{
					slime[i].Show(cena);
					slime[i].moviment++;
				}
			}
		}
	}
	if (fase == 2)
	{
		if (boss1.HP>0) 
		{
			if (boss1.moviment==10)
			{
				move = 1 + rand() % 4;
				switch (move)
				{
				case 1: boss1.MoveOnX( LEFT, buffer, screen, cena); break;
				case 2: boss1.MoveOnX( RIGHT, buffer, screen, cena); break;
				case 3: boss1.MoveOnY( UP, buffer, screen, cena); break;
				case 4: boss1.MoveOnY( DOWN, buffer, screen, cena); break;
				}
				boss1.moviment = 0;
			}
			else 
			{
				boss1.Show(cena);
				boss1.moviment++;
			}
		}
	}
}
bool CheckMov(Character Char, int u, int v)
{
	int judge = 0;
	int movrange = 5+Char.SPD/10;
	int hei = Char.images[0][0]->h;
	int wei = Char.images[0][0]->w;
	if (u == -1)
		for (int X = 0; X<movrange; X++)
			for (int Y = 0; Y<hei; Y++)
				if(matriz[Char.GetX()-X][Char.GetY()+Y]==0)
					if (judge++>0.25*(movrange)*(hei))
						return true;
	if (u == 1)
		for (int X = wei; X < wei+movrange; X++)
			for (int Y = 0; Y<hei; Y++)
				if(matriz[Char.GetX()+X][Char.GetY()+Y]==0)
					if (judge++>0.25*(movrange)*(hei))
						return true;
	if (v == -1)
		for (int X = 0; X < wei; X++)
			for (int Y = hei; Y<hei+movrange; Y++)
				if(matriz[Char.GetX()+X][Char.GetY()+Y]==0)
					if (judge++>0.25*(movrange)*(wei))
						return true;
	if (v == 1)
		for (int X = 0; X < wei; X++)
			for (int Y = 0; Y<movrange; Y++)
				if(matriz[Char.GetX()+X][Char.GetY()-Y]==0)
					if (judge++>0.25*(movrange)*(wei))
						return true;
	Char.move = false;
	return false;
}
void movePlayer()
{
	myChar.move = myChar2.move = false;
	if (key[KEY_LEFT] || key[KEY_RIGHT] || key[KEY_UP] || key[KEY_DOWN]) 
	{
		myChar.move = true;
		if( key[KEY_LEFT] && CheckMov(myChar, -1, 0)) {
			myChar2.Show(cena);
			myChar.MoveOnX( LEFT, buffer, screen, cena);
		}
		else if( key[KEY_RIGHT] && CheckMov(myChar, 1, 0)){
			myChar2.Show(cena);
			myChar.MoveOnX( RIGHT, buffer, screen, cena);
		}
		else if( key[KEY_UP] && CheckMov(myChar, 0, 1)) {
			myChar2.Show(cena);
			myChar.MoveOnY( UP, buffer, screen, cena);
		}
		else if( key[KEY_DOWN] && CheckMov(myChar, 0, -1)){
			myChar2.Show(cena);
			myChar.MoveOnY( DOWN, buffer, screen, cena);
		}
	}
	if (key[KEY_A]|| key[KEY_D]|| key[KEY_S] || key[KEY_W])
	{
		myChar2.move = true;
		if( key[KEY_A] && CheckMov(myChar2, -1, 0)){
			myChar.Show(cena);
			myChar2.MoveOnX( LEFT, buffer, screen, cena);
		}
		else if( key[KEY_D] && CheckMov(myChar2, 1, 0)){
			myChar.Show(cena);
			myChar2.MoveOnX( RIGHT, buffer, screen, cena);
		}
		else if( key[KEY_W] && CheckMov(myChar2, 0, 1)){
			myChar.Show(cena);
			myChar2.MoveOnY( UP, buffer, screen, cena);
		}
		else if( key[KEY_S] && CheckMov(myChar2, 0, -1)){
			myChar.Show(cena);
			myChar2.MoveOnY( DOWN, buffer, screen, cena);
		}
	}
	if (!myChar.move && !myChar2.move)
	{
		myChar.Show(cena);
		myChar2.Show(cena);
		draw_sprite(screen, cena, 0, 0);
	}
}
/******************************************************/
void game_pause()
{
	draw_sprite(buffer, pause, 0, 0);
	myChar.ShowStats(150,75, buffer);
	myChar2.ShowStats(465,75, buffer);
	if (slot1 !=NULL) slot1->ShowStats(780,75, buffer);
	if (slot2 !=NULL) slot2->ShowStats(1100,75, buffer);
	draw_sprite(buffer, saida, 800, 500);
	draw_sprite(screen, buffer, 0, 0);
	do
	{
		if(mouse_b & 1)
		{
			if (mouse_x>800 && mouse_x<950)
				if (mouse_y>500 && mouse_y<580)
					exit(1);
			if (mouse_x>800 && mouse_x<950)
				if (mouse_y>350 && mouse_y<450)
					sistemaluta.PvP = !sistemaluta.PvP;
		}
		if (sistemaluta.PvP) draw_sprite(buffer, PvPon, 800, 350);
		else draw_sprite(buffer, PvPoff, 800, 350);
		show_mouse(buffer);
		draw_sprite(screen, buffer, 0, 0);
		rest(100);
	} while (!key[KEY_SPACE]);
	rest(100);
}
/*********************** Equipar *************************/
void equipar(Character *Char, Equipament Equipa, int tipo)
{
	f5buy = true;
	Char->MONEY -= Equipa.custo;
	Char->HP0 += Equipa.HP0; Char->STA += Equipa.STA;
	Char->ATK += Equipa.ATK; Char->DEF += Equipa.DEF;
	Char->SPD += Equipa.SPD; Char->SPC += Equipa.SPC;
	Char->RANGE += Equipa.RANGE;
	if (tipo == 1)
	{
		if (!Char->armored)
			Char->armored = true;
		else
		{
			Char->HP0 -= Char->armor.HP0; Char->STA -= Char->armor.STA;
			Char->ATK -= Char->armor.ATK; Char->DEF -= Char->armor.DEF;
			Char->SPD -= Char->armor.SPD; Char->SPC -= Char->armor.SPC;
			Char->RANGE -= Char->armor.RANGE;

		}
		Char->armor = Equipa;
	}
	else if (tipo == 2)
	{
		if (strcmp(Equipa.nome,"OP Sword")==0)
			if (strcmp(Char->nome,"Lance")==0)
				myChar.AtkAnim.SetImages ("Itens\\OPSWORD1\\0.bmp","Itens\\OPSWORD1\\1.bmp","Itens\\OPSWORD1\\2.bmp",
											"Itens\\OPSWORD1\\3.bmp","Itens\\OPSWORD1\\4.bmp");
			else 
				myChar2.AtkAnim.SetImages ("Itens\\OPSWORD1\\0.bmp","Itens\\OPSWORD1\\1.bmp","Itens\\OPSWORD1\\2.bmp",
											"Itens\\OPSWORD1\\3.bmp","Itens\\OPSWORD1\\4.bmp");
		if (!Char->sworded)
			Char->sworded = true;
		else
		{
			Char->HP0 -= Char->sword.HP0; Char->STA -= Char->sword.STA;
			Char->ATK -= Char->sword.ATK; Char->DEF -= Char->sword.DEF;
			Char->SPD -= Char->sword.SPD; Char->SPC -= Char->sword.SPC;
			Char->RANGE -= Char->sword.RANGE;
		}
		Char->sword = Equipa;

	}
	else if (tipo == 3)
	{
		if (!Char->othered)
			Char->othered = true;
		else
		{
			Char->HP0 -= Char->other.HP0; Char->STA -= Char->other.STA;
			Char->ATK -= Char->other.ATK; Char->DEF -= Char->other.DEF;
			Char->SPD -= Char->other.SPD; Char->SPC -= Char->other.SPC;
			Char->RANGE -= Char->other.RANGE;
		}
		Char->other = Equipa;

	}

}
/*********************** Buy Screen *************************/
void game_buy()
{
	f5buy = true;
	play_midi(mercado,true);
	do
	{
		if (f5buy)
		{
			draw_sprite(buffer, buyscreen, 0, 0);
			myChar.ShowStats(150,75, buffer);
			myChar2.ShowStats(465,75, buffer);
			for (int i=0; i<=3; i++)
			{
				armor[i].showEquip(689,181+56*i,buffer);
				sword[i].showEquip(882,180+56*i,buffer);
				other[i].showEquip(1073,178+56*i,buffer);
			}
			draw_sprite(screen, buffer, 0, 0);
			f5buy = false;
		}
		if(mouse_b & 1)
		{
			if (mouse_x>771 && mouse_x<823)
				if (mouse_y>22 && mouse_y<73)
					P=!P;
			if (mouse_x>709 && mouse_x<762)
				if (mouse_y>22 && mouse_y<73)
					P=!P;
			for (int i=0; i<=3; i++)
			{
				if (mouse_x>689 && mouse_x<689+32)
					if (mouse_y>181+56*i && mouse_y<181+32+56*i)
					{
						if (P && myChar.MONEY > armor[i].custo) equipar(&myChar, armor[i], 1);
						if (!P && myChar2.MONEY > armor[i].custo) equipar(&myChar2, armor[i], 1);
					}
				if (mouse_x>882 && mouse_x<882+32)
					if (mouse_y>180+56*i && mouse_y<180+32+56*i)
					{
						if (P && myChar.MONEY > sword[i].custo) equipar(&myChar, sword[i], 2);
						if (!P && myChar2.MONEY > sword[i].custo) equipar(&myChar2, sword[i], 2);
					}
				if (mouse_x>1073 && mouse_x<1073+32)
					if (mouse_y>178+56*i && mouse_y<178+32+56*i)
					{
						if (P && myChar.MONEY > other[i].custo) equipar(&myChar, other[i], 3);
						if (!P && myChar2.MONEY > other[i].custo) equipar(&myChar2, other[i], 3);
					}
			}
		}
		if (P) draw_sprite(buffer, P1, 709, 22);
		else draw_sprite(buffer, P2, 709, 22);
		show_mouse(buffer);
		draw_sprite(screen, buffer, 0, 0);
		rest(100);
	} while (!key[KEY_B]);
	play_midi(city,true);
	rest(100);
}
/*********************** Mouse *************************/
void comando_mouse()
{
	if (mouse_x>365 && mouse_x<430)
		if (mouse_y>180 && mouse_y<240) {
			myChar.HP = myChar.HP0;
			myChar2.HP = myChar2.HP0;
		}
	if (fase==1)
	{
		for (int i = 0; i<5; i++) {
			if (mouse_x>slime[i].GetX() && mouse_x<slime[i].GetX()+32)
				if (mouse_y>slime[i].GetY() && mouse_y<slime[i].GetY()+25) 
				{
					if (slot == 1) {
						if (slot1==NULL)
							slot1 = (Monster*)malloc(sizeof(Monster));
						*slot1 = slime[i];
						slot = 2;
					}
					else {
						if (slot2==NULL)
							slot2 = (Monster*)malloc(sizeof(Monster));
						*slot2 = slime[i];
						slot = 1;
					}
					game_pause();
				}
		}
	}
	if (fase==2)
	{
		if (mouse_x>boss1.GetX() && mouse_x<boss1.GetX()+32)
			if (mouse_y>boss1.GetY() && mouse_y<boss1.GetY()+25) 
			{
				if (slot == 1) {
					if (slot1==NULL)
						slot1 = (Monster*)malloc(sizeof(Monster));
					*slot1 = boss1;
					slot = 2;
				}
				else {
					if (slot2==NULL)
						slot2 = (Monster*)malloc(sizeof(Monster));
					*slot2 = boss1;
					slot = 1;
				}
				game_pause();
			}
	}
}
/*********************** Controle das Fases *************************/
void show_fase()
{
	if (fase == 1)
	{
		draw_sprite( cena, fase1, 0, 0);
		if (myChar.GetX()<30 && myChar2.GetX()<30)
			if (myChar.GetY()>240 && myChar2.GetY()>240)
				if (myChar.GetY()<290 && myChar2.GetY()<290)
				{
					rectfill(screen, 0, 0, 1280, 640, makecol(0, 0, 0));
					play_midi(boss,true);
					myChar.SetX(200); myChar.SetY(250);
					myChar2.SetX(400); myChar2.SetY(250);
					fase = 2;
					rest(100);
				}
	}
	if (fase == 2)
	{
		draw_sprite( cena, fase2, 0, 0);
		if (myChar.GetX()<30 && myChar2.GetX()<30)
			if (myChar.GetY()>240 && myChar2.GetY()>240)
				if (myChar.GetY()<290 && myChar2.GetY()<290)
				{
					rectfill(screen, 0, 0, 1280, 640, makecol(0, 0, 0));
					play_midi(city,true);
					myChar.SetX(200); myChar.SetY(250);
					myChar2.SetX(400); myChar2.SetY(250);
					fase = 1;
					rest(100);
				}
	}
}
/*********************** Main *************************/
void main()
{
    allegro_init(); 
    install_mouse(); 
    install_keyboard(); 
    set_color_depth(16); 
    install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 1280, 640, 0, 0); 
    
    Setup();
	while (!key[KEY_ENTER]);
	play_midi(city,true);
    while( !key[KEY_ESC])
	{
		if(mouse_b & 1) comando_mouse();
		if (key[KEY_SPACE]) game_pause();
		if (key[KEY_B]) game_buy();
		show_fase();
		show_mouse(cena);
		Combat();
		moveMonster();
		movePlayer();
		rest(FPS);
    }
    
}