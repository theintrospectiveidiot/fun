## fun

After going through Ken Thompson's Turing Award lecture titled "Reflections on trusting Trust", I felt like the idea of self reproducing code was such a cool thing!

If you wanna know the coolest thing here? Just go [here](https://github.com/theintrospectiveidiot/fun/tree/master?tab=readme-ov-file#now-the-cool-part).

But, I would suggest to go through all of them, or atleast from [here](https://github.com/theintrospectiveidiot/fun/tree/master?tab=readme-ov-file#now-comes-the-fun-part).

So, I wrote [inital_trojanized_quine.c](https://github.com/theintrospectiveidiot/fun/blob/master/initial_trojanized_quine.c) which would quietly change the `char` to ` int` after compiling.
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


## Now, comes the fun part!!

I thought, wouldn't it be cool if we can update a counter after it compiles itself, and somehow know how many times the program has run.

Implemented that in [gen_counter.c](https://github.com/theintrospectiveidiot/fun/blob/master/gen_counter.c).

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

Now, just compiling and overwriting itself with 
`gcc gen_counter.c -o gen_counter && ./gen_counter 2> gen_counter.c` would increase the comment by one, and the variable `n` in main() by 1.

## Now, the responsible part!!

So, the program overwrites itself, right? What if we do a small pointer incrementing mistake and the overwritten program crahses? 

What if the new overwritten file has weird characters because of our small mistake?

So, then implemented a version control system, which saves the code, along with the generation in `collection_of_all_sins`, and in case it crashes, just go and fetch the previous generation code.

So, wrote two programs that do exactly this!

[append.c](https://github.com/theintrospectiveidiot/fun/blob/master/append.c)

```c

int main(int argc,char *argv[]) {
	FILE *g = fopen(argv[2],"a+");  //collection_of_all_sins
	FILE *f = fopen(argv[1],"r");
	FILE *h = fopen("gen_counter.c","r");
	char c,d;
	fputc(60,g);
	while((c = fgetc(h)) != 10) {
		fputc(c,g);  //Gets the generation count from the gen_counter.c and saves it in this specific format.
	}
	fputc(62,g);

	while((c = fgetc(f)) != '#') 
		d = c;

	fputc('~',g);
	fputc(10,g);
	fputc(c,g);
	while((c = fgetc(f)) != EOF) {
		fputc(c,g);	 //This is the program storing the program we are working on, to collection_of_all_sins
	}
	fputc('?',g);  //This helps in identifying that the segement has ended.
	fputc(10,g);
}
```
We have used `gen_counter.c` to store the genration of some other program which might not necessarily be a quine. 

Although, the program we are doing this for (`trojanized_quine.c`) is a quine indeed, `gen_counter.c` makes it general...

To append it, that it for the next generation to `inherit` the previous generation, just make a Makefile


```Makefile

trojanized_quine.o: trojanized_quine.c
	gcc -c trojanized_quine.c

build_cemetery: append.c
	gcc append.c -o append

change_gen_counter: gen_counter.c
	gcc gen_counter.c -o gen_counter

inherit: trojanized_quine.o append gen_counter 
	gcc trojanized_quine.o -o trojanized_quine && ./append trojanized_quine.c collection_of_all_sins && ./trojanized_quine 2> trojanized_quine.c && ./gen_counter 2> gen_counter.c
```

Running `make inherit`  would save the program along with its generation count in `collection_of_all_sins` and increase the generation count in `gen_counter.c`.

Now, if u wanna summon the previous generation, u gotta `visit_cemetery`

[fetch.c](https://github.com/theintrospectiveidiot/fun/blob/master/fetch.c)

```c
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
			fputc(i,g);  //fetches the specific generation from the generation count and overwrites the code. (The format we used, really helps us)
		}
	}
	fgetc(f);
	}

	char *s = "//%d%c%c#include<stdio.h>%c#include<string.h>%c%cconst char *s = %c%s%c;%c%cvoid wired(const char *s,int n) {%c%cchar *q = %c//%%d%c;%c%cchar r[10];%c%csprintf(r,q,n);%c%cint i = 0;%c%csize_t l = strlen(s);%c%cchar *p = %cn = %%d%c;%c%cchar z[10];%c%csprintf(z,p,n);%c%csize_t l1 = strlen(r);%c%csize_t l2 = strlen(z);%c%cwhile(i < l) {%c%c%cif(strncmp(&s[i],r,l1) == 0) {%c%c%c%cfprintf(stderr,%c//%%d%c,n+1);%c%c%c%ci += l1;%c%c%c}%c%c%cif(strncmp(&s[i],z,l2) == 0) {%c%c%c%cfprintf(stderr,%cn = %%d%c,n+1);%c%c%c%ci += l2;%c%c%c}%c%c%celse {fputc(s[i],stderr);%c%c%ci++;}%c%c}%c}%c%cint main() {%c%cchar string[4096];%c%cint n = %d;%c%c//fprintf(stdout,%c%%cHello, there is nothing fishy here...%%c(:^o^:)%%c%c,10,10,10);%c%csprintf(string,s,n,10,10,10,10,10,34,s,34,10,10,10,9,34,34,10,9,10,9,10,9,10,9,10,9,34,34,10,9,10,9,10,9,10,9,10,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,10,9,10,10,10,10,9,10,9,n,10,9,34,34,10,9,10,9,10,10);%c%cwired(string,n);%c}%c";
	int n = atoi(argv[1]);
	fprintf(h,s,n,10,10,10,10,10,34,s,34,10,10,10,9,34,34,10,9,10,9,10,9,10,9,10,9,34,34,10,9,10,9,10,9,10,9,10,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,10,9,10,10,10,10,9,10,9,n,10,9,34,34,10,9,10,9,10,10);
	//adjusts the generation count in gen_counter.c accordingly.
}
```

This searches for the gen count we saved in that order, overwrites the current generation with the earlier generation, stops at `?` and updates the gen_counter.c accordingly

To make it work, just doing `gcc fetch.c -o fetch && ./fetch $(GEN)` would be sufficient.

## Now the cool part!!!!!!

Why just stop at counting generations?
What if we wanna change what the code does after it reaches a certain generation?

Something stupid like, changing the sorting algorithm from `select_sort()` to `bubble_sort()` when the code has been compiled and overwritten 42 times?

That's exactly what I did with [trojanized_quine.c](https://github.com/theintrospectiveidiot/fun/blob/master/trojanized_quine.c)!

```c
const char *s = "//%d%c%c#include<stdio.h>%c#include<string.h>%c#include%ceverything_everywhere_all_at_once.h%c%c%cconst char *s = %c%s%c;%c%cvoid wired(const char *s,int n) {%c%cchar *q = %c//%%d%c;%c%cchar r[10];%c%csprintf(r,q,n);%c%cint i = 0;%c%csize_t l = strlen(s);%c%cchar *p = %cn = %%d%c;%c%cchar z[10];%c%csprintf(z,p,n);%c%csize_t l1 = strlen(r);%c%csize_t l2 = strlen(z);%c%cwhile(i < l) {%c%c%cif(strncmp(&s[i],r,l1) == 0) {%c%c%c%cfprintf(stderr,%c//%%d%c,n+1);%c%c%c%ci += l1;%c%c%c}%c%c%cif(strncmp(&s[i],z,l2) == 0) {%c%c%c%cfprintf(stderr,%cn = %%d%c,n+1);%c%c%c%ci += l2;%c%c%c}%c%c%cif(strncmp(&s[i],%cselect_sort()%c,13) == 0) {%c%c%c%cif(n == 42) {%c%c%c%c%cfprintf(stderr,%cbubble_sort()%c);%c%c%c%c%ci += 13;%c%c%c%c}%c%c%c%celse {fputc(s[i],stderr);%c%c%c%ci++;}%c%c%c}%c%c%celse {fputc(s[i],stderr);%c%c%ci++;}%c%c}%c}%c%cint main() {%c%cchar string[4096];%c%cint n = %d;%c%cselect_sort();%c%cfprintf(stdout,%c%%cHello, there is nothing fishy here...%%c(:^o^:)%%c%c,10,10,10);%c%csprintf(string,s,n,10,10,10,10,34,34,10,10,34,s,34,10,10,10,9,34,34,10,9,10,9,10,9,10,9,10,9,34,34,10,9,10,9,10,9,10,9,10,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,34,34,10,9,9,9,10,9,9,9,9,34,34,10,9,9,9,9,10,9,9,9,10,9,9,9,10,9,9,9,10,9,9,10,9,9,10,9,9,10,9,10,10,10,10,9,10,9,n,10,9,10,9,34,34,10,9,10,9,10,10);%c%cwired(string,n);%c}%c";
```

This is again the string that stores the skeleton of the code, just like it did in `gen_counter.c` and `initial_trojanized_quine.c`,

Again, injecting this string `s` into `string` in `main()`:

```c
	char string[4096];
	int n = 22;
	fprintf(stdout,"%cHello, there is nothing fishy here...%c(:^o^:)%c",10,10,10);
	sprintf(string,s,n,10,10,10,10,34,34,10,10,34,s,34,10,10,10,9,34,34,10,9,10,9,10,9,10,9,10,9,34,34,10,9,10,9,10,9,10,9,10,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,10,9,9,9,34,34,10,9,9,9,10,9,9,10,9,9,34,34,10,9,9,9,10,9,9,9,9,34,34,10,9,9,9,9,10,9,9,9,10,9,9,9,10,9,9,9,10,9,9,10,9,9,10,9,9,10,9,10,10,10,10,9,10,9,n,10,9,10,9,34,34,10,9,10,9,10,10);
```

This injects `s` into `string` in `main()`.

Now, the main part, the function that does this!

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
			i += l1;  //increments the gen count in the comment
		}
		if(strncmp(&s[i],z,l2) == 0) {
			fprintf(stderr,"n = %d",n+1);
			i += l2;  //increments the gen count of the variable in main()
		}
		if(strncmp(&s[i],"select_sort()",13) == 0) {
			if(n == 42) {
				fprintf(stderr,"bubble_sort()");
				i += 13;  //changes the function being called from main() when n = 42
			}
			else {fputc(s[i],stderr);
			i++;}
		}
		else {fputc(s[i],stderr);
		i++;}
	}
}
```

Just calling it in main by `wired(string,n);` in `main()` would do the work.

To see it work, just run `make inherit` and see it quietly altering stuff.

The functions `select_sort()` and `bubble_sort()` are defined in the header file [everything_everywhere_all_at_once.h](https://github.com/theintrospectiveidiot/fun/blob/master/everything_everywhere_all_at_once.h) which also has my custom `printf()` called `put_stuff()` and custom `scanf()` called `get_stuff()`.


## P.S.

I have also implemented re-rooting that is starting a new branch, u gotta do `patricide`. The recipe for that too is in the [Makefile](https://github.com/theintrospectiveidiot/fun/blob/master/Makefile). 

