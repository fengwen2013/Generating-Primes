#include "hw7.h"

void printBIGNUM(BIGNUM *bn_n){
	char *s = NULL;
	int len = BN_num_bytes(bn_n);
	
	s = (char *)malloc(len + 1);
	s = BN_bn2dec(bn_n);
	
	puts(s);
}

void printIndents(int num){
	int i = 0;
	
	for(i = 0; i < num; i++){
		putchar(' ');
	}
}

int trialdiv(BIGNUM *bn_n, FILE *primesfile, int num_idnt){
	BIGNUM *m_test = NULL;
	BIGNUM *bn_square = NULL;
	BIGNUM *maxval = NULL;
	BN_CTX *bn_ctx = NULL;
	BIGNUM *rem = NULL;
	unsigned char m_a[4];
	
	maxval = BN_new();
	m_test = BN_new();
	rem = BN_new();
	bn_square = BN_new();
	bn_ctx = BN_CTX_new();
	if(maxval == NULL){
		fprintf(stderr, "Error: BIGNUM Error\n");
		return -1;
	}
	BN_CTX_init(bn_ctx);
	
	fseek(primesfile, 0, SEEK_SET);
	BN_zero(maxval);
	fread(m_a, 1, 4, primesfile);
	BN_bin2bn(m_a, 4, maxval);
	
	while(!feof(primesfile)){
		fread(m_a, 1, 4, primesfile);
		if(!feof(primesfile)){
			BN_bin2bn(m_a, 4, m_test);
			BN_sqr(bn_square, m_test, bn_ctx);
			if(BN_cmp(bn_square, bn_n) >= 0){
				printIndents(num_idnt);
				fprintf(stdout, "n passes trial division test\n");
				break;
			} 
			
			BN_div(NULL, rem, bn_n, m_test, bn_ctx);
			if(BN_is_zero(rem) == 1){
				printIndents(num_idnt);
				fprintf(stdout, "n is composite by trial division (mod %s = 0)\n", BN_bn2dec(m_test));
				return 0;
			}
		}
	}
	
	BN_sqr(m_test, maxval, bn_ctx);
	//Now m_test is the square of maxval
	if(BN_cmp(bn_n, m_test) > 0){
		printIndents(num_idnt);
		fprintf(stdout, "n passes trial division test (not enough primes)\n");
	}
	
	BN_CTX_free(bn_ctx);
	BN_free(maxval);
	BN_free(m_test);
	BN_free(bn_square);
	return 1;
}
