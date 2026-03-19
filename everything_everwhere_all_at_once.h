#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdarg.h>

void int_print(int val,int location);
void float_print(double val,int location);
ssize_t length(char* s);
int expo(int a,int b);
void string_to_int(char *s,ssize_t l,int *p);
void string_to_float(char *s,ssize_t l,double *f);
void put_stuff(int where,char *s, ...);
void milky_twilight(int A[],int size,int numbr);
int bin_to_int(int A[],int s);

int comp(int a) {
	if(a == 1) {
		return 0;
	}
	else if (a == 0) {
		return 1;
	}
}

int chaos(int numbr) {
	int parent_row[512],offspring_row[512];
	/*if(numbr == 85 || numbr == 172 || numbr == 171 || numbr == 170) {
		numbr = (chaos(numbr/4) + chaos(numbr/2) + chaos(numbr/8) + chaos(numbr/16));
	}*/
	for(int i=0;i<512;i++) {
		parent_row[i] = 0;
	}
	
	milky_twilight(parent_row + 252,8,numbr);

	/*for(int i=0;i<8;i++) {
		put_stuff("~d\t",*(parent_row+252+i));
	}*/
	//put_stuff("~d",bin_to_int(parent_row+252,8));
	
	for(int i=0;i<512;i++) {
		offspring_row[i] = 0;
	}
	//put_stuff("\n");
	for(int j=1;j<511;j++) {
		if(parent_row[j+1] + parent_row[j] == 0) {
			offspring_row[j] = parent_row[j-1];
		}
		else offspring_row[j] = !(parent_row[j-1]);
	}
	/*for(int i=0;i<8;i++) {
		put_stuff("~d\t",*(offspring_row+252+i));
	}
	put_stuff("~d",bin_to_int(offspring_row+252,8));
	put_stuff("\n");*/
	return bin_to_int(offspring_row + 252,8);
}

void milky_twilight(int A[],int size,int numbr) {
	for(int i=size-1;i>=0;i--) {
		A[i] = numbr % 2;
		//put_stuff("~d ~d\n",A[i],numbr);
		numbr /= 2;
	}
}

int bin_to_int(int A[],int s) {
	int n=0;
	s -= 1;
	int i=0;
	for(;s>=0;s--) {
		n += A[s] * expo(2,i);
		i++;	
	}
	return n;
}

void string_to_float(char *s,ssize_t l,double *f) {
	char *p;
	int i=0;
	for(p=s;*p;p++) {
		if(*p != '.' && *p != '\n' && *p != '\0') {
			i++;
			continue;
		}
		else break;
	}
	
	*f=0;
	for(int j=0;j<i;j++) {
		*f += (s[j] - '0') * expo(10,i-j-1);
	}
	
	if(i + 2 != l) {
		for(int j=i+1;j<l-1;j++) {
		*f += (double) (s[j] - '0')/expo(10,j-i);
		}
	}
}

void float_print(double f,int location) {
	int i = (int) f;
	double g = f - i;
	int_print(i,location);
	write(location,".",1);
	for(int j=0;j<6;j++) {
		g = g*10;
		int_print((int) g,location);
		g = g - ((int) g);
	}
}



void get_stuff(int from,char* s, ...) {
va_list arg;
char *p;
char A[512];
ssize_t r = read(from,A,512);
va_start(arg,s);
for(p=s;*p;p++) {
	if(*p == '~') {
		switch(*++p) {
			case 'd': 
				int *i = va_arg(arg,int*);
				string_to_int(A,r,i);
				break;
			case 'f':
				double *f = va_arg(arg,double*);
				string_to_float(A,r,f);
				break;
			case 's':
				char *string = va_arg(arg,char*);
				for(int o=0;o<r;o++) {
					string[o] = A[o];
				}
				break;
			case 'c':
				int *c = va_arg(arg,int*);
				*c = A[0] - '0';
				break;
		}
	}
}
va_end(arg);
}

void string_to_int(char *s,ssize_t l,int *p) {
	l -= 2;
	int i = 0;
	*p = 0;
	for(;l>=0;l--) {
		*p += ((s[l] - '0') % 10)*expo(10,i) ;
		i++;
	}
}

void put_stuff(int where,char *s, ...) {
va_list arg;
char *p,*t;
char c;
int i;
char g;
double f;
va_start(arg,s);
for(p=s;*p;p++) {
if(*p != '~') {
g = *p;
write(where,&g,1);
}

else {switch(*++p) {
case 'd':
	i = va_arg(arg,int);
	int_print(i,where);
	break;
case 'f':
	f = va_arg(arg,double);
	float_print(f,where);
	break;
case 's':
	t = va_arg(arg,char *);
	write(where,t,length(t));
	break;
case 'c':
	c = va_arg(arg,int) + '0';
	write(where,&c,1);
	break;	
default: write(where,p,1);
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

void int_print(int val,int location) {
if(val == 0) {
write(location,"0",1);
}

if(val < 0) {
write(location,"-",1);
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
write(location,&A[i],1);
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
		put_stuff(1,"Enter number ~d: ",i);
		get_stuff(0,"~d",&A[i]);
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
	put_stuff(1,"\n---ARRAY SORTED---\n");
	for(i=0;i<5;i++) {
		put_stuff(0,"~d\t",A[i]);
	}
	put_stuff(1,"\n");
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
put_stuff(1,"Enter number ~d: ",i);
get_stuff(0,"~d",&A[i]);}

for(j=0;j<5;j++){

k = low(A,4-j);
	
for(i=0;i<4-j;i++)
{if(A[i] == k){t = A[i];
               A[i] = A[4-j];
               A[4-j] = t;}}}

put_stuff(1,"\n---ARRAY SORTED---\n");
for(i=4;i>=0;i--){put_stuff(1,"~d\t",A[i]);}
put_stuff(1,"\n");
}
