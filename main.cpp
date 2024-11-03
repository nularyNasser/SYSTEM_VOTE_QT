#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Candidat
{
    int id;
    string name;
    int nombre_voix = 0;
    bool is_elu = false;
    bool is_eliminated = false;

    // Constructeur
    Candidat(int id, string name) : id(id), name(name) {}
};

struct Electeur{
    vector <int> liste_vote;

    // Constructeur
    Electeur(vector <int> liste_vote) : liste_vote(liste_vote) {}
};


// Fonction findCandidat pour attribuer les points
int findCandidat(const vector <Candidat>& candidats, int id){
    for (size_t i = 0; i < candidats.size(); i += 1){
        if (candidats[i].id == id && !candidats[i].is_elu){
            return i;
        }
    }
    return -1;
} // findCandidat()


// Fonction indexMinVote pour connaitre celui qui à le moins de voix;
int indexMinVote(const vector <Candidat>& candidats){
    int imin = 0;
    for (size_t i = 1; i < candidats.size(); i += 1){
        if (candidats[i].nombre_voix < candidats[imin].nombre_voix){
            imin = i;
        }
    }

    return imin;
}


int main()
{
    // Création de la liste des candidats (4 candidats)
    vector <Candidat> candidats = {
        {1, "Choco"},
        {2, "Banane"},
        {3, "Mangue"},
        {4, "Fraise"}
    };

    // Création de la liste des votes des électeurs (6 électeurs)
    vector <Electeur> electeurs = {
        {{3, 1, 4, 2}},
        {{3, 4, 1, 2}},
        {{2, 1, 3, 4}},
        {{4, 2, 1, 3}},
        {{1, 3, 4, 2}},
        {{2, 3, 1, 4}}
    };


    // Calcule du quota
    int quota = electeurs.size() / 2 + 1;

    while (true){

        // Nombre de voix de premier choix
        for (size_t i = 0; i < electeurs.size(); i += 1){
            for (size_t j = 0; j < electeurs[i].liste_vote.size(); j += 1){
                int index_to_attribute_point = findCandidat(candidats, electeurs[i].liste_vote[j]);
                if (index_to_attribute_point != -1){
                    candidats[index_to_attribute_point].nombre_voix += 1;
                    break;
                }
            }
        }

        // Vérification si un candidat dépasse le quota
        bool someone_elected = false;
        for (size_t i = 0; i < candidats.size(); i += 1){
            if (candidats[i].nombre_voix >= quota){
                candidats[i].is_elu = true;
                someone_elected = true;
                cout << candidats[i].name << " gagne avec " << candidats[i].nombre_voix << " voix !" << endl;
                break;
            }
        }

        if (someone_elected) break;

        // Si personne n'à atteint le quota on élimine celui avec le moint de voix
        int idLoserIndex = indexMinVote(candidats);
        candidats[idLoserIndex].is_eliminated = true;

        // Redistribution des voix du candidat éliminé
        int idLoser = candidats[idLoserIndex].id;

        for (Electeur& electeur : electeurs){
            auto iterator = find(electeur.liste_vote.begin(), electeur.liste_vote.end(), idLoser);
            if (iterator != electeur.liste_vote.end()){
                electeur.liste_vote.erase(iterator); // On supprime le candidat éliminé de tout les bulletin
            }
        }
    }

    return 0;
}
