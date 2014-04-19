#include "hw7.h"

void printBIGNUM(BIGNUM *bn_n){
	char *s = NULL;
	int len = BN_num_bytes(bn_n);
	
	s = (char *)malloc(len + 1);
	s = BN_bn2dec(bn_n);
	
	puts(s);
}

void trialdiv(BIGNUM *bn_n, FILE *primesfile){
	BIGNUM *m_test = NULL;
	BIGNUM *maxval = NULL;
	BN_CTX *bn_ctx = NULL;
	BIGNUM *rem = NULL;
	unsigned char m_a[4];
	
	maxval = BN_new();
	m_test = BN_new();
	rem = BN_new();
	bn_ctx = BN_CTX_new();
	if(maxval == NULL){
		fprintf(stdout, "Error: BIGNUM Error\n");
		return;
	}
	BN_CTX_init(bn_ctx);
	
	
	BN_zero(maxval);
	fread(m_a, 1, 4, primesfile);
	BN_bin2bn(m_a, 4, maxval);
	
	while(!feof(primesfile)){
		fread(m_a, 1, 4, primesfile);
		if(!feof(primesfile)){
			BN_bin2bn(m_a, 4, m_test);
			BN_div(NULL, rem, bn_n, m_test, bn_ctx);
			if(BN_is_zero(rem) == 1){
				fprintf(stdout, "n is composite by trial division (mod %s = 0)\n", BN_bn2dec(m_test));
				return;
			}
		}
	}
	
	BN_sqr(m_test, maxval, bn_ctx);
	//Now m_test is the square of maxval
	if(BN_cmp(bn_n, m_test) == -1 || BN_cmp(bn_n, m_test) == 0){
		fprintf(stdout, "n passes trial division test\n");
	}
	else{
		fprintf(stdout, "n passes trial division test (not enough primes)\n");
	}
	
	BN_CTX_free(bn_ctx);
	BN_free(maxval);
	BN_free(m_test);
	
}
