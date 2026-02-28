//22

#include<stdio.h>
#include<string.h>

const char *s = "//%d%c%c#include<stdio.h>%c#include<string.h>%c%cconst char *s = %c%s%c;%c%cvoid wired(const char *s,int n) {%c%cchar *q = %c//%%d%c;%c%cchar r[10];%c%csprintf(r,q,n);%c%cint i = 0;%c%csize_t l = strlen(s);%c%cchar *p = %cn = %%d%c;%c%cchar z[10];%c%csprintf(z,p,n);%c%csize_t l1 = strlen(r);%c%csize_t l2 = strlen(z);%c%cwhile(i < l) {%c%c%cif(strncmp(&s[i],r,l1) == 0) {%c%c%c%cfprintf(stderr,%c//%%d%c,n+1);%c%c%c%ci += l1;%c%c%c}%c%c%cif(strncmp(&s[i],z,l2) == 0) {%c%c%c%cfprintf(stderr,%cn = %%d%c,n+1);%c%c%c%ci += l2;%c%c%c}%c%c%celse {fputc(s[i],stderr);%c%c%ci++;}%c%c}%c}%c%cint main() {%c%cchar string[4096];%c%cint n = %d;%c%c//fprintf(stdout,%c%%cHello, there is nothing fishy here...%%c(:^o^:)%%c%c,10,10,10);%c%csprintf(string,s,n,10,10,10,10,10,34,s,34,10,10,10,9,34,34,10,9,10,9,10,9,10,9,10,9,34,34,10,9,10,9,10,9,10,9,10,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,10,9,10,10,10,10,9,10,9,n,10,9,34,34,10,9,10,9,10,10);%c%cwired(string,n);%c}%c";

void wired(const char *s,int n) {
	char *q = "//%d";
	char r[10];
	sprintf(r,q,n);
	int i = 0;
	size_t l = strlen(s);
	char *p = "n = %d";
	char z[10];
	sprintf(z,p,n);
	size_t l1 = strlen(r);
	size_t l2 = strlen(z);
	while(i < l) {
		if(strncmp(&s[i],r,l1) == 0) {
			fprintf(stderr,"//%d",n+1);
			i += l1;
		}
		if(strncmp(&s[i],z,l2) == 0) {
			fprintf(stderr,"n = %d",n+1);
			i += l2;
		}
		else {fputc(s[i],stderr);
		i++;}
	}
}

int main() {
	char string[4096];
	int n = 22;
	//fprintf(stdout,"%cHello, there is nothing fishy here...%c(:^o^:)%c",10,10,10);
	sprintf(string,s,n,10,10,10,10,10,34,s,34,10,10,10,9,34,34,10,9,10,9,10,9,10,9,10,9,34,34,10,9,10,9,10,9,10,9,10,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,10,9,10,10,10,10,9,10,9,n,10,9,34,34,10,9,10,9,10,10);
	wired(string,n);
}
