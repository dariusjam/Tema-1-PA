/* Mangea Liviu Darius 324CA */

#include<stdio.h>
#include<stdlib.h>

int main(int args, char** argv) {
	
	int N, perechi, i, j, k, sum = 0;
	int *master, *slave, *index, *imperechere, *slave_afis, *master_afis, *aux;
	
	FILE *fr, *fw;

	fr = fopen("date.in", "r");	
	fw = fopen("date.out", "w");
	
	fscanf(fr, "%d", &N);
	perechi = N / 2;
	
	master = (int*)malloc((N + 1) * sizeof(int));
	slave = (int*)malloc((N + 1) * sizeof(int));
	index = (int*)calloc((N + 1), sizeof(int));
	imperechere = (int*)malloc((N + 1) * sizeof(int));
	slave_afis = (int*)calloc((N + 1), sizeof(int));
	master_afis = (int*)calloc((N + 1), sizeof(int));
	aux = (int*)calloc((N + 1), sizeof(int));
	
	/* Citirea din fisier */
	for(i = 1; i <= N; i++) {
		fscanf(fr, "%d", &master[i]);
		fscanf(fr, "%d", &slave[i]);
	}


	int dif, count = 0;
	
	/* DIn prima pereche e obligatoriu sa aleg slave-ul */
	sum += slave[1];
	imperechere[1] = 1;
	slave_afis[1] = 1;
	
	/*Aceste 2 foruri imi pun in vectorul index un conor care imi face ca un
	clasament al diferentelor dintre master si slave */
	for(i = 2; i < N; i++) {
		aux[i] = master[i] - slave[i];
	}
	
	for (i = 2; i < N; i++) {
		for (j = 2; j < N; ) {
			if(aux[i] <= aux[j++]) {
				index[i]++;
			}
		}
	}
	

	/* In acest vector adun la suma cei mai convenabili jumatete din slaves
	si cei mai convenabili jumatate din masters, ramanand sa corectez astfel
	incat sa se respecte regula de imperechere */
	for(i = 2; i < N; i++) {
	
		if (index[i] >= perechi) {
			sum += master[i];
			imperechere[i] = imperechere[i - 1] - 1;
			master_afis[i] = 1;
		} else {
			sum += slave[i];
			imperechere[i] = imperechere[i - 1] + 1;
			slave_afis[i] = 1;
		}
		
	}
	
	/* Se schimba masterul cu slave in anumite perechi astfel incat sa se
	respecte regula de imperechere. Interschimbarile au in vedere ca in
	momentul in care se intalneste o pozitie in vector cu valoarea din vectorul
	imperechere negativa (vectorul imperechere imi tine diferenta intre numarul
	de slaves si de masters alesi pana in momentul respectiv care trebuie sa fie
	>= 0), se cauta in spate cea mai convenabila pereche pentru a se
	interschimba (folosind vectorul index) astfel se elimina greseala pana 
	in punctul respectiv. Apoi se merge in continuare pana la capat dupa 
	aceiasi idee. */
	int min, max = 2, cont = 0;
	for(i = 2; i < N; i++) {
		if(imperechere[i] < 0) {

			min = i;
			for(j = i; j >= 2; j--) {
				if(index[j] < index[min] && index[j] >= perechi) {
					min = j;
				}
			}
			
			sum -= master[min];
			sum += slave[min];
			index[min] = 0;
			imperechere[min] += 2;
			slave_afis[min] = 1;
			master_afis[min] = 0;
	
			for(j = min + 1; j < N; j++) {
				imperechere[j] += 2;
			}
			cont++;
		}
			
	}

	/* Aici se interschimba din slave in master un numar de perechi egal cu cel
	care s-a interschimbat in forul anterior pentru a fi jumatate din fiecare
	in final si se are in vedere sa nu se strice regula de imperechere */
	for(i = N - 1; i >= 2; i--) {
		
		max = 0;
		
		if(cont > 0) {
			j = N - 1;
			while (imperechere[j] >= 2) {
				if(index[max] < index[j]  && index[j] < perechi) {
					max = j;
				}
				j--;
			}
			
			sum -= slave[max];
			sum += master[max];
			slave_afis[max] = 0;
			master_afis[max] = 1;
			
			for(j = max; j < N; j++) {
				imperechere[j] -= 2;
			}
			
			index[max] = N;
			cont--;
		} else {
			break;
		}
	}
				
	/* Din ultima pereche este obligatoriu sa aleg masterul*/	
	sum += master[N];
	master_afis[N] = 1;
	
	fprintf(fw, "%d\n", sum);
	
	/*Se afiseaza perechile formate in ordinea ceruta. Pentru asta am tinut doi
	vectori, slave_afis, si master_afis care contineau 1 doar pe pozitile in
	care alesesem un slave sau un master. Parcurg cei doi vectori alternativ
	pana cand intalnesc o valoare de 1 si pun in fisier salariu respectiv. */
	i = 1;
	j = 1;
	k = 1;
	while(i <= N) {
		while(master_afis[j] == 0) {
			j++;
		}
		i++;
		fprintf(fw, "%d ", j);
		j++;
		
		while(slave_afis[k] == 0) {
			k++;
		}
		i++;
		fprintf(fw, "%d\n", k);
		k++;
	}
	

	free(master);
	free(slave);
	free(imperechere);
	free(index);
	free(master_afis);
	free(slave_afis);
	free(aux);
	fclose(fr);
	fclose(fw);	

	return 0;
}
