#include "hw7.h"

void setBitInArray(char a[], long j){
	int i = j / 8;
	int mask = 1;
	
	if(i * 8 < j){
		mask = mask << (j - i * 8 - 1);
		if((a[i] & mask) == mask){
			a[i] = a[i] ^ mask;
		}
	}
	else{
		if((a[i - 1] & 0x80) == 0x80){
			a[i - 1] = a[i - 1] ^ 0x80;
		}
	}
}

void eratosthenes(long n, char a[], long num){
	int i = 2;
	long p = 2;
	long j = 0;
	
	for(i = 0; i < num; i++){
		a[i] = 0xff;
	}
	a[0] = a[0] & 0xfe;
	
	p = 2;
	while((p * p) <= n){
		j = p * p;
		while(j <= n){
			setBitInArray(a, j);
			j = j + p;
		}
		p++;
	}
}

void putPrime(long n){
	int i = 0;
	for(i = 3; i >= 0; i--){
		putchar((n >> (i * 8)) & 0xff);
	}
}

void printSmallPrimes(char a[], int numOfLastPrimes, long num){
	int j = 0;
	int mask = 1;
	for(j = 0, mask = 1; j < numOfLastPrimes; j++){
		if((a[num] & mask) == mask){
			putPrime((num) * 8 + j + 1);
		}
		mask = mask << 1;
	}	
}

void primes(long maxval){
	char *a = NULL;
	long i = 0;
	long num = (maxval / 8) * 8 < maxval ? maxval / 8 + 1: maxval / 8;
	int numOfLastPrimes = 0;
	
	a = (char *)malloc(num);
	if(a == NULL){
		fprintf(stdout, "Error: Allocate Memory Error\n");
		return;
	}
	eratosthenes(maxval, a, num);
	putPrime(maxval);
	for(i = 0; i < num - 1; i++){
		printSmallPrimes(a, 8, i);	
	}
	
	numOfLastPrimes = maxval - 8 * (num - 1);
	printSmallPrimes(a, numOfLastPrimes, num - 1);
	
	free(a);
	
}
