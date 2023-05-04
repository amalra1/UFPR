#include <stdio.h>
#include <stdlib.h>
#include "lp_solve_5.5/lp_lib.h"


int main () 
{
    lprec *lp;
    
    /* Read LP model */
    lp = read_LP("model.lp", NORMAL, "test model");
    
    if (lp == NULL)
    {
        fprintf(stderr, "Unable to read model\n");
        return(1);
    }

  delete_lp(lp);

    return 0;
}

