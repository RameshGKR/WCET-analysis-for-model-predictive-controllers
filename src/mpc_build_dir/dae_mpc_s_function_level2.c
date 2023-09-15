
        #define S_FUNCTION_NAME dae_mpc_s_function_level2
        #define S_FUNCTION_LEVEL 2

        #include "simstruc.h"
        /* How to prefix internal symbols */
#ifdef CASADI_CODEGEN_PREFIX
  #define CASADI_NAMESPACE_CONCAT(NS, ID) _CASADI_NAMESPACE_CONCAT(NS, ID)
  #define _CASADI_NAMESPACE_CONCAT(NS, ID) NS ## ID
  #define CASADI_PREFIX(ID) CASADI_NAMESPACE_CONCAT(CODEGEN_PREFIX, ID)
#else
  #define CASADI_PREFIX(ID) dae_mpc_ ## ID
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
#define casadi_s2 CASADI_PREFIX(s2)
#define casadi_sq CASADI_PREFIX(sq)

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

casadi_real casadi_sq(casadi_real x) { return x*x;}

static const casadi_int casadi_s0[8] = {4, 1, 0, 4, 0, 1, 2, 3};
static const casadi_int casadi_s1[5] = {1, 1, 0, 1, 0};
static const casadi_int casadi_s2[4] = {0, 1, 0, 0};

/* dae_mpc:(x[4],u,z[0],p[0],t)->(ode[4],alg[0]) */
static int casadi_f0(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem) {
  casadi_real w0, w1, w2, w3, w4, w5;
  /* #0: @0 = input[0][2] */
  w0 = arg[0] ? arg[0][2] : 0;
  /* #1: output[0][0] = @0 */
  if (res[0]) res[0][0] = w0;
  /* #2: @0 = input[0][3] */
  w0 = arg[0] ? arg[0][3] : 0;
  /* #3: output[0][1] = @0 */
  if (res[0]) res[0][1] = w0;
  /* #4: @1 = -2 */
  w1 = -2.;
  /* #5: @2 = input[0][1] */
  w2 = arg[0] ? arg[0][1] : 0;
  /* #6: @3 = sin(@2) */
  w3 = sin( w2 );
  /* #7: @1 = (@1*@3) */
  w1 *= w3;
  /* #8: @1 = (@1*@0) */
  w1 *= w0;
  /* #9: @1 = (@1*@0) */
  w1 *= w0;
  /* #10: @3 = 9.81 */
  w3 = 9.8100000000000005e+00;
  /* #11: @4 = cos(@2) */
  w4 = cos( w2 );
  /* #12: @3 = (@3*@4) */
  w3 *= w4;
  /* #13: @4 = sin(@2) */
  w4 = sin( w2 );
  /* #14: @3 = (@3*@4) */
  w3 *= w4;
  /* #15: @1 = (@1+@3) */
  w1 += w3;
  /* #16: @3 = input[1][0] */
  w3 = arg[1] ? arg[1][0] : 0;
  /* #17: @1 = (@1+@3) */
  w1 += w3;
  /* #18: @4 = 1.5 */
  w4 = 1.5000000000000000e+00;
  /* #19: @5 = cos(@2) */
  w5 = cos( w2 );
  /* #20: @5 = sq(@5) */
  w5 = casadi_sq( w5 );
  /* #21: @4 = (@4-@5) */
  w4 -= w5;
  /* #22: @1 = (@1/@4) */
  w1 /= w4;
  /* #23: output[0][2] = @1 */
  if (res[0]) res[0][2] = w1;
  /* #24: @1 = -2 */
  w1 = -2.;
  /* #25: @4 = cos(@2) */
  w4 = cos( w2 );
  /* #26: @1 = (@1*@4) */
  w1 *= w4;
  /* #27: @4 = sin(@2) */
  w4 = sin( w2 );
  /* #28: @1 = (@1*@4) */
  w1 *= w4;
  /* #29: @1 = (@1*@0) */
  w1 *= w0;
  /* #30: @1 = (@1*@0) */
  w1 *= w0;
  /* #31: @0 = cos(@2) */
  w0 = cos( w2 );
  /* #32: @3 = (@3*@0) */
  w3 *= w0;
  /* #33: @1 = (@1+@3) */
  w1 += w3;
  /* #34: @3 = 14.715 */
  w3 = 1.4715000000000000e+01;
  /* #35: @0 = sin(@2) */
  w0 = sin( w2 );
  /* #36: @3 = (@3*@0) */
  w3 *= w0;
  /* #37: @1 = (@1+@3) */
  w1 += w3;
  /* #38: @3 = 1.5 */
  w3 = 1.5000000000000000e+00;
  /* #39: @2 = cos(@2) */
  w2 = cos( w2 );
  /* #40: @2 = sq(@2) */
  w2 = casadi_sq( w2 );
  /* #41: @3 = (@3-@2) */
  w3 -= w2;
  /* #42: @3 = (2.*@3) */
  w3 = (2.* w3 );
  /* #43: @1 = (@1/@3) */
  w1 /= w3;
  /* #44: output[0][3] = @1 */
  if (res[0]) res[0][3] = w1;
  return 0;
}

CASADI_SYMBOL_EXPORT int dae_mpc(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem){
  return casadi_f0(arg, res, iw, w, mem);
}

CASADI_SYMBOL_EXPORT int dae_mpc_alloc_mem(void) {
  return 0;
}

CASADI_SYMBOL_EXPORT int dae_mpc_init_mem(int mem) {
  return 0;
}

CASADI_SYMBOL_EXPORT void dae_mpc_free_mem(int mem) {
}

CASADI_SYMBOL_EXPORT int dae_mpc_checkout(void) {
  return 0;
}

CASADI_SYMBOL_EXPORT void dae_mpc_release(int mem) {
}

CASADI_SYMBOL_EXPORT void dae_mpc_incref(void) {
}

CASADI_SYMBOL_EXPORT void dae_mpc_decref(void) {
}

CASADI_SYMBOL_EXPORT casadi_int dae_mpc_n_in(void) { return 5;}

CASADI_SYMBOL_EXPORT casadi_int dae_mpc_n_out(void) { return 2;}

CASADI_SYMBOL_EXPORT casadi_real dae_mpc_default_in(casadi_int i) {
  switch (i) {
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const char* dae_mpc_name_in(casadi_int i) {
  switch (i) {
    case 0: return "x";
    case 1: return "u";
    case 2: return "z";
    case 3: return "p";
    case 4: return "t";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const char* dae_mpc_name_out(casadi_int i) {
  switch (i) {
    case 0: return "ode";
    case 1: return "alg";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const casadi_int* dae_mpc_sparsity_in(casadi_int i) {
  switch (i) {
    case 0: return casadi_s0;
    case 1: return casadi_s1;
    case 2: return casadi_s2;
    case 3: return casadi_s2;
    case 4: return casadi_s1;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const casadi_int* dae_mpc_sparsity_out(casadi_int i) {
  switch (i) {
    case 0: return casadi_s0;
    case 1: return casadi_s2;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT int dae_mpc_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w) {
  if (sz_arg) *sz_arg = 7;
  if (sz_res) *sz_res = 3;
  if (sz_iw) *sz_iw = 0;
  if (sz_w) *sz_w = 6;
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
        n_in  = dae_mpc_n_in();
        n_out = dae_mpc_n_out();
        dae_mpc_work(&sz_arg, &sz_res, &sz_iw, &sz_w);

        /* Set up simulink input/output ports */
        int_T i;
        if (!ssSetNumInputPorts(S, n_in)) return;
        for (i=0;i<n_in;++i) {
          const casadi_int* sp = dae_mpc_sparsity_in(i);
          /* Dense inputs assumed here */
          ssSetInputPortDirectFeedThrough(S, i, 1);
          ssSetInputPortMatrixDimensions(S, i, sp[0], sp[1]);
          ssSetInputPortRequiredContiguous(S, i, 1);
        }

        if (!ssSetNumOutputPorts(S, n_out)) return;
        for (i=0;i<n_out;++i) {
          const casadi_int* sp = dae_mpc_sparsity_out(i);
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
        dae_mpc_incref();
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

          int mem = dae_mpc_checkout();

          /* Run the CasADi function */
          int_T ret = dae_mpc(arg,res,iw,w,mem);

          if (ret && 1) {
              static char msg[125];
              sprintf(msg, "SFunction 'dae_mpc_s_function_level2' failed to compute (error code %d) at t=%.6fs.", ret, ssGetT(S));
              #ifdef ssSetLocalErrorStatus
                ssSetLocalErrorStatus(S, msg);
              #else
                #ifdef ssSetErrorStatus
                  ssSetErrorStatus(S, msg);
                #endif
              #endif
          }

          /* Release hold */
          dae_mpc_release(mem);

        }

        static void mdlTerminate(SimStruct *S) {
          dae_mpc_decref();
          }

        #ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
        #include "simulink.c"      /* MEX-file interface mechanism */
        #else
        #include "cg_sfun.h"       /* Code generation registration function */
        #endif
        