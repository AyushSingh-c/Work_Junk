#include "Headers/Logic.h"

#define FAST ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define subt cerr << "Time : " << 1000 * ((double)clock()) / (double)CLOCKS_PER_SEC << "ms\n" 

int main() 
{
    FAST;
    
	Logic *solver = new Logic(16);
    (*solver).Run();

    subt;       
    return 0;
}
