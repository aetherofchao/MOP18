#include <stdio.h>

struct List
{
    int resize = 10;
    long leng = 5   //je průměrná velikost listu 
    long pole = malloc(sizeof(long)*leng); 
    long count = 0; // ukazatel posledního zapsaného věci
    
    int add(long addition)
    {
        // basecase
        if (count == leng) // 
        {   
            leng *= resize;
            pole = (long*)relloc(pole, sizeof(long)*leng);
        }
        
        // add
        count++;
        pole[count] = addition;
        return 0;
    }
    bool IsOdd;
}

int pop(long a, long b)
{
    mesto[a].pole[b] = NULL; // vimaž cestu od 1 do 2 města a opačně
    mesto[b].pole[a] = NULL; // je Null povole pro long?
}

int main(void)
{
   
    // dostan rozměry
    long n, m, k;
    scanf("%i %i %i",&n, &m, &k);
    
    // declaruj proměné
    List mesto[n];
    long zakazene[2*k];
    long liche[n], licheCount = 0;
     
    // načti pole 
    int tmp1, tmp2;
    for (int i = 0, j = 0; i < m; i++) // prjdi všechny řadky vztupu 
    {
        scanf("%i %i",&tmp1, &tmp2);
        mesto[tmp1].add(tmp2);  // z 1ho města do druhého 
        mesto[tmp2].add(tmp1);  // Z 2ho do 1ho
        
        if(j < k) // potřebuju někat uložit které ul jsou zakazané zbořit
        {
            zakazene[2*j] = tmp1;
            zakazene[2*j +1] = tmp2;
        }
    }
    
    // urči liché 
    // lichost můžeme kontrolovat až po načtení 
    for (int i = 0; i < m; i++)
    {
        if (mesto[i].count %2 != 0) 
        {
            mesto[i].IsOdd = true;
            liche[licheCount] = i;
            licheCount++;
        }
        else mesto[i].IsOdd = false;
    } 
    // už víme kterých měst se snažíme zbavit --> lichost nemusíme už kontrolovat

    // ulice které nesmíme už použít budeme odstranovat (ty ktere mají být zbořenny starostou zaroven ukladat)
    for (int i = 0; i < k; i++)
    {
        // zboříme ty ulice u kterých je to zakazané jsem totiž rebel
        pop(zakazene[2*k], zakazane[2*k +1]);       
        // zakazané je uložené jako sude a liché 
    }
    
    // najdi vždy 2 nejbiší kriřovatky >>> inspirace Bellmann-Fordovým algoritmem (použití negativních ciklů je užitečné až v druhém příkladu)<<<
    
    for (int start = 0; start< licheCount; start++)
    {
        long pouzite[n], pouziteCount = 0;
        long predecesors[n], predecesorsCount = 0;
        
        while(true /* dokud se nenajde další lichá ulice*/)
        {
            
        }
        
    }
    
    
    
    
}