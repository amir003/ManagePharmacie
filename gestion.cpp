#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <map>
#include <list>
#include <limits>

#include "Pharmacie.hpp"

using namespace std;


void Pharmacie::afficheHisto(){
	map<string, vector<string> >::iterator it; 
	list<string> eff;
	cout <<"Affichage de l'histogramme : \n"<<endl;
	for (it = this->meds.begin(); it!= this->meds.end(); ++it){
		for( vector<string> :: iterator j = it->second.begin(); j != it->second.end(); ++j){
            if(!est_present(eff, *j)){
                eff.push_back((*j));
            }
		}
	}
    for(list<string> :: iterator it2 = eff.begin(); it2 != eff.end(); ++it2)
    {
        cout << (*it2) << " : ";
        for(int h = 0; h < 50 - (*it2).size(); h++){
        	cout <<" ";
        }
        for(int i = 0; i < rechercheEffet((*it2)).size(); ++i)
        {
            cout << "*";
        }
        cout << endl;
    }
}

void Pharmacie::afficherMap(){
    for ( map <string, vector<string> > ::iterator i = this->meds.begin() ; i != this->meds.end() ; ++i)
	{
	    cout << "Medicament : " << i->first << endl;
	    cout << "Effet(s) secondaire(s) : ";
        for( vector<string> :: iterator j = i->second.begin(); j != i->second.end(); ++j){
            cout << (*j) << " ";
        }
        cout << endl;
	}
}

void Pharmacie::rechercheChoice(){
	cout << "Veuillez entrer un nom d'effet secondaire recherche : ";
	string effet;
	//On demande à l'utilisateur l'effet demandé
	cin >> effet;
    //On remplit le vecteur resultat en appellant la recherche
	vector<string> res = rechercheEffet(effet);
	cout << "Medicaments trouves : "<< endl;

	//On parcourt le vecteur de résultat et on affiche le nom des médicaments trouvés
	for(vector<string>::iterator i = res.begin(); i != res.end(); ++i){
        cout << (*i) << endl;
    }
}

void Pharmacie::compareChoice(){
    vector<string> effets;
    int nbEf;
    string nomEf;
    cout <<"Combien d'effets voulez-vous comparer ?"<<endl;
    cin >> nbEf;
    for (int i=0; i<nbEf; i++){
	    cout <<"Entrez l'effet "<<i+1<<endl;
	    cin >> nomEf;
	    effets.push_back(nomEf);
	}
    cout << "Medicament ayant le plus d'effets communs avec ces effets secondaires  : " << endl;
    list<string> plusCommuns = rechercheCommun(effets, nbEf+1);
}

void Pharmacie::DeuxPremiersChoice(){
    vector<string> effets;
    int nb;
    string nom;
    cout <<"Combien d'effets voulez-vous entrer ?"<<endl;
    cin >> nb;
    for (int i=0; i<nb; i++){
	    cout <<"Entrez l'effet "<<i+1<<endl;
	    cin >> nom;
	    effets.push_back(nom);
	}
    cout << "Deux premiers médicaments ayant au moins un de ces effets : " << endl;
    pair<string, string> res = rechercheCommun2Premiers(effets);
    cout << res.first << " " << res.second << endl;
}

void Pharmacie::RandomChoice(){
    vector<string> effets;
    int nb;
    string nom;
    cout <<"Combien d'effets voulez-vous entrer ?"<<endl;
    cin >> nb;
    for (int i=0; i<nb; i++){
	    cout <<"Entrez l'effet "<<i+1<<endl;
	    cin >> nom;
	    effets.push_back(nom);
	}
    cout << "Deux premiers médicaments ayant au moins un de ces effets : " << endl;
    string res = rechercheCommunRandom(effets);
    cout << res << endl;
}

void Pharmacie::AjouteMed(){
	int nbrMed;
	cout <<"Combien de médicaments voulez-vous ajouter ?"<<endl;
	cin >> nbrMed;

	for(int i=0; i<nbrMed; i++){
		cout << "Veuillez entrer le nom du médicament "<<i+1<<" : ";
			string nomMed;
			cin >> nomMed;
		if (medicamentExiste(nomMed)){
			 cout << "Le médicament " << nomMed << " existe déjà dans la base de données" << endl;
		}else{
			cout << "Veuillez entrer le 1er effet du médicament : " << endl;
			string effet;
			cin >> effet;
			vector<string> vecEffets;
			int count = 2;
			while (effet.compare("exit") != 0){
				cout << "Veuillez entrer le " << count <<"ème effets de ce médicament ou sinon tappez exit : " << endl;
				vecEffets.push_back(effet);
				cin >> effet;
				count++;
			}		
			ajouterMedicament(nomMed, vecEffets);
		}
	}
}

void Pharmacie::afficherPrecisionMed (map <string, double> medPresision){
   cout << "Précision de l'algorithme de recherche :" << endl;
   for ( map <string, double > ::iterator i = medPresision.begin() ; i != medPresision.end() ; ++i){
       cout << (*i).first << " : " << (*i).second << endl;
    }
}

void Pharmacie::PrecisionAlgo(){
	cout << "Veuillez entrer le 1er effet du médicament : " << endl;
	string effet;
	cin >> effet;
	vector<string> vecEffets;
	int count = 2;
	while (effet.compare("exit") != 0){
		cout << "Veuillez entrer le " << count <<"ème effets de ce médicament ou sinon tappez exit : " << endl;
		vecEffets.push_back(effet);
		cin >> effet;
		count++;
	}		
	map <string, double> res = precisionMed(vecEffets);
	afficherPrecisionMed(res);
}

void Pharmacie::afficherMenu(){
	int choice;
	bool prog=true;
	while(prog != false){
		cout<<"\n---Bienvenue dans la gestion d'une Pharmacie---\n\n";
		cout<<"Que voulez-vous faire ? \n";
		cout << " 1 - Afficher l'histogramme des effets secondaires \n"
		<< " 2 - Visualisation des médicaments (et leurs effets secondaires)\n"
		<< " 3 - Rechercher un médicament en entrant un effet secondaire\n"
		<< " 4 - Calcul de la précision\n"
		<< " 5 - Trouver les medicaments ayant le plus d'effets en commun\n"
		<< " 6 - Trouver les 2 premiers médicaments ayant des effets en commun \n"
		<< " 7 - Recherche aléatoire de médicaments\n"
		<< " 8 - Ajouter un médicament (option)\n"
		<< " 9 - Quitter.\n"
		<< " Entrer votre choix ";
		if (!(cin >> choice)){
          cerr << "\nMerci d'entrer un entier valide" << endl;
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else{
			switch (choice){
			case 1:
			afficheHisto();
			break;
			case 2:
			afficherMap();
			break;
			case 3:
			rechercheChoice();
			break;
			case 4:
			PrecisionAlgo();
			break;
			case 5:
			compareChoice();
			break;
			case 6:
			DeuxPremiersChoice();
			break;
			case 7:
            RandomChoice();
            break;
            case 8:
            AjouteMed();
            break;
			case 9:
			cout <<"\nMerci d'avoir utiliser ManagePharmacie.\n";
			cout << "Fin du programme.\n";
			prog=false;
			break;
			default:
			cout << "Choix non valide. \n"
			<< "Choisir à nouveau.\n";
			break;
			}
		}
	}

}
