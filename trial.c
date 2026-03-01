#include"everything_everywhere_all_at_once.h"

int main() {
	double a,b;
	int c,d,e;
	char s[100],t;
	put_stuff("Enter the first float number:\n");
	get_stuff("~f",&a);
	put_stuff("Enter the second float number:\n");
	get_stuff("~f",&b);
	double f = a + b;
	put_stuff("~f is sum of ~f and ~f (according to me)\n",f,a,b);
	put_stuff("Enter the first decimal number:\n");
	get_stuff("~d",&c);
	put_stuff("Enter the second decimal number:\n");
	get_stuff("~d",&d);
	put_stuff("~d is sum (according to me)\n",c+d);

	put_stuff("Enter a string, any string\n");
	get_stuff("~s",s);
	put_stuff("Please:\n");
	get_stuff("~d",&e);
	put_stuff("~c is the ~dth character, I think\n",s[e-1]-'0',e);
	put_stuff("Enter the character u wanna replace, at the position u have entered earlier.\n");
	int z;
	get_stuff("~c",&z);
	s[e-1] = z + '0';
	put_stuff("The new string (manipulated one) becomes: ~s",s);
}
