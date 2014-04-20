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
int trialdiv(BIGNUM *bn_n, FILE *primesfile, int num_idnt);
int millerrabin(BIGNUM *bn_n, int maxitr, FILE *primesfile, int num_idnt);
void rndsearch(int numbits, int maxitr, FILE *primesfile, FILE *rndfile);
void maurer(int numbits, FILE *primesfile, FILE *rndfile);

void printIndents(int num);
void rndOddNum(BIGNUM *bn_n, int k, FILE *rndfile);
