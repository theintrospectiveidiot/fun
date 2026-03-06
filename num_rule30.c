#include"/run/media/theintrospectiveidiot/New Volume/fun/everything_everywhere_all_at_once.h"

int main() {
	int p = 256;
	int A[256][512];

	for(int i=0;i<p;i++) {
		for(int j=0;j<2*p;j++) {
			A[i][j] = 0;
		}
	}
	
	A[0][252+1] = 1;
	A[0][252+5] = 1;
	A[0][252+7] = 1;
	put_stuff("~d\n",bin_to_int(A[0] + 252,8));
	for(int i=1;i<p;i++) {
		for(int j=1;j<2*p-1;j++) {
			if(A[i-1][j] + A[i-1][j+1] == 0) {
				A[i][j] = A[i-1][j-1];
			}
			else A[i][j] = comp(A[i-1][j-1]);
		}	
	}
	
	char z = 32;
	for(int i=0;i<p;i++) {
		/*for(int j=0;j<2*p;j++) {
			put_stuff("~d",A[i][j]);
		}*/
		put_stuff("\t ~d\t~d\t~s",i,bin_to_int(A[i] + 252,8),((bin_to_int(A[i] + 252,8) % 42) == 0) ? "Yup":"Nope");
		put_stuff("\n");
	}
}
