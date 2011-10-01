


char *context_new(void) {
    char *c = malloc(strlen("# Context \n"));
    return strcat(c, "# Context \n");
}

// context_add
char *context_add(char *context, char *string) {          //log(context);
    context = realloc(context, strlen(context) + strlen(string) + 1);
    return strcat(context, string);
    //return strcpy(old, new);
    //strcpy(new, old);
    //return new;
}

// context_add_file
char *context_add_file(char *context, char *filename) {
    FILE* f = fopen(filename, "r");
    if(f == NULL) printf("\nCan't open %s!\n", filename);
    
    // quick & dirty filesize calculation
    fseek(f, 0, SEEK_END);
    size_t filesize = ftell(f);      
    fseek(f, 0, SEEK_SET);

    char buffer[filesize + 1];
    //char* buffer = malloc(filesize);

    fread(buffer, 1, filesize, f);
    
    buffer[filesize-1] = '\0';
//    printf("filesize == %d\n", filesize);


    context = context_add(context, buffer);
    //free(buffer);
    if(fclose(f) != 0) printf("\nCan't close %s!\n", filename);
    return context;
}


// context_find_def
char *context_find_def(char *context, char *word) {
    char def[sizeof(word) + 2];
    sprintf(def, "\n%s:", word);
                   
    char *r = strstr(context, def);
    if(r == NULL) return NULL;
    else return r + strlen(def);
}       


void context_del(char *context) {
    free(context);
    context = NULL;
}


