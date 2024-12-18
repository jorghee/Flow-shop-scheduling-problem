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

inline int elapsed(bool reset = false) {
  static clock_t start = clock();
  if (reset) start = clock();
  return (1000.00 * double(clock() - start) / double(CLOCKS_PER_SEC));
}

int ILS_B(vector<int> &BS) {
  vector<int> S;
  int mk, bmk;
  elapsed(true);
  NEH(S);
  bmk = mk = BusquedaLocal(S);
  BS = S;

  while (elapsed() < 15 * nT * mM) {
    auto b1 = S.begin() + Rand() % S.size();
    auto b2 = S.begin() + Rand() % S.size();
    swap(*b1, *b2);
    b1 = S.begin() + Rand() % S.size();
    b2 = S.begin() + Rand() % S.size();

    mk = BusquedaLocal(S);
    if (bmk > mk) {BS = S; bmk = mk;}
    else {S = BS; mk = bmk;}
  }
  return bmk;
}

int ILS_RW(vector<int> &BS) {
  vector<int> S;
  int mk, bmk;
  elapsed(true);
  NEH(S);
  bmk = mk = BusquedaLocal(S);
  BS = S;

  while (elapsed() < 15 * nT * mM) {
    auto b1 = S.begin() + Rand() % S.size();
    auto b2 = S.begin() + Rand() % S.size();
    swap(*b1, *b2);
    b1 = S.begin() + Rand() % S.size();
    b2 = S.begin() + Rand() % S.size();

    mk = BusquedaLocal(S);
    if (bmk > mk) {BS = S; bmk = mk;}
    // else {S = BS; mk = bmk;}
  }
  return bmk;
}

int ILS_SA(vector<int> &BS) {
  vector<int> S, NS;
  int mk, bmk, nmk;
  int sum_p = 0;

  for (int j = 0; j < nT; j++)
    for (int i = 0; i < mM; i++)
      sum_p += P[j][i];
  double T = double(sum_p) / (nT * mM * 25);

  elapsed(true);
  bmk = mk = NEH(S);
  bmk = mk = BusquedaLocal(S);
  BS = S;

  while (elapsed() < 15 * nT * mM) {
    NS = S;
    auto b1 = NS.begin() + Rand() % NS.size();
    auto b2 = NS.begin() + Rand() % NS.size();
    swap(*b1, *b2);
    b1 = NS.begin() + Rand() % NS.size();
    b2 = NS.begin() + Rand() % NS.size();
    swap(*b1, *b2);

    nmk = BusquedaLocal(NS);
    if (nmk < mk) {
      S = NS; mk = nmk;
      if (mk < bmk) {BS = S; bmk = mk;}
    } else if (double(Rand()) / Rand.max() <= 
          exp(-(double(nmk - mk) / T))) {
      S = NS; mk = nmk;
    }
  }

  return bmk;
}

int main(void) {
  vector<int> SS;
  cargar("flowshop/ta023");
  cout << nT << "x" << mM << endl;

  cout << "ilsb " << ILS_B(SS) << endl;
  for (auto &j : SS) cout << j << ",";
  cout << endl;

  cout << "ilsrw " << ILS_RW(SS) << endl;
  for (auto &j : SS) cout << j << ",";
  cout << endl;

  cout << "ilssa " << ILS_SA(SS) << endl;
  for (auto &j : SS) cout << j << ",";
  cout << endl;

  return 0;
}
