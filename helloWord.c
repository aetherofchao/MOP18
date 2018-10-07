#include <stdio.h>

struct List // jelikož nezname "velikost" křižovatky a nemůžeme si dovolit 10^12 ~ terabyte paměrti. primitivní verze listu 
{
    int resize = 3;
    long Size = 6; //je průměrná velikost listu 
    long ulice = malloc(sizeof(long)*Size); 
    long Lengh = 0; // ukazatel posledního zapsaného věci
    
    int add(long addition)
    {
        // basecase
        if (++Lengh == Size) // 
        {   
            Size *= resize;
            ulice = (long*)relloc(ulice, sizeof(long)*Size);
        }
        
        // add
        ulice[Lengh] = addition;
        Lengh++;
        return 0;
    }
    bool IsOdd;
}


// declare all global variables
int pop(long a, long b);
int load();
int lichost();
int next(long pocatek, long b);

long n, m, k;
List krizovatka[++n];
long Temp[n], tempLeng = 0;
long liche[++n], licheLengh = 0;
long predecesor[++n];


//  >>>>> Maaaain <<<<<
int main(void)
{
   
    // dostan rozměry
    scanf("%i %i %i",&n, &m, &k);
    
    load();
    
    lichost(); 
    // už víme kterých měst se snažíme zbavit --> lichost nemusíme už kontrolovat
    
    // nejsou-li zaden liché križovatky řešení je 0
    if (licheLengh == 0) return 0;

    // ulice které nesmíme už použít budeme odstranovat (ty ktere mají být zbořenny starostou zaroven ukladat)
    for (int i = 0; i < k; i++)
    {
        // zboříme ty ulice u kterých je to zakazané jsem totiž rebel
        pop(Temp[2*i], zakazane[2*i +1]);       
        // zakazané je uložené jako sude a liché 
    }
    
    // najdi vždy 2 nejbiší kriřovatky >>> inspirace Bellmann-Fordovým algoritmem (použití negativních ciklů je užitečné až v druhém příkladu)<<<
    
    for (long lichePocatek = 0; lichePocatek< licheLengh; lichePocatek++)
    {
        spojL(liche[lichePocatek]);
        

    }
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
          if (dalsi == 0 || predecesor[dalsi] != 0) // nezajímej se o hodnoty 0 aka. ty které jsme vyřadily 
          {
              continue;
          }
          
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


int pop(long a, long b)
{
    for (int i = 0; i < krizovatka[a].Lengh; i++)
    {
        if (krizovatka[a].ulice[i] == b) {
            krizovatka[a].ulice[i] == 0;
            break;
        }
    }
    for (int i = 0; i < krizovatka[b].Lengh; i++)
    {
        if (krizovatka[b].ulice[i] == a) {
            krizovatka[b].ulice[i] == 0;
            break;
        }
    }
    return 0; // all is good
}

int load()
{
    // načti ulice 
    int tmp1, tmp2;
    for (int i = 1; i <= m; i++) // prjdi všechny řadky vztupu 
    {
        scanf("%i %i",&tmp1, &tmp2);
        krizovatka[tmp1].add(tmp2);  // z 1ho města do druhého 
        krizovatka[tmp2].add(tmp1);  // Z 2ho do 1ho
        
        if(--i < k) // potřebuju někat uložit které ul jsou zakazané zbořit
        {
            Temp[2*i] = tmp1;
            Temp[2*i +1] = tmp2;
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