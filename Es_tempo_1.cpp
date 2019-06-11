#include <iostream>

using namespace std;

int main() 
{
    // delimitatore iniziale output del programma (stringa "start")
    // ATTENZIONE! Non cancellare l'istruzione sottostante
    cout << "start" << endl;
    
    // inserire qui il codice del programma

    int A1[10][5], A2[10][5];
    int N=50;
    int a=0,b=0;
    
    for(int j=0;j<10;j++){//R1=(letti k+(5*j) valori)&&(0<=j<10)
        for(int k=0;k<5;k++){//R2=(letti k valori)&&(0<=k<5)
            cin>>A1[j][k];
        }
    }
    //Riempie A2
    for(int j=0;j<10;j++){//(R3=assegnati k+(5*j) valori ad A2)&&(A2[a][b]=A1[j][k])&&(0<=j<10)
        for(int k=0;k<5;k++){//R4=(assegnati k valori ad A2)&&(0<=k<5)
            if(a==10){
                a=0;
                b++;
            }
            A2[a][b]=A1[j][k];
            if(a<10){
                a++;
            }
        }
    }
    //stampa A1
    for(int j1=0;j1<10;j1++){//R5=(stampati k1+(5*j1) valori)&&(0<=j1<10)
        for(int k1=0;k1<5;k1++){//R6=(stampati k1 valori)&&(0<=k1<5)
            cout<<A1[j1][k1]<<" ";
        }
        cout<<endl;
    }
    //stampa A2
    for(int j2=0;j2<10;j2++){//R7=(stampati k2+(5*j2) valori)&&(0<=j2<10)
        for(int k2=0;k2<5;k2++){//R8=(stampati k2 valori)&&(0<=k2<5)
            cout<<A2[j2][k2]<<" ";
        }
        cout<<endl;
    }
    bool B[10][10];
    bool d=true;
    int r1=0, r2=1, c1=0, c2=0;
    while(r1<10){//R9=(0<=r1<10)&&(controllate r2+(r1*10)+1 righe e in ognuna di esse c2+(c1*5) colonne)&&(se A2[r1][c1]==A2[r2][c2] è vero, allora B[r1][r2]=false e B[r2][r1]=false)
    //&&(se A2[r1][c1]==A2[r2][c2] è falso, allora B[r1][r2]=true e B[r2][r1]=true)
        r2=1+r1;
        while(r2<10){//R10=(1<=r2<10)&&(controllate r2 righe)&&(se d rimane vero, allora B[r1][r2]=true e B[r2][r1]=true)
            c1=0;
            d=true;
            while(c1<5){//R11=(0<=c1<5)&&(nelle righe r1 e r2 sono state controllate c2+(c1*5) colonne)&&(se d è falso esci dal ciclo)
                c2=0;
                while(c2<5){//R12=(0<=c2<5)&&(nelle righe r1 e r2 sono state controllate c2 colonne)&&(se A2[r1][c1]==A2[r2][c2], allora (B[r1][r2]=false e B[r2][r1]=false)&&(d=false))
                    if(A2[r1][c1]==A2[r2][c2]){
                        B[r1][r2]=false;
                        B[r2][r1]=false;
                        d=false;
                        break;
                    }
                    c2++;
                }
                if(d==false){
                    break;
                }
                c1++;
            }
            if(d==true){
                B[r1][r2]=true;
                B[r2][r1]=true;
            }
            r2++;
        }
        r1++;
    }
    for(int j4=0;j4<10;j4++){//R13=(0<=j4<10)&&(controllati k4+(5*j4) valori)
        for(int k4=0;k4<10;k4++){//R14=(0<=k4<10)&&(controllati k4 valori)&&(se j4=k4, allora B[j4][k4]=false)
            if(j4==k4){
                B[j4][k4]=false;
            }
        }
    }
    
    for(int j3=0;j3<10;j3++){//R15=(stampati k3+(5*j3) valori)&&(0<=j3<10)
        for(int k3=0;k3<10;k3++){//R16=(stampati k3 valori)&&(0<=k3<5)
            cout<<B[j3][k3]<<" ";
        }
        cout<<endl;
    }

     // delimitatore finale output del programma (stringa "end")
    // ATTENZIONE! Non cancellare l'istruzione sottostante
    cout << "end" << endl;
}