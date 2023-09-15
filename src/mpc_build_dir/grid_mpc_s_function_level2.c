
        #define S_FUNCTION_NAME grid_mpc_s_function_level2
        #define S_FUNCTION_LEVEL 2

        #include "simstruc.h"
        /* How to prefix internal symbols */
#ifdef CASADI_CODEGEN_PREFIX
  #define CASADI_NAMESPACE_CONCAT(NS, ID) _CASADI_NAMESPACE_CONCAT(NS, ID)
  #define _CASADI_NAMESPACE_CONCAT(NS, ID) NS ## ID
  #define CASADI_PREFIX(ID) CASADI_NAMESPACE_CONCAT(CODEGEN_PREFIX, ID)
#else
  #define CASADI_PREFIX(ID) grid_mpc_ ## ID
#endif

#include <math.h>

#ifndef casadi_real
#define casadi_real real_T
#endif

#ifndef casadi_int
#define casadi_int int_T
#endif

/* Add prefix to internal symbols */
#define casadi_f0 CASADI_PREFIX(f0)
#define casadi_s0 CASADI_PREFIX(s0)
#define casadi_s1 CASADI_PREFIX(s1)

/* Symbol visibility in DLLs */
#ifndef CASADI_SYMBOL_EXPORT
  #if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
    #if defined(STATIC_LINKED)
      #define CASADI_SYMBOL_EXPORT
    #else
      #define CASADI_SYMBOL_EXPORT __declspec(dllexport)
    #endif
  #elif defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
    #define CASADI_SYMBOL_EXPORT __attribute__ ((visibility ("default")))
  #else
    #define CASADI_SYMBOL_EXPORT
  #endif
#endif

static const casadi_int casadi_s0[8] = {4, 1, 0, 4, 0, 1, 2, 3};
static const casadi_int casadi_s1[105] = {1, 51, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* grid_mpc:(x_current[4],x_final[4])->(grid[1x51]) */
static int casadi_f0(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem) {
  casadi_real w0;
  /* #0: @0 = 0 */
  w0 = 0.;
  /* #1: output[0][0] = @0 */
  if (res[0]) res[0][0] = w0;
  /* #2: @0 = 0.04 */
  w0 = 4.0000000000000001e-02;
  /* #3: output[0][1] = @0 */
  if (res[0]) res[0][1] = w0;
  /* #4: @0 = 0.08 */
  w0 = 8.0000000000000002e-02;
  /* #5: output[0][2] = @0 */
  if (res[0]) res[0][2] = w0;
  /* #6: @0 = 0.12 */
  w0 = 1.2000000000000000e-01;
  /* #7: output[0][3] = @0 */
  if (res[0]) res[0][3] = w0;
  /* #8: @0 = 0.16 */
  w0 = 1.6000000000000000e-01;
  /* #9: output[0][4] = @0 */
  if (res[0]) res[0][4] = w0;
  /* #10: @0 = 0.2 */
  w0 = 2.0000000000000001e-01;
  /* #11: output[0][5] = @0 */
  if (res[0]) res[0][5] = w0;
  /* #12: @0 = 0.24 */
  w0 = 2.3999999999999999e-01;
  /* #13: output[0][6] = @0 */
  if (res[0]) res[0][6] = w0;
  /* #14: @0 = 0.28 */
  w0 = 2.8000000000000003e-01;
  /* #15: output[0][7] = @0 */
  if (res[0]) res[0][7] = w0;
  /* #16: @0 = 0.32 */
  w0 = 3.2000000000000001e-01;
  /* #17: output[0][8] = @0 */
  if (res[0]) res[0][8] = w0;
  /* #18: @0 = 0.36 */
  w0 = 3.5999999999999999e-01;
  /* #19: output[0][9] = @0 */
  if (res[0]) res[0][9] = w0;
  /* #20: @0 = 0.4 */
  w0 = 4.0000000000000002e-01;
  /* #21: output[0][10] = @0 */
  if (res[0]) res[0][10] = w0;
  /* #22: @0 = 0.44 */
  w0 = 4.4000000000000000e-01;
  /* #23: output[0][11] = @0 */
  if (res[0]) res[0][11] = w0;
  /* #24: @0 = 0.48 */
  w0 = 4.7999999999999998e-01;
  /* #25: output[0][12] = @0 */
  if (res[0]) res[0][12] = w0;
  /* #26: @0 = 0.52 */
  w0 = 5.2000000000000002e-01;
  /* #27: output[0][13] = @0 */
  if (res[0]) res[0][13] = w0;
  /* #28: @0 = 0.56 */
  w0 = 5.6000000000000005e-01;
  /* #29: output[0][14] = @0 */
  if (res[0]) res[0][14] = w0;
  /* #30: @0 = 0.6 */
  w0 = 5.9999999999999998e-01;
  /* #31: output[0][15] = @0 */
  if (res[0]) res[0][15] = w0;
  /* #32: @0 = 0.64 */
  w0 = 6.4000000000000001e-01;
  /* #33: output[0][16] = @0 */
  if (res[0]) res[0][16] = w0;
  /* #34: @0 = 0.68 */
  w0 = 6.8000000000000005e-01;
  /* #35: output[0][17] = @0 */
  if (res[0]) res[0][17] = w0;
  /* #36: @0 = 0.72 */
  w0 = 7.1999999999999997e-01;
  /* #37: output[0][18] = @0 */
  if (res[0]) res[0][18] = w0;
  /* #38: @0 = 0.76 */
  w0 = 7.6000000000000001e-01;
  /* #39: output[0][19] = @0 */
  if (res[0]) res[0][19] = w0;
  /* #40: @0 = 0.8 */
  w0 = 8.0000000000000004e-01;
  /* #41: output[0][20] = @0 */
  if (res[0]) res[0][20] = w0;
  /* #42: @0 = 0.84 */
  w0 = 8.3999999999999997e-01;
  /* #43: output[0][21] = @0 */
  if (res[0]) res[0][21] = w0;
  /* #44: @0 = 0.88 */
  w0 = 8.8000000000000000e-01;
  /* #45: output[0][22] = @0 */
  if (res[0]) res[0][22] = w0;
  /* #46: @0 = 0.92 */
  w0 = 9.2000000000000004e-01;
  /* #47: output[0][23] = @0 */
  if (res[0]) res[0][23] = w0;
  /* #48: @0 = 0.96 */
  w0 = 9.5999999999999996e-01;
  /* #49: output[0][24] = @0 */
  if (res[0]) res[0][24] = w0;
  /* #50: @0 = 1 */
  w0 = 1.;
  /* #51: output[0][25] = @0 */
  if (res[0]) res[0][25] = w0;
  /* #52: @0 = 1.04 */
  w0 = 1.0400000000000000e+00;
  /* #53: output[0][26] = @0 */
  if (res[0]) res[0][26] = w0;
  /* #54: @0 = 1.08 */
  w0 = 1.0800000000000001e+00;
  /* #55: output[0][27] = @0 */
  if (res[0]) res[0][27] = w0;
  /* #56: @0 = 1.12 */
  w0 = 1.1200000000000001e+00;
  /* #57: output[0][28] = @0 */
  if (res[0]) res[0][28] = w0;
  /* #58: @0 = 1.16 */
  w0 = 1.1599999999999999e+00;
  /* #59: output[0][29] = @0 */
  if (res[0]) res[0][29] = w0;
  /* #60: @0 = 1.2 */
  w0 = 1.2000000000000000e+00;
  /* #61: output[0][30] = @0 */
  if (res[0]) res[0][30] = w0;
  /* #62: @0 = 1.24 */
  w0 = 1.2400000000000000e+00;
  /* #63: output[0][31] = @0 */
  if (res[0]) res[0][31] = w0;
  /* #64: @0 = 1.28 */
  w0 = 1.2800000000000000e+00;
  /* #65: output[0][32] = @0 */
  if (res[0]) res[0][32] = w0;
  /* #66: @0 = 1.32 */
  w0 = 1.3200000000000001e+00;
  /* #67: output[0][33] = @0 */
  if (res[0]) res[0][33] = w0;
  /* #68: @0 = 1.36 */
  w0 = 1.3600000000000001e+00;
  /* #69: output[0][34] = @0 */
  if (res[0]) res[0][34] = w0;
  /* #70: @0 = 1.4 */
  w0 = 1.4000000000000001e+00;
  /* #71: output[0][35] = @0 */
  if (res[0]) res[0][35] = w0;
  /* #72: @0 = 1.44 */
  w0 = 1.4399999999999999e+00;
  /* #73: output[0][36] = @0 */
  if (res[0]) res[0][36] = w0;
  /* #74: @0 = 1.48 */
  w0 = 1.4800000000000000e+00;
  /* #75: output[0][37] = @0 */
  if (res[0]) res[0][37] = w0;
  /* #76: @0 = 1.52 */
  w0 = 1.5200000000000000e+00;
  /* #77: output[0][38] = @0 */
  if (res[0]) res[0][38] = w0;
  /* #78: @0 = 1.56 */
  w0 = 1.5600000000000001e+00;
  /* #79: output[0][39] = @0 */
  if (res[0]) res[0][39] = w0;
  /* #80: @0 = 1.6 */
  w0 = 1.6000000000000001e+00;
  /* #81: output[0][40] = @0 */
  if (res[0]) res[0][40] = w0;
  /* #82: @0 = 1.64 */
  w0 = 1.6400000000000001e+00;
  /* #83: output[0][41] = @0 */
  if (res[0]) res[0][41] = w0;
  /* #84: @0 = 1.68 */
  w0 = 1.6799999999999999e+00;
  /* #85: output[0][42] = @0 */
  if (res[0]) res[0][42] = w0;
  /* #86: @0 = 1.72 */
  w0 = 1.7200000000000000e+00;
  /* #87: output[0][43] = @0 */
  if (res[0]) res[0][43] = w0;
  /* #88: @0 = 1.76 */
  w0 = 1.7600000000000000e+00;
  /* #89: output[0][44] = @0 */
  if (res[0]) res[0][44] = w0;
  /* #90: @0 = 1.8 */
  w0 = 1.8000000000000000e+00;
  /* #91: output[0][45] = @0 */
  if (res[0]) res[0][45] = w0;
  /* #92: @0 = 1.84 */
  w0 = 1.8400000000000001e+00;
  /* #93: output[0][46] = @0 */
  if (res[0]) res[0][46] = w0;
  /* #94: @0 = 1.88 */
  w0 = 1.8800000000000001e+00;
  /* #95: output[0][47] = @0 */
  if (res[0]) res[0][47] = w0;
  /* #96: @0 = 1.92 */
  w0 = 1.9199999999999999e+00;
  /* #97: output[0][48] = @0 */
  if (res[0]) res[0][48] = w0;
  /* #98: @0 = 1.96 */
  w0 = 1.9600000000000000e+00;
  /* #99: output[0][49] = @0 */
  if (res[0]) res[0][49] = w0;
  /* #100: @0 = 2 */
  w0 = 2.;
  /* #101: output[0][50] = @0 */
  if (res[0]) res[0][50] = w0;
  return 0;
}

CASADI_SYMBOL_EXPORT int grid_mpc(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem){
  return casadi_f0(arg, res, iw, w, mem);
}

CASADI_SYMBOL_EXPORT int grid_mpc_alloc_mem(void) {
  return 0;
}

CASADI_SYMBOL_EXPORT int grid_mpc_init_mem(int mem) {
  return 0;
}

CASADI_SYMBOL_EXPORT void grid_mpc_free_mem(int mem) {
}

CASADI_SYMBOL_EXPORT int grid_mpc_checkout(void) {
  return 0;
}

CASADI_SYMBOL_EXPORT void grid_mpc_release(int mem) {
}

CASADI_SYMBOL_EXPORT void grid_mpc_incref(void) {
}

CASADI_SYMBOL_EXPORT void grid_mpc_decref(void) {
}

CASADI_SYMBOL_EXPORT casadi_int grid_mpc_n_in(void) { return 2;}

CASADI_SYMBOL_EXPORT casadi_int grid_mpc_n_out(void) { return 1;}

CASADI_SYMBOL_EXPORT casadi_real grid_mpc_default_in(casadi_int i) {
  switch (i) {
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const char* grid_mpc_name_in(casadi_int i) {
  switch (i) {
    case 0: return "x_current";
    case 1: return "x_final";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const char* grid_mpc_name_out(casadi_int i) {
  switch (i) {
    case 0: return "grid";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const casadi_int* grid_mpc_sparsity_in(casadi_int i) {
  switch (i) {
    case 0: return casadi_s0;
    case 1: return casadi_s0;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const casadi_int* grid_mpc_sparsity_out(casadi_int i) {
  switch (i) {
    case 0: return casadi_s1;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT int grid_mpc_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w) {
  if (sz_arg) *sz_arg = 2;
  if (sz_res) *sz_res = 2;
  if (sz_iw) *sz_iw = 0;
  if (sz_w) *sz_w = 1;
  return 0;
}




        static int_T n_in, n_out;
        static casadi_int sz_arg, sz_res, sz_iw, sz_w;
        static int id;

        static void mdlInitializeSizes(SimStruct *S) {
          int flag;
          char casadi_file[2048];
          ssSetNumSFcnParams(S, 0);
          if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
              return; /* Parameter mismatch will be reported by Simulink */
          }
        
        /* Read in CasADi function dimensions */
        n_in  = grid_mpc_n_in();
        n_out = grid_mpc_n_out();
        grid_mpc_work(&sz_arg, &sz_res, &sz_iw, &sz_w);

        /* Set up simulink input/output ports */
        int_T i;
        if (!ssSetNumInputPorts(S, n_in)) return;
        for (i=0;i<n_in;++i) {
          const casadi_int* sp = grid_mpc_sparsity_in(i);
          /* Dense inputs assumed here */
          ssSetInputPortDirectFeedThrough(S, i, 1);
          ssSetInputPortMatrixDimensions(S, i, sp[0], sp[1]);
          ssSetInputPortRequiredContiguous(S, i, 1);
        }

        if (!ssSetNumOutputPorts(S, n_out)) return;
        for (i=0;i<n_out;++i) {
          const casadi_int* sp = grid_mpc_sparsity_out(i);
          /* Dense outputs assumed here */
          ssSetOutputPortMatrixDimensions(S, i, sp[0], sp[1]);
        }

        ssSetNumSampleTimes(S, 1);
        
        /* Set up CasADi function work vector sizes */
        ssSetNumRWork(S, sz_w);
        ssSetNumIWork(S, 2*sz_iw);
        ssSetNumPWork(S, sz_arg+sz_res);
        ssSetNumNonsampledZCs(S, 0);

        /* specify the sim state compliance to be same as a built-in block */
        ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

        ssSetOptions(S,
                    SS_OPTION_EXCEPTION_FREE_CODE |
                    SS_OPTION_USE_TLC_WITH_ACCELERATOR);

        /* Signal that we want to use the CasADi Function */
        grid_mpc_incref();
        }

        static void mdlInitializeSampleTimes(SimStruct *S)
        {
            ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
            ssSetOffsetTime(S, 0, 0.0);
            ssSetModelReferenceSampleTimeDefaultInheritance(S); 
        }

        static void mdlOutputs(SimStruct *S, int_T tid)
        {

          /* Set up CasADi function work vectors */
          void** p = ssGetPWork(S);
          const real_T** arg = (const real_T**) p;
          p += sz_arg;
          real_T** res = (real_T**) p;
          real_T* w = ssGetRWork(S);
          int_T* iw = ssGetIWork(S);
          
          
          /* Point to input and output buffers */
          int_T i;   
          for (i=0; i<n_in;++i) {
            arg[i] = ssGetInputPortSignal(S,i);
          }
          for (i=0; i<n_out;++i) {
            res[i] = ssGetOutputPortRealSignal(S,i);
          }

          /* Get a hold on a location to read/write persistant internal memory
          */

          int mem = grid_mpc_checkout();

          /* Run the CasADi function */
          int_T ret = grid_mpc(arg,res,iw,w,mem);

          if (ret && 1) {
              static char msg[126];
              sprintf(msg, "SFunction 'grid_mpc_s_function_level2' failed to compute (error code %d) at t=%.6fs.", ret, ssGetT(S));
              #ifdef ssSetLocalErrorStatus
                ssSetLocalErrorStatus(S, msg);
              #else
                #ifdef ssSetErrorStatus
                  ssSetErrorStatus(S, msg);
                #endif
              #endif
          }

          /* Release hold */
          grid_mpc_release(mem);

        }

        static void mdlTerminate(SimStruct *S) {
          grid_mpc_decref();
          }

        #ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
        #include "simulink.c"      /* MEX-file interface mechanism */
        #else
        #include "cg_sfun.h"       /* Code generation registration function */
        #endif
        