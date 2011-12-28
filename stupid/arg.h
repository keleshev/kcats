 /*
  * arg.h -- macros to count and access arguments.
  *
  * arg_count(...) -- count number of passed arguments.
  * arg_get(n, ...) -- get the nth passed argument.
  */

#ifndef ARG_H
#define ARG_H

 /* 
  * arg_count(...) 
  *
  * Returns number of arguments passed to it. 
  * Especially usefull as arg_count(__VA_ARGS__).
  *
  * Works with 1 to 63 arguments.
  *
  * Examples:
  *     arg_count(a) -> 1
  *     arg_count(a, b, c) -> 3
  *     arg_count() -> Error, should be 1 to 63 arguments.
  *
  * Idea by Laurent Deniau, pretty version by Roland Illig:      
  * http://groups.google.com/group/comp.std.c/browse_thread/thread/77ee8c8f92e4a3fb
  */ 
#define arg_count(...) _narg_(__VA_ARGS__, _rseq_n()) 

#define _narg_(...) _arg_n(__VA_ARGS__) 
#define _arg_n( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N 
#define _rseq_n() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0 

 /*
  * arg_get(n, ...)
  *
  * Gets nth arguments passed. 
  * Especially usefull to acess specific argument of __VA_ARGS__.
  *
  * Can retreive from 1st to 16th arguemnt.
  *
  * Examples:
  *     arg_get(1, a, b) -> a
  *     arg_get(3, a, b, c) -> c
  *     arg_get(4, a, b, c) -> error
  *
  * Could be used as lvalue:
  *     arg_get(2, a, b) = NULL;  // b = NULL;
  */ 
#define arg_get(n, ...) _arg_get_##n(__VA_ARGS__,) 
// Last comma: ISO C99 requires rest arguments to be used,
// however, empty argument is sufficient.

#define _arg_get_1(_1, ...) _1
#define _arg_get_2(_1,_2, ...) _2
#define _arg_get_3(_1,_2,_3, ...) _3
#define _arg_get_4(_1,_2,_3,_4, ...) _4
#define _arg_get_5(_1,_2,_3,_4,_5, ...) _5
#define _arg_get_6(_1,_2,_3,_4,_5,_6, ...) _6
#define _arg_get_7(_1,_2,_3,_4,_5,_6,_7, ...) _7
#define _arg_get_8(_1,_2,_3,_4,_5,_6,_7,_8, ...) _8
#define _arg_get_9(_1,_2,_3,_4,_5,_6,_7,_8,_9, ...) _9
#define _arg_get_10(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10, ...) _10
#define _arg_get_11(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11, ...) _11
#define _arg_get_12(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12, ...) _12
#define _arg_get_13(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13, ...) _13
#define _arg_get_14(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14, ...) _14
#define _arg_get_15(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15, ...) _15
#define _arg_get_16(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16, ...) _16


#endif // guard
