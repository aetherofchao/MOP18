#include <stdio.h>

struct List{
    long Size;
    long ulice[5]; 
    long Lengh; // ukazatel posledního zapsaného věci
    bool IsOdd;
};


// declare all global variables
// int pop(long a, long b);
int load();
int lichost();
int next(long pocatek, long b);
int addition(struct krizovatka ulice, long addition);

long n, m, k;
struct List *krizovatka;
long *Temp; long tempLeng = 0;
long *liche; long licheLengh = 0;
long *predecesor;


//  >>>>> Maaaain <<<<<
int main(void)
{
    // dostan rozměry
    scanf("%ld %ld %ld",&n, &m, &k);
    
    krizovatka = (struct List *)malloc( ++n);
    for (int i = 0; i <= n; i++)
    {
        krizovatka[i].Lengh = 0;
    }
    Temp = (long *)malloc(n);
    liche = (long *)malloc( ++n);
    predecesor =(long *)malloc( ++n);
    
    load();
    
    lichost(); 
    // už víme kterých měst se snažíme zbavit --> lichost nemusíme už kontrolovat
    
    // nejsou-li zaden liché križovatky řešení je 0
    if (licheLengh == 0) return 0;

    // najdi vždy 2 nejbiší kriřovatky >>> inspirace Bellmann-Fordovým algoritmem (použití negativních ciklů je užitečné až v druhém příkladu)<<<
    for (long lichePocatek = 0; lichePocatek< licheLengh; lichePocatek++)
    {
        spojL(liche[lichePocatek]);
    }
}

int add(struct krizovatka node, long addition)
{ 
    // basecase
    if (++node.Lengh == node.Size) // 
    {   
        node.Size *= node.times;
        node.ulice = (long*)relloc(node.ulice,node.Size);
    }
    
    // add
    node.ulice[node.Lengh] = addition;
    node.Lengh++;
    return 0;
}
int spojL(long pocatek)
{
    vynuluj(predecesor, ++n);
    while (true)
    {
        // basecase
        if (tempLeng == 0) return 1; // zadna cesta nevede do říma
        
        vynuluj(Temp,n);
        tempLeng = 0;
        
        for ( int i = 0; i < tempLeng; i++)
        {
            if (next(Temp[i]) == 0) return 0;
        }
    }
}


int next(long pocatek)
{
    for (int i = 0; i < krizovatka[pocatek].Lengh; i++) // všechna krizivatky z aktualní pozice
    {
        long dalsi = krizovatka[pocatek].ulice[i]; 
        
        // ignoruj vymazane
        if (dalsi == 0 || predecesor[dalsi] != 0) continue; // nezajímej se o hodnoty 0 aka. ty které jsme vyřadily 
        
        // basecase
        if (krizovatka[dalsi].IsOdd)
        {
            // TODO 
            //  - zahrn cestu k dalsi ve Return
            //  - odstran cestu 
            //  - should be function
              
            return 0; // all have gone good 
        }
        
        // jednorozmerná cesta k počátku
        predecesor[dalsi] = pocatek;
        Temp[tempLeng] = dalsi;
        tempLeng++;
    }
}

int vunuluj(long *pole, long b)
{
    for (long i = 0; i < b; i++)
        {
            pole[i] == 0;
        }
}

int load()
{
    // načti ulice 
    int tmp1, tmp2;
    for (int i = 1; i <= m; i++) // projdi všechny řadky vztupu 
    {
        scanf("%i %i",&tmp1, &tmp2);
        if(--i < k) // potřebuju někat uložit které ul jsou zakazané zbořit
        {
            krizovatka[tmp1].add(0);  // potřebujeme abycho mohly stale urcit lichost ale nedostali se z tmp1 do tmp2
            krizovatka[tmp2].add(0); 
        }
        else
        {
            krizovatka[tmp1].add(tmp2);  // z 1ho města do druhého 
            krizovatka[tmp2].add(tmp1);  // Z 2ho do 1ho
        }
    }
    return 0;
}    

int lichost()
{
    // urči liché 
    // lichost můžeme kontrolovat až po načtení 
    for (int i = 1; i <= n; i++)
    {
        if (krizovatka[i].Lengh %2 != 0) 
        {
            krizovatka[i].IsOdd = true;
            liche[licheLengh] = --i;
            licheLengh++;
        }
        else krizovatka[i].IsOdd = false;
    }
    return 0;
}