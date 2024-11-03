#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

struct Candidat {
    int id;
    std::string nom;
    int votes = 0;
    bool elu = false;
};

struct Electeur {
    std::vector<int> preferences; // Liste d'IDs de candidats classés par ordre de préférence
};

int main() {
    // Initialisation des candidats
    std::vector<Candidat> candidats = {
        {1, "Alice"},
        {2, "Bob"},
        {3, "Charlie"}
    };

    // Initialisation des électeurs et de leurs préférences
    std::vector<Electeur> electeurs = {
        {{1, 2, 3}},
        {{2, 1, 3}},
        {{2, 3, 1}},
        {{3, 1, 3}},
        {{1, 3, 2}},
        {{1, 2, 3}}
    };

    // Calcul du seuil pour être élu (majorité simple)
    int seuil = electeurs.size() / 2 + 1;
    std::cout << seuil << std::endl;

    while (true) {
        // Réinitialisation des votes
        for (auto &candidat : candidats) {
            candidat.votes = 0;
        }

        // Attribution des votes selon les préférences des électeurs
        for (const auto &electeur : electeurs) {
            for (int pref : electeur.preferences) {
                auto it = std::find_if(candidats.begin(), candidats.end(), [pref](const Candidat &c) {
                    return c.id == pref && !c.elu;
                });
                if (it != candidats.end()) {
                    it->votes++;
                    break;
                }
            }
        }

        // Vérification si un candidat dépasse le seuil
        bool elu = false;
        for (auto &candidat : candidats) {
            if (candidat.votes >= seuil) {
                candidat.elu = true;
                std::cout << "Le candidat " << candidat.nom << " est élu avec " << candidat.votes << " votes !" << std::endl;
                elu = true;
                break;
            }
        }

        if (elu) break;

        // Si personne n'est élu, éliminer le candidat avec le moins de votes
        auto it_min = std::min_element(candidats.begin(), candidats.end(), [](const Candidat &a, const Candidat &b) {
            return (!a.elu && (b.elu || a.votes < b.votes));
        });

        if (it_min != candidats.end()) {
            std::cout << "Le candidat " << it_min->nom << " est éliminé avec " << it_min->votes << " votes." << std::endl;
            it_min->elu = true;
        } else {
            std::cout << "Aucun candidat restant n'a été élu." << std::endl;
            break;
        }
    }

    return 0;
}
