#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include <unistd.h>

// Create an algorithm to match the target with the sum of any 2 numbers in the array

int *func(int target){
	int vec[] = {0,1,2,3,4,5,6,7,8,9};
	static int vret[2] = {0};

	for(int i = 0; i < sizeof(vec); i++)
		for(int j = i+1; j < sizeof(vec); j++)
			if (vec[i] + vec[j] == target){
				vret[0] = vec[i];
				vret[1] = vec[j];
			return vret;
		}
	return vret;
}

int main(){

	uint8_t vec[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	register int tam = sizeof(vec);

	srand(time(0));
	int gen = rand() % 10;
	register int target = 8 + gen;
	printf("\x1b[33m RANDOM NUM GENERATED: %d <=========================== \n\n\x1b[0m", target);


	for(int i = 0; i < tam-1; i++){
		for (int j = i+1; j < tam; j++){
			if ((vec[j] + vec[i]) == target)
				printf("FOUNDED: [ %d ] + [ %d ] = %d \n", vec[j], vec[i], target);
		}
	}
//	printf("GERAR O PROXIMO... \n\n");
//	sleep(1);
//	printf("%d - %d\n", func(rand()%10)[0], func(rand()%10)[1]);

return 0;
}
