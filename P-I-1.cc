#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <set>
#include <iostream>

int BellFordEsq(unsigned int pocatek);
int NxtGen();
void AddToReturn(unsigned int position);

unsigned int n, m, k;
std::set<int> *SetsArray;
bool *OddnesArray;
unsigned int *Gen, *GenTmp, *pre, *ToRtrn, *Tmp;
unsigned int countG, countGT, coutTR, from, into;

int main()
{
    std::cin >> n >> m >> k;
    countG = 0; coutTR = 0;
    SetsArray = new std::set<int> [n+1];
    OddnesArray = (bool*)calloc(n+1, sizeof(bool));
    for (int i = 0; i <= n; i++) {OddnesArray[i] = false;} // iniciuj jako sude
    Gen = (unsigned int *)calloc(n,sizeof(unsigned int)); // tyto proměné musí být globalní, ale jejich velikost muzeme urcit az po nactení n
    GenTmp = (unsigned int *)calloc(n,sizeof(unsigned int)); 
    ToRtrn = (unsigned int *)calloc(2*n,sizeof(unsigned int)); 
    pre =(unsigned int *)calloc(n+1,sizeof(unsigned int)); // predesesors
    for (int i = 0; i < m; i++) { // load
        std::cin >> from >> into;
        if(OddnesArray[from]) OddnesArray[from] = false;  else OddnesArray[from] = true; // řeší lichost 
        if(OddnesArray[into]) OddnesArray[into] = false;  else OddnesArray[into] = true; // řeší lichost 
        if(i >= k){
            SetsArray[from].insert(into);
            SetsArray[into].insert(from);} // ulice do k je zakazane pouzívat
    }
    for (unsigned int i = 1; i <= n; i++){
        if ((OddnesArray[i]) && (BellFordEsq(i) == 1)){
            std::cout << -1 << std::endl; return 0;
        }
    } // proved BellFordEsq a zarozen kontroluj pro nemoznot
    std::cout << (coutTR/2)<< std::endl; 
    for (unsigned int i = 0; i < coutTR; i += 2) {
        std::cout << ToRtrn[i]<< ' ' << ToRtrn[i + 1] << std::endl;} // vypis
}

int BellFordEsq(unsigned int pocatek)
{
    OddnesArray[pocatek] = false; // po skoncení nebude licha
    Gen[0] = pocatek; countG = 1;// první generace se skádá pouze z pocátku
    for (unsigned int i = 0; i <=n; i++){
        pre[i] = 0;} // predecesor musi byt ze zacatku prazdny
    pre[pocatek] = pocatek; // pocatek už byl použit
    while (true){ // nehrozí možnost nekonečného cyklu
        if (countG == 0)  return 1; // zadna cesta nevede
        if (NxtGen() == 1)return 0; // fc NxtGen zbourala cestu a zbavila se tak dvou lichých měst
    } 
}
int NxtGen()
{
    Tmp = GenTmp; GenTmp = Gen; Gen = Tmp; // otoč generace
    countGT = countG; countG = 0; // nový musí nahradit stare a ti pak zestarnout
    for (unsigned int tmp = 0; tmp <= countGT; tmp++){
        for(auto dalsi : SetsArray[GenTmp[tmp]]){
            if (pre[dalsi] != 0) continue; // nezajímej se o hodnoty 0 aka. ty které jsme vyřadily 
            pre[dalsi] = GenTmp[tmp];  //cesta k počátku
            if (OddnesArray[dalsi]){ // dorazili jsme do cile
                OddnesArray[dalsi] = false;
                AddToReturn(dalsi); return 1; // musime se ujistit ze zadna cesta není zbouraná dvakrat --> deletion
            }
            Gen[countG] = dalsi; countG++;
        }
    }return 0;
}

void AddToReturn(unsigned int position)
{
    if (pre[position] == position) return;
    ToRtrn[coutTR] = position; ToRtrn[coutTR+ 1] = pre[position];
    coutTR += 2;
    SetsArray[pre[position]].erase(position); 
    SetsArray[position].erase(pre[position]);// vymaz cestu obema smery
    AddToReturn(pre[position]); // rekurze
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
5 6

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