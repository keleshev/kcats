#include <stdio.h>
#include <alloca.h>
#define log(v) printf("\n[%s:%d] " #v " == " "%s \n", __func__, __LINE__, v)

typedef char* str;
str _uniq;
#define concat(a,b) (_uniq = alloca(sizeof(a)+sizeof(b)+1), strcat(_uniq,a), strcat(_uniq,b), _uniq)

int main() {
    str a = "hello, ";
    str b = "world!";
    
    str s = concat(a,b);
    //str s = (_uniq = alloca(sizeof(a)+sizeof(b)+1), strcat(_uniq,a), strcat(_uniq,b), _uniq);
    
    log(s);log(_uniq); 

}

/*

typedef char* str;


str str(str s) {} 

int str_len(str s) {} 

str str_new( len) {}

void str_del(str s) {} 

str str_sub(str s, int begin, int end) {}

str str_con(str s1, str s2, ...) {}


str s = str_con

str s = str("ha-ha");
str c = str(s);
str w = str_sub(s, 1, -3);
str e = str_con(s, c);
bool n = str_eq(s, e);
int pos = str_srch(":", s);
pos = str_srch_back(":", s);
str spc = str_trunc("  bla  \n", " \n\t");
str str_whsp = str(" \n\r\t");
str m = str_match(s, "*.rkt");

s = str_app(s, "other");

del(s,c,w,e,spc,str_whsp,m);
 */



