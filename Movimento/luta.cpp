#include "Luta.h"
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <math.h>

Luta::Luta()
{
	srand(time(NULL));
	PvP = true;
	inbattle = false;
	kill = load_wav("Musica\\kill.wav");
	ataquesound = load_wav("Musica\\ataque.wav");
	fireball = load_wav("Musica\\fireball.wav");
	sword = load_wav("Musica\\sword.wav");

}

Luta::~Luta(){

}

int minimo (int x, int y)
{
	if (x>y) return y;
	return x;
}
void Luta::checkLVL (Character *P)
{
	if (P->MP<0)
	{
		P->LVL--;
		P->HP0 *= 0.9; P->RANGE *= 0.9;
		P->ATK *= 0.9; P->DEF *= 0.9;
		P->SPD *= 0.9; P->SPC *= 0.9;
		P->MP = 0;
	}
	if (P->MP>=10*P->LVL)
	{
		P->LVL++;
		P->HP0 *= 1.1; P->RANGE *= 1.1;
		P->ATK *= 1.1; P->DEF *= 1.1;
		P->SPD *= 1.1; P->SPC *= 1.1;
		P->MP = 0;
	}
}

void Luta::checkdeath (Character *P1, Character *P2){
	if (P1->HP<=0)
	{
		if(strcmp(P1->nome,"Lance")==0)
			if (P1->habil.cooldownQ <= P1->habil.CDEQ)
				abilityQ1(P1,P2);
		P2->MP += P1->HP0;
		checkLVL(P2);
		P2->MONEY += 1/5*P1->MONEY;
		P1->MONEY -= 1/5*P1->MONEY;
		play_sample(kill,255,90,1000,0);
		play_midi(city,true);
	}
	if (P2->HP<=0)
	{
		if(strcmp(P1->nome,"Lance")==0)
			if (P1->habil.cooldownQ <= P1->habil.CDEQ)
				abilityQ1(P1,P2);
		P1->MP += P2->HP0;
		checkLVL(P1);
		P1->MONEY += 1/5*P2->MONEY;
		P2->MONEY -= 1/5*P2->MONEY;
		play_sample(kill,255,90,1000,0);
		play_midi(city,true);
	}
}
void Luta::ataque( Character *Ataque, Character *Defesa, int power, bool ehSPC)
{
	int dano, bonus, ataq;
	if (ehSPC) ataq = Ataque->SPC;
	else ataq = Ataque->ATK;
	bonus = rand() % 16;
	play_sample(ataquesound,255,90,1000,0);
	for (int i=0; i<4; i++)
	{
		draw_sprite(screen, Ataque->AtkAnim.animat[0][i], Defesa->GetX(), Defesa->GetY());
		rest(40);
	}
	if (bonus < Ataque->LUCK) {
		bonus = 50;
		textout_ex(screen, font, "Critical Hit", Defesa->GetX()+30, Defesa->GetY()-20, makecol(255,0,0), -1);
	}
	dano = ((1+0.2*(float)Ataque->LVL)*(float)ataq/(float)Defesa->DEF)*((float)(power+bonus)/100);
	textout_ex(screen, font, itoa(dano,palavra,10), Defesa->GetX()+30, Defesa->GetY()-20, makecol(255,0,0), -1);
	Defesa->HP -= dano;
	Ataque->STA = 0;
}

void Luta::abilityQ2 (Character *P1, Character *P2)
{
	play_sample(sword,255,90,1000,0);
	for (int i=0; i<4; i++)
	{
		draw_sprite(screen, P2->habil.ability[0][i], P1->GetX()-20, P1->GetY()-20);
		rest(20);
	}
	ataque (P2,P1,150,1);
	P2->habil.cooldownQ = 0;
}

void Luta::abilityQ1 (Character *P1, Character *P2)
{
	if (P1->habil.cooldownQ >= P1->habil.CDQ)
	{
		for (int i=0; i<4; i++)
		{
			play_sample(fireball,255,90,1000,0);
			draw_sprite(screen, P1->habil.ability[0][i], P1->GetX()-20, P1->GetY()-20);
			rest(20);
		}
		temp1 = P1->ATK; temp2 = P1->SPD;
		P1->ATK += 0.5*P1->ATK; P1->SPD += 0.5*P1->SPD;
		ataque (P1,P2,100,1);
		P1->habil.cooldownQ = 0;
		P1->STA = 0;
	}
	else if (P1->habil.cooldownQ <= P1->habil.CDEQ)
	{
		P1->ATK = temp1;
		P1->SPD = temp2;
	}
}

void Luta::fight( Character *P1, Character *P2)
{

	if (P1->STA>255/P1->SPD) 
		ataque (P1,P2,100,0);
	else P1->STA++;

	if (P2->STA>255/P2->SPD) 
		ataque (P2,P1,100,0);
	else P2->STA++;

	if(strcmp(P1->nome,"Lance")==0)
	{
		if (P1->habil.cooldownQ >= P1->habil.CDQ)
			if( key[KEY_HOME]) 
				abilityQ1(P1,P2);
		if (P1->habil.cooldownQ == P1->habil.CDEQ)
			abilityQ1(P1,P2);
	}
	if (strcmp(P2->nome,"Kirito")==0)
		if (P2->habil.cooldownQ >= P2->habil.CDQ) 
			if( key[KEY_1]) 
				abilityQ2(P1,P2);
	checkdeath(P1,P2);
}

void Luta::checkCombat( Character *P1, Character *P2, BITMAP *cena)
{
	int min;
	float distance, x1, x2, y1, y2;

	if (P1->HP>0 && P2->HP>0)
	{
		x1 = P1->GetX(); x2 = P2->GetX();
		y1 = P1->GetY(); y2 = P2->GetY();
		distance = sqrt((float)((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
		min = minimo(P1->RANGE, P2->RANGE);

		if (distance < min) 
		{
			if (!inbattle) play_midi(battle,true);
			inbattle = true;
			circle ( cena, (x1+x2)/2, (y1+y2)/2, min/2, makecol( 255, 0, 0));
			fight (P1,P2);
		}
		else 
		{
			if (inbattle) play_midi(city,true);
			inbattle = false;
		}
	}
}

/****************************/

void Luta::checkdeathM (Character *P1, Monster *P2){
	if (P1->HP<=0)
	{
		if(strcmp(P1->nome,"Lance")==0)
			if (P1->habil.cooldownQ <= P1->habil.CDEQ)
				abilityQ1M(P1,P2);
		P1->MP -= P2->HP0;
		P1->MONEY = P1->MONEY/2;
		checkLVL(P1);
	}
	if (P2->HP<=0)
	{
		if(strcmp(P1->nome,"Lance")==0)
			if (P1->habil.cooldownQ <= P1->habil.CDEQ)
				abilityQ1M(P1,P2);
		P1->MP += P2->HP0;
		P1->MONEY += P2->HP0;
		checkLVL(P1);
	}
}
void Luta::ataqueM( Monster *Ataque, Character *Defesa, int power){
	int dano, bonus;
	bonus = rand() % 16;
	if (bonus == 10) {
		bonus = 50;
		textout_ex(screen, font, "Critical Hit", Defesa->GetX()+30, Defesa->GetY()-20, makecol(255,0,0), -1);
	}
	dano = ((1+0.2*(float)Ataque->LVL)*(float)Ataque->ATK/(float)Defesa->DEF)*((float)(power+bonus)/100);
	textout_ex(screen, font, itoa(dano,palavra,10), Defesa->GetX()+30, Defesa->GetY()-20, makecol(255,0,0), -1);
	Defesa->HP -= dano;
	Ataque->STA = 0;
}

void Luta::ataqueP( Character *Ataque, Monster *Defesa, int power, bool ehSPC){
	int dano, bonus, ataq;
	if (ehSPC) ataq = Ataque->SPC;
	else ataq = Ataque->ATK;
	bonus = rand() % 16;
	for (int i=0; i<4; i++)
	{
		draw_sprite(screen, Ataque->AtkAnim.animat[0][i], Defesa->GetX(), Defesa->GetY());
		rest(20);
	}
	if (bonus == 10) {
		bonus = 50;
		textout_ex(screen, font, "Critical Hit", Defesa->GetX()+10, Defesa->GetY()-30, makecol(255,0,0), -1);
	}
	play_sample(ataquesound,255,90,1000,0);
	dano = ((1+0.2*(float)Ataque->LVL)*(float)ataq/(float)Defesa->DEF)*((float)(power+bonus)/100);
	textout_ex(screen, font, itoa(dano,palavra,10), Defesa->GetX(), Defesa->GetY()-30, makecol(255,0,0), -1);
	Defesa->HP -= dano;
	Ataque->STA = 0;
}

void Luta::abilityQ2M (Character *P1, Monster*P2)
{
	play_sample(sword,255,90,1000,0);
	for (int i=0; i<4; i++)
	{
		draw_sprite(screen, P1->habil.ability[0][i], P2->GetX()-20, P2->GetY()-20);
		rest(20);
	}
	ataqueP (P1,P2,150,1);
	P1->habil.cooldownQ = 0;
}

void Luta::abilityQ1M (Character *P1, Monster *P2)
{
	if (P1->habil.cooldownQ >= P1->habil.CDQ)
	{
		play_sample(fireball,255,90,1000,0);
		for (int i=0; i<4; i++)
		{
			draw_sprite(screen, P1->habil.ability[0][i], P1->GetX()-20, P1->GetY()-20);
			rest(20);
		}
		temp1 = P1->ATK; temp2 = P1->SPD;
		P1->ATK += 0.5*P1->ATK; P1->SPD += 0.5*P1->DEF;
		ataqueP (P1,P2,100,1);
		P1->habil.cooldownQ = 0;
		P1->STA = 0;
	}
	else if (P1->habil.cooldownQ <= P1->habil.CDEQ)
	{
		P1->ATK = temp1;
		P1->SPD = temp2;
	}
}
void Luta::fightM( Character *P1, Monster *P2){

	if (P1->STA>255/P1->SPD) 
		ataqueP (P1,P2,100,0);
	else P1->STA++;

	if (P2->STA>255/P2->SPD) 
		ataqueM (P2,P1,100);
	else P2->STA++;

	if(strcmp(P1->nome,"Lance")==0)
	{
		if (P1->habil.cooldownQ >= P1->habil.CDQ)
			if( key[KEY_HOME]) 
				abilityQ1M(P1,P2);
		if (P1->habil.cooldownQ == P1->habil.CDEQ)
			abilityQ1M(P1,P2);
	}
	if (strcmp(P1->nome,"Kirito")==0)
	{
		if (P1->habil.cooldownQ >= P1->habil.CDQ)
			if( key[KEY_1]) 
				abilityQ2M(P1,P2);
	}
	checkdeathM(P1,P2);
}

void Luta::checkMCombat( Character *P1, Monster *P2, BITMAP *cena){
	float distance, x1, x2, y1, y2;
	if (P1->HP>0 && P2->HP>0)
	{
		x1 = P1->GetX(); x2 = P2->GetX();
		y1 = P1->GetY(); y2 = P2->GetY();
		distance = sqrt((float)((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
		if (distance < P1->RANGE) 
		{
			circle ( cena, (x1+x2)/2, (y1+y2)/2, P1->RANGE/2, makecol( 255, 0, 0));
			fightM (P1,P2);
		}
	}
}