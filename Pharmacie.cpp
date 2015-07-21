#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <map>
#include <list>
#include <cstdlib>
#include <ctime>

#include "Pharmacie.hpp"

using namespace std;



Pharmacie::Pharmacie(string s){
	//vérification que le fichier est valide
	ifstream input(s.c_str());
	if(input.good()) //vérifie que le fichier est valide
		parsePharma(input);
	else
		throw runtime_error("file not good");
		//retourne une exception
}


void Pharmacie::parsePharma(ifstream& in){
		string s;
		while(in.good()){ // tant que le fichier n'est pas vide
			s = '\0';
			getline(in,s,'\n');//récupère la ligne jusqu'à \n
			parseMed(s);
		}
}

void Pharmacie::parseMed(string s){
	size_t z = s.find(':');
	size_t t = 0;
	string nameMed = s.substr(0, z-1); // nom du médicament (de la position 0 dans le string à z-1, vu qu'il y a un espace avant ':')
	trim(nameMed);
	vector<string> effects;  // liste d'effets secondaires
	int i = z+2; // position du premier caractère après les ':'
	while(i < s.length()){ // boucle jusqu'à la fin de la ligne
		t = s.find(',', i);
		if( t >= s.length()){ // pas de vigule trouvée, on en est donc au dernier effet secondaire
			string tmpEffet = s.substr(i,s.length()-1-i);
			trim(tmpEffet);
			effects.push_back(tmpEffet);
			break;
		}
		else{ // il y a plusieurs effets secondaires à traiter encore
			string tmpEffet = s.substr(i, t-i);
			trim(tmpEffet);
			effects.push_back(tmpEffet);
			i = t+2;	// on fait avancer i de la taille de la chaine + l'espace et la virgule
		}
	}

	meds.insert(pair<string, vector<string> >(nameMed, effects)); //insertion de la paire représentant le médicament dans la map
}


void Pharmacie::trim(string& str){ // méthode pour ne pas repeter les espace (cf. dizziness)
  string::size_type pos = str.find_last_not_of(' ');
  if(pos != string::npos){
    str.erase(pos + 1);
    pos = str.find_first_not_of(' ');
    if(pos != string::npos) str.erase(0, pos);
  }
  else str.erase(str.begin(), str.end());
}

// retourne un vecteur de string comprenant les noms des medicaments provoquant cet effet
vector<string> Pharmacie::rechercheEffet(string effet){
   vector<string> res;

    for ( map <string, vector<string> > ::iterator i = this->meds.begin() ; i != this->meds.end() ; ++i){
       //Pour chaque element de la map <string(nom du medicament), vector<string>(vecteurs comprenant les effets du medicament)
        for ( vector<string> ::iterator j = (*i).second.begin() ; j != (*i).second.end() ; ++j){
           // On compare si l'effet est celui recherche, si oui, on l'ajoute a notre vecteur de resultat
           if((*j).compare(effet) == 0) res.push_back((*i).first);
        }
    }
    return res;
}

//fonction de vérification de présence d'un élément dans une liste
bool Pharmacie::est_present(list<string> liste, string nom){
    for(list<string> :: iterator it = liste.begin(); it != liste.end(); ++it){
        if( (*it).compare(nom) == 0) return true;
    }
    return false;
}

/**
bool est_present_score(map<string,int > la_map, string nom){
    if(la_map.find(nom) != la_map.end()) return true;
    return false;
}
*/

void afficherPlusCommuns(list<string> la_liste, int nb){
    while(nb != 0){
        cout << la_liste.front() << endl;
        la_liste.pop_front();
        --nb;
    }
}


map <string, double> Pharmacie::statMedParEffets (vector<string> effets){
    map <string, double> res;
    for ( map <string, vector<string> > ::iterator i = this->meds.begin() ; i != this->meds.end() ; ++i){
        res.insert(pair<string, double> ((*i).first, 0));
        for ( vector<string> ::iterator j = (*i).second.begin() ; j != (*i).second.end() ; ++j){
            //On compare si les effets de ce medicament contiennent des effets recherches
            for(vector<string> ::iterator k = effets.begin(); k != effets.end(); ++k){
               // On compare si l'effet est celui recherche, si oui, on l'ajoute au vecteur de resultat
               if((*j).compare((*k)) == 0){
                   //On incremente le nombre d'effets communs
                   res[(*i).first]++;
               }
           }
        }
    }
    return res;
}

map <string, double> Pharmacie::precisionMed (vector<string> effets){
  map <string, double> res = statMedParEffets(effets);
  int nombreEffets = effets.size();
  for ( map <string, double > ::iterator i = res.begin() ; i != res.end() ; ++i){
      (*i).second = ((*i).second / nombreEffets) * 100;
    }
  return res;
}


//Fonction de recherche d'un medicament par effets
list<string> Pharmacie::rechercheCommun(vector<string> effets, int nb){
  map <string, double> res = statMedParEffets(effets);
	int max = 0;
	list<string> listeRes;
	string nom_max;
	for(map <string,double> :: iterator z = res.begin(); z != res.end(); ++z){
        if( res[(*z).first] >= max && !est_present(listeRes, (*z).first)){
            max = res[(*z).first];
            listeRes.push_front((*z).first);
        }
	}
	afficherPlusCommuns(listeRes, nb);
	return listeRes;
}

pair<string, string> Pharmacie::rechercheCommun2Premiers(vector<string> effets){
    map <string, double> res = statMedParEffets(effets);
    map<string, double> :: iterator it_res = res.begin();
    string res1 = (*it_res).first;
    it_res++;
    string res2 = (*it_res).first;
    return pair<string, string>(res1, res2);
}

bool Pharmacie::medicamentExiste(string nomMed){
  map<string, vector<string> >::iterator trouve=meds.find(nomMed);
  if(trouve != meds.end()){
     return true;
  }
  return false;
}

void Pharmacie::ajouterMedicament (string nomMed, vector<string> vectEffets){
    meds.insert(pair<string, vector<string> >(nomMed, vectEffets));
}

string Pharmacie::rechercheCommunRandom(vector<string> effets){
    map <string, int> res;
    string effRand;
    std::srand(std::time(0));
    for ( map <string, vector<string> > ::iterator i = this->meds.begin() ; i != this->meds.end() ; advance(i, rand()% this->meds.size() +1 )){
        res.insert(pair<string, int> ((*i).first, 0));
        for ( vector<string> ::iterator j = (*i).second.begin() ; j != (*i).second.end() ; ++j){
            //On compare si les effets de ce medicament contiennent des effets recherches
            for(vector<string> ::iterator k = effets.begin(); k != effets.end(); ++k){
               // On compare si l'effet est celui recherche, si oui, on l'ajoute a notre vecteur de resultat
               if((*j).compare((*k)) == 0){
                   effRand=i->first;
               }
           }
        }
    }
    return effRand;
}
