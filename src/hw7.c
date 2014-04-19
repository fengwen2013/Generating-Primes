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

}

void mrCommand(char *argv[], int argc){

}

void rndsearchCommand(char *argv[], int argc){

}

void maurerCommand(char *argv[], int argc){

}



