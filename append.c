#include<stdio.h>

int main(int argc,char *argv[]) {
	FILE *g = fopen(argv[2],"a+");
	FILE *f = fopen(argv[1],"r");
	FILE *h = fopen("gen_counter.c","r");
	char c,d;
	fputc(60,g);
	while((c = fgetc(h)) != 10) {
		fputc(c,g);
	}
	fputc(62,g);

	while((c = fgetc(f)) != '#') 
		d = c;

	fputc('~',g);
	fputc(10,g);
	fputc(c,g);
	while((c = fgetc(f)) != EOF) {
		fputc(c,g);	
	}
	fputc('?',g);
	fputc(10,g);
}
