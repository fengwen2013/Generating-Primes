#include "hw7.h"

void computeI(BIGNUM *bn_I, int k, BIGNUM *bn_q, BN_CTX *bn_ctx){
	BIGNUM *bn_2 = NULL;
	int i = 0;
	bn_2 = BN_new();
	BN_set_word(bn_2, 2);
	BN_one(bn_I);
	for(i = 0; i < k; i++){
		BN_mul(bn_I, bn_I, bn_2, bn_ctx);
	}
	BN_div(bn_I, NULL, bn_I, bn_q, bn_ctx);
	
}

void gcd(BIGNUM *bn_d, BIGNUM *bn_b, BIGNUM *bn_n, BN_CTX *bn_ctx){
	BIGNUM *bn_0 = NULL;
	bn_0 = BN_new();
	BN_zero(bn_0);
	
	while(BN_cmp(bn_b, bn_0) != 0){
		BN_copy(bn_d, bn_b);
		BN_mod(bn_b, bn_n, bn_b, bn_ctx);
		BN_copy(bn_n, bn_d);
	}
	
	BN_copy(bn_d, bn_n);
}

void compute_b(BIGNUM *bn_b, BIGNUM *bn_a, BIGNUM *bn_n_1, BIGNUM *bn_n, BN_CTX *bn_ctx){
	compute_y(bn_b, bn_a, bn_n_1, bn_n, bn_ctx);
}

unsigned char rndByte(FILE *rndfile){
	unsigned char c = 0;
	fread(&c, 1, 1, rndfile);
	return c;
}

void maurer(BIGNUM *bn_n, int numbits, FILE *primesfile, FILE *rndfile, int level){
	BIGNUM *bn_q = NULL;
	BIGNUM *bn_I = NULL;
	BIGNUM *bn_R = NULL;
	BIGNUM *bn_a = NULL;
	BIGNUM *bn_b = NULL;
	BIGNUM *bn_d = NULL;
	BIGNUM *bn_1 = NULL;
	BIGNUM *bn_2 = NULL;
	BIGNUM *bn_n_1 = NULL;
			
	BN_CTX *bn_ctx = NULL;
	
	FILE *primesfile2 = NULL;
	FILE *rndfile2 = NULL;
	
	int m = 20;
	float r = 0;
	int num_bits_in_q = 0;
	int num_bits_in_n = 0;
	int i = 0;
	int j = 0;
	
	fprintf(stdout, "Maurer: level %d, k=%d\n", level, numbits);
	
	if(numbits <= 20){
		while(1){
			rndOddNum(bn_n, numbits, rndfile);
			fprintf(stdout, "  step 1.1, n = %s\n", BN_bn2dec(bn_n));
			if(trialdiv(bn_n, primesfile, 4) == PRIME){
				
				break;
			}
		}
		if(level == 0){
			fprintf(stdout, "\nMaurer's Algorithm found an %d-bit prime:\n  n = %s\n", numbits, BN_bn2dec(bn_n));
		}
		return;
	}
	else{
		m = 20;
		if(numbits <= 2*m){
			r = 0.5;
			fprintf(stdout, "  step 4, r = %d%%\n", round(r * 100));
		}
		else{
			while(1){
				j = rndByte(rndfile);
				r =  j / 255.0;
				r = 0.5 + r / 2.0;
				if(numbits * (1 - r) * 1.0 > m * 1.0){
					break;
				}
			}
			fprintf(stdout, "  step 4, random byte = %d, r = %d%%\n", j, round(r * 100));
		}
		
		bn_q = BN_new();
		primesfile2 = fdopen(dup(fileno(primesfile)), "r");
		rndfile2 = fdopen(dup(fileno(rndfile)), "r");
		
		maurer(bn_q, r * numbits + 1, primesfile2, rndfile2, level+1);
		fprintf(stdout, "Maurer: back to level %d, k=%d, q=%s\n", level, numbits, BN_bn2dec(bn_q));
		fseek(rndfile, 0, SEEK_SET);
		
		bn_I = BN_new();
		bn_R = BN_new();
		bn_1 = BN_new();
		bn_2 = BN_new();
		bn_a = BN_new();
		bn_b = BN_new();
		bn_d = BN_new();
		bn_n_1 = BN_new();
		BN_set_word(bn_1, 1);
		BN_set_word(bn_2, 2);
		
		bn_ctx = BN_CTX_new();
		BN_CTX_init(bn_ctx);
		
		num_bits_in_q = BN_num_bits(bn_q);
		computeI(bn_I, numbits - 2, bn_q, bn_ctx);
		i = 0;
		while(1){
			i++;
			fseek(primesfile, 0, SEEK_SET);
			rndOddNum(bn_R, numbits + 1 - num_bits_in_q, rndfile);
			BN_mod(bn_R, bn_R, bn_I, bn_ctx);
			BN_add(bn_R, bn_R, bn_I);
			BN_add(bn_R, bn_R, bn_1);
 			BN_mul(bn_n, bn_2, bn_R, bn_ctx);
			BN_mul(bn_n, bn_n, bn_q, bn_ctx);
			BN_add(bn_n, bn_n, bn_1);
			fprintf(stdout, "  step 7, itr %d: R = %s, n = %s\n", i, BN_bn2dec(bn_R), BN_bn2dec(bn_n));
			if(trialdiv(bn_n, primesfile, 4) != COMPOSITE){
				num_bits_in_n = BN_num_bits(bn_n);
				BN_sub(bn_n_1, bn_n, bn_1);
				//fseek(rndfile2, 0, SEEK_SET);
				//printf("nn:%d\n", num_bits_in_n);
				do{
					rndOddNum(bn_a, num_bits_in_n, rndfile);
				}while(BN_cmp(bn_a, bn_1) <= 0 || BN_cmp(bn_a, bn_n_1) >= 0);
				fprintf(stdout, "  step 7.2.1, itr %d: a = %s\n", i, BN_bn2dec(bn_a));
				compute_b(bn_b, bn_a, bn_n_1, bn_n, bn_ctx);
				if(BN_cmp(bn_b, bn_1) == 0){
					BN_mul(bn_n_1, bn_2, bn_R, bn_ctx);
					compute_b(bn_b, bn_a, bn_n_1, bn_n, bn_ctx);
					BN_sub(bn_b, bn_b, bn_1);
					BN_copy(bn_n_1, bn_n);
					gcd(bn_d, bn_b, bn_n_1, bn_ctx);
					if(BN_cmp(bn_d, bn_1) == 0){
						BN_CTX_free(bn_ctx);
						BN_free(bn_a);
						BN_free(bn_b);
						BN_free(bn_d);
						if(level == 0){
							fprintf(stdout, "\nMaurer's Algorithm found an %d-bit prime:\n  n = %s\n", numbits, BN_bn2dec(bn_n));
						}
						return;
					}
				}
			}
		}		
	}
}
