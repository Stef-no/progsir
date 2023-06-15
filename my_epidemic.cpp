#include "my_epidemic.hpp"
#include "my_date.hpp"
#include "my_control_print.hpp"

#include <iomanip>
#include <iostream>
#include <limits>

int main() {
  /*int Pop_, Inf_, Dead_, Heal_, Duration_, ImmDur_, PanStart_, VaxStart_,
      VaxMax_, NewSusc_;
  double Beta_, Gamma_, DeadIndex_, VaxIndex_;  // so che Giacomini non apprezza
  char Previous_;

  Pop_ = 1010;
  Inf_ = 10;
  Dead_ = 0;
  Heal_ = 0;
  Beta_ = 0.3;
  Gamma_ = 0.05;
  DeadIndex_ = 0.5;
  Duration_ = 10;
  ImmDur_ = 1;  // tempo di guarigione
  PanStart_ = 0;
  VaxStart_ = 1;    // quando iniziano i vaccini
  Previous_ = 'n';  // pandemia già in corso?
  VaxIndex_ = 0.3;
  VaxMax_ = 1;
  NewSusc_ = 0;
  char View_ = 'y';*/

  std::cout << "Nell'inserimento dei dati della pandemia si richiede di "
               "seguire le seguenti indicazioni: \n";
  std::cout << "- i dati temporali e riguardanti la popolazione sono numeri "
               "interi e positivi; \n";
  std::cout << "- gli indici sono numeri decimali compresi tra 0 e 1 (estremi "
               "inclusi). \n";

  std::cout << "Inserire \n";

  // if (!std::cin) {
  //   std::cin.clear();
  //   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  // }

  int Pop_;
  while (true) {
    std::cout << "Population: \n";
    if (std::cin >> Pop_) {
      while(Pop_ <= 0) {
        std::cout << "Population has to be > 0 \n";
        std::cin >> Pop_;
      }
      break;
    } else {
      std::cout << "Invalid input. \n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  int Inf_;
  std::cout << "Popolazione infetta:\t";
  std::cin >> Inf_;
  while (Inf_ < 0 || Inf_ > Pop_) {
    std::cout << " Inf's value has to be between 0 and Pop's value.\n ";
    std::cin >> Inf_;
  }

  double Beta_;
  std::cout << "Indice di contagiosità:\t";
  std::cin >> Beta_;
  while (Beta_ < 0 || Beta_ > 1) {
    std::cout << " Beta's value has to be between 0 and 1.\n ";
    std::cin >> Beta_;
  }

  char bVar_;
  std::cout << "Beta varia?\t";
  std::cin >> bVar_;
  while (bVar_ != 'N' && bVar_ != 'Y' && bVar_ != 'n' && bVar_ != 'y') {
    std::cout << " Beta variation has to be Y/n.\n ";
    std::cin >> bVar_;
  }

  int bVarTime_ = 0;
  int bVarStart_ = 0;

  if (bVar_ == 'Y' || bVar_ == 'y') {
    std::cout << "Giorno di inizio della diminuzione di beta:\t";
    std::cin >> bVarStart_;
    while (bVarStart_ < 0) {
      std::cout << " bVarStart has to be > than 0.\n ";
      std::cin >> bVarStart_;
    }

    std::cout << "Quando vale il tempo di dimezzamento dell'indice di "
                 "contagione? \t";
    std::cin >> bVarTime_;
    while (bVarTime_ < 0) {
      std::cout << "bVarTime has to be > 0.\n ";
      std::cin >> bVarTime_;
    }
  }

  double Gamma_;
  std::cout << "Indice di rimozione:\t";
  std::cin >> Gamma_;
  while (Gamma_ < 0 || Gamma_ > 1) {
    std::cout << " Gamma's value has to be between 0 and 1.\n ";
    std::cin >> Gamma_;
  }

  char gVar_;
  std::cout << "Gamma varia?\t";
  std::cin >> gVar_;
  while (gVar_ != 'N' && gVar_ != 'Y' && gVar_ != 'n' && gVar_ != 'y') {
    std::cout << " Gamma variation has to be Y/n.\n ";
    std::cin >> gVar_;
  }

  int gVarStart_ = 0;
  int gVarTime_ = 0;

  if (gVar_ == 'Y' || gVar_ == 'y') {
    std::cout << "Giorno di inizio della variazione di gamma:\t";
    std::cin >> gVarStart_;
    while (gVarStart_ < 0) {
      std::cout << " gVarStart has to be > than 0.\n ";
      std::cin >> gVarStart_;
    }

    std::cout << "Quando vale il tempo di dimezzamento dell'indice di NON"
                 "rimozione? \t";
    std::cin >> gVarTime_;
    while (gVarTime_ < 0) {
      std::cout << "gVarTime has to be > 0.\n ";
      std::cin >> gVarTime_;
    }
  }

  double DeadIndex_;
  std::cout << "Indice di mortalità:\t";
  std::cin >> DeadIndex_;
  while (DeadIndex_ < 0 || DeadIndex_ > 1) {
    std::cout << " DeadIndex's value has to be between 0 and 1.\n ";
    std::cin >> DeadIndex_;
  }

  char DIVar_;
  std::cout << "La mortalità varia?\t";
  std::cin >> DIVar_;
  while (DIVar_ != 'N' && DIVar_ != 'Y' && DIVar_ != 'n' && DIVar_ != 'y') {
    std::cout << " Mortality variation has to be Y/n.\n ";
    std::cin >> DIVar_;
  }

  int DIVarTime_ = 0;
  int DIVarStart_ = 0;

  if (DIVar_ == 'Y' || DIVar_ == 'y') {
    std::cout << "Giorno di inizio della variazione della mortalità:\t";
    std::cin >> DIVarStart_;
    while (DIVarStart_ < 0) {
      std::cout << " Il giorno di inizio della variazione della mortalità has "
                   "to be > than 0.\n ";
      std::cin >> DIVarStart_;
    }

    std::cout << "Quando vale il tempo di dimezzamento dell'indice di "
                 "mortalità? \t";
    std::cin >> DIVarTime_;
    while (DIVarTime_ < 0) {
      std::cout << "DIVarTime has to be > 0.\n ";
      std::cin >> DIVarTime_;
    }
  }

  char Vax_;
  std::cout << "Ci sono i vaccini?\t";
  std::cin >> Vax_;
  while (Vax_ != 'N' && Vax_ != 'Y' && Vax_ != 'n' && Vax_ != 'y') {
    std::cout << " Vax has to be Y/n.\n ";
    std::cin >> Vax_;
  }

  double VaxIndex_ = 0;
  int VaxStart_ = 0;
  int VaxMax_ = 0;

  if (Vax_ == 'Y' || Vax_ == 'y') {
    std::cout << "Indice di vaccinazione:\t";
    std::cin >> VaxIndex_;
    while (VaxIndex_ < 0 || VaxIndex_ > 1) {
      std::cout << " VaxIndex's value has to be between 0 and 1.\n ";
      std::cin >> VaxIndex_;
    }

    std::cout << "Giorno di inizio dei vaccini:\t";
    std::cin >> VaxStart_;
    while (VaxStart_ < 0) {
      std::cout << " VaxStart has to be > than 0.\n ";
      std::cin >> VaxStart_;
    }

    std::cout << "Giorni per raggiungere la massima velocità percentuale di "
                 "vaccinazione :\t";
    std::cin >> VaxMax_;
    while (VaxMax_ < 0) {
      std::cout << " VaxMax has to be > than 0.\n ";
      std::cin >> VaxMax_;
    }
  }

  int Duration_;
  std::cout << "Durata simulazione:\t";
  std::cin >> Duration_;
  while (Duration_ <= 0) {
    std::cout << " Duration has to be > than 0.\n ";
    std::cin >> Duration_;
  }

  int ImmDur_;
  std::cout << "Durata immunità:\t";
  std::cin >> ImmDur_;
  while (ImmDur_ <= 0) {
    std::cout << " Imm has to be > than 0.\n ";
    std::cin >> ImmDur_;
  }

  char Previous_;
  std::cout << "La pandemia è già in corso?\t";
  std::cin >> Previous_;
  while (Previous_ != 'N' && Previous_ != 'Y' && Previous_ != 'n' &&
         Previous_ != 'y') {
    std::cout << " Previous has to be Y/n.\n ";
    std::cin >> Previous_;
  }

  int PanStart_;
  if (Previous_ == 'Y' || Previous_ == 'y') {
    std::cout << " Da quanti giorni? \t";
    std::cin >> PanStart_;
    while (PanStart_ < 0) {
      std::cout << " PanStart has to be major than 0.\n ";
      std::cin >> PanStart_;
    }
  } else {
    PanStart_ = 0;
  }

  int Dead_;
  if (Previous_ == 'Y' || Previous_ == 'y') {
    std::cout << " Dead: \t";
    std::cin >> Dead_;
    while (Dead_ < 0 || Dead_ > Pop_ - Inf_) {
      std::cout << " Dead has to be between 0 and Pop - Inf.\n ";
      std::cin >> Dead_;
    }
  } else {
    Dead_ = 0;
  }

  int Heal_;
  if (Previous_ == 'Y' || Previous_ == 'y') {
    std::cout << " Heal: \t";
    std::cin >> Heal_;
    while (Heal_ < 0 || Heal_ > Pop_ - Inf_ - Dead_) {
      std::cout << " Heal has to be between 0 and Pop - Inf - Dead.\n ";
      std::cin >> Heal_;
    }
  } else {
    Heal_ = 0;
  }

  int NewSusc_ = 0;

  char View_;
  std::cout << "Vuoi vedere tutti i giorni in stampa?\t";
  std::cin >> View_;
  while (View_ != 'N' && View_ != 'Y' && View_ != 'n' && View_ != 'y') {
    std::cout << " View has to be Y/n.\n ";
    std::cin >> View_;
  }

  PandemicData initial_state{Pop_ - Inf_ - Dead_ - Heal_,
                             Inf_,
                             Dead_,
                             Heal_,
                             Dead_ + Heal_,
                             NewSusc_,
                             Beta_,
                             Gamma_,
                             DeadIndex_,
                             VaxIndex_};

  Contagion epidemic{initial_state, DIVar_,     DIVarStart_, DIVarTime_,
                     ImmDur_,       bVar_,      bVarStart_,  bVarTime_,
                     gVar_,         gVarStart_, gVarTime_,   PanStart_,
                     Vax_, VaxStart_,     VaxMax_,    Previous_};

  std::vector<PandemicData> data = epidemic.generate_data(Duration_);

  int d = 0;

  std::cout << '\n'
            << std::setw(9) << "Giorno  "
            << "|" << std::setw(12) << "Suscettibili"
            << "|" << std::setw(12) << "Infetti  "
            << "|" << std::setw(12) << "Morti   "
            << "|" << std::setw(12) << "Guariti  "
            << "|" << std::setw(12) << "Rimossi  "
            << "|" << std::setw(12) << "NewSusc  "
            << "|" << std::setw(12) << "Infettività "
            << "|" << std::setw(12) << "Rimozione  "
            << "|" << std::setw(12) << "Mortalità  "
            << "|" << std::setw(12) << "Vaccinazione"
            << "|" << std::setw(12) << "Popolation "
            << "|\n"
            << "---------------------------------------------------------------"
               "---------------------------------------------------------------"
               "---------------------------"
            << '\n';

  if (View_ == 'Y' || View_ == 'y') {
    while (d <= Duration_) {
      control_print(d, data[d].Susc, data[d].Inf, data[d].Dead, data[d].Heal,
                    data[d].Rec, data[d].NewSusc, data[d].Beta, data[d].Gamma,
                    data[d].DeadIndex, data[d].VaxIndex, Pop_);
      ++d;
    }
  } else if (View_ == 'N' || View_ == 'n') {
    char a = ' ';
    if (Duration_ <= 150) {
      a = 'x';
    } else if (Duration_ <= 500) {
      a = 'y';
    } else {
      a = 'z';
    }

    std::cout.precision(3);

    switch (a) {
      case 'x':
        while (d <= Duration_) {
          control_print(d, data[d].Susc, data[d].Inf, data[d].Dead,
                        data[d].Heal, data[d].Rec, data[d].NewSusc,
                        data[d].Beta, data[d].Gamma, data[d].DeadIndex,
                        data[d].VaxIndex, Pop_);
          ++d;
        }
        break;

      case 'y':
        while (d <= Duration_) {
          control_print(d, data[d].Susc, data[d].Inf, data[d].Dead,
                        data[d].Heal, data[d].Rec, data[d].NewSusc,
                        data[d].Beta, data[d].Gamma, data[d].DeadIndex,
                        data[d].VaxIndex, Pop_);
          d += 10;
          if (d > Duration_ && d != Duration_ + 10) {
            control_print(Duration_, data[Duration_].Susc, data[Duration_].Inf,
                          data[Duration_].Dead, data[Duration_].Heal,
                          data[Duration_].Rec, data[Duration_].NewSusc,
                          data[Duration_].Beta, data[Duration_].Gamma,
                          data[Duration_].DeadIndex, data[Duration_].VaxIndex,
                          Pop_);
          }
        }
        break;

      case 'z':
        while (d <= Duration_) {
          control_print(d, data[d].Susc, data[d].Inf, data[d].Dead,
                        data[d].Heal, data[d].Rec, data[d].NewSusc,
                        data[d].Beta, data[d].Gamma, data[d].DeadIndex,
                        data[d].VaxIndex, Pop_);
          d += 20;
          if (d > Duration_ && d != Duration_ + 20) {
            control_print(Duration_, data[Duration_].Susc, data[Duration_].Inf,
                          data[Duration_].Dead, data[Duration_].Heal,
                          data[Duration_].Rec, data[Duration_].NewSusc,
                          data[Duration_].Beta, data[Duration_].Gamma,
                          data[Duration_].DeadIndex, data[Duration_].VaxIndex,
                          Pop_);
          }
        }
        break;
    }
  }

  std::cout << "---------------------------------------------------------------"
               "---------------------------------------------------------------"
               "---------------------------\n";

  now = time(0) + ConvToSec(Duration_);
  tm *ldt = localtime(&now);
  std::cout << "La simulazione termina il " << ldt->tm_mday << ' '
            << ConvToString(ldt->tm_mon) << ' ' << 1900 + ldt->tm_year
            << std::endl;
}
// grafici (Sani, Infetti, Morti, Guariti, Suscettibili, (Vaccinati)).
// variazioni automatiche b, g || variazioni predefinite in momenti
// giaco-defined (eventualmente con slider). Molto eventualmente mappa.
// aggiunta varianti tramite variabile (sigma) in base alle variazioni di b e g
// con spostamento di tutti i guariti nei suscettibili fino a (20) giorni prima.