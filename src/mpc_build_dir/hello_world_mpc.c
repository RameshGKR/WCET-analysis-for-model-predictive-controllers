
        #include <mpc.h>
        #include <stdio.h>
        #include <stdlib.h>
        #include <assert.h>

        int main() {
          int i, j, n_row, n_col, flag;
          double *u_scratch, *x_scratch;
          impact_struct* m = impact_initialize(printf, 0);
          if (!m) {
            printf("Failed to initialize\n");
            return 1;
          }
      
          /* Example: how to set a parameter */
          double val_x_final[4] = {0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000};
          impact_set(m, "p", "x_final", IMPACT_EVERYWHERE, val_x_final, IMPACT_FULL);

        
          double x0[4] = { 0.5000000000000000,0.0000000000000000,0.0000000000000000,0.0000000000000000 };

          impact_set(m, "x_current", IMPACT_ALL, IMPACT_EVERYWHERE, x0, IMPACT_FULL);

          double num = 0.5000000000000000;

          impact_set(m, "x_current", "model_definition.pos", IMPACT_EVERYWHERE, &num, IMPACT_FULL);

          impact_print_problem(m);


          printf("Start a solve.\n");
          flag = impact_solve(m);
          if (flag) {
            printf("Solve indicates a problem: return code %d.\n", flag);
          }
          printf("Solve finished.\n");

          const impact_stats* stats = impact_get_stats(m);
          if (stats) {
            printf("Number of outer iterations: %d\n", stats->n_sqp_iter);
            printf("Stop criterion: %d\n", stats->sqp_stop_crit);
            printf("Runtime [s]: %e\n", stats->runtime);
          } else {
            printf("No stats available.\n");
          }

          impact_print_problem(m);

          impact_hotstart(m);

          impact_print_problem(m);

          impact_solve(m);

          /* Allocate scratch space for state and control trajectories */
          impact_get_size(m, "u_opt", IMPACT_ALL, IMPACT_EVERYWHERE, IMPACT_FULL, &n_row, &n_col);
          printf("u_opt dims: %d - %d\n", n_row, n_col);
          /* u_scratch = malloc(sizeof(double)*n_row*n_col); */
          u_scratch = malloc(sizeof(double)*n_row);

          impact_get_size(m, "x_opt", IMPACT_ALL, IMPACT_EVERYWHERE, IMPACT_FULL, &n_row, &n_col);
          printf("x_opt dims: %d - %d\n", n_row, n_col);
          x_scratch = malloc(sizeof(double)*n_row*n_col);

          printf("Single OCP\n");

          impact_get(m, "x_opt", IMPACT_ALL, IMPACT_EVERYWHERE, x_scratch, IMPACT_FULL);
          for (i=0;i<n_col;++i) {
            for (j=0;j<n_row;++j) {
              printf("%0.3e ", x_scratch[i*n_row+j]);
            }
            printf("\n");
          }

          free(x_scratch);

          x_scratch = malloc(sizeof(double)*n_row);

          printf("Simulated MPC\n");
  
          for (i=0;i<100;++i) {
            impact_solve(m);
            impact_get(m, "u_opt", IMPACT_ALL, 0, u_scratch, IMPACT_FULL);
            impact_get(m, "x_opt", IMPACT_ALL, 1, x_scratch, IMPACT_FULL);
            impact_set(m, "x_current", IMPACT_ALL, 0, x_scratch, IMPACT_FULL);

            for (j=0;j<n_row;++j) {
              printf("%0.3e ", x_scratch[j]);
            }
            printf("\n");

          }
          free(u_scratch);
          free(x_scratch);

          impact_destroy(m);
        }
      