/* Mangea Liviu Darius 324CA */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MOD 40009

/* Functia ridica matricea a la puterea n in timp logaritmic.
In while (care calculeaza efectiv ridicarea(pana acolo sunt declarari de 
matrici)) daca p este par se ridica matricea a la patrat si p se injumatateste
iar daca p este impar, rezultatul se inmulteste cu a si p scade cu o unitate.
Astfel se fac mai putine inmultiri pentru ca, de exemplu daca vrem sa ridicam la
a 4-a, e mai rapid sa ridicam la a doua si apoi rezultatul sa il ridicam din nou
la a doua decat sa imnultim rezultatul cu matricea a de 4 ori. (Totul se face
modulo 40009)*/

long long** logPowMatrix(long long **a, int n, int k) {

	long long  **res, **aux;
	int p = n, i, j, q;
	long long sum = 0;
	
	res = (long long**)calloc((k + 1), sizeof(long long*));
	
	for(i = 0; i <= k; i++) {
		res[i] = (long long *)calloc((k + 1), sizeof(long long));
	}
	
	
	for(i = 0; i <= k; i++) {
		for(j = 0; j <= k; j++) {
			if(i == j) {
				res[i][j] = 1;
			}
		}
	}
	
	aux = (long long**)calloc((k + 1), sizeof(long long*));
	
	for(i = 0; i <= k; i++) {
		aux[i] = (long long *)calloc((k + 1), sizeof(long long));
	}
	
	
	for(i = 0; i <= k; i++) {
		for(j = 0; j <= k; j++) {
			if(i == j) {
				aux[i][j] = 1;
			}
		}
	}
	
	/* Ridicarea la putere */
	while(p) {
	
		if(p % 2 == 1) {
			for(i = 0; i <= k; i++) {
				for(j = 0; j <= k; j++) {
					aux[i][j] = res[i][j];
				}
			}
			
			
			for(i = 0; i <= k; i++) {
				for(j = 0; j <= k; j++) {
					for(q = 0; q <= k; q++) {
						sum += ((res[i][q] * a[q][j]) % MOD);
					}

					aux[i][j] = sum;
					sum = 0;
				}
			}
			
			for(i = 0; i <= k; i++) {
				for(j = 0; j <= k; j++) {
					res[i][j] = aux[i][j];
				}
			}
			
			p--;
		}
			
		for(i = 0; i <= k; i++) {
			for(j = 0; j <= k; j++) {
				for(q = 0; q <= k; q++) {
					sum += (a[i][q] * a[q][j]) % MOD;
				}
				aux[i][j] = sum;
				sum = 0;
			}
		}
		
		for(i = 0; i <= k; i++) {
			for(j = 0; j <= k; j++) {
				a[i][j] = aux[i][j];
			}
		}

		p = p / 2;
	
	}
	
	return res;
	
}

/* power imi ridica un numar la o putere pe aceiasi idee ca la ridicarea
matricelor */					
long long power(long long result, int m) {
	int res = 1;
	
	while(m) {
		if(m % 2 == 1) {
			res = (res * result) % MOD;
			m--;
		}
		
		result = (result * result) % MOD;
		m = m / 2;
	}
		
	return res;
}			

/* Am folosit Fibonacci generalizat */
int main(int args, char** argv) {
	
	int n, m, k, i, j;
	long long **a, *initial;
	
	FILE *fr, *fw;

	fr = fopen("date.in", "r");	
	fw = fopen("date.out", "w");
	
	fscanf(fr, "%d", &n);
	fscanf(fr, "%d", &m);
	fscanf(fr, "%d", &k);
	
	a = (long long**)calloc((k + 1), sizeof(long long*));
	
	for(i = 0; i <= k; i++) {
		a[i] = (long long *)calloc((k + 1), sizeof(long long));
	}
	
	initial = (long long *)calloc((k + 1), sizeof(long long));
	
	/* Pe vectorul termenilor initiali se pun puteri ale lui 2 */
	for(i = 0; i <= k; i++) {
		initial[i] = pow(2, i);
	}

	/* In matrice se pune 1 pe diagonala de deasupra celei principale (pentru a
	se avansa cu cate un termen la fiecare inmultire si a se lua in considerare
	doar ultimi k) si 1 pe ultima linie (al k + 1 termen se calculeaza ca suma 
	celor k + 1 termeni de la pasul anterior) */
	for(i = 0; i < k + 1; i++) {
		for(j = 0; j < k + 1; j++) {
			if(j == i + 1) {
				a[i][j] = 1;
			}
			if(i == k) {
				a[i][j] = 1;
			}
		}
	}

	/* Se ridica a la n - k in vederea calculului celui de-al n-lea termen */
	a = logPowMatrix(a, n - k, k);

	
	/* Se inmulteste vectorul intial cu matricea a */
	long long result = 0;
	for(i = 0; i <= k; i++) {
		result += ((a[k][i] * initial[i]) % MOD);
	}
	
	/* Rezultatul se ridica la puterea numarul de coloane pt numarul total de
	cadre */
	result = power(result, m);
	

	fprintf(fw, "%lli", result);
	
	/* Se elibereaza memoria */
	for(i = 0; i <= k; i++) {
		free(a[i]);
	}
	free(a);
	free(initial);
	fclose(fr);
	fclose(fw);	

	return 0;
}
