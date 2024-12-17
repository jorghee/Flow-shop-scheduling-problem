/**
 * Laboratorio Métodos heurísticos
 *
 * Por favor, puede visitar el siguiente repositorio GitHub y estaré 
 * agradecido de su feedback para mejorar y/o corregir la información
 *
 * https://github.com/jorghee/Flow-shop-scheduling-problem/tree/main
 */

#include <bits/stdc++.h>
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

tuple<int, vector<int>::iterator> MejorPosicisionInsercion(vector<int> &S, int nj) {
  fill(&EF[0][0], &EF[0][mM], 0);
  for (int k = 1; k <= S.size(); k++) {
    int j = S[k - 1];
    EF[k][0] = EF[k - 1][0] + P[j][0];
    for (int i = 1; i < mM; i++)
      EF[k][i] = max(EF[k - 1][i], EF[k][i - 1]) + P[j][i];
  }

  for (int k = 0; k <= S.size(); k++) {
    EF[k][0] += P[nj][0];
    for (int i = 1; i < mM; i++)
      EF[k][i] = max(EF[k][i], EF[k][i - 1]) + P[nj][i];
  }

  fill(&LS[S.size()][0], &LS[S.size()][mM], 0);
  for (int k = S.size() - 1; k >= 0; k--) {
    int j = S[k];
    LS[k][mM - 1] = LS[k + 1][mM - 1] + P[j][mM - 1];
    for (int i = mM - 2; i >= 0; i--)
      LS[k][i] = max(LS[k][i + 1], LS[k + 1][i]) + P[j][i];
  }

  int bmk = numeric_limits<int>::max(), mk, pos;
  for (int k = 0; k <= S.size(); k++) {
    mk = 0;
    for (int i = 0; i < mM; i++)
      if (mk < EF[k][i] + LS[k][i])
        mk = EF[k][i] + LS[k][i];
    if (mk < bmk) { bmk = mk; pos = k; }
  }

  return {bmk, S.begin() + pos};
}

int NEH(vector<int> &S) {
  int mk;
  vector<int> orden;
  PrioridadNEH(orden);
  S = {orden[0]};
  for (int k = 1; k < nT; k++) {
    vector<int>::iterator pos;
    tie(mk, pos) = MejorPosicisionInsercion(S, orden[k]);
    S.insert(pos, orden[k]);
  }
  return mk;
}

int BusquedaLocal(vector<int> &S, int pmk = 0) {
  vector<int> orden(S);
  shuffle(orden.begin(), orden.end(), Rand);
  int k = 0;
  int c = 0;
  int bmk = pmk;
  if (bmk == 0) bmk = makespan(S);
  do {
    int mk; vector<int>::iterator pos;
    S.erase(find(S.begin(), S.end(), orden[k]));
    tie(mk, pos) = MejorPosicisionInsercion(S, orden[k]);
    S.insert(pos, orden[k]);
    if (mk < bmk) { bmk = mk; c = 0; }
    k++; if (k >= nT) k = 0;
    c++;
  } while (c < nT);
  return bmk;
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
  // vector<int> S = {4, 3, 5, 1, 0, 2};
  vector<int> S = {4, 3, 1, 0};
  cout << makespan(S) << "\n";


  cout << "\nExample of PrioridadNEH\n";

  vector<int> ss;
  PrioridadNEH(ss);
  for (auto &j : ss) cout << j << ",";
  cout << "\n";


  cout << "\nExample 1 of Aceleración de Taillard\n";

  int mk; vector<int>::iterator pj;
  tie(mk, pj) = MejorPosicisionInsercion(S, 2);
  S.insert(pj, 2);
  cout << mk << ": ";
  for (auto &j : S) cout << j << ",";
  cout << "\n";


  cout << "\nExample 2 of Aceleración de Taillard\n";
  
  S = {3};
  cout << makespan(S) << "\n";
  
  for (auto &j : {4, 0, 1, 2, 5}) {
    int mk; vector<int>::iterator pj;
    tie(mk, pj) = MejorPosicisionInsercion(S, j);
    S.insert(pj, j);
    cout << mk << ": ";
    for (auto &j : S) cout << j << ",";
    cout << "\n";
  }

  // Instancias
  vector<string> Instancias = {"br66", "ta021", "ta022", "ta023", "ta024",
    "ta025", "ta026", "ta027", "ta028", "ta029", "ta030"};


  cout << "\nSoluciones producidas por NEH\n";

  ss.clear();
  for (auto &instancia : Instancias) {
    cargar("flowshop/" + instancia);
    cout << instancia << "\t" << NEH(ss) << ": ";
    for (auto &j : ss) cout << j << ",";
    cout << "\n"; 
  }


  cout << "\nSoluciones luego de una Búsqueda Local\n";

  ss.clear();
  for (auto &instancia : Instancias) {
    cargar("flowshop/" + instancia);
    int mk = NEH(ss); mk = BusquedaLocal(ss, mk);
    if (mk != makespan(ss)) cout << "ERROR!!!\n";
    cout << instancia << "\t" << mk << ": ";
    for (auto &j : ss) cout << j << ",";
    cout << "\n";
  }

  return 0;
}
