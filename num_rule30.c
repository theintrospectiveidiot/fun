#include"/run/media/theintrospectiveidiot/New Volume/fun/everything_everywhere_all_at_once.h"

int main() {
	int p = 256;
	int A[256][512];

	for(int i=0;i<p;i++) {
		for(int j=0;j<2*p;j++) {
			A[i][j] = 0;
		}
	}
	
    //69 => 0 1 0 0 0 1 0 1

	A[0][512 - 1] = 1;
	A[0][512 - 3] = 1;
	A[0][512 - 7] = 1;
	put_stuff(1,"~d\n",bin_to_int(A[0], 512));
	for(int i=1;i<p;i++) {
		for(int j=1;j<2*p-1;j++) {
			if(A[i-1][j] + A[i-1][j+1] == 0) {
				A[i][j] = A[i-1][j-1];
			}
			else A[i][j] = !(A[i-1][j-1]);
		}	
	}
	
	char z = 32;
	for(int i=0;i<p;i++) {
		/*for(int j=0;j<2*p;j++) {
			put_stuff("~d",A[i][j]);
		}*/
		put_stuff(1,"\t ~d\t~d\t~s",i,bin_to_int(A[i], 512),((bin_to_int(A[i], 512) % 42) == 0) ? "Yup":"Nope");
		put_stuff(1,"\n");
	}
}
