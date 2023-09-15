
          #include <stdlib.h>
          #include <string.h>          
          #include "mpc_codegen.h"
          #include "mpc.h"

          typedef struct impact__pool {
            casadi_int n;
            casadi_int size;            
            const char** names; /* length n */
            const casadi_int* trajectory_length;  /*  length n */
            const casadi_int* part_offset;  /*  length n */
            const casadi_int* part_unit;  /*  length n a non-full may span multiple parts */
            const casadi_int* part_stride;  /*  length n a non-full may span multiple parts */
            casadi_real* data;
            casadi_int stride;
          } impact_pool;

          typedef void (*fatal_fp)(impact_struct* m, const char * loc, const char * fmt, ...);
          typedef void (*info_fp)(impact_struct* m, const char * fmt, ...);

          struct impact__struct {
            int id;
            int pop; /*  need to pop when destroyed? */
            casadi_int n_in;
            casadi_int n_out;

            casadi_int sz_arg;
            casadi_int sz_res;
            casadi_int sz_iw;
            casadi_int sz_w;

            const casadi_real** arg;
            casadi_real** res;
            casadi_int* iw;
            casadi_real* w;

            const casadi_real** arg_casadi;
            casadi_real** res_casadi;
            casadi_int* iw_casadi;
            casadi_real* w_casadi;

            impact_pool* x_current;

            impact_pool* x_initial_guess;
            impact_pool* z_initial_guess;
            impact_pool* u_initial_guess;
            impact_pool* v_initial_guess;
            impact_pool* p;


            impact_pool* x_opt;
            impact_pool* z_opt;
            impact_pool* u_opt;
            impact_pool* v_opt;

            casadi_real* hotstart_in;
            casadi_real* hotstart_out;

            int mem;

            formatter fp;
            fatal_fp fatal;
            info_fp info;
          };

          /* For printing */
          #include <stdio.h>
          #include <stdarg.h>
          static const casadi_int impact_p_offsets[3] = {0,4,8};
          static const casadi_int impact_x_part_offset[5] = {0,1,2,3,4};
          static const casadi_int impact_z_part_offset[1] = {0};
          static const casadi_int impact_u_part_offset[2] = {0,1};
          static const casadi_int impact_p_part_offset[3] = {0,4,8};
          static const casadi_int impact_v_part_offset[1] = {0};
          static const casadi_int impact_x_part_unit[4] = {1,1,1,1};
          static const casadi_int impact_z_part_unit[1];
          static const casadi_int impact_u_part_unit[1] = {1};
          static const casadi_int impact_p_part_unit[2] = {4,4};
          static const casadi_int impact_v_part_unit[1];
          static const casadi_int impact_x_part_stride[4] = {4,4,4,4};
          static const casadi_int impact_z_part_stride[1];
          static const casadi_int impact_u_part_stride[1] = {1};
          static const casadi_int impact_p_part_stride[2] = {4,4};
          static const casadi_int impact_v_part_stride[1];
          static const char* impact_x_names[4] = {"model_definition.pos","model_definition.theta","model_definition.dpos","model_definition.dtheta"};
          static const char* impact_z_names[1];
          static const char* impact_u_names[1] = {"model_definition.F"};
          static const char* impact_p_names[2] = {"x_current","x_final"};
          static const char* impact_v_names[1];
          static const casadi_int impact_x_trajectory_length[4] = {51,51,51,51};
          static const casadi_int impact_z_trajectory_length[1];
          static const casadi_int impact_u_trajectory_length[1] = {50};
          static const casadi_int impact_p_trajectory_length[2] = {1,1};
          static const casadi_int impact_v_trajectory_length[1];
          static const casadi_int impact_x_current_trajectory_length[4] = {1,1,1,1};
          static const casadi_real impact_x_nominal[204] = {0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000};
          static const casadi_real impact_z_nominal[1];
          static const casadi_real impact_u_nominal[50] = {0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000};
          static const casadi_real impact_p_nominal[8] = {0.500000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000};
          static const casadi_real impact_v_nominal[1];
          static const casadi_real impact_x_current_nominal[4] = {0.500000000000000000,0.000000000000000000,0.000000000000000000,0.000000000000000000};

          static const char* impact_pool_names[9] = { "x_initial_guess","z_initial_guess","u_initial_guess","v_initial_guess","p","x_opt","z_opt","u_opt","v_opt" };

          static const char* impact_flag_names[7] = { "ALL","EVERYWHERE","FULL","HREP","VREP","COLUMN_MAJOR","ROW_MAJOR" };
          static int impact_flag_values[7] = { IMPACT_ALL,IMPACT_EVERYWHERE,IMPACT_FULL,IMPACT_HREP,IMPACT_VREP,IMPACT_COLUMN_MAJOR,IMPACT_ROW_MAJOR };

          int impact_flag_size(impact_struct* m) {
            return 7;
          }
          const char* impact_flag_name(impact_struct* m, int index) {
            if (index<0 || index>=7) return 0;
            return impact_flag_names[index];
          }
          int impact_flag_value(impact_struct* m, int index) {
            if (index<0 || index>=7) return 0;
            return impact_flag_values[index];
          }



          void impact_fatal(impact_struct* m, const char* loc, const char* fmt, ...) {
            va_list args;
            char buffer[1024];
            if (m->fp) {
              va_start(args, fmt);
              if (loc) {
                sprintf(buffer, "Error in %s: ", loc);
                m->fp(buffer);
              }
              vsprintf(buffer, fmt, args);
              m->fp(buffer);
              va_end(args);
            }
          }
          void impact_info(impact_struct* m, const char* fmt, ...) {
            va_list args;
            char buffer[1024];
            if (m->fp) {
              va_start(args, fmt);
              vsprintf(buffer, fmt, args);
              m->fp(buffer);
              va_end(args);
            }
          }


          impact_struct* impact_initialize(formatter fp, const char* build_dir) {
            int flag;
            int i;
            impact_struct* m;
            char casadi_file[2048];
            m = malloc(sizeof(impact_struct));
            m->fp = fp;
            m->fatal = impact_fatal;
            m->info = impact_info;
            m->id = -1;
            /* Allocate memory (thread-safe) */
            ocpfun_incref();
            /* Checkout thread-local memory (not thread-safe) */
            m->mem = ocpfun_checkout();

            impact_work(m, &m->sz_arg, &m->sz_res, &m->sz_iw, &m->sz_w);
            impact_set_work(m,
              malloc(sizeof(const casadi_real*)*m->sz_arg),
              malloc(sizeof(casadi_real*)*m->sz_res),
              malloc(sizeof(casadi_int)*m->sz_iw),
              malloc(sizeof(casadi_real)*m->sz_w));

            m->arg_casadi = m->arg;
            m->res_casadi = m->res;
            m->iw_casadi = m->iw;
            m->w_casadi = m->w;

            m->p = malloc(sizeof(impact_pool));
            m->p->names = impact_p_names;
            m->p->size = 8;
            m->p->data = malloc(sizeof(casadi_real)*8);
            m->p->n = 2;
            m->p->trajectory_length = impact_p_trajectory_length;
            m->p->stride = -1;
            m->p->part_offset = impact_p_part_offset;
            m->p->part_unit = impact_p_part_unit;
            m->p->part_stride = impact_p_part_stride;

            m->x_current = malloc(sizeof(impact_pool));
            m->x_current->names = impact_x_names;
            m->x_current->size = 4;
            m->x_current->data = m->p->data+m->p->part_offset[0];
            m->x_current->n = 4;
            m->x_current->trajectory_length = impact_x_current_trajectory_length;
            m->x_current->stride = 4;
            m->x_current->part_offset = impact_x_part_offset;
            m->x_current->part_unit = impact_x_part_unit;
            m->x_current->part_stride = impact_x_part_stride;
      
            m->x_initial_guess = malloc(sizeof(impact_pool));
            m->x_initial_guess->names = impact_x_names;
            m->x_initial_guess->size = 204;
            m->x_initial_guess->data = malloc(sizeof(casadi_real)*204);
            m->x_initial_guess->n = 4;
            m->x_initial_guess->trajectory_length = impact_x_trajectory_length;
            m->x_initial_guess->stride = 4;
            m->x_initial_guess->part_offset = impact_x_part_offset;
            m->x_initial_guess->part_unit = impact_x_part_unit;
            m->x_initial_guess->part_stride = impact_x_part_stride;

            m->x_opt = malloc(sizeof(impact_pool));
            m->x_opt->names = impact_x_names;
            m->x_opt->size = 204;
            m->x_opt->data = malloc(sizeof(casadi_real)*204);
            m->x_opt->n = 4;
            m->x_opt->trajectory_length = impact_x_trajectory_length;
            m->x_opt->stride = 4;
            m->x_opt->part_offset = impact_x_part_offset;
            m->x_opt->part_unit = impact_x_part_unit;
            m->x_opt->part_stride = impact_x_part_stride;
            
            m->z_initial_guess = malloc(sizeof(impact_pool));
            m->z_initial_guess->names = impact_z_names;
            m->z_initial_guess->size = 0;
            m->z_initial_guess->data = malloc(sizeof(casadi_real)*1);
            m->z_initial_guess->n = 0;
            m->z_initial_guess->trajectory_length = impact_z_trajectory_length;
            m->z_initial_guess->stride = 0;
            m->z_initial_guess->part_offset = impact_z_part_offset;
            m->z_initial_guess->part_unit = impact_z_part_unit;
            m->z_initial_guess->part_stride = impact_z_part_stride;

            m->z_opt = malloc(sizeof(impact_pool));
            m->z_opt->names = impact_z_names;
            m->z_opt->size = 0;
            m->z_opt->data = malloc(sizeof(casadi_real)*1);
            m->z_opt->n = 0;
            m->z_opt->trajectory_length = impact_z_trajectory_length;
            m->z_opt->stride = 0;
            m->z_opt->part_offset = impact_z_part_offset;
            m->z_opt->part_unit = impact_z_part_unit;
            m->z_opt->part_stride = impact_z_part_stride;
            
            m->u_initial_guess = malloc(sizeof(impact_pool));
            m->u_initial_guess->names = impact_u_names;
            m->u_initial_guess->size = 50;
            m->u_initial_guess->data = malloc(sizeof(casadi_real)*50);
            m->u_initial_guess->n = 1;
            m->u_initial_guess->trajectory_length = impact_u_trajectory_length;
            m->u_initial_guess->stride = 1;
            m->u_initial_guess->part_offset = impact_u_part_offset;
            m->u_initial_guess->part_unit = impact_u_part_unit;
            m->u_initial_guess->part_stride = impact_u_part_stride;

            m->u_opt = malloc(sizeof(impact_pool));
            m->u_opt->names = impact_u_names;
            m->u_opt->size = 50;
            m->u_opt->data = malloc(sizeof(casadi_real)*50);
            m->u_opt->n = 1;
            m->u_opt->trajectory_length = impact_u_trajectory_length;
            m->u_opt->stride = 1;
            m->u_opt->part_offset = impact_u_part_offset;
            m->u_opt->part_unit = impact_u_part_unit;
            m->u_opt->part_stride = impact_u_part_stride;
            
            m->v_initial_guess = malloc(sizeof(impact_pool));
            m->v_initial_guess->names = impact_v_names;
            m->v_initial_guess->size = 0;
            m->v_initial_guess->data = malloc(sizeof(casadi_real)*1);
            m->v_initial_guess->n = 0;
            m->v_initial_guess->trajectory_length = impact_v_trajectory_length;
            m->v_initial_guess->stride = -1;
            m->v_initial_guess->part_offset = impact_v_part_offset;
            m->v_initial_guess->part_unit = impact_v_part_unit;
            m->v_initial_guess->part_stride = impact_v_part_stride;

            m->v_opt = malloc(sizeof(impact_pool));
            m->v_opt->names = impact_v_names;
            m->v_opt->size = 0;
            m->v_opt->data = malloc(sizeof(casadi_real)*1);
            m->v_opt->n = 0;
            m->v_opt->trajectory_length = impact_v_trajectory_length;
            m->v_opt->stride = -1;
            m->v_opt->part_offset = impact_v_part_offset;
            m->v_opt->part_unit = impact_v_part_unit;
            m->v_opt->part_stride = impact_v_part_stride;
            
            m->hotstart_in = malloc(sizeof(casadi_real)*1);
            m->hotstart_out = malloc(sizeof(casadi_real)*1);

            memcpy(m->p->data, impact_p_nominal, 8*sizeof(casadi_real));
            memcpy(m->x_opt->data, impact_x_nominal, 204*sizeof(casadi_real));
            memcpy(m->z_opt->data, impact_z_nominal, 0*sizeof(casadi_real));
            memcpy(m->u_opt->data, impact_u_nominal, 50*sizeof(casadi_real));
            memcpy(m->v_opt->data, impact_v_nominal, 0*sizeof(casadi_real));
            for (i=0;i<0;++i) m->hotstart_out[i] = 0.0;
            impact_freshstart(m);
            return m;
          }

          void impact_coldstart(impact_struct* m) {
            int i;
            for (i=0;i<0;++i) m->hotstart_in[i] = 0.0;
          }

          void impact_freshstart(impact_struct* m) {
            int i;
            memcpy(m->x_initial_guess->data, impact_x_nominal, 204*sizeof(casadi_real));
            memcpy(m->z_initial_guess->data, impact_z_nominal, 0*sizeof(casadi_real));
            memcpy(m->u_initial_guess->data, impact_u_nominal, 50*sizeof(casadi_real));
            memcpy(m->v_initial_guess->data, impact_v_nominal, 0*sizeof(casadi_real));
            for (i=0;i<0;++i) m->hotstart_in[i] = 0.0;
          }

          void impact_hotstart(impact_struct* m) {
            int i;
            memcpy(m->x_initial_guess->data, m->x_opt->data, 204*sizeof(casadi_real));
            memcpy(m->z_initial_guess->data, m->z_opt->data, 0*sizeof(casadi_real));
            memcpy(m->u_initial_guess->data, m->u_opt->data, 50*sizeof(casadi_real));
            memcpy(m->v_initial_guess->data, m->v_opt->data, 0*sizeof(casadi_real));
            memcpy(m->hotstart_in, m->hotstart_out, 0*sizeof(casadi_real));
          }

          void impact_destroy(impact_struct* m) {
            if (m) {
              /* Free memory (thread-safe) */
              ocpfun_decref();
              /* Release thread-local (not thread-safe) */
              ocpfun_release(m->mem);
              
              /*free(m->arg);
              free(m->res);
              free(m->iw);
              free(m->w);
              free(m->p->data);
              free(m->p);
              free(m->x_current);
              free(m->x_initial_guess->data);
              free(m->x_initial_guess);
              free(m->z_initial_guess->data);
              free(m->z_initial_guess);
              free(m->u_initial_guess->data);
              free(m->u_initial_guess);
              free(m->v_initial_guess->data);
              free(m->v_initial_guess);
              free(m->hotstart_in);
              free(m->hotstart_out);
              free(m->x_opt->data);
              free(m->x_opt);
              free(m->z_opt->data);
              free(m->z_opt);
              free(m->u_opt->data);
              free(m->u_opt);
              free(m->v_opt->data);
              free(m->v_opt);*/
              free(m);
            }
          }

          void impact_set_work(impact_struct* m, const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w) {
            m->arg = arg;
            m->res = res;
            m->iw = iw;
            m->w = w;
          }

          void impact_work(impact_struct* m, casadi_int* sz_arg, casadi_int* sz_res, casadi_int* sz_iw, casadi_int* sz_w) {
            ocpfun_work(sz_arg,sz_res,sz_iw,sz_w);
            /* We might want to be adding other working memory here */
          }

          const impact_pool* impact_get_pool_by_name(impact_struct* m, const char* name) {
            if (!strcmp(name,"p")) {
              return m->p;
            } else if (!strcmp(name,"x_current")) {
              return m->x_current;
            } else if (!strcmp(name,"x_initial_guess")) {
              return m->x_initial_guess;
            } else if (!strcmp(name,"z_initial_guess")) {
              return m->z_initial_guess;
            } else if (!strcmp(name,"u_initial_guess")) {
              return  m->u_initial_guess;
            } else if (!strcmp(name,"v_initial_guess")) {
              return  m->v_initial_guess;
            } else if (!strcmp(name,"x_opt")) {
              return m->x_opt;
            } else if (!strcmp(name,"z_opt")) {
              return m->z_opt;
            } else if (!strcmp(name,"u_opt")) {
              return  m->u_opt;
            } else if (!strcmp(name,"v_opt")) {
              return  m->v_opt;
            } else {
              m->fatal(m, "get_pool_by_name", "Pool with name '%s' not recognized.                                        Use one of: ['x_initial_guess', 'z_initial_guess', 'u_initial_guess', 'v_initial_guess', 'p', 'x_opt', 'z_opt', 'u_opt', 'v_opt']. \n", name);
              return 0;
            }
          }


          int impact_get_id_count(impact_struct* m, const char* pool) {
            const impact_pool* p;
            if (!pool) {
              m->fatal(m, "get_id_count (ret code -1)", "You may not pass a null pointer as pool. \n");
              return -1;
            }
            p = impact_get_pool_by_name(m, pool);
            if (!p) {
              m->fatal(m, "get_id_count (ret code -2)", "Failed to find a pool named '%s'. \n", pool);
              return -2;
            }
            return p->n;
          }

          int impact_get_id_from_index(impact_struct* m, const char* pool, int index, const char** id) {
            int i;
            const impact_pool* p;
            if (!pool) {
              m->fatal(m, "get_id_from_index (ret code -1)", "You may not pass a null pointer as pool. \n");
              return -1;
            }
            p = impact_get_pool_by_name(m, pool);
            if (!p) {
              m->fatal(m, "get_id_from_index (ret code -2)", "Failed to find a pool named '%s'. \n", pool);
              return -2;
            }
            if (index<0 || index>= p->n) {
              m->fatal(m, "get_id_from_index (ret code -3)", "Index %d is out of bounds for pool %s: need [0,%d[. \n", index, pool, p->n);
              return -3;
            }
            *id = p->names[index];

            return 0;
          }


          int impact_get_size(impact_struct* m, const char* pool, const char* id, int stage, int flags, int* n_row, int* n_col) {
            int index, i;
            const impact_pool* p;
            if (!pool) {
              m->fatal(m, "get_size (ret code -1)", "You may not pass a null pointer as pool. \n");
              return -1;
            }
            p = impact_get_pool_by_name(m, pool);
            if (!p) {
              m->fatal(m, "get_size (ret code -2)", "Failed to find a pool named '%s'. \n", pool);
              return -2;
            }

            /* Determine index */
            index = -1;
            if (id!=IMPACT_ALL) {
              for (i=0;i<p->n;++i) {
                if (!strcmp(id, p->names[i])) break;
              }
              if (i==p->n) {
                m->fatal(m, "get_id_from_index (ret code -4)", "Id '%s' not found for pool '%s'. Use one of these options: \n", id, pool);
                for (i=0;i<p->n;++i) {
                  m->fatal(m, 0, " - %s\n", p->names[i]);
                }
                return -4;
              }
              index = i;
            }

            if (index==-1) {
              if (p->stride>=0) {
                *n_row = p->stride;
                *n_col = p->trajectory_length[0];
              } else {
                *n_row = p->size;
                *n_col = 1;
              }
            } else {
              *n_row = p->part_unit[index];
              *n_col = p->trajectory_length[index];
            }

            if (stage!=IMPACT_EVERYWHERE) *n_col = 1;

            return 0;
          }

          int impact_get_nx() { return 4; }
          int impact_get_nz() { return 0; }
          int impact_get_nu() { return 1; }
          int impact_get_nv() { return 0; }

          int impact_set_get(impact_struct* m, const char* pool, const char* id, int stage, double* data, int data_flags, char mode) {
            int i, j, k, index, i_start, i_stop, k_start, k_stop, offset, row, col, stride, data_i;
            const impact_pool* p;
            if (!pool) {
              m->fatal(m, "set_get (ret code -1)", "You may not pass a null pointer as pool. \n");
              return -1;
            }
            if (!data) {
              m->fatal(m, "set_get (ret code -2)", "You may not pass a null pointer for src/dst. \n");
              return -2;
            }
            p = impact_get_pool_by_name(m, pool);
            if (!p) {
              m->fatal(m, "set_get (ret code -3)", "Failed to find a pool named '%s'. \n", pool);
              return -3;
            }

            /* Determine index */
            index = -1;
            if (id!=IMPACT_ALL) {
              for (i=0;i<p->n;++i) {
                if (!strcmp(id, p->names[i])) break;
              }
              if (i==p->n) {
                m->fatal(m, "set_get (ret code -4)", "Id '%s' not found for pool '%s'. Use one of these options: \n", id, pool);
                for (i=0;i<p->n;++i) {
                  m->fatal(m, 0, " - %s\n", p->names[i]);
                }
                return -4;
              }
              index = i;
            }

            i_start = index==-1? 0 : index;
            i_stop  = index==-1? p->n : index+1;
            k_start = stage==IMPACT_EVERYWHERE? 0 : stage;
            offset = 0;
            data_i = -1;
            for (i=i_start;i<i_stop;++i) {
              row = id==IMPACT_ALL ? p->part_offset[i] : 0;
              if (data_flags & IMPACT_ROW_MAJOR) {
                stride = p->trajectory_length[i];
              } else {
                stride = id==IMPACT_ALL ? p->part_stride[i] : p->part_unit[i];
              }
              for (j=0;j<p->part_unit[i];++j) {
                k_stop  = stage==IMPACT_EVERYWHERE? p->trajectory_length[i] : stage+1;
                for (k=k_start;k<k_stop;++k) {
                  col = (data_flags & IMPACT_HREP || stage!=IMPACT_EVERYWHERE) ? 0 : k;
                  data_i = data_flags & IMPACT_ROW_MAJOR ? stride*row + col : row + stride*col;
                  if (mode) {
                    data[data_i] = p->data[j+ p->part_offset[i] + p->part_stride[i]*k];
                  } else {
                    /* skip nan */
                    if (data[data_i]==data[data_i]) p->data[j+ p->part_offset[i] + p->part_stride[i]*k] = data[data_i];
                  }
                }
                row++;
              }
            }
            return data_i+1;
          }

          int impact_set(impact_struct* m, const char* pool, const char* id, int stage, const double* src, int src_flags) {
            return impact_set_get(m, pool, id, stage, (double*) src, src_flags, 0);
          }

          int impact_get(impact_struct* m, const char* pool, const char* id, int stage, double* dst, int dst_flags) {
            return impact_set_get(m, pool, id, stage, dst, dst_flags, 1);
          }

          int impact_get_pool(const impact_pool* p, casadi_real* value) {
            if (!value) return 1;
            memcpy(value, p->data, p->size*sizeof(casadi_real));
            return 0;
          }

          int impact_print_problem(impact_struct* m) {
            int i,j,k,l,max_len;
            char formatbuffer[10];
            const impact_pool* p;
            if (!m->fp) return 1;
            max_len=0;
            for (l=0;l<5;++l) {
              p = impact_get_pool_by_name(m, impact_pool_names[l]);
              for (i=0;i<p->n;++i) {
                max_len = strlen(p->names[i])>max_len? strlen(p->names[i]) : max_len;
              }
            }

            if (m->fp) {
              for (l=0;l<5;++l) {
                const impact_pool* p = impact_get_pool_by_name(m, impact_pool_names[l]);
                m->info(m, "=== %s ===\n", impact_pool_names[l]);
                sprintf(formatbuffer, "%%-%ds", max_len);
                for (i=0;i<p->n;++i) {
                  m->info(m, formatbuffer, p->names[i]);
                  m->info(m, ":");
                  for (j=0;j<p->part_unit[i];++j) {
                    if (j>0) {
                        m->info(m, formatbuffer, "");
                        m->info(m, " ");
                    }
                    for (k=0;k<p->trajectory_length[i];++k) {
                      m->info(m, " %.4e", p->data[j+ p->part_offset[i] + p->part_stride[i]*k]);
                    }
                    m->info(m, "\n");
                  }
                }
              }
            }
            return 0;
          }

          int impact_solve(impact_struct* m) {
            int i;
            m->arg_casadi[0] = m->x_initial_guess->data;
            m->arg_casadi[1] = m->z_initial_guess->data;
            m->arg_casadi[2] = m->u_initial_guess->data;
            m->arg_casadi[3] = m->v_initial_guess->data;
            for (i=0;i<2;i++) {
              m->arg_casadi[4+i] = m->p->data + impact_p_offsets[i];
            }
            m->arg_casadi[4+2] = m->hotstart_in;
            m->res_casadi[0] = m->x_opt->data;
            m->res_casadi[1] = m->z_opt->data;
            m->res_casadi[2] = m->u_opt->data;
            m->res_casadi[3] = m->v_opt->data;
            m->res_casadi[4] = m->hotstart_out;
            return ocpfun(m->arg_casadi,m->res_casadi,m->iw_casadi,m->w_casadi,m->mem);
          }

          int impact_get_p_by_id(impact_struct* m, const char* id, const casadi_real* value) {
            return 0;
          }

          void impact_get_u(impact_struct* m, double* value) {

          }

          const impact_stats* impact_get_stats(const impact_struct* m) {
            return ocpfun_stats();
          }

        