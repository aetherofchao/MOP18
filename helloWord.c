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
}


int main(void)
{
   
    // dostan rozměry
    long n, m, k;
    scanf("%i %i %i",&n, &m, &k);
    
    // declaruj proměné
    List krizovatka[++n];
    long zakazene[2*k + 1];
    long liche[++n], licheLengh = 0;
     
    // načti ulice 
    int tmp1, tmp2;
    for (int i = 1; i <= m; i++) // prjdi všechny řadky vztupu 
    {
        scanf("%i %i",&tmp1, &tmp2);
        krizovatka[tmp1].add(tmp2);  // z 1ho města do druhého 
        krizovatka[tmp2].add(tmp1);  // Z 2ho do 1ho
        
        if(--i < k) // potřebuju někat uložit které ul jsou zakazané zbořit
        {
            zakazene[2*i] = tmp1;
            zakazene[2*i +1] = tmp2;
        }
    }
    
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
    // nejsou-li zaden liché križovatky řešení je 0
    if (licheLengh == 0) return 0;
    
    // už víme kterých měst se snažíme zbavit --> lichost nemusíme už kontrolovat

    // ulice které nesmíme už použít budeme odstranovat (ty ktere mají být zbořenny starostou zaroven ukladat)
    for (int i = 0; i < k; i++)
    {
        // zboříme ty ulice u kterých je to zakazané jsem totiž rebel
        pop(zakazene[2*i], zakazane[2*i +1]);       
        // zakazané je uložené jako sude a liché 
    }
    
    // najdi vždy 2 nejbiší kriřovatky >>> inspirace Bellmann-Fordovým algoritmem (použití negativních ciklů je užitečné až v druhém příkladu)<<<
    
    for (long start = 0; start< licheLengh; start++)
    {
        long curent = liche[start];
        long predecesor[++n];
        
        // iniciuj predecesor jako prazdný
        for (long i = 1; i <= n; i++)
        {
            predecesor[i] == 0;
        }
        
        while(true /* dokud se nenajde další lichá ulice*/)
        {
                // TODO udelat metodu recursive algorithtm
               for (int i = 0; i < krizovatka[curent].Lengh; i++) // všechna krizivatky z aktualní pozice
               {
                   long dalsi = krizovatka[curent].ulice[i]; 
                   
                   // Basecase
                   if (dalsi == 0 || predecesor[dalsi] == 0) // nezajímej se o hodnoty 0 aka. ty které jsme vyřadily 
                   {
                       continue;
                   }
                   if (krizovatka[dalsi].IsOdd)
                   {
                       /*updatereturn*/
                   }
                   
                   // jednorozmerná cesta k počátku
                   predecesor[dalsi] = curent;
            
               }
        }
    }
}