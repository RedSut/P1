// NOTE:
/*
  Ho dimenticato il controllo che n_ele_H_fette deve essere >= nP
  anzi lo faccio ma non è esplicito
*/

#include <iostream>
using namespace std;

bool match(int*T, int inizio,int*P, int nP,int lim2, int lim3);
int F(int i, int lim2, int lim3);

main()
{
  int X[400], P[20], n_ele, nP, lim1, lim2, lim3;
  cin >> n_ele;
  for (int i = 0; i < n_ele; i++)
    cin >> X[i];
  cin >> lim1 >> lim2 >> lim3;
  if (lim1 * lim2 * lim3 < n_ele)
    n_ele = lim1 * lim2 * lim3;
  cin >> nP;
  for (int i = 0; i < nP; i++)
    cin >> P[i];
  int numeroStratiPieni = n_ele / (lim2 * lim3), elementiUltimoStrato = n_ele % (lim2 * lim3), righePieneUltimoStrato = elementiUltimoStrato / lim3, elementiUltimaRigaUltimoStrato = elementiUltimoStrato % lim3;
  cout << "start" << endl;
  bool trovato = false;
  for (int i = 0; i < lim2 && !trovato; i++)
  {
    int n_ele_H_fetta  = numeroStratiPieni * lim3;
    if (i < righePieneUltimoStrato && elementiUltimaRigaUltimoStrato > 0) {
      n_ele_H_fetta += lim3;
    }
    if(i==righePieneUltimoStrato && elementiUltimaRigaUltimoStrato > 0){
      n_ele_H_fetta += elementiUltimaRigaUltimoStrato;
    }
    for(int j = 0; j < n_ele_H_fetta-nP+1 && !trovato; j++)
    {
      trovato = match(X+i*lim3, j, P, nP, lim2, lim3);
      if(trovato){
        cout << "match trovato a partire dalla posizione "<< j <<" della H-fetta "<< i << endl;
      }
    }
    
  }

  if (!trovato)
    cout << "nessun match trovato" << endl;
  cout << "end" << endl;
}
//PRE=(T punta all’inizio di una H-fetta in X tale che a partire dal suo elemento inizio abbia almeno nP elementi, P, nP, lim2 e lim3, sono definiti ed hanno il senso usuale)
bool match(int*T, int inizio,int*P, int nP,int lim2, int lim3){
  int matchCounter = 0;
  bool trovato = false;
  int contatore = 0;
  while (contatore < nP)
  // R = (0 <= contatore <= nP)
  {
    if(T[F(inizio,lim2,lim3)] == P[matchCounter]){
      matchCounter++;
      if (matchCounter == nP) {
        trovato = true;
      }
    }else{
      matchCounter = 0;
    }
    inizio++;
    contatore++;
  }
  return trovato;
}
//POST=(restituisce true  sse nella H-fetta che inizia in T, gli elementi, inizio, inizio+1,..inizio+nP-1 sono identici a P[0..nP-1])

int F(int i, int lim2, int lim3)
{
  return ((i / lim3) * (lim2 * lim3) + (i % lim3));
}