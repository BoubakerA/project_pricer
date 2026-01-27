#include <iostream>
// I/O standard pour afficher les résultats dans le terminal (std::cout).

#include "include/types.hpp"
#include "include/european_option.hpp"
#include "include/asian_option.hpp"
#include "include/barrier_option.hpp"
#include "include/digital_option.hpp"
#include "include/black_and_scholes_pricer.hpp"
#include "include/monte_carlo_pricer.hpp"
// Inclusion des types (enums), des différentes options, et des pricers
// (Black–Scholes fermé + Monte-Carlo).

int main() {

    // -------------------------------
    // Paramètres de marché / modèle
    // -------------------------------
    double spot = 100.0;        // spot        : prix initial du sous-jacent S0
    double strike = 100.0;      // strike      : strike K
    double rate = 0.05;         // rate        : taux sans risque r
    double volatility = 0.2;    // volatility  : volatilité sigma (constante ici)
    double maturity = 1.0;      // maturity    : maturité T (en années)

    // -------------------------------
    // Paramètres produits exotiques
    // -------------------------------
    double cashPayoff = 1.0;    // cashPayoff : montant versé par l'option digitale si elle est "in the money"
    double barrier = 130.0;  // barrier    : niveau de barrière B
    bool isUpAndOut = true;     // isUpAndOut : true => Up-and-Out, false => Down-and-Out

    // -------------------------------
    // Paramètres Monte-Carlo
    // -------------------------------
    int num_sims = 100000;   // num_sims  : nombre de simulations Monte-Carlo
    int num_steps_ = 100;    // num_steps_: nombre de pas de temps pour les options path-dependent (Asian, Barrier)

    // -------------------------------
    // Construction des produits
    // -------------------------------
    // Option européenne (vanilla) : payoff dépend uniquement de S_T || Call : max(S_T - K, 0)
    EuropeanOption europeanCall(
        OptionType::Call,
        spot, strike, rate, volatility, maturity
    );

    // Option asiatique : payoff dépend de la moyenne du chemin ||Call : max(average(S_t) - K, 0)
    AsianOption asianCall(
        OptionType::Call,
        spot, strike, rate, volatility, maturity
    );

    // Option barrière (knock-out dans ton code) : payoff dépend du chemin
    // - si la barrière est touchée => payoff = 0
    // - sinon => payoff vanilla à maturité
    BarrierOption barrierCall(
        OptionType::Call,
        spot, strike, rate, volatility, maturity, barrier, isUpAndOut
    );

    // Option digitale (cash-or-nothing) : payoff binaire dépend uniquement de S_T
    // Call digitale : cashPayoff si S_T > K, sinon 0
    DigitalOption digitalCall(
        OptionType::Call,
        spot, strike, rate, volatility, maturity, cashPayoff
    );

    // -------------------------------
    // Construction des pricers
    // -------------------------------
    // => pricer Monte-Carlo avec uniquement des simulations terminales (S_T) ou 1 pas
    // (adapté aux options qui dépendent seulement de S_T : European/Digital).
    MonteCarloPricer mc_without_path(num_sims);

    // => pricer Monte-Carlo qui simule un chemin complet de num_steps_ pas
    // (adapté aux options path-dependent : Asian/Barrier).
    MonteCarloPricer mc_with_path(num_sims, num_steps_);

    // Pricer Black–Scholes fermé : formule explicite pour options européennes
    BlackAndScholesPricer bs;

    // -------------------------------
    // Affichage des prix
    // -------------------------------
    // Prix Black–Scholes pour l'option européenne (référence "exacte" du modèle)
    std::cout << "BS Price: " << bs.price(europeanCall) << "\n";

    // Prix Monte-Carlo pour l'option européenne :
    // devrait converger vers le prix BS quand num_sims augmente.
    std::cout << "MC Price: " << mc_without_path.price(europeanCall) << "\n";

    // Prix Monte-Carlo de l'option asiatique :
    // nécessite un chemin complet => usage de mc_with_path.
    std::cout << "Asian MC Price: " << mc_with_path.price(asianCall) << "\n";

    // Prix Monte-Carlo de l'option barrière :
    // nécessite un chemin complet => usage de mc_with_path.
    std::cout << "Barrier MC Price: " << mc_with_path.price(barrierCall) << "\n";

    // Prix Monte-Carlo de l'option digitale :
    // dépend seulement de S_T => usage de mc_without_path.
    std::cout << "Digital MC Price: " << mc_without_path.price(digitalCall) << "\n";

    // Pas de "return 0;" explicite : en C++ (depuis C++11), main() retourne 0 implicitement
    // si on atteint la fin de la fonction.
}