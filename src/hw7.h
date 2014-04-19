#include "util.h"
#include <openssl/bn.h>

#define MAX_SMALLPRIME 16777216
#define MIN_SMALLPRIME 2 
#define COMPOSITE 0
#define PRIME 1
#define FAILURE -1

void primesCommand(char *argv[], int argc);
void trialdivCommand(char *argv[], int argc);
void mrCommand(char *argv[], int argc);
void rndsearchCommand(char *argv[], int argc);
void maurerCommand(char *argv[], int argc);

void primes(long maxval);
void trialdiv(BIGNUM *bn_n, FILE *primesfile);
int millerrabin(BIGNUM *bn_n, int maxitr, FILE *primesfile);
void rndsearch(int numbits, int maxitr, FILE *primesfile, FILE *rndfile);
void maurer(int numbits, FILE *primesfile, FILE *rndfile);
