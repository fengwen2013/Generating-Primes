#include "hw7.h"

int compute_sr(BIGNUM *bn_n, BIGNUM *bn_r, BIGNUM *bn_n_1, BN_CTX *bn_ctx){
	int j = 0;
	BIGNUM *bn_w = NULL;
	BIGNUM *bn_2 = NULL;
	BIGNUM *div = NULL;
	BIGNUM *rem = NULL;
	
	
	rem = BN_new();
	div = BN_new();
	bn_w = BN_new();
	bn_2 = BN_new();
	if(bn_w == NULL || div == NULL || rem == NULL){
		fprintf(stdout, "Error: BIGNUM ERROR!\n");
		return -1;
	}
	
	BN_set_word(bn_w, 1);
	BN_sub(bn_n_1, bn_n, bn_w);
	BN_set_word(bn_w, 2);
	BN_set_word(bn_2, 2);
	BN_copy(bn_r, bn_n_1);
	
	while(1){
		BN_div(div, rem, bn_n_1, bn_w, bn_ctx);
		if(BN_is_zero(rem) == 1){
			BN_copy(bn_r, div);
			BN_mul(bn_w, bn_w, bn_2, bn_ctx);
			j++;
		}
		else{
			break;
		}
	}
	
	BN_free(div);
	BN_free(rem);
	BN_free(bn_w);
	BN_free(bn_2);
	
	return j;	
}

void computeBNArray(BIGNUM **bn_array, BIGNUM *bn_a, BIGNUM *bn_n, BN_CTX *bn_ctx, int num_bits){
	int i = 0;
	

	bn_array[0] = BN_new();
	BN_copy(bn_array[0], bn_a); 
	
	for(i = 1; i < num_bits; i++){
		bn_array[i] = BN_new();
		BN_mod_mul(bn_array[i], bn_array[i - 1], bn_array[i - 1], bn_n, bn_ctx);			
	}
}

void compute_y(BIGNUM *bn_y, BIGNUM *bn_a, BIGNUM *bn_r, BIGNUM *bn_n, BN_CTX *bn_ctx){
	BIGNUM *bn_i = NULL;
	BIGNUM *bn_1 = NULL;
	int num_bits = 0;
	int i = 0;
	BIGNUM **bn_array = NULL;
	
	num_bits = BN_num_bits(bn_r);
	bn_array = (BIGNUM **)malloc(sizeof(BIGNUM*) * num_bits);
	computeBNArray(bn_array, bn_a, bn_n, bn_ctx, num_bits);
	
	bn_1 = BN_new();
	bn_i = BN_new();
	BN_one(bn_1);
	BN_zero(bn_i);
	BN_one(bn_y);
	
	for(i = 0; i < num_bits; i++){
		if(BN_is_bit_set(bn_r, i) == 1){
			BN_mod_mul(bn_y, bn_y, bn_array[i], bn_n, bn_ctx);
		}
	}
	BN_free(bn_1);
	BN_free(bn_i);
}

void ithPrime(int n, FILE *primesfile, BIGNUM *bn_a){
	int i = 0;
	unsigned char m_a[4];
	
	fseek(primesfile, 0, SEEK_SET);
	for(i = 0; i <= n; i++){
		fread(m_a, 1, 4, primesfile);		
	}
	
	BN_bin2bn(m_a, 4, bn_a);
	
}

int millerrabin(BIGNUM *bn_n, int maxitr, FILE *primesfile, int num_idnt){
	int s = 0;
	BIGNUM *bn_r = NULL;
	BIGNUM *bn_n_1 = NULL;
	BN_CTX *bn_ctx = NULL;
	BIGNUM *bn_a = NULL;
	BIGNUM *bn_y = NULL;
	BIGNUM *bn_1 = NULL;
	int i = 0;
	int j = 0;

	bn_a = BN_new();
	bn_y = BN_new();
	bn_r = BN_new();
	bn_1 = BN_new();
	BN_one(bn_1);
	bn_ctx = BN_CTX_new();
	bn_n_1 = BN_new();
	BN_CTX_init(bn_ctx);
	fseek(primesfile, 0 ,SEEK_SET);
	s = compute_sr(bn_n, bn_r, bn_n_1, bn_ctx);
	if(s == -1){
		return -1;
	}
	
	if(num_idnt == 0){
		fprintf(stdout, "n = %s\n", BN_bn2dec(bn_n));
	}
	printIndents(num_idnt);
	fprintf(stdout, "  n-1 = %s\n", BN_bn2dec(bn_n_1));
	printIndents(num_idnt);
	fprintf(stdout, "  s = %d\n", s);
	printIndents(num_idnt);
	fprintf(stdout, "  r = %s\n", BN_bn2dec(bn_r));
	
	for(i = 1; i <= maxitr; i++){
		printIndents(num_idnt);
		fprintf(stdout, "  Itr %d of %d, ", i, maxitr);
		
		ithPrime(i, primesfile, bn_a);
		if(BN_cmp(bn_a, bn_n_1) == 1){
			return -1;
		}
		
		compute_y(bn_y, bn_a, bn_r, bn_n, bn_ctx);
		
		
		if(BN_cmp(bn_y, bn_1) != 0 && BN_cmp(bn_y, bn_n_1) != 0){
			fprintf(stdout, "a = %s, y = %s\n", BN_bn2dec(bn_a), BN_bn2dec(bn_y));
			for(j = 1; j <= s - 1; j++){
				BN_mod_mul(bn_y, bn_y, bn_y, bn_n, bn_ctx);
				printIndents(num_idnt);
				fprintf(stdout, "    j = %d of %d, y = %s", j, s - 1, BN_bn2dec(bn_y));
				if(BN_cmp(bn_y, bn_n_1) == 0){
					fprintf(stdout, " (which is n-1)\n");
					break;
				}
				putchar('\n');
				
				if(BN_cmp(bn_y, bn_1) == 0){
					return 0;
				}
			}
			
			if(BN_cmp(bn_y, bn_n_1) != 0){
				printIndents(num_idnt);
				fprintf(stdout, "Miller-Rabin found a strong witness %s\n", BN_bn2dec(bn_a));
				return 0;
			}
		}
		else{
			if(BN_cmp(bn_y, bn_n_1) == 0){
				fprintf(stdout, "a = %s, y = %s (which is n-1)\n", BN_bn2dec(bn_a), BN_bn2dec(bn_y));
			}
			else{
				fprintf(stdout, "a = %s, y = %s\n", BN_bn2dec(bn_a), BN_bn2dec(bn_y));
			}
		}
		
		
	}
	printIndents(num_idnt);
	fprintf(stdout, "Miller-Rabin declares n to be a prime number\n");	
	return 1;
	
	BN_free(bn_1);
	BN_free(bn_a);
	BN_free(bn_y);
	BN_free(bn_r);
	BN_CTX_free(bn_ctx);
}
