#include <unistd.h>

int ilen(int li[]) {
    int n = 0;
    while (li[n += 4]) {}
    return n / 4;
}

void func(int k[]){
	//char result[2] = {(char)(sizeof(k)>>2)+0x30, '\n'};  // Melhor forma de compactar

	char result[2] = {(char)ilen(k)+0x30, '\n'};  // Melhor forma de compactar
	write(1, result, 2);
}

int main(void){
	int k[] =  {12,13,2,3,4,5};

	char result[2] = {(char)(sizeof(k)>>2)+0x30, '\n'};  // Melhor forma de compactar

	//char result[2];
	//	result[0] = (char)(sizeof(k)>>2)+0x30;
	//	result[1] = '\n';

	write(1, result ,2);

	func(k);

   return 0;
}
