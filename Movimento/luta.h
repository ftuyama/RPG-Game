#ifndef LUTA_H
#define LUTA_H

#include <allegro.h>
#include "Character.h"
#include "Monster.h"

class Luta
{

public:
	int temp1, temp2;
	char palavra[50];
	bool PvP, inbattle;
	MIDI *boss, *battle, *city;
	SAMPLE *fireball, *sword, *ataquesound, *kill;

	Luta();
	~Luta();

	void checkLVL (Character *P);
	void checkdeath (Character *P1, Character *P2);
	void ataque( Character *Ataque, Character *Defesa, int power, bool ehSPC);
	void abilityQ2 (Character *P1, Character *P2);
	void abilityQ1 (Character *P1, Character *P2);
	void fight( Character *P1, Character *P2);
	void checkCombat( Character *P1, Character *P2, BITMAP *cena);

	void checkdeathM (Character *P1, Monster *P2);
	void ataqueM( Monster *Ataque, Character *Defesa, int power);
	void ataqueP( Character *Ataque, Monster *Defesa, int power, bool ehSPC);
	void abilityQ2M (Character *P1, Monster*P2);
	void abilityQ1M (Character *P1, Monster *P2);
	void fightM( Character *P1, Monster *P2);
	void checkMCombat( Character *P1, Monster *P2, BITMAP *cena);

};

#endif