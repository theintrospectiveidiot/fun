## fun

After going through Ken Thompson's Turing Award lecture titled "Reflections on trusting Trust", I realized that the idea of self reproducing code was such a cool thing!

So, I wrote `inital_trojanized_quine.c` which would quietly change the `char` to ` int` after compiling.
```c
	const char s = #include<stdio.h>%c#include<string.h>%c%cconst char *s = %c%s%c;%c%cvoid wired(const char *s) {%c%cchar *r = %cchar%c;%c%cint i = 0;%c%csize_t l = strlen(s);%c%cwhile(i < l) {%c%c%cif(strncmp(&s[i],r,4) == 0) {%c%c%c%cprintf(%c int%c);%c%c%c%ci += 4;%c%c%c}%c%c%celse {putchar(s[i]);%c%c%ci++;}%c%c}%c}%c%cint main() {%c%cchar string[4096];%c%csprintf(string,s,10,10,10,34,s,34,10,10,10,9,34,34,10,9,10,9,10,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,10,9,10,10,10,10,9,10,9,10,9,10);%c%cwired(string);%c};
```

This is the string that contains the code itself. Now we just need to put the ASCII values for `%c` and the integer for `%d` in the string using `sprintf`.

```c
	char string[4096];
    sprintf(string,s,10,10,10,34,s,34,10,10,10,9,34,34,10,9,10,9,10,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,10,9,10,10,10,10,9,10,9,10,9,10);
```
This injects the code to `string` and then, we pass it to the function `wired` which does the mutation.

```c
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
```

Now, just calling by `wired(string)` would do what we wanted.


Now, comes the fun part!!

I thought, wouldn't it be cool if we can update a counter after it compiles itself, and somehow know how many times the program has run.

Implemented that in `gen_counter.c`.
`//22` represents the number of times it has been compiled and overwritten.

```c
const char *s = "//%d%c%c#include<stdio.h>%c#include<string.h>%c%cconst char *s = %c%s%c;%c%cvoid wired(const char *s,int n) {%c%cchar *q = %c//%%d%c;%c%cchar r[10];%c%csprintf(r,q,n);%c%cint i = 0;%c%csize_t l = strlen(s);%c%cchar *p = %cn = %%d%c;%c%cchar z[10];%c%csprintf(z,p,n);%c%csize_t l1 = strlen(r);%c%csize_t l2 = strlen(z);%c%cwhile(i < l) {%c%c%cif(strncmp(&s[i],r,l1) == 0) {%c%c%c%cfprintf(stderr,%c//%%d%c,n+1);%c%c%c%ci += l1;%c%c%c}%c%c%cif(strncmp(&s[i],z,l2) == 0) {%c%c%c%cfprintf(stderr,%cn = %%d%c,n+1);%c%c%c%ci += l2;%c%c%c}%c%c%celse {fputc(s[i],stderr);%c%c%ci++;}%c%c}%c}%c%cint main() {%c%cchar string[4096];%c%cint n = %d;%c%c//fprintf(stdout,%c%%cHello, there is nothing fishy here...%%c(:^o^:)%%c%c,10,10,10);%c%csprintf(string,s,n,10,10,10,10,10,34,s,34,10,10,10,9,34,34,10,9,10,9,10,9,10,9,10,9,34,34,10,9,10,9,10,9,10,9,10,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,10,9,10,10,10,10,9,10,9,n,10,9,34,34,10,9,10,9,10,10);%c%cwired(string,n);%c}%c";
```
This is the string that contains the skeleton of code like `initial_trojanized_quine.c`.

And, again injecting stuff into `string` that would be the new code:
```c
char string[4096];
	int n = 22;
	sprintf(string,s,n,10,10,10,10,10,34,s,34,10,10,10,9,34,34,10,9,10,9,10,9,10,9,10,9,34,34,10,9,10,9,10,9,10,9,10,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,10,9,10,10,10,10,9,10,9,n,10,9,34,34,10,9,10,9,10,10);
```
This is basically representing the whole code in `string`.

Now, the function which is responsible for increasing the count (n):

```c
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
			i += l1;      //Increases the count of the comment by 1
		}
		if(strncmp(&s[i],z,l2) == 0) {
			fprintf(stderr,"n = %d",n+1);
			i += l2; 	  //Increases the count of the variable n in main() by 1 
		}
		else {fputc(s[i],stderr);
		i++;}
	}
}
```

Now, just compiling and overwriting itself with `gcc gen_counter.c -o gen_counter && ./gen_counter 2> gen_counter.c` would increase the comment by one, and the variable `n` in main() by 1.





