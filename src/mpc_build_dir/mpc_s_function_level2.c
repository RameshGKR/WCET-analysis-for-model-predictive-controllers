
        #define S_FUNCTION_NAME mpc_s_function_level2
        #define S_FUNCTION_LEVEL 2

        #include <mpc.h>

        #include "simstruc.h"

        static impact_struct* m;
        struct {
          int sz_arg;
          int n_p;
        } config;

        typedef struct {
  int32_T sqp_stop_crit;
  int32_T n_sqp_iter;
  int32_T n_ls;
  int32_T n_max_ls;
  int32_T n_qp_iter;
  int32_T n_max_qp_iter;
  double runtime;
}solver_stats_bus;

        void cleanup() {
          if (m) {
            impact_destroy(m);
          }
        }

        static void mdlInitializeSizes(SimStruct *S) {
#ifdef MATLAB_MEX_FILE
            mexPrintf("mdlInitializeSizes\n");
#endif
            int i;
            int n_row, n_col;
            const char* id;
            casadi_int sz_arg, sz_res, sz_iw, sz_w;
            m = 0;

            /* Simulink does not provide a cleanup-hook when parameters are changed */
            cleanup();

#ifdef MATLAB_MEX_FILE
            m = impact_initialize(mexPrintf, 0);
#else
            m = impact_initialize(0, 0);
#endif
            if (!m) {
              cleanup();
#ifdef MATLAB_MEX_FILE
              mexErrMsgIdAndTxt( "MATLAB:s_function:invalidParameter",
                                "Failed to initialize.");
#else
              return;
#endif           
            }
            impact_print_problem(m);

            /* Read work vector requirements */
            impact_work(m, &sz_arg, &sz_res, &sz_iw, &sz_w);

            /* Set up CasADi function work vector sizes */
            ssSetNumRWork(S, sz_w);
            ssSetNumIWork(S, sz_iw*sizeof(casadi_int)/sizeof(int_T));
            ssSetNumPWork(S, sz_arg+sz_res);

            int n_p = impact_get_id_count(m, "p");
            if (!ssSetNumInputPorts(S, n_p+2+1)) return;
            if (n_p<0) {
              cleanup();
#ifdef MATLAB_MEX_FILE
              mexErrMsgIdAndTxt( "MATLAB:s_function:invalidParameter",
                                "Failure.");
#else
              return;
#endif            
            }
            for (i=0;i<n_p;++i) {
              impact_get_id_from_index(m, "p", i, &id);
              impact_get_size(m, "p", id, IMPACT_EVERYWHERE, IMPACT_FULL, &n_row, &n_col);
              ssSetInputPortDirectFeedThrough(S, i, 1);
              ssSetInputPortMatrixDimensions(S, i, n_row, n_col);
              ssSetInputPortRequiredContiguous(S, i, 1);
            }

            impact_get_size(m, "x_initial_guess", IMPACT_ALL, IMPACT_EVERYWHERE, IMPACT_FULL, &n_row, &n_col);
            ssSetInputPortDirectFeedThrough(S, i, 1);
            ssSetInputPortMatrixDimensions(S, i, n_row, n_col);
            ssSetInputPortRequiredContiguous(S, i, 1);
            i++;
            impact_get_size(m, "u_initial_guess", IMPACT_ALL, IMPACT_EVERYWHERE, IMPACT_FULL, &n_row, &n_col);
            ssSetInputPortDirectFeedThrough(S, i, 1);
            ssSetInputPortMatrixDimensions(S, i, n_row, n_col);
            ssSetInputPortRequiredContiguous(S, i, 1);
            i++;
            
            // Port
            ssSetInputPortDirectFeedThrough(S, i, 1);
            ssSetInputPortMatrixDimensions(S, i, 1, 1);
            ssSetInputPortRequiredContiguous(S, i, 1);
            i++;

            if (!ssSetNumOutputPorts(S, 3)) return;

            i = 0;
            impact_get_size(m, "x_opt", IMPACT_ALL, IMPACT_EVERYWHERE, IMPACT_FULL, &n_row, &n_col);
            ssSetOutputPortMatrixDimensions(S, i, n_row, 1);
            i++;
            impact_get_size(m, "u_opt", IMPACT_ALL, IMPACT_EVERYWHERE, IMPACT_FULL, &n_row, &n_col);
            ssSetOutputPortMatrixDimensions(S, i, n_row, 1);
            i++;

#if MATLAB_MEX_FILE
            if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
                DTypeId tid;
                ssRegisterTypeFromNamedObject(S, "solver_stats_bus", &tid)
                if (tid==INVALID_DTYPE_ID) {
                  mexErrMsgIdAndTxt( "MATLAB:s_function:invalidParameter",
                                    "Could not find solver_stats_bus data_type.");
                }
                ssSetOutputPortDataType(S, i, tid);
            }
#endif  
            ssSetOutputPortWidth(S, i, 1);
            ssSetOutputPortBusMode(S, i, SL_BUS_MODE);
            ssSetBusOutputObjectName(S, i, (void *) "solver_stats_bus");
            ssSetBusOutputAsStruct(S, i, 1);
            i++;

            ssSetNumSampleTimes(S, 1);
            
            ssSetNumNonsampledZCs(S, 0);

            /* specify the sim state compliance to be same as a built-in block */
            ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

            /* Make sure mdlTerminate is called on error */
            ssSetOptions(S,
                        SS_OPTION_EXCEPTION_FREE_CODE |
                        SS_OPTION_USE_TLC_WITH_ACCELERATOR);
        }

        /* Function: mdlInitializeSampleTimes =========================================
        * Abstract:
        *    Specifiy that we inherit our sample time from the driving block.
        */
        static void mdlInitializeSampleTimes(SimStruct *S)
        {
#ifdef MATLAB_MEX_FILE
            mexPrintf("mdlInitializeSampleTimes\n");
#endif
            ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
            ssSetOffsetTime(S, 0, 0.0);
            ssSetModelReferenceSampleTimeDefaultInheritance(S); 
        }

        static void mdlOutputs(SimStruct *S, int_T tid)
        {
            if (!m) {
#ifdef MATLAB_MEX_FILE
              mexPrintf("mdlOutputs (nullptr)\n");
#endif
              return;
            }
            void** p;
            const real_T** arg;
            double* w;
            casadi_int* iw;
            int_T i;
            const char* id;
            
#ifdef MATLAB_MEX_FILE
            mexPrintf("mdlOutputs %p\n", m);
#endif
            /* Set up CasADi function work vectors */
            p = ssGetPWork(S);
            arg = (const real_T**) p;
            p += config.sz_arg;
            real_T** res = (real_T**) p;
            w = ssGetRWork(S);
            iw = (casadi_int*) ssGetIWork(S);

            impact_set_work(m, arg, res, iw, w);
            
            /* Point to input and output buffers */
            int n_p = impact_get_id_count(m, "p"); 
            for (i=0; i<n_p;++i) {
              impact_get_id_from_index(m, "p", i, &id);
              impact_set(m, "p", id, IMPACT_EVERYWHERE, ssGetInputPortSignal(S,i), IMPACT_FULL);
            }
            i = n_p;
            impact_set(m, "x_initial_guess", IMPACT_ALL, IMPACT_EVERYWHERE, ssGetInputPortSignal(S,i++), IMPACT_FULL);
            impact_set(m, "u_initial_guess", IMPACT_ALL, IMPACT_EVERYWHERE, ssGetInputPortSignal(S,i++), IMPACT_FULL);
            
            const real_T* hotstart_ptr = ssGetInputPortSignal(S,i++);
            real_T hotstart = *hotstart_ptr;

            if (hotstart==1.0) {
              impact_hotstart(m);
            } else if (hotstart==-1.0) {
              impact_freshstart(m);
            } else if (hotstart==0.0) {
              impact_coldstart(m);
            }

            int_T ret = impact_solve(m);
            impact_print_problem(m);
            if (ret && 1) {
                static char msg[221];
                sprintf(msg, "SFunction 'mpc_s_function_level2' failed to compute (error code %d) at t=%.6fs. "
                "Export with ('ignore_errors', true) if you want the simulation to continue anyway.", ret, ssGetT(S));
                #ifdef ssSetLocalErrorStatus
                  ssSetLocalErrorStatus(S, msg);
                #else
                  #ifdef ssSetErrorStatus
                    ssSetErrorStatus(S, msg);
                  #endif
                #endif
            }

            i = 0;
            impact_get(m, "x_opt", IMPACT_ALL, 1, ssGetOutputPortRealSignal(S, i++), IMPACT_FULL);
            impact_get(m, "u_opt", IMPACT_ALL, 0, ssGetOutputPortRealSignal(S, i++), IMPACT_FULL);

            

          solver_stats_bus* stats = (solver_stats_bus*) ssGetOutputPortRealSignal(S, i++);
          const impact_stats* s = impact_get_stats(m);
                stats->sqp_stop_crit = s ? s->sqp_stop_crit : 0;
          stats->n_sqp_iter = s ? s->n_sqp_iter : 0;
          stats->n_ls = s ? s->n_ls : 0;
          stats->n_max_ls = s ? s->n_max_ls : 0;
          stats->n_qp_iter = s ? s->n_qp_iter : 0;
          stats->n_max_qp_iter = s ? s->n_max_qp_iter : 0;
          stats->runtime = s ? s->runtime : 0;


        }

        static void mdlStart(SimStruct *S) {
#ifdef  MATLAB_MEX_FILE
          mexPrintf("mdlStart\n");
#endif
        }

        static void mdlTerminate(SimStruct *S) {
#ifdef  MATLAB_MEX_FILE
          mexPrintf("mdlTerminate\n");
#endif
          cleanup();
        }


        #ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
        #include "simulink.c"      /* MEX-file interface mechanism */
        #else
        #include "cg_sfun.h"       /* Code generation registration function */
        #endif
        