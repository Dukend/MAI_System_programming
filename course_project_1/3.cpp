/*  EKA   */
#include "mlisp.h"
extern double VARIANT/*2*/;
	 extern double LAST__DIGIT__OF__GROUP__NUMBER/*3*/;
	 extern double KINDS__OF__COINS/*4*/;
	 double first__denomination/*6*/ (double kind__of__coins) ;
	 double count__change/*17*/ (double amount) ;
	 bool pier_Q/*36*/ (double x_Q, double y_Q);
	 double cc/*40*/ (double amount, double kinds__of__coins) ;
	 double denomination__list/*50*/ (double kinds__of__coins) ;
	 double GR__AMOUNT/*58*/ () ;
	 //________________ 
double VARIANT/*2*/ = 13.;
	 double LAST__DIGIT__OF__GROUP__NUMBER/*3*/ = 6.;
	 double KINDS__OF__COINS/*4*/ = 6.;
	 double first__denomination/*6*/ (double kind__of__coins) {
 return
 ((kind__of__coins == 1.)
	? 1.
	: (kind__of__coins == 2.)
	? 2.
	: (kind__of__coins == 3.)
	? 3.
	: (kind__of__coins == 4.)
	? 5.
	: (kind__of__coins == 5.)
	? 10.
	: (kind__of__coins == 6.)
	? 20.
	: true
	? 0.
	: _infinity);
	 }
double count__change/*17*/ (double amount) {
 display("______\n amount: ");
	 display(amount);
	 newline();
	 display("KINDS-OF-COINS: ");
	 display(KINDS__OF__COINS);
	 newline();
	 {
 double largest__coin( first__denomination(KINDS__OF__COINS) );
	 display("largest-coin: ");
	 display(largest__coin);
	 newline();
	 return (((0. < amount) && (0. < KINDS__OF__COINS) && (0. < largest__coin))
	? display("List of coin denominations: "),
	 denomination__list(KINDS__OF__COINS),
	 display("count-change= "),
	 cc(amount
	 , KINDS__OF__COINS)
	 
	: true
	? display("Improper parameter value!\ncount-change= "),
	 -1.
	: _infinity);
	 }
}
bool pier_Q/*36*/ (double x_Q, double y_Q){
 return
 (0. == ((x_Q || y_Q)
	? 1.
	: true
	? 0.
	: _infinity));
	 }
double cc/*40*/ (double amount, double kinds__of__coins) {
 return
 ((amount == 0.)
	? 1.
	: pier_Q((amount < 0.), (kinds__of__coins == 0.))
	 
	? (cc(amount
	 , (kinds__of__coins - 1.))
	  + cc((amount - first__denomination(kinds__of__coins))
	 , kinds__of__coins)
	 )
	: true
	? 0.
	: _infinity);
	 }
double denomination__list/*50*/ (double kinds__of__coins) {
 return
 ((kinds__of__coins == 0.)
	? newline(),
	 0.
	: true
	? display(first__denomination(kinds__of__coins)),
	 display(" "),
	 denomination__list((kinds__of__coins - 1.))
	: _infinity);
	 }
double GR__AMOUNT/*58*/ () {
 return
 remainder(((100. * LAST__DIGIT__OF__GROUP__NUMBER) + VARIANT)
	 , 231.)
	 ;
	 }
int main(){
 display("Variant ");
	 display(VARIANT);
	 newline();
	 newline();
	 display(count__change(100.));
	 newline();
	 display(count__change(GR__AMOUNT()));
	 newline();
	 KINDS__OF__COINS = 13.;
	 display(count__change(100.));
	 newline();
	 display("(c) Kondratev E.A. 2021\n");
	 std::cin.get();
	 return
 0;
	 }

