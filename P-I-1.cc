#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

struct List{
    long Size;
    long *ulice; 
    long Lengh; // ukazatel posledního zapsaného věci
    long actualleng;
    bool IsOdd;
};


// declare all global variables
void add(struct List *node, long addition);
void load();
void lichost();

// hledaní cest
int spojL(long pocatek);
int next();

// výstup
void addToReturn(long position);

// helpers
void egeing();
void dell(long a, long b);
void vynuluj(long *pole, long b);


long n, m, k;
struct List *krizovatka;
long *newGenration; 
long newGenrationLeng;
long *oldgeneration;
long oldgenerationLengh;
long *liche; 
long licheLengh;
long *predecesor;
long *BigReturn;
long BigReturnLengh;


//  >>>>> Maaaain <<<<<
int main()
{
    // dostan rozměry
    cin >> n >> m >> k;
    
    
    newGenrationLeng = 0;
    licheLengh = 0;
    BigReturnLengh = 0;
    
    krizovatka = (struct List*)calloc(n +1, sizeof(struct List));
    for (int i = 0; i <= n; i++)
    {
        krizovatka[i].Size=5*sizeof(long); 
        krizovatka[i].ulice = (long*)calloc(5,sizeof(long)); 
        krizovatka[i].Lengh = 0;
        krizovatka[i].actualleng = 0;
    }
    newGenration = (long *)calloc(n,sizeof(long)); 
    oldgeneration = (long *)calloc(n,sizeof(long)); 
    BigReturn = (long *)calloc(2*n,sizeof(long)); 
    liche = (long *)calloc(n+1,sizeof(long)); 
    predecesor =(long *)calloc(n+1,sizeof(long)); 
    
    load();
    
    lichost(); 
    // už víme kterých měst se snažíme zbavit --> lichost nemusíme už kontrolovat
    
    // nejsou-li zaden liché križovatky řešení je 0
    if (licheLengh == 0) 
    {
        cout << 0 << endl;
        return 0;
    }
    
    // najdi vždy 2 nejbiší kriřovatky >>> inspirace Bellmann-Fordovým algoritmem (použití negativních ciklů je užitečné až v druhém příkladu)<<<
    for (long i = 0; i< licheLengh; i++)
    {   
        // nekteré křižovatky už byli spojenu takové přeskoč
        if (krizovatka[liche[i]].IsOdd == false) continue;
        
        // zbav se dalsí liche; zkontroluj jestli ano
        if (spojL(liche[i]) == 1)
        {
            // bůh neexistuje uloha nemá řešení
            cout << -1 << endl;
            return 0;
        }
    }
    
    // vypis výstup
    for (long i = 0; i < BigReturnLengh; i += 2)
    {
       cout << BigReturn[i]<< " " << BigReturn[i + 1] << endl;
    }
}

// fc pro přidávání prvků do listu
void add(struct List *node, long addition)
{ 
    node->Lengh++;
    
    if (node->Lengh == node->Size) // 
    {   
        node->Size *= 3;
        node->ulice = (long*)realloc(node->ulice,node->Size);
    }
    
    // add
    node->ulice[node->Lengh] = addition;
    node->actualleng++;
}

// nactení pole
void load()
{
    // načti ulice 
    int tmp1, tmp2;
    for (int i = 1; i <= m; i++) // projdi všechny řadky vztupu 
    {
        cin >> tmp1 >> tmp2;
        if(i -1 < k) // potřebuju někat uložit které ul jsou zakazané zbořit
        {
            krizovatka[tmp1].actualleng++;
            krizovatka[tmp2].actualleng++;
        }
        else
        {
            add(&krizovatka[tmp1],tmp2);  // z 1ho města do druhého 
            add(&krizovatka[tmp2],tmp1);  // Z 2ho do 1ho
        }
    }
    return;
}    

// zjisti vsechna licha
void lichost()
{
    // urči liché 
    // lichost můžeme kontrolovat až po načtení 
    for (long i = 1; i <= n; i++)
    {
        if (krizovatka[i].actualleng %2 != 0) 
        {
            krizovatka[i].IsOdd = true;
            liche[licheLengh] = i;
            licheLengh++;
        }
        else krizovatka[i].IsOdd = false;
    }
    krizovatka[0].IsOdd = false;
}


int spojL(long pocatek)
{
    krizovatka[pocatek].IsOdd = false; // po skoncení nebude licha
    
    // první generace se skádá pouze z pocátku
    newGenration[0] = pocatek;
    newGenrationLeng = 1;
    
    // predecesor je prázdý
    vynuluj(predecesor,n +1);
    predecesor[pocatek] = pocatek; // pocatek už byl použit
    
    do 
    {
        // basecase
        if (newGenrationLeng == 0) return 1; // zadna cesta nevede do říma 
        
        if (next() == 1) return 0; // vsehno probehlo spatne
        
    } while (true); // dokud to neudelas nedostanes večeři
}


int next()
{
    egeing();
    newGenrationLeng = 0;
    for (long tmp = 0; tmp < oldgenerationLengh; tmp++)
    {
        long pocatek = oldgeneration[tmp];
        for (int i = 0; i < krizovatka[pocatek].Lengh; i++) // všechna krizivatky z aktualní pozice
        {
            long dalsi = krizovatka[pocatek].ulice[i]; 
           
            // ignoruj vymazane
            if (dalsi == 0 || predecesor[dalsi] != 0) continue; // nezajímej se o hodnoty 0 aka. ty které jsme vyřadily 
            
            // jednorozmerná cesta k počátku
            predecesor[dalsi] = pocatek;
            
            // basecase
            if (krizovatka[dalsi].IsOdd)
            {
                // uz není liche 
                krizovatka[dalsi].IsOdd = false;
    
                addToReturn(dalsi);
                return 1; // all have gone good 
            }
            newGenration[newGenrationLeng] = dalsi;
            newGenrationLeng++;
        }
    }
    return 0;
}

void addToReturn(long position)
{
    if (predecesor[position] == position) return;
   
    BigReturn[BigReturnLengh] = position;
    BigReturn[BigReturnLengh+ 1] = predecesor[position];
    BigReturnLengh += 2;
    
    // delite root
    dell(predecesor[position], position);
    dell(position, predecesor[position]);
    // tato operace je kontroverzní ??????? neměl bych raději ukládat číslo ulice v predesesor[2,] ???????
    
    addToReturn(predecesor[position]);
}

void egeing()
{
    for (int i = 0; i <= newGenrationLeng; i++)
    {
        oldgeneration[i] = newGenration[i];
    }
    oldgenerationLengh = newGenrationLeng;
}

void dell(long a, long b)
{
    for (int i = 0; i < krizovatka[a].Lengh; i++)
    {
        if(krizovatka[a].ulice[i] == b) krizovatka[a].ulice[i] = 0;
    }
}

void vynuluj(long *pole, long b)
{
    for (long i = 0; i < b; i++)
        {
            pole[i] = 0;
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
1 5

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


*/