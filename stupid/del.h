 /*
  * del.h -- easy deleting/deallocating/freeing of memory.
  *
  * del(...) -- free and set to NULL all arguments.
  * null(...) -- set to NULL all arguments.
  */

#ifndef DEL_H
#define DEL_H

#include <stdarg.h>
#include "arg.h"  // arg_count() 

 /*
  * del(...) 
  *
  * Will free() and null() all its arguments.
  * (works with 1 to 16 arguments)
  *
  * E.g. del(a,b,c) will have the same effect as:
  *     free(a); free(b); free(c);
  *     a = b = c = NULL;
  */
#define del(...) \
    do { _del(arg_count(__VA_ARGS__), __VA_ARGS__); \
         null(__VA_ARGS__); } while(0)

 /*
  * null(...) 
  *
  * Will assign NULL to all its arguments.
  * (works with 1 to 16 arguments)
  *
  * E.g. null(a,b,c) will have the same effect as:
  *     a = b = c = NULL;
  */
#define null(...) _null_n(arg_count(__VA_ARGS__), __VA_ARGS__)

 /*
  * Crap that was necessary to implement the above macros.
  */

#define _tokenpaste2(x, y) x ## y
#define _tokenpaste(x, y) _tokenpaste2(x, y)

#define _null_n(n, ...) _tokenpaste(_null_,n)(__VA_ARGS__)

#define _null_1(_1) do { _1 = NULL; } while(0)
#define _null_2(_1,_2) do { _1=_2=NULL; } while(0)
#define _null_3(_1,_2,_3) do { _1=_2=_3=NULL; } while(0)
#define _null_4(_1,_2,_3,_4) do { _1=_2=_3=_4=NULL; } while(0)
#define _null_5(_1,_2,_3,_4,_5) do { _1=_2=_3=_4=_5=NULL; } while(0)
#define _null_6(_1,_2,_3,_4,_5,_6) do { _1=_2=_3=_4=_5=_6=NULL; } while(0)
#define _null_7(_1,_2,_3,_4,_5,_6,_7) do { _1=_2=_3=_4=_5=_6=_7=NULL; } while(0)
#define _null_8(_1,_2,_3,_4,_5,_6,_7,_8) do { _1=_2=_3=_4=_5=_6=_7=_8=NULL; } while(0)
#define _null_9(_1,_2,_3,_4,_5,_6,_7,_8,_9) do { _1=_2=_3=_4=_5=_6=_7=_8=_9=NULL; } while(0)
#define _null_10(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10) \
            do { _1=_2=_3=_4=_5=_6=_7=_8=_9=_10=NULL; } while(0)
#define _null_11(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11) \
            do { _1=_2=_3=_4=_5=_6=_7=_8=_9=_10=_11=NULL; } while(0)
#define _null_12(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12) \
            do { _1=_2=_3=_4=_5=_6=_7=_8=_9=_10=_11,_12=NULL; } while(0)
#define _null_13(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13) \
            do { _1=_2=_3=_4=_5=_6=_7=_8=_9=_10=_11=_12=_13=NULL; } while(0)
#define _null_14(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14) \
            do { _1=_2=_3=_4=_5=_6=_7=_8=_9=_10=_11=_12=_13=_14=NULL; } while(0)
#define _null_15(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15) \
            do { _1=_2=_3=_4=_5=_6=_7=_8=_9=_10=_11=_12=_13=_14=_15=NULL; } while(0)
#define _null_16(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16) \
            do { _1=_2=_3=_4=_5=_6=_7=_8=_9=_10=_11=_12=_13=_14=_15=_16=NULL; } while(0)
  
void _del(int nargs, ...) {
    va_list vl;
    va_start(vl, nargs); 
    for (unsigned i = 1; i <= nargs; i++)
        free(va_arg(vl, void*));
    va_end(vl);
}


#endif // guard
