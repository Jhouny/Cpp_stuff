#include<stdio.h>

using namespace std;

int main() {
	char c;
	FILE *f1 = fopen("test.txt", "r");
	while(fscanf(f1, "%c", &c) != EOF) {
		printf("%c", c);
	}
	fclose(f1);
}
