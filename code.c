

char std[] = "\n"
"max: dup2 if > : x x . x swp x .  \n"
"dup2: [2] [2] . \n"
"true: 1 . \n"
"false: 0 . \n"
"e: 2.71822 . \n"
"pi: 3.14159 . \n"
"not: 0 == .  \n"
"!: not . \n"
"if: . \n"
"bool: ! ! . \n"
"and: * bool . \n"
"!=: == ! return \n"
"<: swp > return \n"
"-: -1 * + return \n"
"or: ! swp ! and ! return\n"
//"==: [2] [2] > [3] [3] < or ! swp x swp x return \n"
"fact: if [1] 0 == : x 1 .                  \n"
"                    [1] 1 - fact * .       \n"
//"do: 1 + [1] 10 > then . x do . \n"
;

char *add_src(char *new, char *old) {
    old = realloc(old, sizeof(old) + sizeof(new) - 1);
    strcpy(old, new);
    return new;
}

char *add_src_from_file(FILE *f, char *source) {
    //char new[file-len(f)];                          
    //strcpy(new[], 
    //r = add_src(new, source);

}



char *find_def(char *word, const char *source) {
    char def[sizeof(word) + 2];
    sprintf(def, "\n%s:", word);
                   
    char *r = strstr(source, def);
    if(r == NULL) return NULL;
    else return r + strlen(def);
}       


