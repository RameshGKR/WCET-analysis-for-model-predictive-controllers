
        #define S_FUNCTION_NAME cost_mpc_s_function_level2
        #define S_FUNCTION_LEVEL 2

        #include "simstruc.h"
        /* How to prefix internal symbols */
#ifdef CASADI_CODEGEN_PREFIX
  #define CASADI_NAMESPACE_CONCAT(NS, ID) _CASADI_NAMESPACE_CONCAT(NS, ID)
  #define _CASADI_NAMESPACE_CONCAT(NS, ID) NS ## ID
  #define CASADI_PREFIX(ID) CASADI_NAMESPACE_CONCAT(CODEGEN_PREFIX, ID)
#else
  #define CASADI_PREFIX(ID) cost_mpc_ ## ID
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
#define casadi_s0 CASADI_PREFIX(s0)
#define casadi_s1 CASADI_PREFIX(s1)
#define casadi_s2 CASADI_PREFIX(s2)
#define casadi_s3 CASADI_PREFIX(s3)
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

static const casadi_int casadi_s0[258] = {4, 51, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144, 148, 152, 156, 160, 164, 168, 172, 176, 180, 184, 188, 192, 196, 200, 204, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};
static const casadi_int casadi_s1[103] = {1, 50, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static const casadi_int casadi_s2[8] = {4, 1, 0, 4, 0, 1, 2, 3};
static const casadi_int casadi_s3[5] = {1, 1, 0, 1, 0};

/* ode:(x[4],u,z[0],p[8],t[1x1,0nz])->(ode[4],alg[0],quad) */
static int casadi_f3(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem) {
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
  /* #32: @0 = (@3*@0) */
  w0  = (w3*w0);
  /* #33: @1 = (@1+@0) */
  w1 += w0;
  /* #34: @0 = 14.715 */
  w0 = 1.4715000000000000e+01;
  /* #35: @4 = sin(@2) */
  w4 = sin( w2 );
  /* #36: @0 = (@0*@4) */
  w0 *= w4;
  /* #37: @1 = (@1+@0) */
  w1 += w0;
  /* #38: @0 = 1.5 */
  w0 = 1.5000000000000000e+00;
  /* #39: @2 = cos(@2) */
  w2 = cos( w2 );
  /* #40: @2 = sq(@2) */
  w2 = casadi_sq( w2 );
  /* #41: @0 = (@0-@2) */
  w0 -= w2;
  /* #42: @0 = (2.*@0) */
  w0 = (2.* w0 );
  /* #43: @1 = (@1/@0) */
  w1 /= w0;
  /* #44: output[0][3] = @1 */
  if (res[0]) res[0][3] = w1;
  /* #45: @3 = sq(@3) */
  w3 = casadi_sq( w3 );
  /* #46: @1 = 100 */
  w1 = 100.;
  /* #47: @0 = input[0][0] */
  w0 = arg[0] ? arg[0][0] : 0;
  /* #48: @0 = sq(@0) */
  w0 = casadi_sq( w0 );
  /* #49: @1 = (@1*@0) */
  w1 *= w0;
  /* #50: @3 = (@3+@1) */
  w3 += w1;
  /* #51: output[2][0] = @3 */
  if (res[2]) res[2][0] = w3;
  return 0;
}

/* F:(x0[4],u,t0,DT,DT_control,p[8])->(xf[4],poly_coeff[4x5],qf,zf[0],poly_coeff_z[]) */
static int casadi_f2(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem) {
  casadi_int i;
  casadi_real **res1=res+5, *rr;
  const casadi_real **arg1=arg+6, *cr, *cs;
  casadi_real *w0=w+6, w1, w2, w3, *w5=w+13, *w7=w+21, w8, w9, *w10=w+27, *w11=w+31, w12, *w13=w+36, *w14=w+40, *w15=w+44, w16;
  /* #0: @0 = input[0][0] */
  casadi_copy(arg[0], 4, w0);
  /* #1: @1 = input[3][0] */
  w1 = arg[3] ? arg[3][0] : 0;
  /* #2: @2 = 6 */
  w2 = 6.;
  /* #3: @2 = (@1/@2) */
  w2  = (w1/w2);
  /* #4: @3 = input[1][0] */
  w3 = arg[1] ? arg[1][0] : 0;
  /* #5: @4 = 0x1 */
  /* #6: @5 = input[5][0] */
  casadi_copy(arg[5], 8, w5);
  /* #7: @6 = 00 */
  /* #8: {@7, NULL, @8} = ode(@0, @3, @4, @5, @6) */
  arg1[0]=w0;
  arg1[1]=(&w3);
  arg1[2]=0;
  arg1[3]=w5;
  arg1[4]=0;
  res1[0]=w7;
  res1[1]=0;
  res1[2]=(&w8);
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #9: @9 = 2 */
  w9 = 2.;
  /* #10: @9 = (@1/@9) */
  w9  = (w1/w9);
  /* #11: @10 = (@9*@7) */
  for (i=0, rr=w10, cs=w7; i<4; ++i) (*rr++)  = (w9*(*cs++));
  /* #12: @10 = (@0+@10) */
  for (i=0, rr=w10, cr=w0, cs=w10; i<4; ++i) (*rr++)  = ((*cr++)+(*cs++));
  /* #13: @4 = 0x1 */
  /* #14: @6 = 00 */
  /* #15: {@11, NULL, @9} = ode(@10, @3, @4, @5, @6) */
  arg1[0]=w10;
  arg1[1]=(&w3);
  arg1[2]=0;
  arg1[3]=w5;
  arg1[4]=0;
  res1[0]=w11;
  res1[1]=0;
  res1[2]=(&w9);
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #16: @10 = (2.*@11) */
  for (i=0, rr=w10, cs=w11; i<4; ++i) *rr++ = (2.* *cs++ );
  /* #17: @10 = (@7+@10) */
  for (i=0, rr=w10, cr=w7, cs=w10; i<4; ++i) (*rr++)  = ((*cr++)+(*cs++));
  /* #18: @12 = 2 */
  w12 = 2.;
  /* #19: @12 = (@1/@12) */
  w12  = (w1/w12);
  /* #20: @13 = (@12*@11) */
  for (i=0, rr=w13, cs=w11; i<4; ++i) (*rr++)  = (w12*(*cs++));
  /* #21: @13 = (@0+@13) */
  for (i=0, rr=w13, cr=w0, cs=w13; i<4; ++i) (*rr++)  = ((*cr++)+(*cs++));
  /* #22: @4 = 0x1 */
  /* #23: @6 = 00 */
  /* #24: {@14, NULL, @12} = ode(@13, @3, @4, @5, @6) */
  arg1[0]=w13;
  arg1[1]=(&w3);
  arg1[2]=0;
  arg1[3]=w5;
  arg1[4]=0;
  res1[0]=w14;
  res1[1]=0;
  res1[2]=(&w12);
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #25: @13 = (2.*@14) */
  for (i=0, rr=w13, cs=w14; i<4; ++i) *rr++ = (2.* *cs++ );
  /* #26: @10 = (@10+@13) */
  for (i=0, rr=w10, cs=w13; i<4; ++i) (*rr++) += (*cs++);
  /* #27: @13 = (@1*@14) */
  for (i=0, rr=w13, cs=w14; i<4; ++i) (*rr++)  = (w1*(*cs++));
  /* #28: @13 = (@0+@13) */
  for (i=0, rr=w13, cr=w0, cs=w13; i<4; ++i) (*rr++)  = ((*cr++)+(*cs++));
  /* #29: @4 = 0x1 */
  /* #30: @6 = 00 */
  /* #31: {@15, NULL, @16} = ode(@13, @3, @4, @5, @6) */
  arg1[0]=w13;
  arg1[1]=(&w3);
  arg1[2]=0;
  arg1[3]=w5;
  arg1[4]=0;
  res1[0]=w15;
  res1[1]=0;
  res1[2]=(&w16);
  if (casadi_f3(arg1, res1, iw, w, 0)) return 1;
  /* #32: @10 = (@10+@15) */
  for (i=0, rr=w10, cs=w15; i<4; ++i) (*rr++) += (*cs++);
  /* #33: @10 = (@2*@10) */
  for (i=0, rr=w10, cs=w10; i<4; ++i) (*rr++)  = (w2*(*cs++));
  /* #34: @10 = (@0+@10) */
  for (i=0, rr=w10, cr=w0, cs=w10; i<4; ++i) (*rr++)  = ((*cr++)+(*cs++));
  /* #35: output[0][0] = @10 */
  casadi_copy(w10, 4, res[0]);
  /* #36: output[1][0] = @0 */
  casadi_copy(w0, 4, res[1]);
  /* #37: output[1][1] = @7 */
  if (res[1]) casadi_copy(w7, 4, res[1]+4);
  /* #38: @2 = 2 */
  w2 = 2.;
  /* #39: @2 = (@2/@1) */
  w2 /= w1;
  /* #40: @0 = (@11-@7) */
  for (i=0, rr=w0, cr=w11, cs=w7; i<4; ++i) (*rr++)  = ((*cr++)-(*cs++));
  /* #41: @0 = (@2*@0) */
  for (i=0, rr=w0, cs=w0; i<4; ++i) (*rr++)  = (w2*(*cs++));
  /* #42: @2 = 2 */
  w2 = 2.;
  /* #43: @0 = (@0/@2) */
  for (i=0, rr=w0; i<4; ++i) (*rr++) /= w2;
  /* #44: output[1][2] = @0 */
  if (res[1]) casadi_copy(w0, 4, res[1]+8);
  /* #45: @2 = 4 */
  w2 = 4.;
  /* #46: @3 = sq(@1) */
  w3 = casadi_sq( w1 );
  /* #47: @2 = (@2/@3) */
  w2 /= w3;
  /* #48: @11 = (@14-@11) */
  for (i=0, rr=w11, cr=w14, cs=w11; i<4; ++i) (*rr++)  = ((*cr++)-(*cs++));
  /* #49: @11 = (@2*@11) */
  for (i=0, rr=w11, cs=w11; i<4; ++i) (*rr++)  = (w2*(*cs++));
  /* #50: @2 = 6 */
  w2 = 6.;
  /* #51: @11 = (@11/@2) */
  for (i=0, rr=w11; i<4; ++i) (*rr++) /= w2;
  /* #52: output[1][3] = @11 */
  if (res[1]) casadi_copy(w11, 4, res[1]+12);
  /* #53: @2 = 4 */
  w2 = 4.;
  /* #54: @14 = (2.*@14) */
  for (i=0, rr=w14, cs=w14; i<4; ++i) *rr++ = (2.* *cs++ );
  /* #55: @15 = (@15-@14) */
  for (i=0, rr=w15, cs=w14; i<4; ++i) (*rr++) -= (*cs++);
  /* #56: @15 = (@15+@7) */
  for (i=0, rr=w15, cs=w7; i<4; ++i) (*rr++) += (*cs++);
  /* #57: @15 = (@2*@15) */
  for (i=0, rr=w15, cs=w15; i<4; ++i) (*rr++)  = (w2*(*cs++));
  /* #58: @2 = 3 */
  w2 = 3.;
  /* #59: @2 = pow(@1,@2) */
  w2  = pow(w1,w2);
  /* #60: @15 = (@15/@2) */
  for (i=0, rr=w15; i<4; ++i) (*rr++) /= w2;
  /* #61: @2 = 24 */
  w2 = 24.;
  /* #62: @15 = (@15/@2) */
  for (i=0, rr=w15; i<4; ++i) (*rr++) /= w2;
  /* #63: output[1][4] = @15 */
  if (res[1]) casadi_copy(w15, 4, res[1]+16);
  /* #64: @2 = 6 */
  w2 = 6.;
  /* #65: @1 = (@1/@2) */
  w1 /= w2;
  /* #66: @9 = (2.*@9) */
  w9 = (2.* w9 );
  /* #67: @8 = (@8+@9) */
  w8 += w9;
  /* #68: @12 = (2.*@12) */
  w12 = (2.* w12 );
  /* #69: @8 = (@8+@12) */
  w8 += w12;
  /* #70: @8 = (@8+@16) */
  w8 += w16;
  /* #71: @1 = (@1*@8) */
  w1 *= w8;
  /* #72: output[2][0] = @1 */
  if (res[2]) res[2][0] = w1;
  return 0;
}

/* F:(x0[4],u,T,t0,p[8])->(xf[4],Xi[4x2],poly_coeff[4x5],qf,zf[0],Zi[0],poly_coeff_z[]) */
static int casadi_f1(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem) {
  casadi_real **res1=res+7;
  const casadi_real **arg1=arg+5;
  casadi_real *w0=w+49, w1, w2, w3, *w4=w+56, *w5=w+64, *w6=w+68, w7;
  /* #0: @0 = input[0][0] */
  casadi_copy(arg[0], 4, w0);
  /* #1: @1 = input[1][0] */
  w1 = arg[1] ? arg[1][0] : 0;
  /* #2: @2 = input[3][0] */
  w2 = arg[3] ? arg[3][0] : 0;
  /* #3: @3 = input[2][0] */
  w3 = arg[2] ? arg[2][0] : 0;
  /* #4: @4 = input[4][0] */
  casadi_copy(arg[4], 8, w4);
  /* #5: {@5, @6, @7, NULL, NULL} = F(@0, @1, @2, @3, @3, @4) */
  arg1[0]=w0;
  arg1[1]=(&w1);
  arg1[2]=(&w2);
  arg1[3]=(&w3);
  arg1[4]=(&w3);
  arg1[5]=w4;
  res1[0]=w5;
  res1[1]=w6;
  res1[2]=(&w7);
  res1[3]=0;
  res1[4]=0;
  if (casadi_f2(arg1, res1, iw, w, 0)) return 1;
  /* #6: output[0][0] = @5 */
  casadi_copy(w5, 4, res[0]);
  /* #7: output[1][0] = @0 */
  casadi_copy(w0, 4, res[1]);
  /* #8: output[1][1] = @5 */
  if (res[1]) casadi_copy(w5, 4, res[1]+4);
  /* #9: output[2][0] = @6 */
  casadi_copy(w6, 20, res[2]);
  /* #10: output[3][0] = @7 */
  if (res[3]) res[3][0] = w7;
  return 0;
}

/* cost_mpc:(x[4x51],u[1x50],x_current[4],x_final[4])->(f) */
static int casadi_f0(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem) {
  casadi_int i;
  casadi_real **res1=res+1, *rr;
  const casadi_real **arg1=arg+4, *cs;
  casadi_real w0, w1, w2, w3, *w4=w+93, *w5=w+97, *w6=w+101, *w7=w+105, w8;
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
  /* #6: @1 = 0.04 */
  w1 = 4.0000000000000001e-02;
  /* #7: @2 = 0 */
  w2 = 0.;
  /* #8: @5 = input[2][0] */
  casadi_copy(arg[2], 4, w5);
  /* #9: @6 = input[3][0] */
  casadi_copy(arg[3], 4, w6);
  /* #10: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #11: {NULL, NULL, NULL, @3, NULL, NULL, NULL} = F(@4, @0, @1, @2, @7) */
  arg1[0]=w4;
  arg1[1]=(&w0);
  arg1[2]=(&w1);
  arg1[3]=(&w2);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w3);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #12: @0 = input[0][4] */
  w0 = arg[0] ? arg[0][4] : 0;
  /* #13: @1 = input[0][5] */
  w1 = arg[0] ? arg[0][5] : 0;
  /* #14: @2 = input[0][6] */
  w2 = arg[0] ? arg[0][6] : 0;
  /* #15: @8 = input[0][7] */
  w8 = arg[0] ? arg[0][7] : 0;
  /* #16: @4 = vertcat(@0, @1, @2, @8) */
  rr=w4;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  /* #17: @0 = input[1][1] */
  w0 = arg[1] ? arg[1][1] : 0;
  /* #18: @1 = 0.04 */
  w1 = 4.0000000000000001e-02;
  /* #19: @2 = 0.04 */
  w2 = 4.0000000000000001e-02;
  /* #20: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #21: {NULL, NULL, NULL, @8, NULL, NULL, NULL} = F(@4, @0, @1, @2, @7) */
  arg1[0]=w4;
  arg1[1]=(&w0);
  arg1[2]=(&w1);
  arg1[3]=(&w2);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w8);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #22: @3 = (@3+@8) */
  w3 += w8;
  /* #23: @8 = input[0][8] */
  w8 = arg[0] ? arg[0][8] : 0;
  /* #24: @0 = input[0][9] */
  w0 = arg[0] ? arg[0][9] : 0;
  /* #25: @1 = input[0][10] */
  w1 = arg[0] ? arg[0][10] : 0;
  /* #26: @2 = input[0][11] */
  w2 = arg[0] ? arg[0][11] : 0;
  /* #27: @4 = vertcat(@8, @0, @1, @2) */
  rr=w4;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  /* #28: @8 = input[1][2] */
  w8 = arg[1] ? arg[1][2] : 0;
  /* #29: @0 = 0.04 */
  w0 = 3.9999999999999994e-02;
  /* #30: @1 = 0.08 */
  w1 = 8.0000000000000002e-02;
  /* #31: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #32: {NULL, NULL, NULL, @2, NULL, NULL, NULL} = F(@4, @8, @0, @1, @7) */
  arg1[0]=w4;
  arg1[1]=(&w8);
  arg1[2]=(&w0);
  arg1[3]=(&w1);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w2);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #33: @3 = (@3+@2) */
  w3 += w2;
  /* #34: @2 = input[0][12] */
  w2 = arg[0] ? arg[0][12] : 0;
  /* #35: @8 = input[0][13] */
  w8 = arg[0] ? arg[0][13] : 0;
  /* #36: @0 = input[0][14] */
  w0 = arg[0] ? arg[0][14] : 0;
  /* #37: @1 = input[0][15] */
  w1 = arg[0] ? arg[0][15] : 0;
  /* #38: @4 = vertcat(@2, @8, @0, @1) */
  rr=w4;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  /* #39: @2 = input[1][3] */
  w2 = arg[1] ? arg[1][3] : 0;
  /* #40: @8 = 0.04 */
  w8 = 4.0000000000000008e-02;
  /* #41: @0 = 0.12 */
  w0 = 1.2000000000000000e-01;
  /* #42: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #43: {NULL, NULL, NULL, @1, NULL, NULL, NULL} = F(@4, @2, @8, @0, @7) */
  arg1[0]=w4;
  arg1[1]=(&w2);
  arg1[2]=(&w8);
  arg1[3]=(&w0);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w1);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #44: @3 = (@3+@1) */
  w3 += w1;
  /* #45: @1 = input[0][16] */
  w1 = arg[0] ? arg[0][16] : 0;
  /* #46: @2 = input[0][17] */
  w2 = arg[0] ? arg[0][17] : 0;
  /* #47: @8 = input[0][18] */
  w8 = arg[0] ? arg[0][18] : 0;
  /* #48: @0 = input[0][19] */
  w0 = arg[0] ? arg[0][19] : 0;
  /* #49: @4 = vertcat(@1, @2, @8, @0) */
  rr=w4;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  /* #50: @1 = input[1][4] */
  w1 = arg[1] ? arg[1][4] : 0;
  /* #51: @2 = 0.04 */
  w2 = 4.0000000000000008e-02;
  /* #52: @8 = 0.16 */
  w8 = 1.6000000000000000e-01;
  /* #53: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #54: {NULL, NULL, NULL, @0, NULL, NULL, NULL} = F(@4, @1, @2, @8, @7) */
  arg1[0]=w4;
  arg1[1]=(&w1);
  arg1[2]=(&w2);
  arg1[3]=(&w8);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w0);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #55: @3 = (@3+@0) */
  w3 += w0;
  /* #56: @0 = input[0][20] */
  w0 = arg[0] ? arg[0][20] : 0;
  /* #57: @1 = input[0][21] */
  w1 = arg[0] ? arg[0][21] : 0;
  /* #58: @2 = input[0][22] */
  w2 = arg[0] ? arg[0][22] : 0;
  /* #59: @8 = input[0][23] */
  w8 = arg[0] ? arg[0][23] : 0;
  /* #60: @4 = vertcat(@0, @1, @2, @8) */
  rr=w4;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  /* #61: @0 = input[1][5] */
  w0 = arg[1] ? arg[1][5] : 0;
  /* #62: @1 = 0.04 */
  w1 = 3.9999999999999980e-02;
  /* #63: @2 = 0.2 */
  w2 = 2.0000000000000001e-01;
  /* #64: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #65: {NULL, NULL, NULL, @8, NULL, NULL, NULL} = F(@4, @0, @1, @2, @7) */
  arg1[0]=w4;
  arg1[1]=(&w0);
  arg1[2]=(&w1);
  arg1[3]=(&w2);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w8);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #66: @3 = (@3+@8) */
  w3 += w8;
  /* #67: @8 = input[0][24] */
  w8 = arg[0] ? arg[0][24] : 0;
  /* #68: @0 = input[0][25] */
  w0 = arg[0] ? arg[0][25] : 0;
  /* #69: @1 = input[0][26] */
  w1 = arg[0] ? arg[0][26] : 0;
  /* #70: @2 = input[0][27] */
  w2 = arg[0] ? arg[0][27] : 0;
  /* #71: @4 = vertcat(@8, @0, @1, @2) */
  rr=w4;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  /* #72: @8 = input[1][6] */
  w8 = arg[1] ? arg[1][6] : 0;
  /* #73: @0 = 0.04 */
  w0 = 4.0000000000000036e-02;
  /* #74: @1 = 0.24 */
  w1 = 2.3999999999999999e-01;
  /* #75: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #76: {NULL, NULL, NULL, @2, NULL, NULL, NULL} = F(@4, @8, @0, @1, @7) */
  arg1[0]=w4;
  arg1[1]=(&w8);
  arg1[2]=(&w0);
  arg1[3]=(&w1);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w2);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #77: @3 = (@3+@2) */
  w3 += w2;
  /* #78: @2 = input[0][28] */
  w2 = arg[0] ? arg[0][28] : 0;
  /* #79: @8 = input[0][29] */
  w8 = arg[0] ? arg[0][29] : 0;
  /* #80: @0 = input[0][30] */
  w0 = arg[0] ? arg[0][30] : 0;
  /* #81: @1 = input[0][31] */
  w1 = arg[0] ? arg[0][31] : 0;
  /* #82: @4 = vertcat(@2, @8, @0, @1) */
  rr=w4;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  /* #83: @2 = input[1][7] */
  w2 = arg[1] ? arg[1][7] : 0;
  /* #84: @8 = 0.04 */
  w8 = 3.9999999999999980e-02;
  /* #85: @0 = 0.28 */
  w0 = 2.8000000000000003e-01;
  /* #86: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #87: {NULL, NULL, NULL, @1, NULL, NULL, NULL} = F(@4, @2, @8, @0, @7) */
  arg1[0]=w4;
  arg1[1]=(&w2);
  arg1[2]=(&w8);
  arg1[3]=(&w0);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w1);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #88: @3 = (@3+@1) */
  w3 += w1;
  /* #89: @1 = input[0][32] */
  w1 = arg[0] ? arg[0][32] : 0;
  /* #90: @2 = input[0][33] */
  w2 = arg[0] ? arg[0][33] : 0;
  /* #91: @8 = input[0][34] */
  w8 = arg[0] ? arg[0][34] : 0;
  /* #92: @0 = input[0][35] */
  w0 = arg[0] ? arg[0][35] : 0;
  /* #93: @4 = vertcat(@1, @2, @8, @0) */
  rr=w4;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  /* #94: @1 = input[1][8] */
  w1 = arg[1] ? arg[1][8] : 0;
  /* #95: @2 = 0.04 */
  w2 = 3.9999999999999980e-02;
  /* #96: @8 = 0.32 */
  w8 = 3.2000000000000001e-01;
  /* #97: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #98: {NULL, NULL, NULL, @0, NULL, NULL, NULL} = F(@4, @1, @2, @8, @7) */
  arg1[0]=w4;
  arg1[1]=(&w1);
  arg1[2]=(&w2);
  arg1[3]=(&w8);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w0);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #99: @3 = (@3+@0) */
  w3 += w0;
  /* #100: @0 = input[0][36] */
  w0 = arg[0] ? arg[0][36] : 0;
  /* #101: @1 = input[0][37] */
  w1 = arg[0] ? arg[0][37] : 0;
  /* #102: @2 = input[0][38] */
  w2 = arg[0] ? arg[0][38] : 0;
  /* #103: @8 = input[0][39] */
  w8 = arg[0] ? arg[0][39] : 0;
  /* #104: @4 = vertcat(@0, @1, @2, @8) */
  rr=w4;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  /* #105: @0 = input[1][9] */
  w0 = arg[1] ? arg[1][9] : 0;
  /* #106: @1 = 0.04 */
  w1 = 4.0000000000000036e-02;
  /* #107: @2 = 0.36 */
  w2 = 3.5999999999999999e-01;
  /* #108: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #109: {NULL, NULL, NULL, @8, NULL, NULL, NULL} = F(@4, @0, @1, @2, @7) */
  arg1[0]=w4;
  arg1[1]=(&w0);
  arg1[2]=(&w1);
  arg1[3]=(&w2);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w8);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #110: @3 = (@3+@8) */
  w3 += w8;
  /* #111: @8 = input[0][40] */
  w8 = arg[0] ? arg[0][40] : 0;
  /* #112: @0 = input[0][41] */
  w0 = arg[0] ? arg[0][41] : 0;
  /* #113: @1 = input[0][42] */
  w1 = arg[0] ? arg[0][42] : 0;
  /* #114: @2 = input[0][43] */
  w2 = arg[0] ? arg[0][43] : 0;
  /* #115: @4 = vertcat(@8, @0, @1, @2) */
  rr=w4;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  /* #116: @8 = input[1][10] */
  w8 = arg[1] ? arg[1][10] : 0;
  /* #117: @0 = 0.04 */
  w0 = 3.9999999999999980e-02;
  /* #118: @1 = 0.4 */
  w1 = 4.0000000000000002e-01;
  /* #119: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #120: {NULL, NULL, NULL, @2, NULL, NULL, NULL} = F(@4, @8, @0, @1, @7) */
  arg1[0]=w4;
  arg1[1]=(&w8);
  arg1[2]=(&w0);
  arg1[3]=(&w1);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w2);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #121: @3 = (@3+@2) */
  w3 += w2;
  /* #122: @2 = input[0][44] */
  w2 = arg[0] ? arg[0][44] : 0;
  /* #123: @8 = input[0][45] */
  w8 = arg[0] ? arg[0][45] : 0;
  /* #124: @0 = input[0][46] */
  w0 = arg[0] ? arg[0][46] : 0;
  /* #125: @1 = input[0][47] */
  w1 = arg[0] ? arg[0][47] : 0;
  /* #126: @4 = vertcat(@2, @8, @0, @1) */
  rr=w4;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  /* #127: @2 = input[1][11] */
  w2 = arg[1] ? arg[1][11] : 0;
  /* #128: @8 = 0.04 */
  w8 = 3.9999999999999980e-02;
  /* #129: @0 = 0.44 */
  w0 = 4.4000000000000000e-01;
  /* #130: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #131: {NULL, NULL, NULL, @1, NULL, NULL, NULL} = F(@4, @2, @8, @0, @7) */
  arg1[0]=w4;
  arg1[1]=(&w2);
  arg1[2]=(&w8);
  arg1[3]=(&w0);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w1);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #132: @3 = (@3+@1) */
  w3 += w1;
  /* #133: @1 = input[0][48] */
  w1 = arg[0] ? arg[0][48] : 0;
  /* #134: @2 = input[0][49] */
  w2 = arg[0] ? arg[0][49] : 0;
  /* #135: @8 = input[0][50] */
  w8 = arg[0] ? arg[0][50] : 0;
  /* #136: @0 = input[0][51] */
  w0 = arg[0] ? arg[0][51] : 0;
  /* #137: @4 = vertcat(@1, @2, @8, @0) */
  rr=w4;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  /* #138: @1 = input[1][12] */
  w1 = arg[1] ? arg[1][12] : 0;
  /* #139: @2 = 0.04 */
  w2 = 4.0000000000000036e-02;
  /* #140: @8 = 0.48 */
  w8 = 4.7999999999999998e-01;
  /* #141: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #142: {NULL, NULL, NULL, @0, NULL, NULL, NULL} = F(@4, @1, @2, @8, @7) */
  arg1[0]=w4;
  arg1[1]=(&w1);
  arg1[2]=(&w2);
  arg1[3]=(&w8);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w0);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #143: @3 = (@3+@0) */
  w3 += w0;
  /* #144: @0 = input[0][52] */
  w0 = arg[0] ? arg[0][52] : 0;
  /* #145: @1 = input[0][53] */
  w1 = arg[0] ? arg[0][53] : 0;
  /* #146: @2 = input[0][54] */
  w2 = arg[0] ? arg[0][54] : 0;
  /* #147: @8 = input[0][55] */
  w8 = arg[0] ? arg[0][55] : 0;
  /* #148: @4 = vertcat(@0, @1, @2, @8) */
  rr=w4;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  /* #149: @0 = input[1][13] */
  w0 = arg[1] ? arg[1][13] : 0;
  /* #150: @1 = 0.04 */
  w1 = 4.0000000000000036e-02;
  /* #151: @2 = 0.52 */
  w2 = 5.2000000000000002e-01;
  /* #152: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #153: {NULL, NULL, NULL, @8, NULL, NULL, NULL} = F(@4, @0, @1, @2, @7) */
  arg1[0]=w4;
  arg1[1]=(&w0);
  arg1[2]=(&w1);
  arg1[3]=(&w2);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w8);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #154: @3 = (@3+@8) */
  w3 += w8;
  /* #155: @8 = input[0][56] */
  w8 = arg[0] ? arg[0][56] : 0;
  /* #156: @0 = input[0][57] */
  w0 = arg[0] ? arg[0][57] : 0;
  /* #157: @1 = input[0][58] */
  w1 = arg[0] ? arg[0][58] : 0;
  /* #158: @2 = input[0][59] */
  w2 = arg[0] ? arg[0][59] : 0;
  /* #159: @4 = vertcat(@8, @0, @1, @2) */
  rr=w4;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  /* #160: @8 = input[1][14] */
  w8 = arg[1] ? arg[1][14] : 0;
  /* #161: @0 = 0.04 */
  w0 = 3.9999999999999925e-02;
  /* #162: @1 = 0.56 */
  w1 = 5.6000000000000005e-01;
  /* #163: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #164: {NULL, NULL, NULL, @2, NULL, NULL, NULL} = F(@4, @8, @0, @1, @7) */
  arg1[0]=w4;
  arg1[1]=(&w8);
  arg1[2]=(&w0);
  arg1[3]=(&w1);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w2);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #165: @3 = (@3+@2) */
  w3 += w2;
  /* #166: @2 = input[0][60] */
  w2 = arg[0] ? arg[0][60] : 0;
  /* #167: @8 = input[0][61] */
  w8 = arg[0] ? arg[0][61] : 0;
  /* #168: @0 = input[0][62] */
  w0 = arg[0] ? arg[0][62] : 0;
  /* #169: @1 = input[0][63] */
  w1 = arg[0] ? arg[0][63] : 0;
  /* #170: @4 = vertcat(@2, @8, @0, @1) */
  rr=w4;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  /* #171: @2 = input[1][15] */
  w2 = arg[1] ? arg[1][15] : 0;
  /* #172: @8 = 0.04 */
  w8 = 4.0000000000000036e-02;
  /* #173: @0 = 0.6 */
  w0 = 5.9999999999999998e-01;
  /* #174: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #175: {NULL, NULL, NULL, @1, NULL, NULL, NULL} = F(@4, @2, @8, @0, @7) */
  arg1[0]=w4;
  arg1[1]=(&w2);
  arg1[2]=(&w8);
  arg1[3]=(&w0);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w1);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #176: @3 = (@3+@1) */
  w3 += w1;
  /* #177: @1 = input[0][64] */
  w1 = arg[0] ? arg[0][64] : 0;
  /* #178: @2 = input[0][65] */
  w2 = arg[0] ? arg[0][65] : 0;
  /* #179: @8 = input[0][66] */
  w8 = arg[0] ? arg[0][66] : 0;
  /* #180: @0 = input[0][67] */
  w0 = arg[0] ? arg[0][67] : 0;
  /* #181: @4 = vertcat(@1, @2, @8, @0) */
  rr=w4;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  /* #182: @1 = input[1][16] */
  w1 = arg[1] ? arg[1][16] : 0;
  /* #183: @2 = 0.04 */
  w2 = 4.0000000000000036e-02;
  /* #184: @8 = 0.64 */
  w8 = 6.4000000000000001e-01;
  /* #185: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #186: {NULL, NULL, NULL, @0, NULL, NULL, NULL} = F(@4, @1, @2, @8, @7) */
  arg1[0]=w4;
  arg1[1]=(&w1);
  arg1[2]=(&w2);
  arg1[3]=(&w8);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w0);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #187: @3 = (@3+@0) */
  w3 += w0;
  /* #188: @0 = input[0][68] */
  w0 = arg[0] ? arg[0][68] : 0;
  /* #189: @1 = input[0][69] */
  w1 = arg[0] ? arg[0][69] : 0;
  /* #190: @2 = input[0][70] */
  w2 = arg[0] ? arg[0][70] : 0;
  /* #191: @8 = input[0][71] */
  w8 = arg[0] ? arg[0][71] : 0;
  /* #192: @4 = vertcat(@0, @1, @2, @8) */
  rr=w4;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  /* #193: @0 = input[1][17] */
  w0 = arg[1] ? arg[1][17] : 0;
  /* #194: @1 = 0.04 */
  w1 = 3.9999999999999925e-02;
  /* #195: @2 = 0.68 */
  w2 = 6.8000000000000005e-01;
  /* #196: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #197: {NULL, NULL, NULL, @8, NULL, NULL, NULL} = F(@4, @0, @1, @2, @7) */
  arg1[0]=w4;
  arg1[1]=(&w0);
  arg1[2]=(&w1);
  arg1[3]=(&w2);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w8);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #198: @3 = (@3+@8) */
  w3 += w8;
  /* #199: @8 = input[0][72] */
  w8 = arg[0] ? arg[0][72] : 0;
  /* #200: @0 = input[0][73] */
  w0 = arg[0] ? arg[0][73] : 0;
  /* #201: @1 = input[0][74] */
  w1 = arg[0] ? arg[0][74] : 0;
  /* #202: @2 = input[0][75] */
  w2 = arg[0] ? arg[0][75] : 0;
  /* #203: @4 = vertcat(@8, @0, @1, @2) */
  rr=w4;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  /* #204: @8 = input[1][18] */
  w8 = arg[1] ? arg[1][18] : 0;
  /* #205: @0 = 0.04 */
  w0 = 4.0000000000000036e-02;
  /* #206: @1 = 0.72 */
  w1 = 7.1999999999999997e-01;
  /* #207: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #208: {NULL, NULL, NULL, @2, NULL, NULL, NULL} = F(@4, @8, @0, @1, @7) */
  arg1[0]=w4;
  arg1[1]=(&w8);
  arg1[2]=(&w0);
  arg1[3]=(&w1);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w2);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #209: @3 = (@3+@2) */
  w3 += w2;
  /* #210: @2 = input[0][76] */
  w2 = arg[0] ? arg[0][76] : 0;
  /* #211: @8 = input[0][77] */
  w8 = arg[0] ? arg[0][77] : 0;
  /* #212: @0 = input[0][78] */
  w0 = arg[0] ? arg[0][78] : 0;
  /* #213: @1 = input[0][79] */
  w1 = arg[0] ? arg[0][79] : 0;
  /* #214: @4 = vertcat(@2, @8, @0, @1) */
  rr=w4;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  /* #215: @2 = input[1][19] */
  w2 = arg[1] ? arg[1][19] : 0;
  /* #216: @8 = 0.04 */
  w8 = 4.0000000000000036e-02;
  /* #217: @0 = 0.76 */
  w0 = 7.6000000000000001e-01;
  /* #218: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #219: {NULL, NULL, NULL, @1, NULL, NULL, NULL} = F(@4, @2, @8, @0, @7) */
  arg1[0]=w4;
  arg1[1]=(&w2);
  arg1[2]=(&w8);
  arg1[3]=(&w0);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w1);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #220: @3 = (@3+@1) */
  w3 += w1;
  /* #221: @1 = input[0][80] */
  w1 = arg[0] ? arg[0][80] : 0;
  /* #222: @2 = input[0][81] */
  w2 = arg[0] ? arg[0][81] : 0;
  /* #223: @8 = input[0][82] */
  w8 = arg[0] ? arg[0][82] : 0;
  /* #224: @0 = input[0][83] */
  w0 = arg[0] ? arg[0][83] : 0;
  /* #225: @4 = vertcat(@1, @2, @8, @0) */
  rr=w4;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  /* #226: @1 = input[1][20] */
  w1 = arg[1] ? arg[1][20] : 0;
  /* #227: @2 = 0.04 */
  w2 = 3.9999999999999925e-02;
  /* #228: @8 = 0.8 */
  w8 = 8.0000000000000004e-01;
  /* #229: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #230: {NULL, NULL, NULL, @0, NULL, NULL, NULL} = F(@4, @1, @2, @8, @7) */
  arg1[0]=w4;
  arg1[1]=(&w1);
  arg1[2]=(&w2);
  arg1[3]=(&w8);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w0);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #231: @3 = (@3+@0) */
  w3 += w0;
  /* #232: @0 = input[0][84] */
  w0 = arg[0] ? arg[0][84] : 0;
  /* #233: @1 = input[0][85] */
  w1 = arg[0] ? arg[0][85] : 0;
  /* #234: @2 = input[0][86] */
  w2 = arg[0] ? arg[0][86] : 0;
  /* #235: @8 = input[0][87] */
  w8 = arg[0] ? arg[0][87] : 0;
  /* #236: @4 = vertcat(@0, @1, @2, @8) */
  rr=w4;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  /* #237: @0 = input[1][21] */
  w0 = arg[1] ? arg[1][21] : 0;
  /* #238: @1 = 0.04 */
  w1 = 4.0000000000000036e-02;
  /* #239: @2 = 0.84 */
  w2 = 8.3999999999999997e-01;
  /* #240: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #241: {NULL, NULL, NULL, @8, NULL, NULL, NULL} = F(@4, @0, @1, @2, @7) */
  arg1[0]=w4;
  arg1[1]=(&w0);
  arg1[2]=(&w1);
  arg1[3]=(&w2);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w8);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #242: @3 = (@3+@8) */
  w3 += w8;
  /* #243: @8 = input[0][88] */
  w8 = arg[0] ? arg[0][88] : 0;
  /* #244: @0 = input[0][89] */
  w0 = arg[0] ? arg[0][89] : 0;
  /* #245: @1 = input[0][90] */
  w1 = arg[0] ? arg[0][90] : 0;
  /* #246: @2 = input[0][91] */
  w2 = arg[0] ? arg[0][91] : 0;
  /* #247: @4 = vertcat(@8, @0, @1, @2) */
  rr=w4;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  /* #248: @8 = input[1][22] */
  w8 = arg[1] ? arg[1][22] : 0;
  /* #249: @0 = 0.04 */
  w0 = 4.0000000000000036e-02;
  /* #250: @1 = 0.88 */
  w1 = 8.8000000000000000e-01;
  /* #251: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #252: {NULL, NULL, NULL, @2, NULL, NULL, NULL} = F(@4, @8, @0, @1, @7) */
  arg1[0]=w4;
  arg1[1]=(&w8);
  arg1[2]=(&w0);
  arg1[3]=(&w1);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w2);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #253: @3 = (@3+@2) */
  w3 += w2;
  /* #254: @2 = input[0][92] */
  w2 = arg[0] ? arg[0][92] : 0;
  /* #255: @8 = input[0][93] */
  w8 = arg[0] ? arg[0][93] : 0;
  /* #256: @0 = input[0][94] */
  w0 = arg[0] ? arg[0][94] : 0;
  /* #257: @1 = input[0][95] */
  w1 = arg[0] ? arg[0][95] : 0;
  /* #258: @4 = vertcat(@2, @8, @0, @1) */
  rr=w4;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  /* #259: @2 = input[1][23] */
  w2 = arg[1] ? arg[1][23] : 0;
  /* #260: @8 = 0.04 */
  w8 = 3.9999999999999925e-02;
  /* #261: @0 = 0.92 */
  w0 = 9.2000000000000004e-01;
  /* #262: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #263: {NULL, NULL, NULL, @1, NULL, NULL, NULL} = F(@4, @2, @8, @0, @7) */
  arg1[0]=w4;
  arg1[1]=(&w2);
  arg1[2]=(&w8);
  arg1[3]=(&w0);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w1);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #264: @3 = (@3+@1) */
  w3 += w1;
  /* #265: @1 = input[0][96] */
  w1 = arg[0] ? arg[0][96] : 0;
  /* #266: @2 = input[0][97] */
  w2 = arg[0] ? arg[0][97] : 0;
  /* #267: @8 = input[0][98] */
  w8 = arg[0] ? arg[0][98] : 0;
  /* #268: @0 = input[0][99] */
  w0 = arg[0] ? arg[0][99] : 0;
  /* #269: @4 = vertcat(@1, @2, @8, @0) */
  rr=w4;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  /* #270: @1 = input[1][24] */
  w1 = arg[1] ? arg[1][24] : 0;
  /* #271: @2 = 0.04 */
  w2 = 4.0000000000000036e-02;
  /* #272: @8 = 0.96 */
  w8 = 9.5999999999999996e-01;
  /* #273: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #274: {NULL, NULL, NULL, @0, NULL, NULL, NULL} = F(@4, @1, @2, @8, @7) */
  arg1[0]=w4;
  arg1[1]=(&w1);
  arg1[2]=(&w2);
  arg1[3]=(&w8);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w0);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #275: @3 = (@3+@0) */
  w3 += w0;
  /* #276: @0 = input[0][100] */
  w0 = arg[0] ? arg[0][100] : 0;
  /* #277: @1 = input[0][101] */
  w1 = arg[0] ? arg[0][101] : 0;
  /* #278: @2 = input[0][102] */
  w2 = arg[0] ? arg[0][102] : 0;
  /* #279: @8 = input[0][103] */
  w8 = arg[0] ? arg[0][103] : 0;
  /* #280: @4 = vertcat(@0, @1, @2, @8) */
  rr=w4;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  /* #281: @0 = input[1][25] */
  w0 = arg[1] ? arg[1][25] : 0;
  /* #282: @1 = 0.04 */
  w1 = 4.0000000000000036e-02;
  /* #283: @2 = 1 */
  w2 = 1.;
  /* #284: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #285: {NULL, NULL, NULL, @8, NULL, NULL, NULL} = F(@4, @0, @1, @2, @7) */
  arg1[0]=w4;
  arg1[1]=(&w0);
  arg1[2]=(&w1);
  arg1[3]=(&w2);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w8);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #286: @3 = (@3+@8) */
  w3 += w8;
  /* #287: @8 = input[0][104] */
  w8 = arg[0] ? arg[0][104] : 0;
  /* #288: @0 = input[0][105] */
  w0 = arg[0] ? arg[0][105] : 0;
  /* #289: @1 = input[0][106] */
  w1 = arg[0] ? arg[0][106] : 0;
  /* #290: @2 = input[0][107] */
  w2 = arg[0] ? arg[0][107] : 0;
  /* #291: @4 = vertcat(@8, @0, @1, @2) */
  rr=w4;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  /* #292: @8 = input[1][26] */
  w8 = arg[1] ? arg[1][26] : 0;
  /* #293: @0 = 0.04 */
  w0 = 4.0000000000000036e-02;
  /* #294: @1 = 1.04 */
  w1 = 1.0400000000000000e+00;
  /* #295: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #296: {NULL, NULL, NULL, @2, NULL, NULL, NULL} = F(@4, @8, @0, @1, @7) */
  arg1[0]=w4;
  arg1[1]=(&w8);
  arg1[2]=(&w0);
  arg1[3]=(&w1);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w2);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #297: @3 = (@3+@2) */
  w3 += w2;
  /* #298: @2 = input[0][108] */
  w2 = arg[0] ? arg[0][108] : 0;
  /* #299: @8 = input[0][109] */
  w8 = arg[0] ? arg[0][109] : 0;
  /* #300: @0 = input[0][110] */
  w0 = arg[0] ? arg[0][110] : 0;
  /* #301: @1 = input[0][111] */
  w1 = arg[0] ? arg[0][111] : 0;
  /* #302: @4 = vertcat(@2, @8, @0, @1) */
  rr=w4;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  /* #303: @2 = input[1][27] */
  w2 = arg[1] ? arg[1][27] : 0;
  /* #304: @8 = 0.04 */
  w8 = 4.0000000000000036e-02;
  /* #305: @0 = 1.08 */
  w0 = 1.0800000000000001e+00;
  /* #306: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #307: {NULL, NULL, NULL, @1, NULL, NULL, NULL} = F(@4, @2, @8, @0, @7) */
  arg1[0]=w4;
  arg1[1]=(&w2);
  arg1[2]=(&w8);
  arg1[3]=(&w0);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w1);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #308: @3 = (@3+@1) */
  w3 += w1;
  /* #309: @1 = input[0][112] */
  w1 = arg[0] ? arg[0][112] : 0;
  /* #310: @2 = input[0][113] */
  w2 = arg[0] ? arg[0][113] : 0;
  /* #311: @8 = input[0][114] */
  w8 = arg[0] ? arg[0][114] : 0;
  /* #312: @0 = input[0][115] */
  w0 = arg[0] ? arg[0][115] : 0;
  /* #313: @4 = vertcat(@1, @2, @8, @0) */
  rr=w4;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  /* #314: @1 = input[1][28] */
  w1 = arg[1] ? arg[1][28] : 0;
  /* #315: @2 = 0.04 */
  w2 = 3.9999999999999813e-02;
  /* #316: @8 = 1.12 */
  w8 = 1.1200000000000001e+00;
  /* #317: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #318: {NULL, NULL, NULL, @0, NULL, NULL, NULL} = F(@4, @1, @2, @8, @7) */
  arg1[0]=w4;
  arg1[1]=(&w1);
  arg1[2]=(&w2);
  arg1[3]=(&w8);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w0);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #319: @3 = (@3+@0) */
  w3 += w0;
  /* #320: @0 = input[0][116] */
  w0 = arg[0] ? arg[0][116] : 0;
  /* #321: @1 = input[0][117] */
  w1 = arg[0] ? arg[0][117] : 0;
  /* #322: @2 = input[0][118] */
  w2 = arg[0] ? arg[0][118] : 0;
  /* #323: @8 = input[0][119] */
  w8 = arg[0] ? arg[0][119] : 0;
  /* #324: @4 = vertcat(@0, @1, @2, @8) */
  rr=w4;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  /* #325: @0 = input[1][29] */
  w0 = arg[1] ? arg[1][29] : 0;
  /* #326: @1 = 0.04 */
  w1 = 4.0000000000000036e-02;
  /* #327: @2 = 1.16 */
  w2 = 1.1599999999999999e+00;
  /* #328: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #329: {NULL, NULL, NULL, @8, NULL, NULL, NULL} = F(@4, @0, @1, @2, @7) */
  arg1[0]=w4;
  arg1[1]=(&w0);
  arg1[2]=(&w1);
  arg1[3]=(&w2);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w8);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #330: @3 = (@3+@8) */
  w3 += w8;
  /* #331: @8 = input[0][120] */
  w8 = arg[0] ? arg[0][120] : 0;
  /* #332: @0 = input[0][121] */
  w0 = arg[0] ? arg[0][121] : 0;
  /* #333: @1 = input[0][122] */
  w1 = arg[0] ? arg[0][122] : 0;
  /* #334: @2 = input[0][123] */
  w2 = arg[0] ? arg[0][123] : 0;
  /* #335: @4 = vertcat(@8, @0, @1, @2) */
  rr=w4;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  /* #336: @8 = input[1][30] */
  w8 = arg[1] ? arg[1][30] : 0;
  /* #337: @0 = 0.04 */
  w0 = 4.0000000000000036e-02;
  /* #338: @1 = 1.2 */
  w1 = 1.2000000000000000e+00;
  /* #339: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #340: {NULL, NULL, NULL, @2, NULL, NULL, NULL} = F(@4, @8, @0, @1, @7) */
  arg1[0]=w4;
  arg1[1]=(&w8);
  arg1[2]=(&w0);
  arg1[3]=(&w1);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w2);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #341: @3 = (@3+@2) */
  w3 += w2;
  /* #342: @2 = input[0][124] */
  w2 = arg[0] ? arg[0][124] : 0;
  /* #343: @8 = input[0][125] */
  w8 = arg[0] ? arg[0][125] : 0;
  /* #344: @0 = input[0][126] */
  w0 = arg[0] ? arg[0][126] : 0;
  /* #345: @1 = input[0][127] */
  w1 = arg[0] ? arg[0][127] : 0;
  /* #346: @4 = vertcat(@2, @8, @0, @1) */
  rr=w4;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  /* #347: @2 = input[1][31] */
  w2 = arg[1] ? arg[1][31] : 0;
  /* #348: @8 = 0.04 */
  w8 = 4.0000000000000036e-02;
  /* #349: @0 = 1.24 */
  w0 = 1.2400000000000000e+00;
  /* #350: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #351: {NULL, NULL, NULL, @1, NULL, NULL, NULL} = F(@4, @2, @8, @0, @7) */
  arg1[0]=w4;
  arg1[1]=(&w2);
  arg1[2]=(&w8);
  arg1[3]=(&w0);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w1);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #352: @3 = (@3+@1) */
  w3 += w1;
  /* #353: @1 = input[0][128] */
  w1 = arg[0] ? arg[0][128] : 0;
  /* #354: @2 = input[0][129] */
  w2 = arg[0] ? arg[0][129] : 0;
  /* #355: @8 = input[0][130] */
  w8 = arg[0] ? arg[0][130] : 0;
  /* #356: @0 = input[0][131] */
  w0 = arg[0] ? arg[0][131] : 0;
  /* #357: @4 = vertcat(@1, @2, @8, @0) */
  rr=w4;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  /* #358: @1 = input[1][32] */
  w1 = arg[1] ? arg[1][32] : 0;
  /* #359: @2 = 0.04 */
  w2 = 4.0000000000000036e-02;
  /* #360: @8 = 1.28 */
  w8 = 1.2800000000000000e+00;
  /* #361: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #362: {NULL, NULL, NULL, @0, NULL, NULL, NULL} = F(@4, @1, @2, @8, @7) */
  arg1[0]=w4;
  arg1[1]=(&w1);
  arg1[2]=(&w2);
  arg1[3]=(&w8);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w0);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #363: @3 = (@3+@0) */
  w3 += w0;
  /* #364: @0 = input[0][132] */
  w0 = arg[0] ? arg[0][132] : 0;
  /* #365: @1 = input[0][133] */
  w1 = arg[0] ? arg[0][133] : 0;
  /* #366: @2 = input[0][134] */
  w2 = arg[0] ? arg[0][134] : 0;
  /* #367: @8 = input[0][135] */
  w8 = arg[0] ? arg[0][135] : 0;
  /* #368: @4 = vertcat(@0, @1, @2, @8) */
  rr=w4;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  /* #369: @0 = input[1][33] */
  w0 = arg[1] ? arg[1][33] : 0;
  /* #370: @1 = 0.04 */
  w1 = 4.0000000000000036e-02;
  /* #371: @2 = 1.32 */
  w2 = 1.3200000000000001e+00;
  /* #372: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #373: {NULL, NULL, NULL, @8, NULL, NULL, NULL} = F(@4, @0, @1, @2, @7) */
  arg1[0]=w4;
  arg1[1]=(&w0);
  arg1[2]=(&w1);
  arg1[3]=(&w2);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w8);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #374: @3 = (@3+@8) */
  w3 += w8;
  /* #375: @8 = input[0][136] */
  w8 = arg[0] ? arg[0][136] : 0;
  /* #376: @0 = input[0][137] */
  w0 = arg[0] ? arg[0][137] : 0;
  /* #377: @1 = input[0][138] */
  w1 = arg[0] ? arg[0][138] : 0;
  /* #378: @2 = input[0][139] */
  w2 = arg[0] ? arg[0][139] : 0;
  /* #379: @4 = vertcat(@8, @0, @1, @2) */
  rr=w4;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  /* #380: @8 = input[1][34] */
  w8 = arg[1] ? arg[1][34] : 0;
  /* #381: @0 = 0.04 */
  w0 = 4.0000000000000036e-02;
  /* #382: @1 = 1.36 */
  w1 = 1.3600000000000001e+00;
  /* #383: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #384: {NULL, NULL, NULL, @2, NULL, NULL, NULL} = F(@4, @8, @0, @1, @7) */
  arg1[0]=w4;
  arg1[1]=(&w8);
  arg1[2]=(&w0);
  arg1[3]=(&w1);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w2);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #385: @3 = (@3+@2) */
  w3 += w2;
  /* #386: @2 = input[0][140] */
  w2 = arg[0] ? arg[0][140] : 0;
  /* #387: @8 = input[0][141] */
  w8 = arg[0] ? arg[0][141] : 0;
  /* #388: @0 = input[0][142] */
  w0 = arg[0] ? arg[0][142] : 0;
  /* #389: @1 = input[0][143] */
  w1 = arg[0] ? arg[0][143] : 0;
  /* #390: @4 = vertcat(@2, @8, @0, @1) */
  rr=w4;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  /* #391: @2 = input[1][35] */
  w2 = arg[1] ? arg[1][35] : 0;
  /* #392: @8 = 0.04 */
  w8 = 3.9999999999999813e-02;
  /* #393: @0 = 1.4 */
  w0 = 1.4000000000000001e+00;
  /* #394: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #395: {NULL, NULL, NULL, @1, NULL, NULL, NULL} = F(@4, @2, @8, @0, @7) */
  arg1[0]=w4;
  arg1[1]=(&w2);
  arg1[2]=(&w8);
  arg1[3]=(&w0);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w1);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #396: @3 = (@3+@1) */
  w3 += w1;
  /* #397: @1 = input[0][144] */
  w1 = arg[0] ? arg[0][144] : 0;
  /* #398: @2 = input[0][145] */
  w2 = arg[0] ? arg[0][145] : 0;
  /* #399: @8 = input[0][146] */
  w8 = arg[0] ? arg[0][146] : 0;
  /* #400: @0 = input[0][147] */
  w0 = arg[0] ? arg[0][147] : 0;
  /* #401: @4 = vertcat(@1, @2, @8, @0) */
  rr=w4;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  /* #402: @1 = input[1][36] */
  w1 = arg[1] ? arg[1][36] : 0;
  /* #403: @2 = 0.04 */
  w2 = 4.0000000000000036e-02;
  /* #404: @8 = 1.44 */
  w8 = 1.4399999999999999e+00;
  /* #405: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #406: {NULL, NULL, NULL, @0, NULL, NULL, NULL} = F(@4, @1, @2, @8, @7) */
  arg1[0]=w4;
  arg1[1]=(&w1);
  arg1[2]=(&w2);
  arg1[3]=(&w8);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w0);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #407: @3 = (@3+@0) */
  w3 += w0;
  /* #408: @0 = input[0][148] */
  w0 = arg[0] ? arg[0][148] : 0;
  /* #409: @1 = input[0][149] */
  w1 = arg[0] ? arg[0][149] : 0;
  /* #410: @2 = input[0][150] */
  w2 = arg[0] ? arg[0][150] : 0;
  /* #411: @8 = input[0][151] */
  w8 = arg[0] ? arg[0][151] : 0;
  /* #412: @4 = vertcat(@0, @1, @2, @8) */
  rr=w4;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  /* #413: @0 = input[1][37] */
  w0 = arg[1] ? arg[1][37] : 0;
  /* #414: @1 = 0.04 */
  w1 = 4.0000000000000036e-02;
  /* #415: @2 = 1.48 */
  w2 = 1.4800000000000000e+00;
  /* #416: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #417: {NULL, NULL, NULL, @8, NULL, NULL, NULL} = F(@4, @0, @1, @2, @7) */
  arg1[0]=w4;
  arg1[1]=(&w0);
  arg1[2]=(&w1);
  arg1[3]=(&w2);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w8);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #418: @3 = (@3+@8) */
  w3 += w8;
  /* #419: @8 = input[0][152] */
  w8 = arg[0] ? arg[0][152] : 0;
  /* #420: @0 = input[0][153] */
  w0 = arg[0] ? arg[0][153] : 0;
  /* #421: @1 = input[0][154] */
  w1 = arg[0] ? arg[0][154] : 0;
  /* #422: @2 = input[0][155] */
  w2 = arg[0] ? arg[0][155] : 0;
  /* #423: @4 = vertcat(@8, @0, @1, @2) */
  rr=w4;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  /* #424: @8 = input[1][38] */
  w8 = arg[1] ? arg[1][38] : 0;
  /* #425: @0 = 0.04 */
  w0 = 4.0000000000000036e-02;
  /* #426: @1 = 1.52 */
  w1 = 1.5200000000000000e+00;
  /* #427: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #428: {NULL, NULL, NULL, @2, NULL, NULL, NULL} = F(@4, @8, @0, @1, @7) */
  arg1[0]=w4;
  arg1[1]=(&w8);
  arg1[2]=(&w0);
  arg1[3]=(&w1);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w2);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #429: @3 = (@3+@2) */
  w3 += w2;
  /* #430: @2 = input[0][156] */
  w2 = arg[0] ? arg[0][156] : 0;
  /* #431: @8 = input[0][157] */
  w8 = arg[0] ? arg[0][157] : 0;
  /* #432: @0 = input[0][158] */
  w0 = arg[0] ? arg[0][158] : 0;
  /* #433: @1 = input[0][159] */
  w1 = arg[0] ? arg[0][159] : 0;
  /* #434: @4 = vertcat(@2, @8, @0, @1) */
  rr=w4;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  /* #435: @2 = input[1][39] */
  w2 = arg[1] ? arg[1][39] : 0;
  /* #436: @8 = 0.04 */
  w8 = 4.0000000000000036e-02;
  /* #437: @0 = 1.56 */
  w0 = 1.5600000000000001e+00;
  /* #438: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #439: {NULL, NULL, NULL, @1, NULL, NULL, NULL} = F(@4, @2, @8, @0, @7) */
  arg1[0]=w4;
  arg1[1]=(&w2);
  arg1[2]=(&w8);
  arg1[3]=(&w0);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w1);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #440: @3 = (@3+@1) */
  w3 += w1;
  /* #441: @1 = input[0][160] */
  w1 = arg[0] ? arg[0][160] : 0;
  /* #442: @2 = input[0][161] */
  w2 = arg[0] ? arg[0][161] : 0;
  /* #443: @8 = input[0][162] */
  w8 = arg[0] ? arg[0][162] : 0;
  /* #444: @0 = input[0][163] */
  w0 = arg[0] ? arg[0][163] : 0;
  /* #445: @4 = vertcat(@1, @2, @8, @0) */
  rr=w4;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  /* #446: @1 = input[1][40] */
  w1 = arg[1] ? arg[1][40] : 0;
  /* #447: @2 = 0.04 */
  w2 = 4.0000000000000036e-02;
  /* #448: @8 = 1.6 */
  w8 = 1.6000000000000001e+00;
  /* #449: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #450: {NULL, NULL, NULL, @0, NULL, NULL, NULL} = F(@4, @1, @2, @8, @7) */
  arg1[0]=w4;
  arg1[1]=(&w1);
  arg1[2]=(&w2);
  arg1[3]=(&w8);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w0);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #451: @3 = (@3+@0) */
  w3 += w0;
  /* #452: @0 = input[0][164] */
  w0 = arg[0] ? arg[0][164] : 0;
  /* #453: @1 = input[0][165] */
  w1 = arg[0] ? arg[0][165] : 0;
  /* #454: @2 = input[0][166] */
  w2 = arg[0] ? arg[0][166] : 0;
  /* #455: @8 = input[0][167] */
  w8 = arg[0] ? arg[0][167] : 0;
  /* #456: @4 = vertcat(@0, @1, @2, @8) */
  rr=w4;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  /* #457: @0 = input[1][41] */
  w0 = arg[1] ? arg[1][41] : 0;
  /* #458: @1 = 0.04 */
  w1 = 3.9999999999999813e-02;
  /* #459: @2 = 1.64 */
  w2 = 1.6400000000000001e+00;
  /* #460: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #461: {NULL, NULL, NULL, @8, NULL, NULL, NULL} = F(@4, @0, @1, @2, @7) */
  arg1[0]=w4;
  arg1[1]=(&w0);
  arg1[2]=(&w1);
  arg1[3]=(&w2);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w8);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #462: @3 = (@3+@8) */
  w3 += w8;
  /* #463: @8 = input[0][168] */
  w8 = arg[0] ? arg[0][168] : 0;
  /* #464: @0 = input[0][169] */
  w0 = arg[0] ? arg[0][169] : 0;
  /* #465: @1 = input[0][170] */
  w1 = arg[0] ? arg[0][170] : 0;
  /* #466: @2 = input[0][171] */
  w2 = arg[0] ? arg[0][171] : 0;
  /* #467: @4 = vertcat(@8, @0, @1, @2) */
  rr=w4;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  /* #468: @8 = input[1][42] */
  w8 = arg[1] ? arg[1][42] : 0;
  /* #469: @0 = 0.04 */
  w0 = 4.0000000000000036e-02;
  /* #470: @1 = 1.68 */
  w1 = 1.6799999999999999e+00;
  /* #471: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #472: {NULL, NULL, NULL, @2, NULL, NULL, NULL} = F(@4, @8, @0, @1, @7) */
  arg1[0]=w4;
  arg1[1]=(&w8);
  arg1[2]=(&w0);
  arg1[3]=(&w1);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w2);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #473: @3 = (@3+@2) */
  w3 += w2;
  /* #474: @2 = input[0][172] */
  w2 = arg[0] ? arg[0][172] : 0;
  /* #475: @8 = input[0][173] */
  w8 = arg[0] ? arg[0][173] : 0;
  /* #476: @0 = input[0][174] */
  w0 = arg[0] ? arg[0][174] : 0;
  /* #477: @1 = input[0][175] */
  w1 = arg[0] ? arg[0][175] : 0;
  /* #478: @4 = vertcat(@2, @8, @0, @1) */
  rr=w4;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  /* #479: @2 = input[1][43] */
  w2 = arg[1] ? arg[1][43] : 0;
  /* #480: @8 = 0.04 */
  w8 = 4.0000000000000036e-02;
  /* #481: @0 = 1.72 */
  w0 = 1.7200000000000000e+00;
  /* #482: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #483: {NULL, NULL, NULL, @1, NULL, NULL, NULL} = F(@4, @2, @8, @0, @7) */
  arg1[0]=w4;
  arg1[1]=(&w2);
  arg1[2]=(&w8);
  arg1[3]=(&w0);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w1);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #484: @3 = (@3+@1) */
  w3 += w1;
  /* #485: @1 = input[0][176] */
  w1 = arg[0] ? arg[0][176] : 0;
  /* #486: @2 = input[0][177] */
  w2 = arg[0] ? arg[0][177] : 0;
  /* #487: @8 = input[0][178] */
  w8 = arg[0] ? arg[0][178] : 0;
  /* #488: @0 = input[0][179] */
  w0 = arg[0] ? arg[0][179] : 0;
  /* #489: @4 = vertcat(@1, @2, @8, @0) */
  rr=w4;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  /* #490: @1 = input[1][44] */
  w1 = arg[1] ? arg[1][44] : 0;
  /* #491: @2 = 0.04 */
  w2 = 4.0000000000000036e-02;
  /* #492: @8 = 1.76 */
  w8 = 1.7600000000000000e+00;
  /* #493: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #494: {NULL, NULL, NULL, @0, NULL, NULL, NULL} = F(@4, @1, @2, @8, @7) */
  arg1[0]=w4;
  arg1[1]=(&w1);
  arg1[2]=(&w2);
  arg1[3]=(&w8);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w0);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #495: @3 = (@3+@0) */
  w3 += w0;
  /* #496: @0 = input[0][180] */
  w0 = arg[0] ? arg[0][180] : 0;
  /* #497: @1 = input[0][181] */
  w1 = arg[0] ? arg[0][181] : 0;
  /* #498: @2 = input[0][182] */
  w2 = arg[0] ? arg[0][182] : 0;
  /* #499: @8 = input[0][183] */
  w8 = arg[0] ? arg[0][183] : 0;
  /* #500: @4 = vertcat(@0, @1, @2, @8) */
  rr=w4;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  /* #501: @0 = input[1][45] */
  w0 = arg[1] ? arg[1][45] : 0;
  /* #502: @1 = 0.04 */
  w1 = 4.0000000000000036e-02;
  /* #503: @2 = 1.8 */
  w2 = 1.8000000000000000e+00;
  /* #504: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #505: {NULL, NULL, NULL, @8, NULL, NULL, NULL} = F(@4, @0, @1, @2, @7) */
  arg1[0]=w4;
  arg1[1]=(&w0);
  arg1[2]=(&w1);
  arg1[3]=(&w2);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w8);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #506: @3 = (@3+@8) */
  w3 += w8;
  /* #507: @8 = input[0][184] */
  w8 = arg[0] ? arg[0][184] : 0;
  /* #508: @0 = input[0][185] */
  w0 = arg[0] ? arg[0][185] : 0;
  /* #509: @1 = input[0][186] */
  w1 = arg[0] ? arg[0][186] : 0;
  /* #510: @2 = input[0][187] */
  w2 = arg[0] ? arg[0][187] : 0;
  /* #511: @4 = vertcat(@8, @0, @1, @2) */
  rr=w4;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  /* #512: @8 = input[1][46] */
  w8 = arg[1] ? arg[1][46] : 0;
  /* #513: @0 = 0.04 */
  w0 = 4.0000000000000036e-02;
  /* #514: @1 = 1.84 */
  w1 = 1.8400000000000001e+00;
  /* #515: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #516: {NULL, NULL, NULL, @2, NULL, NULL, NULL} = F(@4, @8, @0, @1, @7) */
  arg1[0]=w4;
  arg1[1]=(&w8);
  arg1[2]=(&w0);
  arg1[3]=(&w1);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w2);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #517: @3 = (@3+@2) */
  w3 += w2;
  /* #518: @2 = input[0][188] */
  w2 = arg[0] ? arg[0][188] : 0;
  /* #519: @8 = input[0][189] */
  w8 = arg[0] ? arg[0][189] : 0;
  /* #520: @0 = input[0][190] */
  w0 = arg[0] ? arg[0][190] : 0;
  /* #521: @1 = input[0][191] */
  w1 = arg[0] ? arg[0][191] : 0;
  /* #522: @4 = vertcat(@2, @8, @0, @1) */
  rr=w4;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  *rr++ = w1;
  /* #523: @2 = input[1][47] */
  w2 = arg[1] ? arg[1][47] : 0;
  /* #524: @8 = 0.04 */
  w8 = 3.9999999999999813e-02;
  /* #525: @0 = 1.88 */
  w0 = 1.8800000000000001e+00;
  /* #526: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #527: {NULL, NULL, NULL, @1, NULL, NULL, NULL} = F(@4, @2, @8, @0, @7) */
  arg1[0]=w4;
  arg1[1]=(&w2);
  arg1[2]=(&w8);
  arg1[3]=(&w0);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w1);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #528: @3 = (@3+@1) */
  w3 += w1;
  /* #529: @1 = input[0][192] */
  w1 = arg[0] ? arg[0][192] : 0;
  /* #530: @2 = input[0][193] */
  w2 = arg[0] ? arg[0][193] : 0;
  /* #531: @8 = input[0][194] */
  w8 = arg[0] ? arg[0][194] : 0;
  /* #532: @0 = input[0][195] */
  w0 = arg[0] ? arg[0][195] : 0;
  /* #533: @4 = vertcat(@1, @2, @8, @0) */
  rr=w4;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  *rr++ = w0;
  /* #534: @1 = input[1][48] */
  w1 = arg[1] ? arg[1][48] : 0;
  /* #535: @2 = 0.04 */
  w2 = 4.0000000000000036e-02;
  /* #536: @8 = 1.92 */
  w8 = 1.9199999999999999e+00;
  /* #537: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #538: {NULL, NULL, NULL, @0, NULL, NULL, NULL} = F(@4, @1, @2, @8, @7) */
  arg1[0]=w4;
  arg1[1]=(&w1);
  arg1[2]=(&w2);
  arg1[3]=(&w8);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w0);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #539: @3 = (@3+@0) */
  w3 += w0;
  /* #540: @0 = input[0][196] */
  w0 = arg[0] ? arg[0][196] : 0;
  /* #541: @1 = input[0][197] */
  w1 = arg[0] ? arg[0][197] : 0;
  /* #542: @2 = input[0][198] */
  w2 = arg[0] ? arg[0][198] : 0;
  /* #543: @8 = input[0][199] */
  w8 = arg[0] ? arg[0][199] : 0;
  /* #544: @4 = vertcat(@0, @1, @2, @8) */
  rr=w4;
  *rr++ = w0;
  *rr++ = w1;
  *rr++ = w2;
  *rr++ = w8;
  /* #545: @0 = input[1][49] */
  w0 = arg[1] ? arg[1][49] : 0;
  /* #546: @1 = 0.04 */
  w1 = 4.0000000000000036e-02;
  /* #547: @2 = 1.96 */
  w2 = 1.9600000000000000e+00;
  /* #548: @7 = vertcat(@5, @6) */
  rr=w7;
  for (i=0, cs=w5; i<4; ++i) *rr++ = *cs++;
  for (i=0, cs=w6; i<4; ++i) *rr++ = *cs++;
  /* #549: {NULL, NULL, NULL, @8, NULL, NULL, NULL} = F(@4, @0, @1, @2, @7) */
  arg1[0]=w4;
  arg1[1]=(&w0);
  arg1[2]=(&w1);
  arg1[3]=(&w2);
  arg1[4]=w7;
  res1[0]=0;
  res1[1]=0;
  res1[2]=0;
  res1[3]=(&w8);
  res1[4]=0;
  res1[5]=0;
  res1[6]=0;
  if (casadi_f1(arg1, res1, iw, w, 0)) return 1;
  /* #550: @3 = (@3+@8) */
  w3 += w8;
  /* #551: output[0][0] = @3 */
  if (res[0]) res[0][0] = w3;
  return 0;
}

CASADI_SYMBOL_EXPORT int cost_mpc(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem){
  return casadi_f0(arg, res, iw, w, mem);
}

CASADI_SYMBOL_EXPORT int cost_mpc_alloc_mem(void) {
  return 0;
}

CASADI_SYMBOL_EXPORT int cost_mpc_init_mem(int mem) {
  return 0;
}

CASADI_SYMBOL_EXPORT void cost_mpc_free_mem(int mem) {
}

CASADI_SYMBOL_EXPORT int cost_mpc_checkout(void) {
  return 0;
}

CASADI_SYMBOL_EXPORT void cost_mpc_release(int mem) {
}

CASADI_SYMBOL_EXPORT void cost_mpc_incref(void) {
}

CASADI_SYMBOL_EXPORT void cost_mpc_decref(void) {
}

CASADI_SYMBOL_EXPORT casadi_int cost_mpc_n_in(void) { return 4;}

CASADI_SYMBOL_EXPORT casadi_int cost_mpc_n_out(void) { return 1;}

CASADI_SYMBOL_EXPORT casadi_real cost_mpc_default_in(casadi_int i) {
  switch (i) {
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const char* cost_mpc_name_in(casadi_int i) {
  switch (i) {
    case 0: return "x";
    case 1: return "u";
    case 2: return "x_current";
    case 3: return "x_final";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const char* cost_mpc_name_out(casadi_int i) {
  switch (i) {
    case 0: return "f";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const casadi_int* cost_mpc_sparsity_in(casadi_int i) {
  switch (i) {
    case 0: return casadi_s0;
    case 1: return casadi_s1;
    case 2: return casadi_s2;
    case 3: return casadi_s2;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const casadi_int* cost_mpc_sparsity_out(casadi_int i) {
  switch (i) {
    case 0: return casadi_s3;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT int cost_mpc_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w) {
  if (sz_arg) *sz_arg = 22;
  if (sz_res) *sz_res = 17;
  if (sz_iw) *sz_iw = 0;
  if (sz_w) *sz_w = 114;
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
        n_in  = cost_mpc_n_in();
        n_out = cost_mpc_n_out();
        cost_mpc_work(&sz_arg, &sz_res, &sz_iw, &sz_w);

        /* Set up simulink input/output ports */
        int_T i;
        if (!ssSetNumInputPorts(S, n_in)) return;
        for (i=0;i<n_in;++i) {
          const casadi_int* sp = cost_mpc_sparsity_in(i);
          /* Dense inputs assumed here */
          ssSetInputPortDirectFeedThrough(S, i, 1);
          ssSetInputPortMatrixDimensions(S, i, sp[0], sp[1]);
          ssSetInputPortRequiredContiguous(S, i, 1);
        }

        if (!ssSetNumOutputPorts(S, n_out)) return;
        for (i=0;i<n_out;++i) {
          const casadi_int* sp = cost_mpc_sparsity_out(i);
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
        cost_mpc_incref();
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

          int mem = cost_mpc_checkout();

          /* Run the CasADi function */
          int_T ret = cost_mpc(arg,res,iw,w,mem);

          if (ret && 1) {
              static char msg[126];
              sprintf(msg, "SFunction 'cost_mpc_s_function_level2' failed to compute (error code %d) at t=%.6fs.", ret, ssGetT(S));
              #ifdef ssSetLocalErrorStatus
                ssSetLocalErrorStatus(S, msg);
              #else
                #ifdef ssSetErrorStatus
                  ssSetErrorStatus(S, msg);
                #endif
              #endif
          }

          /* Release hold */
          cost_mpc_release(mem);

        }

        static void mdlTerminate(SimStruct *S) {
          cost_mpc_decref();
          }

        #ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
        #include "simulink.c"      /* MEX-file interface mechanism */
        #else
        #include "cg_sfun.h"       /* Code generation registration function */
        #endif
        