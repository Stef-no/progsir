#ifndef MY_EPIDEMIC_HPP
#define MY_EPIDEMIC_HPP

#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

// cambiare if riga 47 di Previous 's' con y e n

struct PandemicData {
  int Susc;
  int Inf;
  int Dead;
  int Heal;
  int Rec;
  int NewSusc;
  double Beta;
  double Gamma;
  double DeadIndex;
  double VaxIndex;
};
/*
void control_print(int day, int susc, int inf, int dead, int heal, int rec,
                   int newsusc, double beta, double gamma, double deadindex,
                   double vaxindex, int pop) {
  assert(susc >= 0 && susc <= pop);
  assert(inf >= 0 && inf <= pop);
  assert(rec >= 0 && rec <= pop);
  assert(dead >= 0 && dead <= pop);
  assert(heal >= 0 && heal <= pop);
  assert(newsusc >= 0 && newsusc <= pop);
  assert(heal >= 0 && heal <= rec);
  assert(dead >= 0 && dead <= rec);
  assert(deadindex >= 0 && deadindex <= 1);
  assert(vaxindex >= 0 && vaxindex <= 1);
  assert(beta >= 0 && beta <= 1);
  assert(gamma >= 0 && gamma <= 1);
  assert(pop == susc + inf + rec);
  assert(rec == heal + dead);
  assert(day >= 0);

  std::cout << std::setw(9) << day << "|" << std::setw(12) << susc << "|"
            << std::setw(12) << inf << "|" << std::setw(12) << dead << "|"
            << std::setw(12) << heal << "|" << std::setw(12) << rec << "|"
            << std::setw(12) << newsusc << "|" << std::setw(12) << beta << "|"
            << std::setw(12) << gamma << "|" << std::setw(12) << deadindex
            << "|" << std::setw(12) << vaxindex << "|" << std::setw(12) << pop
            << "|\n";
}
*/
class Contagion {
 private:
  PandemicData newstate;
  char DIVar;
  int DIVarStart;
  int DIVarTime;
  int ImmDur;
  char bVar;
  int bVarStart;
  int bVarTime;
  char gVar;
  int gVarStart;
  int gVarTime;
  int PanStart;
  char Vax;
  int VaxStart;
  int VaxMax;
  char Previous;

 public:
  Contagion(PandemicData& initial_state, char div, int divs, int divt, int id,
            char bv, int bvs, int bvt, char gv, int gvs, int gvt, int ps,
            char v, int vs, int vm, char p)
      : newstate{initial_state},
        DIVar{div},
        DIVarStart{divs},
        DIVarTime{divt},
        ImmDur{id},
        bVar{bv},
        bVarStart{bvs},
        bVarTime{bvt},
        gVar{gv},
        gVarStart{gvs},
        gVarTime{gvt},
        PanStart{ps},
        Vax{v},
        VaxStart{vs},
        VaxMax{vm},
        Previous{p} {}

  std::vector<PandemicData> generate_data(int Duration_) {
    std::vector<PandemicData> result{newstate};
    PandemicData state = result.back();

    // double vi = state.VaxIndex;

    for (int i = 0; i < Duration_; ++i) {
      int Pop_ = newstate.Susc + newstate.Inf + newstate.Dead + newstate.Heal;
      int NewRec = std::round(newstate.Gamma * state.Inf);
      int NewInf = std::round(newstate.Beta / Pop_ * state.Susc * state.Inf);
      int NewDead = std::round(NewRec * newstate.DeadIndex);

      if (Previous == 'Y' || Previous == 'y') {
        if (i > DIVarStart - PanStart) {
          if (DIVar == 'Y' || DIVar == 'y') {
            double exponentialDIY =
                std::exp((DIVarStart - PanStart - i) * log(2) / DIVarTime);
            state.DeadIndex = (result[0].DeadIndex * exponentialDIY);
          } else if (bVar == 'N' || bVar == 'n') {
            state.DeadIndex = result[0].DeadIndex;
          };
        } else {
          state.DeadIndex = result[0].DeadIndex;
        }

        if (i > bVarStart - PanStart) {
          if (bVar == 'Y' || bVar == 'y') {
            double exponentialbY =
                std::exp((bVarStart - PanStart - i) * log(2) / bVarTime);
            state.Beta = (result[0].Beta * exponentialbY);
          } else if (bVar == 'N' || bVar == 'n') {
            state.Beta = result[0].Beta;
          };
        } else {
          state.Beta = result[0].Beta;
        }

        if (i > gVarStart - PanStart) {
          if (gVar == 'Y' || gVar == 'y') {
            double exponentialgY =
                std::exp((gVarStart - PanStart - i) * log(2) / gVarTime);
            state.Gamma = 1 - ((1- result[0].Gamma) * exponentialgY);
          } else if (gVar == 'N' || gVar == 'n') {
            state.Gamma = result[0].Gamma;
          };
        } else {
          state.Gamma = result[0].Gamma;
        }

      } else if (Previous == 'N' || Previous == 'n') {
        if (i > DIVarStart) {
          if (DIVar == 'Y' || DIVar == 'y') {
            double exponentialDIY =
                std::exp((DIVarStart - i) * log(2) / DIVarTime);
            state.DeadIndex = (result[0].DeadIndex * exponentialDIY);
          } else if (bVar == 'N' || bVar == 'n') {
            state.DeadIndex = result[0].DeadIndex;
          };
        } else {
          state.DeadIndex = result[0].DeadIndex;
        }

        if (i > bVarStart - PanStart) {
          if (bVar == 'Y' || bVar == 'y') {
            double exponentialbY =
                std::exp((bVarStart - i) * log(2) / bVarTime);
            state.Beta = (result[0].Beta * exponentialbY);
          } else if (bVar == 'N' || bVar == 'n') {
            state.Beta = result[0].Beta;
          };
        } else {
          state.Beta = result[0].Beta;
        }

        if (i > gVarStart - PanStart) {
          if (gVar == 'Y' || gVar == 'y') {
            double exponentialgY =
                std::exp((gVarStart - i) * log(2) / gVarTime);
            state.Gamma = 1 - (( 1 - result[0].Gamma) * exponentialgY);
          } else if (gVar == 'N' || gVar == 'n') {
            state.Gamma = result[0].Gamma;
          };
        } else {
          state.Gamma = result[0].Gamma;
        }
      };

      if (i > ImmDur) {  // giorno 1, 0 i guariti -> inutile
        int j = i - ImmDur;
        newstate.NewSusc =
            result[j].Heal - result[j - 1].Heal + result[j].NewSusc;
      }

      int NewVax = 0;
      if(Vax == 'Y' || Vax == 'y')
        if (state.Inf > Pop_ * 0.001) {
          if (VaxStart <= i && VaxStart + VaxMax > i) {
            NewVax = (state.Susc + newstate.NewSusc - NewInf) *
                     newstate.VaxIndex * ((i - VaxStart + 1.0) / VaxMax);
          } else if (VaxStart + VaxMax <= i) {
            NewVax = (state.Susc + newstate.NewSusc - NewVax) * newstate.VaxIndex;
          }
        } else {
          NewVax = 0;
        } else {
          NewVax = 0;
        }

      state.Susc += newstate.NewSusc - NewInf - NewVax;
      state.Inf += NewInf - NewRec;
      state.Rec += NewRec + NewVax - newstate.NewSusc;
      state.Dead += NewDead;
      state.Heal += NewRec - NewDead + NewVax - newstate.NewSusc;
      state.NewSusc = newstate.NewSusc;

      result.push_back(state);  // vengono immagazzinati tutti i valori di state
                                // giorno per giorno
    }
    return result;
  }
};

#endif

// aggiungere giorni mancanti che fa il conto alla rovescia, utile per i doctest
// mettere le nascite