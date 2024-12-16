/**
 * Laboratorio Métodos heurísticos
 *
 * Por favor, puede visitar el siguiente repositorio GitHub y estaré 
 * agradecido de su feedback para mejorar y/o corregir la información
 *
 * https://github.com/jorghee/Flow-shop-scheduling-problem/tree/main
 */

#include <bits/stdc++.h>
#include <random>
using namespace std;

int nT, mM, P[900][70];
int EF[900][70], LS[900][70];
mt19937 Rand(time(0));

void cargar(string nombre) {
  ifstream archivo(nombre);
  archivo >> nT >> mM;
  int basura;
  for (int j = 0; j < nT; j++)
    for (int i = 0; i < mM; i++)
      archivo >> basura >> P[j][i];
}

int makespan(vector<int> &S) {
  fill(&EF[0][0], &EF[0][mM], 0);
  int k = 1;
  for (auto j : S) {
    EF[k][0] = EF[k - 1][0] + P[j][0];
    for (int i = 1; i < mM; i++)
      EF[k][i] = max(EF[k - 1][i], EF[k][i - 1]) + P[j][i];
    k++;
  }
  return EF[S.size()][mM - 1];
}

void PrioridadNEH(vector<int> &Orden) {
  vector<int> TT;
  TT.resize(nT);

  for (int j = 0; j < nT; j++) {
    int t = 0;
    for (int i = 0; i < mM; i++) t = t + P[j][i];
    TT[j] = t;
  }

  Orden.resize(nT);
  iota(Orden.begin(), Orden.end(), 0);
  sort(Orden.begin(), Orden.end(),
      [&TT] (const int &i, const int &j) {
        return (TT[i] > TT[j] or (TT[i] == TT[j] and i < j));
      });
}

int main(void) {
  cout << "\nMatriz P[j][i]\n";

  cargar("flowshop/br66");
  for (int j = 0; j < nT; j++) {
    for (int i = 0; i < mM; i++)
      cout << P[j][i] << " ";
    cout << "\n";
  }


  cout << "\nCalculate makespan\n";

  cout << nT << "x" << mM << "\n";
  vector<int> S = {4, 3, 5, 1, 0, 2};
  cout << makespan(S) << "\n";


  cout << "\nExample of PrioridadNEH\n";

  vector<int> ss;
  PrioridadNEH(ss);
  for (auto &j : ss) cout << j << ",";
  cout << "\n";
}
