#include "hw7.h"


void rndOddNum(BIGNUM *bn_n, int k, FILE *rndfile){
	int x = (k / 8) * 8 < k ? k / 8 + 1: k / 8;
	unsigned char *s_n = NULL;
	int i = 0;
	s_n = (unsigned char *)malloc(x);
	fread(s_n, 1, x, rndfile);
	BN_bin2bn(s_n, x, bn_n);
	BN_set_bit(bn_n, 0);
	BN_set_bit(bn_n, k - 1);
	for(i = k; i < x * 8; i++){
		BN_clear_bit(bn_n, i);
	}
	 
}

void rndsearch(int numbits, int maxitr, FILE *primesfile, FILE *rndfile){
	int i = 0;
	BIGNUM *bn_n = NULL;
	FILE *primesfile2 = fdopen(dup(fileno(primesfile)), "r");
	bn_n = BN_new();
	while(1){
		i++;
		fprintf(stdout, "RANDOM-SEARCH: iteration %d\n", i);
		rndOddNum(bn_n, numbits, rndfile);
		fprintf(stdout, "  n = %s\n", BN_bn2dec(bn_n));
		if(trialdiv(bn_n, primesfile, 2) == PRIME){
			if(millerrabin(bn_n, maxitr, primesfile2, 2) == PRIME){
				break;
			}
		}
	}
}
