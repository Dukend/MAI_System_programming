/* $n27 */
#include "semantics.h"
using namespace std;
//bool ConstExp = false;
void tSM::init(){
	globals.clear();
  locals.clear();
  params.clear();
  scope = 0; // вне процедуры 

  globals["abs"] = tgName(PROC | DEFINED | BUILT, "", 1);
  globals["atan"] = tgName(PROC | DEFINED | BUILT, "", 1);
  globals["cos"] = tgName(PROC | DEFINED | BUILT, "", 1);
  globals["exp"] = tgName(PROC | DEFINED | BUILT, "", 1);
  globals["expt"] = tgName(PROC | DEFINED | BUILT, "", 2);
  globals["log"] = tgName(PROC | DEFINED | BUILT, "", 1);
  globals["remainder"] = tgName(PROC | DEFINED | BUILT, "", 2);
  globals["quotient"] = tgName(PROC | DEFINED | BUILT, "", 2);
  globals["sin"] = tgName(PROC | DEFINED | BUILT, "", 1);
  globals["sqrt"] = tgName(PROC | DEFINED | BUILT, "", 1);
  globals["tan"] = tgName(PROC | DEFINED | BUILT, "", 1);
  globals["display"] = tgName(PROC | DEFINED | BUILT, "", 1);
  globals["newline"] = tgName(PROC | DEFINED | BUILT, "", 0);
  globals["e"] = tgName(VAR | DEFINED | BUILT, "");
  globals["pi"] = tgName(VAR | DEFINED | BUILT, "");
  return;
}
int tSM::p01(){ //       S -> PROG
	bool error=false;
	for(tGlobal::iterator it=globals.begin(); it!=globals.end(); ++it){
		if((!it->second.test(DEFINED)) && it->second.test(USED)) {
			if(it->second.test(PROC)) {
				ferror_message += "Error[01-1] in line" + it->second.line + ": the procedure '" + it->first +
          		"' is used, but not defined!\n";
				//переменная 'a' используется, но не определена
				//the variable 'a' is used, but not defined!
          		error = true;
			}
			else if(it->second.test(VAR)){
				ferror_message += "Error[01-2] in line" + it->second.line + ": the variable '" + it->first +
          		"' is used, but not defined!\n";
				//процедура 'f' используется, но не определена
				//the procedure 'f' is used, but not defined!
          		error = true;
			}
		}
	}//for...
 if(error) return 1;
	return 0;}
int tSM::p02(){ //    PROG -> CALCS
	return 0;}
int tSM::p03(){ //    PROG -> DEFS
	return 0;}
int tSM::p04(){ //    PROG -> DEFS CALCS
	return 0;}


int tSM::p05(){ // E -> $id
	string name = S1->name;
	switch (scope) {
	case 2: if(locals.count(name))break;
	case 1: if(params.count(name))break;
	default:
		tgName& ref = globals[name];
		if (ref.empty()) {
			ref = tgName(VAR|USED, S1->line);
			break;
		}
		if (ref.test(VAR)){
			ref.set(USED);
			break;
		}
		if (ref.test(BUILT)){
			ferror_message += "Error[05-1] in line "+ S1->line +": the built-in '" + name + 
			"' procedure \n\t\t\t cannot be used as a variable!\n";			
			// встроенную процедуру 'abs' нельзя использовать в качестве переменной
			// the built-in 'abs' procedure cannot be used as a variable
			return 1;
		}
		ferror_message += "Error[05-2] in line "+ S1->line +": the name '" + name + 
			"' cannot be used to refer to a variable;\n" +
			"\t\t\tit was previously declared as a procedure in line "+ ref.line +" !\n";
			// имя 'f' нельзя использовать для ссылки на переменную, в строке 1 оно ранее объявлено как процедура
			// the name 'f' cannot be used to refer to a variable; it was previously declared as a procedure in line 1
		return 1;
	}
	return 0;
}

int tSM::p06(){ //       E -> $int
	return 0;}
int tSM::p07(){ //       E -> $dec
	return 0;}
int tSM::p08(){ //       E -> AREX
	return 0;}
int tSM::p09(){ //       E -> COND
	return 0;}
int tSM::p10(){ //       E -> EASYLET
	return 0;}
int tSM::p11(){ //       E -> CPROC
	return 0;}
int tSM::p12(){ //    AREX -> HAREX E )
	return 0;}
int tSM::p13(){ //   HAREX -> ( AROP
	return 0;}
int tSM::p14(){ //   HAREX -> HAREX E
	return 0;}
int tSM::p15(){ //    AROP -> +
	return 0;}
int tSM::p16(){ //    AROP -> -
	return 0;}
int tSM::p17(){ //    AROP -> *
	return 0;}
int tSM::p18(){ //    AROP -> /
	return 0;}
int tSM::p19(){ // EASYLET -> HEASYL E )
	return 0;}
int tSM::p20(){ //  HEASYL -> ( let ( )
	return 0;}
int tSM::p21(){ //  HEASYL -> HEASYL INTER
	return 0;}


int tSM::p22(){ //   CPROC -> HCPROC )
	switch (scope) { 
	case 2:
		if (locals.count(S1->name)) { ferror_message += "Error[22-1] in line "+ S1->line +
		": the local variable '" + S1->name + "' masks the procedure!\n";
		//локальная переменная 'a' маскирует процедуру!
		//the local variable 'a' masks the procedure!
			return 1; 
		}
	case 1:
		if (params.count(S1->name)) {
		ferror_message = "Error[22-2] in line "+ S1->line +": the parameter '" +
		S1->name +"' masks the procedure!\n";
		//параметр 'a' маскирует процедуру!
		//the parameter 'a' masks the procedure!
		return 1;
		}
	default:
		if (globals[S1->name].empty()) { 
			globals[S1->name] = tgName(PROC | USED, S1->line, S1->count);
			/* if (ConstExp && !globals[S1->name].test(BUILT))
				ConstExp = false; */
				return 0;
			}
		if (!globals[S1->name].test(PROC)) {
			ferror_message = "Error[22-3] in line "+ S1->line + ": '" + S1->name +
			"' is not a procedure\n";
			//'a' не процедура
			//'a' is not a procedure
			return 1;
		}
		if (globals[S1->name].arity != S1->count) {
			ferror_message = "Error[22-4] in line "+ S1->line +": the procedure '" + S1->name + "' ";
			if (globals[S1->name].test(DEFINED)) {
				ferror_message += "expects "; 
			}
			else {
				ferror_message += "has already been called \n\t with "; 
			}
			ferror_message += std::to_string(globals[S1->name].arity) +
			" argument" + (globals[S1->name].arity != 1 ? "s" : "")+ ", given: " + std::to_string(S1->count) + "\n";
			//процедура 'f' ожидает(уже вызывалась с) 1(5) аргумент(ов), дано 4
			//the procedure 'f' expects(has already been called with) 1(5) argument(s), given 4
			return 1; 
		}
		globals[S1->name].set(USED);
		/* if (ConstExp && !globals[S1->name].test(BUILT)) {
		ConstExp = false;
		} */ 
		return 0;
	}
	return 0;
}
	
int tSM::p23(){ //  HCPROC -> ( $id
	S1->name = S2->name; 
    S1->count = 0;
	return 0;
}
int tSM::p24(){ //  HCPROC -> HCPROC E
	++S1->count;
	return 0;
}
int tSM::p25(){ //    COND -> ( cond BRANCHES )
	return 0;}
int tSM::p26(){ //BRANCHES -> ELSE
	return 0;}
int tSM::p27(){ //BRANCHES -> CLAUS BRANCHES
	return 0;}
int tSM::p28(){ //   CLAUS -> ( BOOL E )
	return 0;}
int tSM::p29(){ //    ELSE -> ( else ELSEB )
	return 0;}
int tSM::p30(){ //   ELSEB -> E
	return 0;}
int tSM::p31(){ //   ELSEB -> INTER ELSEB
	return 0;}
int tSM::p32(){ //     STR -> $str
	return 0;}
int tSM::p33(){ //     STR -> SIF
	return 0;}
int tSM::p34(){ //     SIF -> ( if BOOL STR STR )
	return 0;}
int tSM::p35(){ //    BOOL -> $bool
	return 0;}
int tSM::p36(){ //    BOOL -> $idq
	return 0;}
int tSM::p37(){ //    BOOL -> REL
	return 0;}
int tSM::p38(){ //    BOOL -> ( not BOOL )
	return 0;}
int tSM::p39(){ //    BOOL -> CPRED
	return 0;}

int tSM::p40(){ //   CPRED -> HCPRED )
	//cout<< "p40 :" << S1->types << "\n";
	if (globals[S1->name].empty()) {
		globals[S1->name] = tgName(PROC | USED, S1->line, S1->count, S1->types);
		/* if (ConstExp && !globals[S1->name].test(BUILT)) {
			ConstExp = false;
		} */
		return 0; 
	}
	if (!globals[S1->name].test(PROC)) {
	ferror_message = "Error[40-1] in line " + S1->line + ": '" + S1->name +
	"' is not a predicate\n"; return 1;
	//'a' не предикат
	//'a' is not a predicate
	}
	if (globals[S1->name].arity != S1->count) {
		ferror_message = "Error[40-2] in line " + S1->line + ": predicate '" + S1->name + "' ";
		if (globals[S1->name].test(DEFINED)) { 
			ferror_message += "expects\n\t";
		}
		else {
			ferror_message += "has already been called\n\t with ";
		}
		ferror_message += std::to_string(globals[S1->name].arity) +
		" argument" + (globals[S1->name].arity != 1 ? "s" : "") + ", given: " + std::to_string(S1->count) + "\n";
		//предикат 'p' ожидает(уже вызывался с) 1(5) аргумент(ов), дано 4
		//the predicate 'p' expects(has already been called with) 1(5) argument(s), given 4
		return 1; 
	}
    if (globals[S1->name].types != S1->types) {
		ferror_message = "Error[67-3] in line " + S1->line + ": wrong types of parameters in the predicate '" + S1->name + "', " +
		"need " + Uint_to_str(globals[S1->name].types) + ", given " + Uint_to_str(S1->types) + "\n";
		//предикат 'p' ожидает(уже вызывался с) 1(5) аргумент(ов), дано 4
		//the predicate 'p' expects(has already been called with) 1(5) argument(s), given 4
		return 1; 
	}
	globals[S1->name].set(USED);
	/* if (ConstExp && !globals[S1->name].test(BUILT))
		ConstExp = false;  */
    
	return 0;
}

int tSM::p41(){ //  HCPRED -> ( $idq
	S1->name = S2->name;
	S1->count = 0;
	S1->types = 0;
	return 0;
}

int tSM::p42(){ //  HCPRED -> HCPRED ARG
	S1->types = S1->types | (S2->types << S1->count);
	++S1->count;
	//cout << "\t\t\t  1  " << S1->types << "  2  "<< S2->types << "\n";
	return 0;
}
int tSM::p43(){ //     ARG -> E
	S1->types = 0;
	return 0;}
int tSM::p44(){ //     ARG -> BOOL
	S1->types = 1;
	return 0;}
int tSM::p45(){ //     REL -> ( = E E )
	return 0;}
int tSM::p46(){ //     REL -> ( <= E E )
	return 0;}
int tSM::p47(){ //     SET -> HSET E )
	return 0;}


int tSM::p48(){ //    HSET -> ( set! $id
	switch (scope) {
	case 2:
		if (locals.count(S3->name)) {
			return 0; 
		}
	case 1:
		if (params.count(S3->name)) {
			return 0; 
		}
	default:
		if (globals[S3->name].empty()) {
			globals[S3->name] = tgName(VAR | USED);
			return 0; 
		}
		if (globals[S3->name].test(VAR) && globals[S3->name].test(BUILT)) {
			ferror_message = "Error[48-1] in line " + S1->line + ": the variable '" + S3->name +
			"' can't be redefined\n";
			//переменная 'f' не может быть переопределена
			//The variable 'f' cannot be redefined
			return 1;
		}
		if (globals[S3->name].test(PROC)) {
			ferror_message = "Error[48-2] in line " + S1->line + ": the procedure '" + S3->name +
			"can't be redefined\n";
			//процедура 'f' не может быть переопределена
			//The procedure 'f' cannot be redefined
			return 1;
		} 
		globals[S3->name].set(USED);
		return 0;
	}
	return 0;
}


int tSM::p49(){ // DISPSET -> ( display E )
	return 0;}
int tSM::p50(){ // DISPSET -> ( display BOOL )
	return 0;}
int tSM::p51(){ // DISPSET -> ( display STR )
	return 0;}
int tSM::p52(){ // DISPSET -> ( newline )
	return 0;}
int tSM::p53(){ // DISPSET -> SET
	return 0;}
int tSM::p54(){ //   INTER -> DISPSET
	return 0;}
int tSM::p55(){ //   INTER -> E
	return 0;}
int tSM::p56(){ //   CALCS -> CALC
	return 0;}
int tSM::p57(){ //   CALCS -> CALCS CALC
	return 0;}
int tSM::p58(){ //    CALC -> E
	return 0;}
int tSM::p59(){ //    CALC -> BOOL
	return 0;}
int tSM::p60(){ //    CALC -> STR
	return 0;}
int tSM::p61(){ //    CALC -> DISPSET
	return 0;}
int tSM::p62(){ //    DEFS -> DEF
	return 0;}
int tSM::p63(){ //    DEFS -> DEFS DEF
	return 0;}
int tSM::p64(){ //     DEF -> PRED
	return 0;}
int tSM::p65(){ //     DEF -> VAR
	return 0;}
int tSM::p66(){ //     DEF -> PROC
	return 0;}


int tSM::p67(){ //    PRED -> HPRED BOOL )
	cout << "\t count:" << S1->count << "types: " << S1->types << "\n";
	if (globals[S1->name].empty()) {
		params.clear();
		scope = 0;
		globals[S1->name] = tgName(PROC | DEFINED, S1->line, S1->count, S1->types);
		return 0;
	}
	if (globals[S1->name].test(DEFINED)) {
		ferror_message = "Error[67-1] in line " + S1->line + ": the predicate '" + S1->name +
		"'is already defined\n";
		//предикат 'p' уже определен
		//the predicate 'p' is already defined
		return 1;
	}
	if (globals[S1->name].arity != S1->count) {
		ferror_message = "Error[67-2] in line " + S1->line + ": the predicate '" + S1->name + "' " +
		"has already been called \n\t with ";
		ferror_message += std::to_string(globals[S1->name].arity) +
		" argument" + (globals[S1->name].arity != 1 ? "s" : "") + ", given: " + std::to_string(S1->count) + "\n";
		//предикат 'p' ожидает(уже вызывался с) 1(5) аргумент(ов), дано 4
		//the predicate 'p' expects(has already been called with) 1(5) argument(s), given 4
		return 1; 
	}
	if (globals[S1->name].types != S1->types) {
		ferror_message = "Error[67-3] in line " + S1->line + ": wrong types of parameters in the predicate '" + S1->name + "', " +
		"need " + Uint_to_str(globals[S1->name].types) + ", given " + Uint_to_str(S1->types) + "\n";
		//предикат 'p' ожидает(уже вызывался с) 1(5) аргумент(ов), дано 4
		//the predicate 'p' expects(has already been called with) 1(5) argument(s), given 4
		return 1; 
	}
	params.clear();
	scope = 0; 
	globals[S1->name].set(DEFINED);
	return 0;
}


int tSM::p68(){ //   HPRED -> PDPAR )
	scope = 1;
	return 0;
}

int tSM::p69(){ //   PDPAR -> ( define ( $idq
	S1->name = S4->name;
	S1->count = 0;
	S1->types = 0;
	return 0;
}


int tSM::p70(){ //   PDPAR -> PDPAR $idq
	if (params.count(S2->name)) {
		ferror_message = "Error[70-1] in line " + S1->line + ": the predicate '" + S1->name +
		"' duplicates a parameter '" + S2->name + "'\n";
		//предикат 'a' дублирует параметр с именем 'b'
		//the predicate 'a' duplicates a parameter named 'b'
		return 1;
	}
	if(S2->name==S1->name){
      ferror_message+=
        "Warning[70-2] in line "+ S2->line +": the predicate '"
        +S1->name+
        "'has the same name \n"
        "\t\t\tas its parameter!\n";
//procedure 'f' has the same name as its parameter
    }
	S1->types = S1->types | (1<<S1->count);
	++S1->count;
	params.insert(S2->name);
	return 0;
}


int tSM::p71(){ //   PDPAR -> PDPAR $id
	if (params.count(S2->name)) {
		ferror_message = "Error[71-1] in line " + S1->line + ": the predicate '" + S1->name +
		"' duplicates a parameter '" + S2->name + "'\n";
		//переменная 'a' дублирует параметр с именем 'b'
		//the variable 'a' duplicates a parameter named 'b'
		return 1;
	}
	if(S2->name==S1->name){
      ferror_message+=
        "Warning[71-2] in line "+ S2->line +": the predicate '"
        +S1->name+
        "'has the same name \n"
        "\t\t\tas its parameter!\n";
//procedure 'f' has the same name as its parameter
    }
	++S1->count;
	params.insert(S2->name);
	return 0;
}


int tSM::p72(){ //     VAR -> VARDCL E )
	return 0;}


int tSM::p73(){ //  VARDCL -> ( define $id
	if (globals[S3->name].empty()) {
		globals[S3->name] = tgName(VAR | DEFINED);
		return 0;
	}
	if (globals[S3->name].test(DEFINED)) { ferror_message = "Error[73-1] in line " + 
		S1->line + ":redefining the '" + S3->name + "' var\n";
		//переопределение переменной 'a'
		//redefining the 'a' variable
		return 1;
	}
	if (globals[S3->name].test(PROC) && globals[S3->name].test(USED)) {
		ferror_message = "Error[73-2] in line " + S1->line + ": variable '" + S3->name +
		"' has already been used, redefinition is not possible\n";
		//переменная 'a' уже использовалась, переопределение невозможно
		//variable 'a' has already been used, redefinition is not possible
		return 1;
	}
	globals[S3->name].set(DEFINED);
	return 0;
}


int tSM::p74(){ //    PROC -> HPROC BLOCK )
	if (globals[S1->name].empty()) { 
		params.clear();
		scope = 0;
		globals[S1->name] = tgName(PROC | DEFINED, S1->line, S1->count);
		return 0; 
	}
	if (globals[S1->name].test(DEFINED)) { 
		ferror_message = "Error[74-1] in line " + S1->line + 
		": procedure '" + S1->name + "' has been defined\n";
		//процедура 'a' была определена
		//procedure 'a' has been defined
		return 1;
	}
	if (globals[S1->name].arity != S1->count) {
		ferror_message = "Error[74-2] in line " + S1->line + ": the procedure '" + S1->name +
		"' has already been called with " + std::to_string(globals[S1->name].arity) + " parameters, but given "
		+ std::to_string(S1->count) + "\n";
		//процедура 'a' была определена с 5 параметрами, но дано 4
		//procedure 'a' was defined with 5 parameters, but given 4
		return 1;
	}
	params.clear();
	scope = 0;
	globals[S1->name].set(DEFINED);
	return 0;
}

int tSM::p75(){ //    PROC -> HPROC E )
	if (globals[S1->name].empty()) { 
		params.clear();
		scope = 0;
		globals[S1->name] = tgName(PROC | DEFINED, S1->line, S1->count);
		return 0;
	}
	if (globals[S1->name].test(DEFINED)) {
		ferror_message = "Error[75-1] in line " + S1->line + ": the procedure '"
		+ S1->name + "' was defined\n";
		//процедура 'a' была определена
		//procedure 'a' has been defined
		return 1;
	}
	if (globals[S1->name].arity != S1->count) {
		ferror_message = "Error[75-2] in line " + S1->line + ": the procedure '" + S1->name +
		"' has already been called with " +
		std::to_string(globals[S1->name].arity) + " parameters, but given "
		+ std::to_string(S1->count) + "\n";
		//процедура 'a' была определена с 5 параметрами, но дано 4
		//procedure 'a' was defined with 5 parameters, but given 4
		return 1;
	}
	params.clear();
	scope = 0;
	globals[S1->name].set(DEFINED);
	return 0;
}


int tSM::p76(){ //   HPROC -> PCPAR )
	scope = 1;
	return 0;
}


int tSM::p77(){ //   HPROC -> HPROC INTER
	return 0;}

int tSM::p78(){ //   PCPAR -> ( define ( $id
	S1->name = S4->name;
	S1->count = 0;
	return 0;
}

int tSM::p79(){ //   PCPAR -> PCPAR $id
	if (params.count(S2->name)) {
		ferror_message ="Error[79-1] in line " + S1->line + ": the procedure '" + S1->name +
		"' duplicates the parameter '" + S2->name + "'\n";
		//в 'a' дублируется  параметр с именем 'b'
		//the parameter id 'b' is duplicated in 'a'
		return 1;
	}
	if(S2->name==S1->name){
      ferror_message+=
        "Warning[79-2] in line "+ S2->line +": procedure '"
        +S1->name+
        "'has the same name \n"
        "\t\t\tas its parameter!\n";
//procedure 'f' has the same name as its parameter
    }
	++S1->count;
	params.insert(S2->name);
	return 0;
}


int tSM::p80(){ //   BLOCK -> HBLOCK E )
	locals.clear();
	return 0;
}
int tSM::p81(){ //  HBLOCK -> BLVAR )
	scope = 2;
	return 0;
}
int tSM::p82(){ //  HBLOCK -> HBLOCK INTER
	return 0;}


int tSM::p83(){ //   BLVAR -> ( let ( LOCDEF

	S1->name = S4->name;
	S1->count = 1;
	locals.insert(S1->name);
	return 0;
}


int tSM::p84(){ //   BLVAR -> BLVAR LOCDEF
	//cout << S2->name << "\n";
	/* if(globals.count(S2->name)){
		if(globals[S2->name].test(PROC)) {
			ferror_message = "Error[84-1] in line " + S1->line + ": expression-id can't be procedure";
		}
	} */
	if (locals.count(S2->name)) {
		ferror_message = "Error[84-1] in line " + S1->line + ": variable '" + S1->name +
		"' duplicates '" + S2->name + "'\n";
		//переменная 'a' дублирует 'b'
		//variable 'a' duplicates 'b'
		return 1;
	}
	++S1->count;
	locals.insert(S2->name);
	return 0;
}
int tSM::p85(){ //  LOCDEF -> ( $id E )
	//cout << "something  "<< S1->name<< S2->name<< S3->name<< S4->name << "\n";
	if(globals.count(S3->name)){
		if(globals[S3->name].test(PROC)) {
			ferror_message = "Error[85-1] in line " + S3->line + ": expression-id can't be procedure\n";
			return 1;
		}
	}
	S1->name = S2->name;
	return 0;
}
//_____________________
int tSM::p86(){return 0;} int tSM::p87(){return 0;} 
int tSM::p88(){return 0;} int tSM::p89(){return 0;} 
int tSM::p90(){return 0;} int tSM::p91(){return 0;} 
int tSM::p92(){return 0;} int tSM::p93(){return 0;} 
int tSM::p94(){return 0;} int tSM::p95(){return 0;} 
int tSM::p96(){return 0;} int tSM::p97(){return 0;} 
int tSM::p98(){return 0;} int tSM::p99(){return 0;} 
int tSM::p100(){return 0;} int tSM::p101(){return 0;} 
int tSM::p102(){return 0;} int tSM::p103(){return 0;} 
int tSM::p104(){return 0;} int tSM::p105(){return 0;} 
int tSM::p106(){return 0;} int tSM::p107(){return 0;} 
int tSM::p108(){return 0;} int tSM::p109(){return 0;} 
int tSM::p110(){return 0;}