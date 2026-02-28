#include<stdio.h>
#include<string.h>

const char *s = "#include<stdio.h>%c#include<string.h>%c%cconst char *s = %c%s%c;%c%cvoid wired(const char *s) {%c%cchar *r = %cchar%c;%c%cint i = 0;%c%csize_t l = strlen(s);%c%cwhile(i < l) {%c%c%cif(strncmp(&s[i],r,4) == 0) {%c%c%c%cprintf(%c int%c);%c%c%c%ci += 4;%c%c%c}%c%c%celse {putchar(s[i]);%c%c%ci++;}%c%c}%c}%c%cint main() {%c%cchar string[4096];%c%csprintf(string,s,10,10,10,34,s,34,10,10,10,9,34,34,10,9,10,9,10,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,10,9,10,10,10,10,9,10,9,10,9,10);%c%cwired(string);%c}";

void wired(const char *s) {
	char *r = "char";
	int i = 0;
	size_t l = strlen(s);
	while(i < l) {
		if(strncmp(&s[i],r,4) == 0) {
			printf(" int");
			i += 4;
		}
		else {putchar(s[i]);
		i++;}
	}
}

int main() {
	char string[4096];
	sprintf(string,s,10,10,10,34,s,34,10,10,10,9,34,34,10,9,10,9,10,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,10,9,10,10,10,10,9,10,9,10,9,10);
	wired(string);
}
