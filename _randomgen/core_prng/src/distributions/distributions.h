#include <stddef.h>
#ifdef _WIN32
#if _MSC_VER == 1500
#include "../common/stdint.h"
typedef int bool;
#define false 0
#define true 1
#else
#include <stdbool.h>
#include <stdint.h>
#endif
#else
#include <stdbool.h>
#include <stdint.h>
#endif

#include "Python.h"
#include "numpy/npy_common.h"
#include <math.h>

#ifdef DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR extern
#endif

#ifndef min
#define min(x, y) ((x < y) ? x : y)
#define max(x, y) ((x > y) ? x : y)
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846264338328
#endif

typedef struct s_binomial_t {
  int has_binomial; /* !=0: following parameters initialized for binomial */
  double psave;
  long nsave;
  double r;
  double q;
  double fm;
  long m;
  double p1;
  double xm;
  double xl;
  double xr;
  double c;
  double laml;
  double lamr;
  double p2;
  double p3;
  double p4;
} binomial_t;

typedef struct prng {
  void *state;
  uint64_t (*next_uint64)(void *st);
  uint32_t (*next_uint32)(void *st);
  double (*next_double)(void *st);
  uint64_t (*next_raw)(void *st);
  int has_gauss;
  double gauss;
  int has_gauss_f;
  float gauss_f;
  binomial_t *binomial;
} prng_t;

DECLDIR float random_sample_f(prng_t *prng_state);
DECLDIR double random_sample(prng_t *prng_state);

DECLDIR int64_t random_positive_int64(prng_t *prng_state);
DECLDIR int32_t random_positive_int32(prng_t *prng_state);
DECLDIR long random_positive_int(prng_t *prng_state);
DECLDIR unsigned long random_uint(prng_t *prng_state);

DECLDIR double random_standard_exponential(prng_t *prng_state);
DECLDIR float random_standard_exponential_f(prng_t *prng_state);
DECLDIR double random_standard_exponential_zig(prng_t *prng_state);
DECLDIR float random_standard_exponential_zig_f(prng_t *prng_state);

DECLDIR double random_gauss(prng_t *prng_state);
DECLDIR float random_gauss_f(prng_t *prng_state);
DECLDIR double random_gauss_zig(prng_t *prng_state);
DECLDIR float random_gauss_zig_f(prng_t *prng_state);

DECLDIR double random_standard_gamma(prng_t *prng_state, double shape);
DECLDIR float random_standard_gamma_f(prng_t *prng_state, float shape);
DECLDIR double random_standard_gamma_zig(prng_t *prng_state, double shape);
DECLDIR float random_standard_gamma_zig_f(prng_t *prng_state, float shape);

DECLDIR double random_normal(prng_t *prng_state, double loc, double scale);
DECLDIR double random_normal_zig(prng_t *prng_state, double loc, double scale);

DECLDIR double random_gamma(prng_t *prng_state, double shape, double scale);
DECLDIR float random_gamma_float(prng_t *prng_state, float shape, float scale);

DECLDIR double random_exponential(prng_t *prng_state, double scale);
DECLDIR double random_uniform(prng_t *prng_state, double lower, double range);
DECLDIR double random_beta(prng_t *prng_state, double a, double b);
DECLDIR double random_chisquare(prng_t *prng_state, double df);
DECLDIR double random_f(prng_t *prng_state, double dfnum, double dfden);
DECLDIR double random_standard_cauchy(prng_t *prng_state);
DECLDIR double random_pareto(prng_t *prng_state, double a);
DECLDIR double random_weibull(prng_t *prng_state, double a);
DECLDIR double random_power(prng_t *prng_state, double a);
DECLDIR double random_laplace(prng_t *prng_state, double loc, double scale);
DECLDIR double random_gumbel(prng_t *prng_state, double loc, double scale);
DECLDIR double random_logistic(prng_t *prng_state, double loc, double scale);
DECLDIR double random_lognormal(prng_t *prng_state, double mean, double sigma);
DECLDIR double random_rayleigh(prng_t *prng_state, double mode);
DECLDIR double random_standard_t(prng_t *prng_state, double df);
DECLDIR double random_noncentral_chisquare(prng_t *prng_state, double df,
                                           double nonc);
DECLDIR double random_noncentral_f(prng_t *prng_state, double dfnum,
                                   double dfden, double nonc);
DECLDIR double random_wald(prng_t *prng_state, double mean, double scale);
DECLDIR double random_vonmises(prng_t *prng_state, double mu, double kappa);
DECLDIR double random_triangular(prng_t *prng_state, double left, double mode,
                                 double right);

DECLDIR long random_poisson(prng_t *prng_state, double lam);
DECLDIR long random_negative_binomial(prng_t *prng_state, double n, double p);
DECLDIR long random_binomial(prng_t *prng_state, double p, long n);
DECLDIR long random_logseries(prng_t *prng_state, double p);
DECLDIR long random_geometric_search(prng_t *prng_state, double p);
DECLDIR long random_geometric_inversion(prng_t *prng_state, double p);
DECLDIR long random_geometric(prng_t *prng_state, double p);
DECLDIR long random_zipf(prng_t *prng_state, double a);
DECLDIR long random_hypergeometric(prng_t *prng_state, long good, long bad,
                                   long sample);

DECLDIR uint64_t random_interval(prng_t *prng_state, uint64_t max);
DECLDIR uint64_t random_bounded_uint64(prng_t *prng_state, uint64_t off,
                                       uint64_t rng, uint64_t mask);
DECLDIR uint32_t random_buffered_bounded_uint32(prng_t *prng_state,
                                                uint32_t off, uint32_t rng,
                                                uint32_t mask, int *bcnt,
                                                uint32_t *buf);

DECLDIR uint16_t random_buffered_bounded_uint16(prng_t *prng_state,
                                                uint16_t off, uint16_t rng,
                                                uint16_t mask, int *bcnt,
                                                uint32_t *buf);
DECLDIR uint8_t random_buffered_bounded_uint8(prng_t *prng_state, uint8_t off,
                                              uint8_t rng, uint8_t mask,
                                              int *bcnt, uint32_t *buf);
DECLDIR npy_bool random_buffered_bounded_bool(prng_t *prng_state, npy_bool off,
                                              npy_bool rng, npy_bool mask,
                                              int *bcnt, uint32_t *buf);
DECLDIR void random_bounded_uint64_fill(prng_t *prng_state, uint64_t off,
                                        uint64_t rng, npy_intp cnt,
                                        uint64_t *out);
DECLDIR void random_bounded_uint32_fill(prng_t *prng_state, uint32_t off,
                                        uint32_t rng, npy_intp cnt,
                                        uint32_t *out);
DECLDIR void random_bounded_uint16_fill(prng_t *prng_state, uint16_t off,
                                        uint16_t rng, npy_intp cnt,
                                        uint16_t *out);
DECLDIR void random_bounded_uint8_fill(prng_t *prng_state, uint8_t off,
                                       uint8_t rng, npy_intp cnt, uint8_t *out);
DECLDIR void random_bounded_bool_fill(prng_t *prng_state, npy_bool off,
                                      npy_bool rng, npy_intp cnt,
                                      npy_bool *out);
