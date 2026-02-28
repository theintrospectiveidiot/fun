#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char *argv[]) {
	FILE *f = fopen("collection_of_all_sins","r");
	FILE *g = fopen("trojanized_quine.c","w");
	FILE *h = fopen("gen_counter.c","w");
	char *c = "%c%c%c%s%c%c";
	char check[4096],string[4096];
	char z[10];
	sprintf(z,c,60,'/','/',argv[1],62,'~');
	char i;
	while(fscanf(f,"%[^\n]",check) != EOF) {
	if(strcmp(check,z) == 0) {
		fgetc(f);
		fprintf(g,"//%s\n\n",argv[1]);
		while((i = fgetc(f)) != '?') {
			fputc(i,g);
		}
	}
	fgetc(f);
	}

	char *s = "//%d%c%c#include<stdio.h>%c#include<string.h>%c%cconst char *s = %c%s%c;%c%cvoid wired(const char *s,int n) {%c%cchar *q = %c//%%d%c;%c%cchar r[10];%c%csprintf(r,q,n);%c%cint i = 0;%c%csize_t l = strlen(s);%c%cchar *p = %cn = %%d%c;%c%cchar z[10];%c%csprintf(z,p,n);%c%csize_t l1 = strlen(r);%c%csize_t l2 = strlen(z);%c%cwhile(i < l) {%c%c%cif(strncmp(&s[i],r,l1) == 0) {%c%c%c%cfprintf(stderr,%c//%%d%c,n+1);%c%c%c%ci += l1;%c%c%c}%c%c%cif(strncmp(&s[i],z,l2) == 0) {%c%c%c%cfprintf(stderr,%cn = %%d%c,n+1);%c%c%c%ci += l2;%c%c%c}%c%c%celse {fputc(s[i],stderr);%c%c%ci++;}%c%c}%c}%c%cint main() {%c%cchar string[4096];%c%cint n = %d;%c%c//fprintf(stdout,%c%%cHello, there is nothing fishy here...%%c(:^o^:)%%c%c,10,10,10);%c%csprintf(string,s,n,10,10,10,10,10,34,s,34,10,10,10,9,34,34,10,9,10,9,10,9,10,9,10,9,34,34,10,9,10,9,10,9,10,9,10,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,10,9,10,10,10,10,9,10,9,n,10,9,34,34,10,9,10,9,10,10);%c%cwired(string,n);%c}%c";
	int n = atoi(argv[1]);
	fprintf(h,s,n,10,10,10,10,10,34,s,34,10,10,10,9,34,34,10,9,10,9,10,9,10,9,10,9,34,34,10,9,10,9,10,9,10,9,10,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,10,9,10,10,10,10,9,10,9,n,10,9,34,34,10,9,10,9,10,10);
}
