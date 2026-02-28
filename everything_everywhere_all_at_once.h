#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdarg.h>

void int_print(int val);
void float_print(double val);
ssize_t length(char* s);
int expo(int a,int b);
int string_to_int(char *s,ssize_t l);

void get_stuff(char* s, ...) {
va_list arg;
char *p;
double* f;
int *o;
char A[512];
ssize_t r = read(0,A,512);
va_start(arg,s);
for(p=s;*p;p++) {
	if(*p == '~') {
		switch(*++p) {
			case 'd': 
				int *i = va_arg(arg,int*);
				*i = string_to_int(A,r);
				break;
		}
	}
}
va_end(arg);
}

int string_to_int(char *s,ssize_t l) {
	l -= 2;
	int i = 0;
	int p = 0;
	for(;l>=0;l--) {
		p += ((s[l] - '0') % 10)*expo(10,i) ;
		i++;
	}
	return p;
}

void put_stuff(char *s, ...) {
va_list arg;
char *p,*t;
int i;
char g;
double f;
va_start(arg,s);
for(p=s;*p;p++) {
if(*p != '~') {
g = *p;
write(1,&g,1);
}

else {switch(*++p) {
case 'd':
	i = va_arg(arg,int);
	int_print(i);
	break;
/*case 'f':
	f = va_arg(arg,double);
	float_print(f);
	break;*/
case 's':
	t = va_arg(arg,char *);
	write(1,t,length(t));
	break;
default: write(1,p,1);
}}
}
va_end(arg);
}

int cant_open(int a,char *file) {
		if(a == -1) {
		write(2,"Error opening file\n",19);
		return 1;
		}
} 

ssize_t length(char *s) {
ssize_t i=0;
char *p;
p = s;
while(*p) {
i++;
p++;
}
return i;
}

void int_print(int val) {
if(val == 0) {
write(1,"0",1);
}

if(val < 0) {
write(1,"-",1);
val = -val;
}
char A[64];
int i=0;
char p;
while(val > 0) {
p = '0' + (val%10);
val /= 10;
A[i] = p;
i++;
}

i -= 1;

for(;i>=0;i--) {
write(1,&A[i],1);
}

}

int expo(int a,int b) {
	if(b == 0) {
		return 1;
	}
	else return a*expo(a,b-1);
}

void bubble_sort() {
	int A[5];
	int i,j,k;

	for(i=0;i<5;i++) {
		put_stuff("Enter number ~d: ",i);
		get_stuff("~d",&A[i]);
	}

	for(i=0;i<5;i++) {
		for(j=1;j<5;j++) {
			if(A[j-1] > A[j]) {
				k = A[j-1];
				A[j-1] = A[j];
				A[j]=k;
			}
		}
	}
	put_stuff("\n---ARRAY SORTED---\n");
	for(i=0;i<5;i++) {
		put_stuff("~d\t",A[i]);
	}
	put_stuff("\n");
}

int low(int A[],int p)
{
int a,i;
a = A[0];

for(i=1;i<=p;i++){if(a>A[i]){a = A[i];}}

return a;
}

void select_sort()
{
int A[5];
int k,i,t,j;

for(i=0;i<5;i++)
{
put_stuff("Enter number ~d: ",i);
get_stuff("~d",&A[i]);}

for(j=0;j<5;j++){

k = low(A,4-j);
	
for(i=0;i<4-j;i++)
{if(A[i] == k){t = A[i];
               A[i] = A[4-j];
               A[4-j] = t;}}}

put_stuff("\n---ARRAY SORTED---\n");
for(i=4;i>=0;i--){put_stuff("~d\t",A[i]);}
put_stuff("\n");
}
