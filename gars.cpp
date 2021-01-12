#include <cstdlib>
#include <iostream>
#include <ncurses.h>
#include <ctime>

#include "File.hpp"
#include "Client.hpp"
#include "Etablissement.hpp"
#include "Poste.hpp"
#include "Guichet.hpp"

#define dureeOuverture 8*60*60 // Secondes
#define MAX_ACCELERATION 4096 // Accéleration maximale de la simulation
#define MIN_ACCELERATION 1 // Accélération minimale de la simulation


using namespace std;

int main(int argc, char* argv[]) {
	int temps = 0;
	char yes_or_no;
	bool library_ncurses = false;
	int NbGuichet = 1;
	int frequentation = 50; // Taux de fréquentation par heure
	int Acceleration = 1; // Accélération de la simulation

	// Utiles pour la fréquence de traitement
	int horloge = 0;
	int horloge_1 = -1;
	// Utile pour la fréquence d'affichage
	int temps_affichage = 0;
	// Représente une touche du clavier (Bibliothèque Ncurses)
	int ch;

	if (argc == 2) {
		Acceleration = atoi(argv[1]);
	}
	else if (argc == 3) {
		Acceleration = atoi(argv[1]);
		frequentation = atoi(argv[2]);
	}

	cout << "Nombre de guichets : ";
	cin >> NbGuichet;
	cout << endl;

	// Détermination de l'utilisation de la bibliothèque ncurses
	while (yes_or_no != 'Y' && yes_or_no != 'N' && yes_or_no != 'y' && yes_or_no != 'n'){
		cout << "Utilisation de la bibliothèque NCurses ? (Y:Oui, N:Non) : ";
		cin >> yes_or_no;
		cout << endl;
		if (yes_or_no != 'Y' && yes_or_no != 'N' && yes_or_no != 'y' && yes_or_no != 'n') cout << "Réponse non valide" << endl;
		else if (yes_or_no == 'Y' || yes_or_no == 'y') library_ncurses = true;
		else if (yes_or_no == 'N' || yes_or_no == 'n') library_ncurses = false;
	}	

	if (library_ncurses){
		initscr();
		keypad(stdscr, TRUE);	
		mvprintw(LINES/2, COLS/2 - 13/2, "ON COMMENCE ?");
		ch = getch();
		timeout(0);
	}

	Etablissement *poste = new Poste (dureeOuverture, NbGuichet, frequentation);
	Client client;

	while(poste->getBoolOuverture(temps) && ch != 'q') {
		horloge = Acceleration*clock()/CLOCKS_PER_SEC;
		if (library_ncurses) {
			refresh();
			ch = getch();
			if (ch == KEY_UP && Acceleration <= MAX_ACCELERATION) {
				Acceleration *= 2;
				temps_affichage=temps;
			}
			else if (ch == KEY_DOWN && Acceleration > MIN_ACCELERATION) {
				Acceleration /= 2;
				temps_affichage=temps;
			}
		}

		if(horloge_1 != horloge) {	
			horloge_1 = horloge;
			temps++;
			int numeroGuichet = -1;
			string s_arrivee="";

			if (poste->entreeClient(temps)) {
				//On sauvegarde l'affichage du client qui entre, on l'affichera à la fin avec les autres guichets
				s_arrivee = poste->choixGuichet(client, temps);
				numeroGuichet = poste->setClientToGuichet(client);
			}
			
			//Cette condition permet d'effectuer un affichage independemment de la fréquence de traitement du programme
			//Cela permet de limiter l'effet de clignottement avec la bibliothèque ncurses
			if (temps-temps_affichage == 1+Acceleration/20 || !poste->getBoolOuverture(temps) || !library_ncurses) {
				if (library_ncurses) {
					temps_affichage = temps;
					clear();
				}
				else cout << "---------- " << temps/3600 << "h : " << temps/60-(temps/3600)*60 << "m : " << temps%60 << "s" << " ----------" << endl;

				for (int k = 0; k < NbGuichet; k++) {
					//On vérifie l'état de chaque guichet
					//et de leur file d'attente
					string s_sortie = poste->etatGuichet(temps, k);

					//Enfin, on affiche les vecteurs 
					if (library_ncurses) {
						if (k != numeroGuichet) mvprintw(0+k, 0, (poste->getGuichet(k).toString() + s_sortie).c_str());
						else mvprintw(0+k, 0, (s_arrivee + s_sortie).c_str());
					}
					else {
						if (k != numeroGuichet) cout << poste->getGuichet(k) << s_sortie << endl;
						else cout << s_arrivee << s_sortie << endl;
					}
				}

				// Menu encadré qui permet à l'utilisateur de réaliser certaines actions pendant la simulation
				if (library_ncurses) {
					int colonne = COLS/1.9;
					int ligne = LINES/5; 
					string str_temps = to_string(temps/3600) + "h : " + to_string(temps/60-(temps/3600)*60) + "m : " + to_string(temps%60) + "s";
					attron(A_BOLD);
					mvprintw(ligne-3, colonne+24, str_temps.c_str());
					attroff(A_BOLD);
					mvprintw(ligne-2, colonne, ("Accélération : x" + to_string(Acceleration)).c_str());
					mvprintw(ligne, colonne, "Appuyer sur \"Flèche du haut\" pour accélérer le temps"); 
					mvprintw(ligne+1, colonne, "Appuyer sur \"Flèche du bas\" pour décélérer le temps");
					mvprintw(ligne+2, colonne, "Appuyer sur \"q\" pour quitter");
					WINDOW *boite = subwin(stdscr, 10, 65, ligne-5, colonne-3);
    				wborder(boite, '|', '|', '-', '-', '+', '+', '+', '+');
    				wrefresh(boite);
				}
			}
			//Si on effectue pas d'affichage à ce front d'horloge, on continue tout de même le traitement des clients
			else {
				for (int k = 0; k < NbGuichet; k++) {
					//On vérifie l'état de chaque guichet
					//et de leur file d'attente
					string s_sortie = poste->etatGuichet(temps, k);
				}
			}	
		}
	}

	if (library_ncurses) {
		attron(A_BOLD);
		mvprintw(LINES/2, COLS/2 - 19/2, "Simulation terminée");
		timeout(-1);
		getch();

		endwin();
	}

	//On calcul le ratio d'impatience de la journée (3 guichets permet de descendre en dessous de 5%)
	double ratioImpatience = poste->ratioImpatience();
	cout << "Ratio d'impatients sortants: " << ratioImpatience << " %" << endl;

	return EXIT_SUCCESS;
}
