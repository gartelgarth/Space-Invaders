#include "Coord.h"
#include "ExtraTerrestre.h"
#include"Laser.h"
#include"Martien.h"
#include"Vaisseau.h"
#include<iostream>
#include "UIKit.h"
#include <Windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

class Timer {
private:
	long timer;
	long delai;

public:
	Timer(long delai) {
		this->delai = delai;
	}

	void start() {
		this->timer = clock();
	}

	bool estPret() {
		bool pret = false;

		if (clock() >= timer + delai) {
			pret = true;
			timer = clock();
		}

		return pret;
	}
};

#define MAX_LASERS 5
#define MAX_INVADERS 5
#define nbColonnes 70
#define nbLignes 30

int main()
{
	Martien * lesaliens[MAX_INVADERS];

	for (int i = 0; i < MAX_INVADERS; i++) {
		lesaliens[i] = new Martien((int)'x', 5);
		lesaliens[i]->resetExtraTerrestre();
	}

	UIKit::curseurVisible(false);

	bool finDeJeu = false;
	UIKit::setDimensionFenetre(0, 0, nbColonnes + 30, nbLignes + 10);
	UIKit::cadre(0, 0, nbColonnes, nbLignes, 50);
	UIKit::cadre(71, 0, 90, nbLignes, 200);
	UIKit::color(0004);
	//	le vaisseau du joueur
	Vaisseau monVaisseau;
	Martien invader(5, 6);
	Timer timerVaisseau(100);
	Timer timerJiggle(400);

	//	un laser (pas à l'écran au début)
	Laser mesLasers[MAX_LASERS];
	for (int i = 0; i < MAX_LASERS; i++)
		mesLasers[i].isAlive = false;
	Timer timerLaser(70);

	//	boucle principale de jeu
	while (!finDeJeu) {
		//	gestion du clavier
		if (_kbhit() && timerVaisseau.estPret()) {
			char touche = _getch();

			if (touche == ' ') {
				//	on recherche un laser libre
				int i = 0;
				while (i < MAX_LASERS && mesLasers[i].isAlive)
					i++;

				if (i < MAX_LASERS) {
					mesLasers[i].startLaser(monVaisseau.coord.getPositionX());
				}
			}
			else {
				Coord vaisseauCoord = monVaisseau.coord;
				if (touche == 'k' && vaisseauCoord.getPositionX() > 1
					|| touche == 'l' && vaisseauCoord.getPositionX() < 69) {
					monVaisseau.modifierPosition(touche);
				}
			}
		}
		//	on déplace le laser
		if (timerLaser.estPret())
		{
			for (int i = 0; i < MAX_LASERS; i++)
			{
				if (mesLasers[i].coord.getPositionY() == 1)
				{
					mesLasers[i].killLaser();
				}
				if (mesLasers[i].isAlive)
				{
					mesLasers[i].moveLaser();
				}
			}
		}
		if (timerJiggle.estPret()) {
			for (int i = 0; i < MAX_INVADERS; i++) {
				if (lesaliens[i]->isAlive) {
					lesaliens[i]->jiggleMartien();
				}
			}
		}

		for (int i = 0; i < MAX_LASERS; i++) {
			if (mesLasers[i].isAlive) {
				Coord laserCoord = mesLasers[i].coord;
				for (int j = 0; j < MAX_INVADERS; j++) {
					if (lesaliens[j]->isAlive) {
						Coord alienCoord = lesaliens[j]->coord;
						if (laserCoord.getPositionX() == alienCoord.getPositionX() && laserCoord.getPositionY() == alienCoord.getPositionY()) {
							lesaliens[j]->isAlive = false;
							mesLasers[i].killLaser();
						}
					}
				}
			}
		}
	}

	return 0;
}