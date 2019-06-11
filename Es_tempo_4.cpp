#include<iostream>
using namespace std;

int F(int i ,int lim2, int lim3){
    if(i<lim2){
        return i;
    }else{
        //cout<<i/(lim3)<<" ";
        int ris=(i/lim3)*(lim2*lim3+(i%lim2));
        return ris;
    }
}
bool match (int*T, int inizio, int*P, int nP,int lim2, int lim3){
    int ele=inizio;
    ele=F(inizio,lim2,lim3);
    int r=ele%lim2;
    //cout<<r<<" ";
    //cout<<ele<<" ";
    T=T+ele;
    //cout<<"T0:"<<*T<<endl;
    bool ok=true;
    for(int i=0; i<nP && ok; i++){
        int i_e=F(i,lim2,lim3);
        //cout<<i_e<<" ";
        //cout<<*(T+i_e)<<" ";
        if(*(T+i_e)!=*(P+i))
            ok=false;
    }
        return ok;


}
main()
{
  int X[400], P[20], n_ele, nP, lim1, lim2, lim3;
  cin >> n_ele;
  for(int i=0; i<n_ele; i++)
    cin >> X[i];
  cin >> lim1 >> lim2 >> lim3;
  if(lim1*lim2*lim3 < n_ele)
    n_ele=lim1*lim2*lim3;
  cin >> nP;
for(int i=0; i<nP; i++)
    cin >> P[i];
int nsp= n_ele/(lim2*lim3), eus= n_ele%(lim2*lim3), rpus= eus/lim3, ur= eus%lim3;
cout<<"start"<<endl;
int h_ele=0,inizio=0;
int* P1=&X[0];
bool trovato= false;
for(int i=0; i<lim2 && !trovato; i++){
    // calcolo elementi H-fetta
    h_ele=nsp*3;
    if(rpus>i){
        h_ele+=3;
    }else if(rpus==i){
        h_ele+=ur;
    }
    if(i!=0){
       P1=P1+lim2;
    }
    //cout<<*P1<<" ";
    for(int j=0;j<h_ele-nP+1;j++){
        if(match(P1,j,P,nP,lim2,lim3)){
            cout<<"match trovato a partire dalla posizione "<<j<<" della H-fetta "<<i<<endl;
            trovato=true;
        }
    }
    


}
    
if(!trovato)
	cout<< "nessun match trovato"<<endl;
cout<<"end"<<endl;
}




/*input 
22
1 2 3
4 5 6
7 8 9
10 11 12
13 14 15
16 17 18
19 20 21
22
5 3 3
3
8 9 16
*/
