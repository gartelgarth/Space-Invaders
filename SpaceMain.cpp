#include "Vaisseau.h"
#include "Laser.h"
#include "Martien.h"
#include "ExtraTerrestre.h"
#include "UIKit.h"
#include <Windows.h>
#include <conio.h>
#include "Timer.h"
using namespace std;




#define MAX_LASERS 10
#define MAX_INVADERS 5
#define nbColonnes 70
#define nbLignes 30

int main()
{
	UIKit::curseurVisible(false);

	bool finDeJeu = false;
	UIKit::setDimensionFenetre(0, 0, nbColonnes + 30, nbLignes + 10);
	UIKit::cadre(0, 0, nbColonnes, nbLignes, 50);
	UIKit::cadre(71, 0, 90, nbLignes, 200);
	UIKit::color(1);
	//	le vaisseau du joueur
	Vaisseau monVaisseau;
	Martien invader(5,6);
	Timer timerVaisseau(100);

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
				monVaisseau.modifierPosition(touche);
			}
		}
		//	on déplace le laser
		if (timerLaser.estPret())
		{
			for (int i = 0; i < MAX_LASERS; i++)
			{
				if (mesLasers[i].isAlive)
				{
					mesLasers[i].moveLaser();
				}
			}
		}	
		ExtraTerrestre * lesaliens[MAX_INVADERS];
		lesaliens[MAX_INVADERS] = new Martien(5, 5);
		lesaliens[MAX_INVADERS]->resetExtraTerrestre();
		lesaliens[MAX_INVADERS]->putExtraTerrestre();

		

	}

	return 0;
}
