#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

struct List{
    unsigned int Size;
    unsigned int *Array; 
    unsigned int Lengh; // ukazatel posledního zapsaného věci
    bool IsOdd;
};
void add(struct List *node, unsigned int addition);
int BellFordEsq(unsigned int pocatek);
int NxtGen();
void AddToReturn(unsigned int position);
void deletion(unsigned int a, unsigned int b);

unsigned int n, m, k;
struct List *Struct;
unsigned int *Gen, *GenTmp, *predecesor, *ToRtrn, *Tmp;
unsigned int countG, countGT, coutTR, from, into;


//  >>>>> Maaaain <<<<<
int main()
{
    cin >> n >> m >> k;
    
    if (k == m) {cout << 0 << endl; return 0;}
    
    countG = 0; coutTR = 0;
    Struct = (struct List*)calloc(n +1, sizeof(struct List));
    for (int i = 0; i <= n; i++) {
        Struct[i].Size=5*sizeof(unsigned int); 
        Struct[i].Array = (unsigned int*)calloc(5,sizeof(unsigned int)); 
        Struct[i].Lengh = 0;
        Struct[i].IsOdd = false;
    }
    Gen = (unsigned int *)calloc(n,sizeof(unsigned int)); 
    GenTmp = (unsigned int *)calloc(n,sizeof(unsigned int)); 
    ToRtrn = (unsigned int *)calloc(2*n,sizeof(unsigned int)); 
    predecesor =(unsigned int *)calloc(n+1,sizeof(unsigned int)); 
    for (int i = 0; i < m; i++) {
        cin >> from >> into;
        if(Struct[from].IsOdd) Struct[from].IsOdd = false;  else Struct[from].IsOdd = true;
        if(Struct[into].IsOdd) Struct[into].IsOdd = false;  else Struct[into].IsOdd = true;
        if(i >= k){
            add(&Struct[from],into);  // z 1ho města do druhého 
            add(&Struct[into],from);  // Z 2ho do 1ho
        }
    }
    for (unsigned int i = 1; i <= n; i++){ if ((Struct[i].IsOdd) && (BellFordEsq(i) == 1)){ cout << -1 << endl; return 0;}}
    cout << (coutTR/2)<< endl;
    for (unsigned int i = 0; i < coutTR; i += 2) {cout << ToRtrn[i]<< ' ' << ToRtrn[i + 1] << endl;}
}

// fc pro přidávání prvků do listu
void add(struct List *node, unsigned int addition)
{ 
    node->Lengh++;
    if (node->Lengh == node->Size){   
        node->Size *= 2;   
        Tmp = (unsigned int*)realloc(node->Array,node->Size);
        free(node->Array); node->Array = Tmp;
        
    }
    node->Array[node->Lengh] = addition; // add
}

int BellFordEsq(unsigned int pocatek)
{
    Struct[pocatek].IsOdd = false; // po skoncení nebude licha
    // první generace se skádá pouze z pocátku
    Gen[0] = pocatek;  countG = 1;
    // predecesor musi byt ze zacatku prazdny
    for (unsigned int i = 0; i <=n; i++){ predecesor[i] = 0;}
    predecesor[pocatek] = pocatek; // pocatek už byl použit
    while (true){ // dokud to neudelas nedostanes večeři
        if (countG == 0)  return 1; // zadna cesta nevede do říma 
        if (NxtGen() == 1)return 0; // vsehno probehlo spatne
    } 
}
int NxtGen()
{
    Tmp = GenTmp;
    GenTmp = Gen;   countGT = countG;
    Gen = Tmp;      countG = 0;
    for (unsigned int tmp = 0; tmp <= countGT; tmp++){
        unsigned int pocatek = GenTmp[tmp];
        for (int i = 0; i <= Struct[pocatek].Lengh; i++){
            unsigned int dalsi = Struct[pocatek].Array[i]; 
            if (dalsi == 0 || predecesor[dalsi] != 0) continue; // nezajímej se o hodnoty 0 aka. ty které jsme vyřadily 
            predecesor[dalsi] = pocatek;  //cesta k počátku
            if (Struct[dalsi].IsOdd){ // dorazili jsme do cile
                Struct[dalsi].IsOdd = false;
                AddToReturn(dalsi); return 1; // musime se ujistit ze zadna cesta není zbouraná dvakrat --> deletion
            }Gen[countG] = dalsi; countG++;}
    }return 0;
}

void AddToReturn(unsigned int position)
{
    if (predecesor[position] == position) return;
    ToRtrn[coutTR] = position;   
    ToRtrn[coutTR+ 1] = predecesor[position];
    coutTR += 2;
    // vymaz cestu 
    deletion(predecesor[position], position);
    deletion(position, predecesor[position]);
    // tato operace je kontroverzní ??????? neměl bych raději ukládat číslo ulice v predesesor[2,] ???????
    AddToReturn(predecesor[position]);
}

void deletion(unsigned int a, unsigned int b)
{
    for (int i = 0; i < Struct[a].Lengh; i++){
        if(Struct[a].Array[i] == b) {
            Struct[a].Array[i] = 0; return;
        }
    }
}


/*
    Tests
    
11 31 6
1 3
1 5
1 7
1 9
1 11
2 3
2 4
2 5
2 6
2 1
2 7
2 8
2 9
3 4
3 8
3 9
4 5
4 8
4 1
6 1
6 7
6 8
6 9
6 10
7 9
7 10
7 11
8 9
9 10
10 11
8 7

5 6 1
1 2
1 3
1 4
3 2
5 2
4 5

3 3 2
1 2
1 3
2 3

5 6 1
1 2
1 3
2 3
1 4
4 5
2 5

*/