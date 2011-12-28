 /*
  * any.h -- usefull polymorphic macros.
  *          GCC-specific.
  *
  * any_print(value) -- try to print value according to its type.
  * any_output(stream, value) -- same for different streams.
  *
  * _type_eq(t1, t2) -- compare types at compile-time.
  * _type_eq_str(t) -- check if type is string-compatible.
  */

#ifndef ANY_H
#define ANY_H

                              
#define any_print(value) any_output(stdout, value)

#define any_output(stream, value)                               \
    do {                                                        \
        char* _f;                                               \
        if(_type_eq(value, char*))        _f = "\"%s\"";         \
        else if(_type_eq(value, char[]))  _f = "\"%s\"";         \
        else if(_type_eq(value, char) )   _f = "'%c'";           \
        else if(_type_eq(value, int))     _f = "%i";             \
        else if(_type_eq(value, double))  _f = "%g";             \
        else if(_type_eq(value, float))   _f = "%g";             \
        else _f = "%p";                                         \
        fprintf(stream, _f, value);                             \
    } while (0)

#define _type_eq(t1, t2) __builtin_types_compatible_p(__typeof__(t1), __typeof__(t2))

#define _type_eq_str(t) (_type_eq(t, char*) || _type_eq(t, char[]))

#endif // guard
