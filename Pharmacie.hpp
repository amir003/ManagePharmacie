#ifndef __PHARMACIE_HPP
#define __PHARMACIE_HPP

#include <cassert>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <map>
#include <list>
#include <vector>
#include <string>

using namespace std;

class Pharmacie{
	private:
		map<string, vector<string> > meds;
        vector<string> vecEffets;

	public:
		Pharmacie(string);
		void parsePharma(ifstream&); // parse le fichier d'entrée
		void parseMed(string); // parse un médicament
		void afficheHisto();// affiche la liste des médicaments
		void trim(string&);// supprime les espaces 
		void afficherMap();// affiche la map
		vector<string> rechercheEffet(string); //renvoie les médicaments comportant un effet précisé en paramètre
		list<string> rechercheCommun(vector<string>, int);// renvoie les X médicaments ayant le plus d'effets communs avec ceux passés en paramètre
		void rechercheChoice();// lance rechercheEffet
        void compareChoice();// lance rechercheCommun
		void DeuxPremiersChoice();// lance rechercheCommun2premiers
		void RandomChoice();// lance la rechercheCommunRandom
		void afficherMenu();// affiche le menu
		bool est_present(list<string> liste, string nom);// vérifie la présence d'un string dans une liste de string
		pair<string, string> rechercheCommun2Premiers(vector<string>);//renvoi 2 premiers médicaments de la map
		string rechercheCommunRandom(vector<string> effets);//retourne premier medicament trouve ayant effet recherche
		void ajouterMedicament (string , vector<string> );//ajout couple medicament/effet
		void AjouteMed();// lance ajouterMedicament
		bool medicamentExiste(string);//vérifie la présence d'un médicament dans la map
		map <string, double> precisionMed (vector<string> );//retourne map contenant pourcentage d effets trouve
		map <string, double> statMedParEffets (vector<string> );//stocke effets et frequence dans une map
		void afficherPrecisionMed (map <string, double> );//affiche resultat de la precicion
		void PrecisionAlgo();//affiche resultat de la precision

};

#endif
