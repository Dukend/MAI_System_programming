/*  EKA   */
#include "mlisp.h"
extern double a/*2*/;
	 extern double b/*2*/;
	 double fun/*3*/ (double x) ;
	 double golden__section__search/*7*/ (double a, double b) ;
	 double golden__start/*12*/ (double a, double b) ;
	 extern double mphi/*19*/;
	 double __EKA__try/*20*/ (double a, double b
	 , double xa, double ya
	 , double xb, double yb) ;
	 bool close__enough_Q/*43*/ (double x, double y);
	 extern double tolerance/*44*/;
	 extern double total__iterations/*45*/;
	 extern double xmin/*46*/;
	 //________________ 
double a/*2*/ = 6.;
	 double b/*2*/ = 8.;
	 double fun/*3*/ (double x) {
 x = (x - (13. / 14.));
	 return
 ((x - sin(x)) - cos(x));
	 }
double golden__section__search/*7*/ (double a, double b) {
 {
 double xmin( ((a < b)
	? golden__start(a
	 , b)
	 
	: true
	? golden__start(b
	 , a)
	 
	: _infinity) );
	 newline();
	 return xmin;
	 }
}
double golden__start/*12*/ (double a, double b) {
 total__iterations = 0.;
	 {
 double xa( (a + (mphi * (b - a))) ),
	 xb( (b + (- (mphi * (b - a)))) );
	 return __EKA__try(a
	 , b
	 , xa
	 , fun(xa)
	 , xb
	 , fun(xb))
	 ;
	 }
}
double mphi/*19*/ = ((3. - sqrt(5.)) * (1. / 2.0e0));
	 double __EKA__try/*20*/ (double a, double b
	 , double xa, double ya
	 , double xb, double yb) {
 return
 (close__enough_Q(a, b)
	 
	? ((a + b) * 0.5e0)
	: true
	? display("+"),
	 total__iterations = (total__iterations + 1.),
	 ((ya < yb)
	? b = xb,
	 xb = xa,
	 yb = ya,
	 xa = (a + (mphi * (b - a))),
	 __EKA__try(a
	 , b
	 , xa
	 , fun(xa)
	 , xb
	 , yb)
	 
	: true
	? a = xa,
	 xa = xb,
	 ya = yb,
	 xb = (b - (mphi * (b - a))),
	 __EKA__try(a
	 , b
	 , xa
	 , ya
	 , xb
	 , fun(xb))
	 
	: _infinity)
	: _infinity);
	 }
bool close__enough_Q/*43*/ (double x, double y){
 return
 (abs((x - y)) < tolerance);
	 }
double tolerance/*44*/ = 0.001e0;
	 double total__iterations/*45*/ = 0.;
	 double xmin/*46*/ = 0.;
	 int main(){
 xmin = golden__section__search(a
	 , b)
	 ;
	 display("Interval=\t[");
	 display(a);
	 display(" , ");
	 display(b);
	 display("]\n");
	 display("Total number of iteranions=");
	 display(total__iterations);
	 newline();
	 display("xmin=\t\t");
	 display(xmin);
	 newline();
	 display("f(xmin)=\t");
	 display(fun(xmin));
	 newline();
	 std::cin.get();
	 return
 0;
	 }

