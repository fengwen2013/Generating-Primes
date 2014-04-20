#include "hw7.h"

int main(int argc, char *argv[]){
	if(argc < 2){
		fprintf(stderr, "Error: Too few arguments\n");
		return -1;
	}
	
	if(strcmp(argv[1], "primes") == 0){
		primesCommand(argv, argc);
	}
	else{
		if(strcmp(argv[1], "trialdiv") == 0){
			trialdivCommand(argv, argc);
		}
		else{
			if(strcmp(argv[1], "millerrabin") == 0){
				mrCommand(argv, argc);
			}
			else{
				if(strcmp(argv[1], "rndsearch") == 0){
					rndsearchCommand(argv, argc);
				}
				else{
					if(strcmp(argv[1], "maurer") == 0){
						maurerCommand(argv, argc);
					}
					else{
						fprintf(stderr, "Error: First argument should be (primes | trialdiv | millerrabin | rndsearch | maurer)!!!\n");
						return -1;
					}	
				}
			}
		}
	}
	return 0;
}

void primesCommand(char *argv[], int argc){
	long maxval = 0;
	if(argc != 3){
		fprintf(stderr, "Error: Wrong number of arguments for tablecheck command\n");
		return;
	}
	else{
		if(optionCheck(argv[2], "-n") == -1){
				return;
		}
		else{
			if((maxval = strToLong(argv[2]+3)) == -1){
				return;	
			}
			
			if(maxval < MIN_SMALLPRIME || maxval > MAX_SMALLPRIME){
				fprintf(stdout, "Error: maxval must be between 2 and 2^24, inclusive\n");
				return;
			}
			primes(maxval);
		}
	}
}

void trialdivCommand(char *argv[], int argc){
	int i = 2;
	FILE *primesfile = NULL;
	unsigned char *bn_p = NULL;
	int len = 0;
	BIGNUM *bn_n = NULL;
	
	if(argc != 4){
		fprintf(stderr, "Error: Wrong number of arguments for the command\n");
		return;
	}
	else{
		while(i < argc){
			if(optionCheck(argv[i], "-n") == 1){
				bn_n = BN_new();
				if(bn_n == NULL){
					fprintf(stdout, "Error: BIGNUM Error\n");
					return;
				}
				BN_zero(bn_n);
				len = strlen(argv[i]) - 3;
				bn_p = (unsigned char *)malloc(len);
				arrayCopy(bn_p, argv[i] + 3, len);
				BN_dec2bn(&bn_n, argv[i] + 3);
			}
			else{
				if(optionCheck(argv[i], "-p") == 1){
					if((primesfile = openFile(argv[i] + 3)) == NULL){
						return;
					}
					
				}
				else{
					fprintf(stderr, "Error: Wrong option, should be \"-n\" or \"-p\"\n");
				}
			}
			i++;
		}
		trialdiv(bn_n, primesfile, 0);
		BN_free(bn_n);
		free(bn_p);
	}
}

void mrCommand(char *argv[], int argc){
	int i = 2;
	FILE *primesfile = NULL;
	unsigned char *bn_p = NULL;
	int len = 0;
	int maxitr = 0;
	BIGNUM *bn_n = NULL;
	
	if(argc != 5){
		fprintf(stderr, "Error: Wrong number of arguments for the command\n");
		return;
	}
	else{
		while(i < argc){
			if(optionCheck(argv[i], "-n") == 1){
				bn_n = BN_new();
				if(bn_n == NULL){
					fprintf(stdout, "Error: BIGNUM Error\n");
					return;
				}
				BN_zero(bn_n);
				len = strlen(argv[i]) - 3;
				bn_p = (unsigned char *)malloc(len);
				arrayCopy(bn_p, argv[i] + 3, len);
				BN_dec2bn(&bn_n, argv[i] + 3);
			}
			else{
				if(optionCheck(argv[i], "-p") == 1){
					if((primesfile = openFile(argv[i] + 3)) == NULL){
						return;
					}
					
				}
				else{
					if(optionCheck(argv[i], "-t") == 1){
						sscanf(argv[i] + 3, "%d", &maxitr);
					}
					else{
					fprintf(stderr, "Error: Wrong option, should be \"-n\" or \"-p\"\n");
					}
				}
			}
			i++;
		}
		millerrabin(bn_n, maxitr, primesfile, 0);
		BN_free(bn_n);
		free(bn_p);
	}
}

void rndsearchCommand(char *argv[], int argc){
	int i = 2;
	FILE *primesfile = NULL;
	FILE *rndfile = NULL;
	int maxitr = 0;
	int numbits = 0;
	
	if(argc != 6){
		fprintf(stderr, "Error: Wrong number of arguments for the command\n");
		return;
	}
	else{
		while(i < argc){
			if(optionCheck(argv[i], "-k") == 1){
				sscanf(argv[i] + 3, "%d", &numbits);
			}
			else{
				if(optionCheck(argv[i], "-p") == 1){
					if((primesfile = openFile(argv[i] + 3)) == NULL){
						return;
					}
					
				}
				else{
					if(optionCheck(argv[i], "-t") == 1){
						sscanf(argv[i] + 3, "%d", &maxitr);
					}
					else{
						if(optionCheck(argv[i], "-r") == 1){
							if((rndfile = openFile(argv[i] + 3)) == NULL){
								return;
							}
						}
						else{
							fprintf(stderr, "Error: Wrong option, should be \"-n\" or \"-p\"\n");
						}
					}
				}
			}
			i++;
		}
		rndsearch(numbits, maxitr, primesfile, rndfile);
	}

}

void maurerCommand(char *argv[], int argc){

}



