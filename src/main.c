#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mpc_build_dir/mpc.h"
#include "input.h"

int main(void)
{
    /* Initialize IMPACT library */
    impact_struct* m = impact_initialize(printf, 0);
    if (!m) {
        printf("Failed to initialize\n");
        return -1;
    }

    /* Get size of state variable x */
    int x_row, x_col;
    impact_get_size(m, "x_current", IMPACT_ALL, IMPACT_EVERYWHERE, IMPACT_FULL, &x_row, &x_col);
    if (x_row*x_col != INPUT_COLS) {
        printf("Input format invalid.\n");
        return -1;
    }

    /* Allocate space for u_opt */
    int u_row, u_col;
    impact_get_size(m, "u_opt", IMPACT_ALL, 0, IMPACT_FULL, &u_row, &u_col);
    double* u_opt = malloc(sizeof(double)*u_row*u_col);

    double x_current[x_row*x_col];
    for (int i = 0; i < INPUT_ROWS; i++)
    {

        /** Set current state
         * id: IMPACT_ALL --> set all state variables
         * stage: IMPACT_EVERYWHERE --> set at all time instants
         * source: x_current --> set current state to value of x_current
         * flags: IMPACT_FULL --> not clear what this does?
        */
        for (int j = 0; j < INPUT_COLS; j++)
        {
            x_current[j] = INPUT[i][j];
        }
        impact_set(m, "x_current", IMPACT_ALL, IMPACT_EVERYWHERE, x_current, IMPACT_FULL);

        /** Solve */
        impact_solve(m);

        /** Get optimal control input
         * id: IMPACT_ALL --> get all control inputs
         * stage: 0 --> get at first time instant
         * dst: u_opt --> store value in u_opt
         * flags: IMPACT_FULL --> not clear what this does?
        */
        impact_get(m, "u_opt", IMPACT_ALL, 0, u_opt, IMPACT_FULL);

        /* Print current state and optimal control input */
        #ifdef PRINT_OUTPUT
        printf("x_current = [");
        for (int i = 0; i < x_row*x_col; i++) {
            printf("%+6.5e", x_current[i]);
            if (i < x_row*x_col-1) {
                printf(",");
            }
        }
        printf("]; ");
        printf("u_opt = [");
        for (int i = 0; i < u_row*u_col; i++) {
            printf("%+6.5e", u_opt[i]);
            if (i < u_row*u_col-1) {
                printf(",");
            }
        }
        printf("]\n");
        #endif
    }

    /* Clean up */
    free(u_opt);
    impact_destroy(m);

    return 0;
}
