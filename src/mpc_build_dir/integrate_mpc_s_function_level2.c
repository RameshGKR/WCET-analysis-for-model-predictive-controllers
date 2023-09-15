
        #define S_FUNCTION_NAME integrate_mpc_s_function_level2
        #define S_FUNCTION_LEVEL 2

        #include "simstruc.h"
        /* How to prefix internal symbols */
#ifdef CASADI_CODEGEN_PREFIX
  #define CASADI_NAMESPACE_CONCAT(NS, ID) _CASADI_NAMESPACE_CONCAT(NS, ID)
  #define _CASADI_NAMESPACE_CONCAT(NS, ID) NS ## ID
  #define CASADI_PREFIX(ID) CASADI_NAMESPACE_CONCAT(CODEGEN_PREFIX, ID)
#else
  #define CASADI_PREFIX(ID) integrate_mpc_ ## ID
#endif

#include <math.h>

#ifndef casadi_real
#define casadi_real real_T
#endif

#ifndef casadi_int
#define casadi_int int_T
#endif

/* Add prefix to internal symbols */
#define casadi_copy CASADI_PREFIX(copy)
#define casadi_f0 CASADI_PREFIX(f0)
#define casadi_f1 CASADI_PREFIX(f1)
#define casadi_f2 CASADI_PREFIX(f2)
#define casadi_f3 CASADI_PREFIX(f3)
#define casadi_f4 CASADI_PREFIX(f4)
#define casadi_s0 CASADI_PREFIX(s0)
#define casadi_s1 CASADI_PREFIX(s1)
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

void casadi_copy(const casadi_real* x, casadi_int n, casadi_real* y) {
  casadi_int i;
  if (y) {
    if (x) {
      for (i=0; i<n; ++i) *y++ = *x++;
    } else {
      for (i=0; i<n; ++i) *y++ = 0.;
    }
  }
}

static const casadi_int casadi_s0[8] = {4, 1, 0, 4, 0, 1, 2, 3};
static const casadi_int casadi_s1[5] = {1, 1, 0, 1, 0};

/* dae:(t,x[4],z[0],p[3],u[0])->(ode[4],alg[0],quad[0]) */
static int casadi_f4(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem) {
  casadi_int i;
  casadi_real *rr;
  const casadi_real *cs;
  casadi_real w0, w1, w2, w3, w4, w5, w6, w7, *w8=w+8;
  /* #0: @0 = input[3][2] */
  w0 = arg[3] ? arg[3][2] : 0;
  /* #1: @1 = input[1][2] */
  w1 = arg[1] ? arg[1][2] : 0;
  /* #2: @2 = input[1][3] */
  w2 = arg[1] ? arg[1][3] : 0;
  /* #3: @3 = -2 */
  w3 = -2.;
  /* #4: @4 = input[1][1] */
  w4 = arg[1] ? arg[1][1] : 0;
  /* #5: @5 = sin(@4) */
  w5 = sin( w4 );
  /* #6: @3 = (@3*@5) */
  w3 *= w5;
  /* #7: @3 = (@3*@2) */
  w3 *= w2;
  /* #8: @3 = (@3*@2) */
  w3 *= w2;
  /* #9: @5 = 9.81 */
  w5 = 9.8100000000000005e+00;
  /* #10: @6 = cos(@4) */
  w6 = cos( w4 );
  /* #11: @5 = (@5*@6) */
  w5 *= w6;
  /* #12: @6 = sin(@4) */
  w6 = sin( w4 );
  /* #13: @5 = (@5*@6) */
  w5 *= w6;
  /* #14: @3 = (@3+@5) */
  w3 += w5;
  /* #15: @5 = input[3][0] */
  w5 = arg[3] ? arg[3][0] : 0;
  /* #16: @3 = (@3+@5) */
  w3 += w5;
  /* #17: @6 = 1.5 */
  w6 = 1.5000000000000000e+00;
  /* #18: @7 = cos(@4) */
  w7 = cos( w4 );
  /* #19: @7 = sq(@7) */
  w7 = casadi_sq( w7 );
  /* #20: @6 = (@6-@7) */
  w6 -= w7;
  /* #21: @3 = (@3/@6) */
  w3 /= w6;
  /* #22: @6 = -2 */
  w6 = -2.;
  /* #23: @7 = cos(@4) */
  w7 = cos( w4 );
  /* #24: @6 = (@6*@7) */
  w6 *= w7;
  /* #25: @7 = sin(@4) */
  w7 = sin( w4 );
  /* #26: @6 = (@6*@7) */
  w6 *= w7;
  /* #27: @6 = (@6*@2) */
  w6 *= w2;
  /* #28: @6 = (@6*@2) */
  w6 *= w2;
  /* #29: @7 = cos(@4) */
  w7 = cos( w4 );
  /* #30: @5 = (@5*@7) */
  w5 *= w7;
  /* #31: @6 = (@6+@5) */
  w6 += w5;
  /* #32: @5 = 14.715 */
  w5 = 1.4715000000000000e+01;
  /* #33: @7 = sin(@4) */
  w7 = sin( w4 );
  /* #34: @5 = (@5*@7) */
  w5 *= w7;
  /* #35: @6 = (@6+@5) */
  w6 += w5;
  /* #36: @5 = 1.5 */
  w5 = 1.5000000000000000e+00;
  /* #37: @4 = cos(@4) */
  w4 = cos( w4 );
  /* #38: @4 = sq(@4) */
  w4 = casadi_sq( w4 );
  /* #39: @5 = (@5-@4) */
  w5 -= w4;
  /* #40: @5 = (2.*@5) */
  w5 = (2.* w5 );
  /* #41: @6 = (@6/@5) */
  w6 /= w5;
  /* #42: @8 = vertcat(@1, @2, @3, @6) */
  rr=w8;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w3;
  *rr++ = w6;
  /* #43: @8 = (@0*@8) */
  for (i=0, rr=w8, cs=w8; i<4; ++i) (*rr++)  = (w0*(*cs++));
  /* #44: output[0][0] = @8 */
  casadi_copy(w8, 4, res[0]);
  return 0;
}

/* step:(t,h,x0[4],v0[0],p[3],u[0])->(xf[4],vf[0],qf[0]) */
static int casadi_f3(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem) {
  casadi_int i;
  casadi_real **res1=res+3, *rr;
  const casadi_real **arg1=arg+6, *cr, *cs;
  casadi_real *w0=w+12, w1, w2, w3, *w5=w+19, *w7=w+22, w8, w9, *w10=w+28, *w11=w+32;
  /* #0: @0 = input[2][0] */
  casadi_copy(arg[2], 4, w0);
  /* #1: @1 = input[1][0] */
  w1 = arg[1] ? arg[1][0] : 0;
  /* #2: @2 = 6 */
  w2 = 6.;
  /* #3: @2 = (@1/@2) */
  w2  = (w1/w2);
  /* #4: @3 = input[0][0] */
  w3 = arg[0] ? arg[0][0] : 0;
  /* #5: @4 = 0x1 */
  /* #6: @5 = input[4][0] */
  casadi_copy(arg[4], 3, w5);
  /* #7: @6 = 0x1 */
  /* #8: {@7, NULL, NULL} = dae(@3, @0, @4, @5, @6) */
  arg1[0]=(&w3);
  arg1[1]=w0;
  arg1[2]=0;
  arg1[3]=w5;
  arg1[4]=0;
  res1[0]=w7;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f4(arg1, res1, iw, w, 0)) return 1;
  /* #9: @8 = 2 */
  w8 = 2.;
  /* #10: @8 = (@1/@8) */
  w8  = (w1/w8);
  /* #11: @9 = (@3+@8) */
  w9  = (w3+w8);
  /* #12: @10 = (@8*@7) */
  for (i=0, rr=w10, cs=w7; i<4; ++i) (*rr++)  = (w8*(*cs++));
  /* #13: @10 = (@0+@10) */
  for (i=0, rr=w10, cr=w0, cs=w10; i<4; ++i) (*rr++)  = ((*cr++)+(*cs++));
  /* #14: @4 = 0x1 */
  /* #15: {@11, NULL, NULL} = dae(@9, @10, @4, @5, @6) */
  arg1[0]=(&w9);
  arg1[1]=w10;
  arg1[2]=0;
  arg1[3]=w5;
  arg1[4]=0;
  res1[0]=w11;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f4(arg1, res1, iw, w, 0)) return 1;
  /* #16: @10 = (2.*@11) */
  for (i=0, rr=w10, cs=w11; i<4; ++i) *rr++ = (2.* *cs++ );
  /* #17: @7 = (@7+@10) */
  for (i=0, rr=w7, cs=w10; i<4; ++i) (*rr++) += (*cs++);
  /* #18: @11 = (@8*@11) */
  for (i=0, rr=w11, cs=w11; i<4; ++i) (*rr++)  = (w8*(*cs++));
  /* #19: @11 = (@0+@11) */
  for (i=0, rr=w11, cr=w0, cs=w11; i<4; ++i) (*rr++)  = ((*cr++)+(*cs++));
  /* #20: @4 = 0x1 */
  /* #21: {@10, NULL, NULL} = dae(@9, @11, @4, @5, @6) */
  arg1[0]=(&w9);
  arg1[1]=w11;
  arg1[2]=0;
  arg1[3]=w5;
  arg1[4]=0;
  res1[0]=w10;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f4(arg1, res1, iw, w, 0)) return 1;
  /* #22: @11 = (2.*@10) */
  for (i=0, rr=w11, cs=w10; i<4; ++i) *rr++ = (2.* *cs++ );
  /* #23: @7 = (@7+@11) */
  for (i=0, rr=w7, cs=w11; i<4; ++i) (*rr++) += (*cs++);
  /* #24: @3 = (@3+@1) */
  w3 += w1;
  /* #25: @10 = (@1*@10) */
  for (i=0, rr=w10, cs=w10; i<4; ++i) (*rr++)  = (w1*(*cs++));
  /* #26: @10 = (@0+@10) */
  for (i=0, rr=w10, cr=w0, cs=w10; i<4; ++i) (*rr++)  = ((*cr++)+(*cs++));
  /* #27: @4 = 0x1 */
  /* #28: {@11, NULL, NULL} = dae(@3, @10, @4, @5, @6) */
  arg1[0]=(&w3);
  arg1[1]=w10;
  arg1[2]=0;
  arg1[3]=w5;
  arg1[4]=0;
  res1[0]=w11;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f4(arg1, res1, iw, w, 0)) return 1;
  /* #29: @7 = (@7+@11) */
  for (i=0, rr=w7, cs=w11; i<4; ++i) (*rr++) += (*cs++);
  /* #30: @7 = (@2*@7) */
  for (i=0, rr=w7, cs=w7; i<4; ++i) (*rr++)  = (w2*(*cs++));
  /* #31: @0 = (@0+@7) */
  for (i=0, rr=w0, cs=w7; i<4; ++i) (*rr++) += (*cs++);
  /* #32: output[0][0] = @0 */
  casadi_copy(w0, 4, res[0]);
  return 0;
}

/* intg:(x0[4],z0[0],p[3],u[0],adj_xf[],adj_zf[],adj_qf[])->(xf[4],zf[],qf[0],adj_x0[],adj_z0[],adj_p[],adj_u[]) */
static int casadi_f2(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem) {
  casadi_real **res1=res+7;
  const casadi_real **arg1=arg+7;
  casadi_real w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w13, w14, w15, w16, w17, w18, w19, w20, *w21=w+57, *w23=w+61, *w25=w+64;
  /* #0: @0 = 0.95 */
  w0 = 9.5000000000000029e-01;
  /* #1: @1 = 0.05 */
  w1 = 5.0000000000000003e-02;
  /* #2: @2 = 0.9 */
  w2 = 9.0000000000000024e-01;
  /* #3: @3 = 0.85 */
  w3 = 8.5000000000000020e-01;
  /* #4: @4 = 0.8 */
  w4 = 8.0000000000000016e-01;
  /* #5: @5 = 0.75 */
  w5 = 7.5000000000000011e-01;
  /* #6: @6 = 0.7 */
  w6 = 7.0000000000000007e-01;
  /* #7: @7 = 0.65 */
  w7 = 6.5000000000000002e-01;
  /* #8: @8 = 0.6 */
  w8 = 5.9999999999999998e-01;
  /* #9: @9 = 0.55 */
  w9 = 5.4999999999999993e-01;
  /* #10: @10 = 0.5 */
  w10 = 4.9999999999999994e-01;
  /* #11: @11 = 0.45 */
  w11 = 4.4999999999999996e-01;
  /* #12: @12 = 0.4 */
  w12 = 3.9999999999999997e-01;
  /* #13: @13 = 0.35 */
  w13 = 3.4999999999999998e-01;
  /* #14: @14 = 0.3 */
  w14 = 2.9999999999999999e-01;
  /* #15: @15 = 0.25 */
  w15 = 2.5000000000000000e-01;
  /* #16: @16 = 0.2 */
  w16 = 2.0000000000000001e-01;
  /* #17: @17 = 0.15 */
  w17 = 1.5000000000000002e-01;
  /* #18: @18 = 0.1 */
  w18 = 1.0000000000000001e-01;
  /* #19: @19 = 0.05 */
  w19 = 5.0000000000000003e-02;
  /* #20: @20 = 0 */
  w20 = 0.;
  /* #21: @21 = input[0][0] */
  casadi_copy(arg[0], 4, w21);
  /* #22: @22 = 0x1 */
  /* #23: @23 = input[2][0] */
  casadi_copy(arg[2], 3, w23);
  /* #24: @24 = 0x1 */
  /* #25: {@25, NULL, NULL} = step(@20, @1, @21, @22, @23, @24) */
  arg1[0]=(&w20);
  arg1[1]=(&w1);
  arg1[2]=w21;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w25;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #26: @22 = 0x1 */
  /* #27: {@21, NULL, NULL} = step(@19, @1, @25, @22, @23, @24) */
  arg1[0]=(&w19);
  arg1[1]=(&w1);
  arg1[2]=w25;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w21;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #28: @22 = 0x1 */
  /* #29: {@25, NULL, NULL} = step(@18, @1, @21, @22, @23, @24) */
  arg1[0]=(&w18);
  arg1[1]=(&w1);
  arg1[2]=w21;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w25;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #30: @22 = 0x1 */
  /* #31: {@21, NULL, NULL} = step(@17, @1, @25, @22, @23, @24) */
  arg1[0]=(&w17);
  arg1[1]=(&w1);
  arg1[2]=w25;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w21;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #32: @22 = 0x1 */
  /* #33: {@25, NULL, NULL} = step(@16, @1, @21, @22, @23, @24) */
  arg1[0]=(&w16);
  arg1[1]=(&w1);
  arg1[2]=w21;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w25;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #34: @22 = 0x1 */
  /* #35: {@21, NULL, NULL} = step(@15, @1, @25, @22, @23, @24) */
  arg1[0]=(&w15);
  arg1[1]=(&w1);
  arg1[2]=w25;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w21;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #36: @22 = 0x1 */
  /* #37: {@25, NULL, NULL} = step(@14, @1, @21, @22, @23, @24) */
  arg1[0]=(&w14);
  arg1[1]=(&w1);
  arg1[2]=w21;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w25;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #38: @22 = 0x1 */
  /* #39: {@21, NULL, NULL} = step(@13, @1, @25, @22, @23, @24) */
  arg1[0]=(&w13);
  arg1[1]=(&w1);
  arg1[2]=w25;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w21;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #40: @22 = 0x1 */
  /* #41: {@25, NULL, NULL} = step(@12, @1, @21, @22, @23, @24) */
  arg1[0]=(&w12);
  arg1[1]=(&w1);
  arg1[2]=w21;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w25;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #42: @22 = 0x1 */
  /* #43: {@21, NULL, NULL} = step(@11, @1, @25, @22, @23, @24) */
  arg1[0]=(&w11);
  arg1[1]=(&w1);
  arg1[2]=w25;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w21;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #44: @22 = 0x1 */
  /* #45: {@25, NULL, NULL} = step(@10, @1, @21, @22, @23, @24) */
  arg1[0]=(&w10);
  arg1[1]=(&w1);
  arg1[2]=w21;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w25;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #46: @22 = 0x1 */
  /* #47: {@21, NULL, NULL} = step(@9, @1, @25, @22, @23, @24) */
  arg1[0]=(&w9);
  arg1[1]=(&w1);
  arg1[2]=w25;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w21;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #48: @22 = 0x1 */
  /* #49: {@25, NULL, NULL} = step(@8, @1, @21, @22, @23, @24) */
  arg1[0]=(&w8);
  arg1[1]=(&w1);
  arg1[2]=w21;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w25;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #50: @22 = 0x1 */
  /* #51: {@21, NULL, NULL} = step(@7, @1, @25, @22, @23, @24) */
  arg1[0]=(&w7);
  arg1[1]=(&w1);
  arg1[2]=w25;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w21;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #52: @22 = 0x1 */
  /* #53: {@25, NULL, NULL} = step(@6, @1, @21, @22, @23, @24) */
  arg1[0]=(&w6);
  arg1[1]=(&w1);
  arg1[2]=w21;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w25;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #54: @22 = 0x1 */
  /* #55: {@21, NULL, NULL} = step(@5, @1, @25, @22, @23, @24) */
  arg1[0]=(&w5);
  arg1[1]=(&w1);
  arg1[2]=w25;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w21;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #56: @22 = 0x1 */
  /* #57: {@25, NULL, NULL} = step(@4, @1, @21, @22, @23, @24) */
  arg1[0]=(&w4);
  arg1[1]=(&w1);
  arg1[2]=w21;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w25;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #58: @22 = 0x1 */
  /* #59: {@21, NULL, NULL} = step(@3, @1, @25, @22, @23, @24) */
  arg1[0]=(&w3);
  arg1[1]=(&w1);
  arg1[2]=w25;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w21;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #60: @22 = 0x1 */
  /* #61: {@25, NULL, NULL} = step(@2, @1, @21, @22, @23, @24) */
  arg1[0]=(&w2);
  arg1[1]=(&w1);
  arg1[2]=w21;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w25;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #62: @22 = 0x1 */
  /* #63: {@21, NULL, NULL} = step(@0, @1, @25, @22, @23, @24) */
  arg1[0]=(&w0);
  arg1[1]=(&w1);
  arg1[2]=w25;
  arg1[3]=0;
  arg1[4]=w23;
  arg1[5]=0;
  res1[0]=w21;
  res1[1]=0;
  res1[2]=0;
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #64: output[0][0] = @21 */
  casadi_copy(w21, 4, res[0]);
  return 0;
}

/* simulator:(x[4],u,p[0],t0,dt,z_initial_guess[0])->(xf[4],zf[]) */
static int casadi_f1(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem) {
  casadi_real **res1=res+2, *rr;
  const casadi_real **arg1=arg+6;
  casadi_real w0, w1, w2, w3, *w4=w+72, *w6=w+76, *w9=w+79;
  /* #0: @0 = input[0][0] */
  w0 = arg[0] ? arg[0][0] : 0;
  /* #1: @1 = input[0][1] */
  w1 = arg[0] ? arg[0][1] : 0;
  /* #2: @2 = input[0][2] */
  w2 = arg[0] ? arg[0][2] : 0;
  /* #3: @3 = input[0][3] */
  w3 = arg[0] ? arg[0][3] : 0;
  /* #4: @4 = vertcat(@0, @1, @2, @3) */
  rr=w4;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w3;
  /* #5: @5 = 0x1 */
  /* #6: @0 = input[1][0] */
  w0 = arg[1] ? arg[1][0] : 0;
  /* #7: @1 = input[3][0] */
  w1 = arg[3] ? arg[3][0] : 0;
  /* #8: @2 = input[4][0] */
  w2 = arg[4] ? arg[4][0] : 0;
  /* #9: @6 = vertcat(@0, @1, @2) */
  rr=w6;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  /* #10: @7 = 0x1 */
  /* #11: @8 = 0x0 */
  /* #12: {@9, NULL, NULL, NULL, NULL, NULL, NULL} = intg(@4, @5, @6, @7, @8, @8, @8) */
  arg1[0]=w4;
  arg1[1]=0;
  arg1[2]=w6;
  arg1[3]=0;
  arg1[4]=0;
  arg1[5]=0;
  arg1[6]=0;
  res1[0]=w9;
  res1[1]=0;
  res1[2]=0;
  res1[3]=0;
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f2(arg1, res1, iw, w, 0)) return 1;
  /* #13: output[0][0] = @9 */
  casadi_copy(w9, 4, res[0]);
  return 0;
}

/* integrate_mpc:(x[4],u,dt)->(xf[4]) */
static int casadi_f0(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem) {
  casadi_real **res1=res+1, *rr;
  const casadi_real **arg1=arg+3;
  casadi_real w0, w1, w2, w3, *w4=w+87, *w7=w+91;
  /* #0: @0 = input[0][0] */
  w0 = arg[0] ? arg[0][0] : 0;
  /* #1: @1 = input[0][1] */
  w1 = arg[0] ? arg[0][1] : 0;
  /* #2: @2 = input[0][2] */
  w2 = arg[0] ? arg[0][2] : 0;
  /* #3: @3 = input[0][3] */
  w3 = arg[0] ? arg[0][3] : 0;
  /* #4: @4 = vertcat(@0, @1, @2, @3) */
  rr=w4;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w3;
  /* #5: @0 = input[1][0] */
  w0 = arg[1] ? arg[1][0] : 0;
  /* #6: @5 = 0x1 */
  /* #7: @1 = 0 */
  w1 = 0.;
  /* #8: @2 = input[2][0] */
  w2 = arg[2] ? arg[2][0] : 0;
  /* #9: @6 = 0x1 */
  /* #10: {@7, NULL} = simulator(@4, @0, @5, @1, @2, @6) */
  arg1[0]=w4;
  arg1[1]=(&w0);
  arg1[2]=0;
  arg1[3]=(&w1);
  arg1[4]=(&w2);
  arg1[5]=0;
  res1[0]=w7;
  res1[1]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #11: output[0][0] = @7 */
  casadi_copy(w7, 4, res[0]);
  return 0;
}

CASADI_SYMBOL_EXPORT int integrate_mpc(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem){
  return casadi_f0(arg, res, iw, w, mem);
}

CASADI_SYMBOL_EXPORT int integrate_mpc_alloc_mem(void) {
  return 0;
}

CASADI_SYMBOL_EXPORT int integrate_mpc_init_mem(int mem) {
  return 0;
}

CASADI_SYMBOL_EXPORT void integrate_mpc_free_mem(int mem) {
}

CASADI_SYMBOL_EXPORT int integrate_mpc_checkout(void) {
  return 0;
}

CASADI_SYMBOL_EXPORT void integrate_mpc_release(int mem) {
}

CASADI_SYMBOL_EXPORT void integrate_mpc_incref(void) {
}

CASADI_SYMBOL_EXPORT void integrate_mpc_decref(void) {
}

CASADI_SYMBOL_EXPORT casadi_int integrate_mpc_n_in(void) { return 3;}

CASADI_SYMBOL_EXPORT casadi_int integrate_mpc_n_out(void) { return 1;}

CASADI_SYMBOL_EXPORT casadi_real integrate_mpc_default_in(casadi_int i) {
  switch (i) {
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const char* integrate_mpc_name_in(casadi_int i) {
  switch (i) {
    case 0: return "x";
    case 1: return "u";
    case 2: return "dt";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const char* integrate_mpc_name_out(casadi_int i) {
  switch (i) {
    case 0: return "xf";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const casadi_int* integrate_mpc_sparsity_in(casadi_int i) {
  switch (i) {
    case 0: return casadi_s0;
    case 1: return casadi_s1;
    case 2: return casadi_s1;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const casadi_int* integrate_mpc_sparsity_out(casadi_int i) {
  switch (i) {
    case 0: return casadi_s0;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT int integrate_mpc_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w) {
  if (sz_arg) *sz_arg = 31;
  if (sz_res) *sz_res = 17;
  if (sz_iw) *sz_iw = 0;
  if (sz_w) *sz_w = 95;
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
        n_in  = integrate_mpc_n_in();
        n_out = integrate_mpc_n_out();
        integrate_mpc_work(&sz_arg, &sz_res, &sz_iw, &sz_w);

        /* Set up simulink input/output ports */
        int_T i;
        if (!ssSetNumInputPorts(S, n_in)) return;
        for (i=0;i<n_in;++i) {
          const casadi_int* sp = integrate_mpc_sparsity_in(i);
          /* Dense inputs assumed here */
          ssSetInputPortDirectFeedThrough(S, i, 1);
          ssSetInputPortMatrixDimensions(S, i, sp[0], sp[1]);
          ssSetInputPortRequiredContiguous(S, i, 1);
        }

        if (!ssSetNumOutputPorts(S, n_out)) return;
        for (i=0;i<n_out;++i) {
          const casadi_int* sp = integrate_mpc_sparsity_out(i);
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
        integrate_mpc_incref();
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

          int mem = integrate_mpc_checkout();

          /* Run the CasADi function */
          int_T ret = integrate_mpc(arg,res,iw,w,mem);

          if (ret && 1) {
              static char msg[131];
              sprintf(msg, "SFunction 'integrate_mpc_s_function_level2' failed to compute (error code %d) at t=%.6fs.", ret, ssGetT(S));
              #ifdef ssSetLocalErrorStatus
                ssSetLocalErrorStatus(S, msg);
              #else
                #ifdef ssSetErrorStatus
                  ssSetErrorStatus(S, msg);
                #endif
              #endif
          }

          /* Release hold */
          integrate_mpc_release(mem);

        }

        static void mdlTerminate(SimStruct *S) {
          integrate_mpc_decref();
          }

        #ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
        #include "simulink.c"      /* MEX-file interface mechanism */
        #else
        #include "cg_sfun.h"       /* Code generation registration function */
        #endif
        