#define IMPACT_ALL 0
#define IMPACT_EVERYWHERE -1
#define IMPACT_FULL 0
#define IMPACT_HREP 1
#define IMPACT_VREP 2
#define IMPACT_COLUMN_MAJOR 0
#define IMPACT_ROW_MAJOR 4


typedef struct {
  int sqp_stop_crit;
  int n_sqp_iter;
  int n_ls;
  int n_max_ls;
  int n_qp_iter;
  int n_max_qp_iter;
  double runtime;
}impact_stats;

struct impact__struct;
typedef struct impact__struct impact_struct;

typedef int (*formatter)(const char * s);

/**
  \brief Initialize and instance of an impact library

  \note Any call to \c initialize must be followed up with a call to \c destroy within the same process.

  \param[in]  fp Function pointer to a printf-like function
              Common values: 0 (null pointer: no printing), printf (C's standard printf method defined in stdio)
  \param[in]  build_dir Location of build directory. If not supplied (null pointer), uses a hard-coded export path.


  \return Impact instance pointer, or a null pointer upon failure

*/
impact_struct* impact_initialize(formatter fp, const char* build_dir);
/**
  \brief Destroy impact instance

  \note May be needed to avoid segementation faults on exit
  \note It is safe to pass a null pointer as argument

  \parameter[in] Impact instance pointer
*/
void impact_destroy(impact_struct* m);

/**
  \brief Compute an MPC action

  \details
  Parameters (\b p) and initial guesses (\b x_initial_guess, \b u_initial_guess, \b z_initial_guess)
  can be supplied through \c get.
  If not supplied, defaults will be taken from the user definition.
  Outputs of the optimization are written into internal pools \b x_opt, \b z_opt, and \b u_opt,
  and can be queried using \c get. 

  \parameter[in] Hotstart

  \return 0 indicates success

*/
int impact_solve(impact_struct* m);

/*
Prepare internal structure such that the next solve is hotstarted with the current solution
*/
void impact_hotstart(impact_struct* m);

/*
Prepare internal structure such that no hotstart information is carried over
*/
void impact_coldstart(impact_struct* m);

/*
Prepare internal structure such that the next solve uses the nominal trajectory from export
*/
void impact_freshstart(impact_struct* m);

/**
  \brief Print numerical data present in pools

  \parameter[in] Impact instance pointer

  \return 0 indicates success

*/
int impact_print_problem(impact_struct* m);

/** \brief Getting and setting numerical data

  \parameter[in] m            Impact instance pointer
  \parameter[in] pool_name    Any of: "x_initial_guess","z_initial_guess","u_initial_guess","v_initial_guess","p","x_opt","z_opt","u_opt","v_opt"
  \parameter[in] id           String identifier for a specific variable name, or IMPACT_ALL
  \parameter[in] stage        Specific time instance (0-based), or IMPACT_EVERYWHERE
  \parameter[in] flags    Composable (using bitwise or '|' ) flags that modify behaviour
                            IMPACT_FULL: default
                            IMPACT_COLUMN_MAJOR (fortran ordering - default)
                            IMPACT_ROW_MINOR (C ordering)
                            IMPACT_HREP (repeat horizontally )

  \return Negative number upon failure

 */
 /** @{ */
/**
  \brief Get numerical data
  \parameter[in] dst          Pointer to a chunk of writable memory.
                               There must be space of at least \b n_row* \b n_col which can be retrieved using \c get_size
*/
int impact_get(impact_struct* m, const char* pool_name, const char* id, int stage, double* dst, int flags);
/**
  \brief Set numerical data
  \parameter[in] src          Pointer to a chunk of readable memory.
                               There will be \b n_row* \b n_col elements read which can be retrieved using \c get_size
                               Any NaNs are ignored (i.e. the memory pool is untouched for those entries)
*/
int impact_set(impact_struct* m, const char* pool_name, const char* id, int stage, const double* src, int flags);
/**
  \brief Get shape of data
*/
int impact_get_size(impact_struct* m, const char* pool_name, const char* id, int stage, int flags, int* n_row, int* n_col);
/* @} */

/**
  \brief Get number of (scalarized) differential states
*/
int impact_get_nx();
/**
  \brief Get number of (scalarized) algebric states
*/
int impact_get_nz();
/**
  \brief Get number of (scalarized) inputs
*/
int impact_get_nu();
/**
  \brief Get number of (scalarized) variables
*/
int impact_get_nv();

int impact_get_id_count(impact_struct* m, const char* pool_name);
int impact_get_id_from_index(impact_struct* m, const char* pool_name, int index, const char** id);
const impact_stats* impact_get_stats(const impact_struct* m);

#define casadi_real double
#define casadi_int long long int

int impact_allocate(impact_struct* m);
void impact_set_work(impact_struct* m, const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w);
void impact_work(impact_struct* m, casadi_int* sz_arg, casadi_int* sz_res, casadi_int* sz_iw, casadi_int* sz_w);

int impact_flag_size(impact_struct* m);
const char* impact_flag_name(impact_struct* m, int index);
int impact_flag_value(impact_struct* m, int index);

      