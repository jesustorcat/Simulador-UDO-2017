/** Analizador sintáctico **/
#include "analizador_sintactico.h"

compilador_sintactico::compilador_sintactico(){}

compilador_sintactico::~compilador_sintactico(){}

//Generación de código objeto para el núcleo 1.
int compilador_sintactico::analisis_sintactico_n1(){
    char a[][20] = {"n1.nop", "n1.mov", "n1.sal", "n1.cda",
                    "n1.sum", "n1.res", "n1.mul", "n1.div",
                    "n1.inc", "n1.dec", "n1.pot", "n1.raiz",
                    "n1.traa", "n1.trab", "n1.set", "n1.reset",
                    "n1.and", "n1.or", "n1.xor", "n1.comp",
                    "n1.desi", "n1.desd", "n1.suma", "n1.resta",
                    "n1.salt", "n1.alto"};

    //Se inicializan las variables en cero "0"
    f1 = 0; lc = 0; i = 0; j = 0;

    FILE *archivo_sl;

    //Se abre el archivo intermedio generado en el analisis léxico
    ifstream archivo_intermedio("archivo_intermedio.dat");

    //Se abre el archivo de simbolos generado en el analisis léxico
    archivo_sl = fopen("archivo_simbolos.dat", "r");

    //Se crea el archivo de sálida donde se generará el código objeto
    ofstream codigo_objeto("codigo_objeto_n1.dat");

    archivo_intermedio.getline(tmp, max_inst);

    //Se dividen las palabras de la línea
    buff2 = strtok(tmp, " .\t");

    while (buff2 != NULL) {
        if (strcmp(buff2, "INICIO") == 0){
            buff2 = strtok(NULL, " .\t");
            lc = atoi(buff2);
            codigo_objeto << lc << "\n";
        }
        buff2 = strtok(NULL, " .\t");
    }

    while (!feof(archivo_sl)) {
        fscanf(archivo_sl, "%s\t%s", etiqueta, direccion);
        longitud = strlen(etiqueta);

        if (etiqueta[longitud - 1] == ':'){
            etiqueta[longitud - 1] = '\0';
        }
        strcpy(simbolo[i], etiqueta);
        strcpy(simb_dir[i], direccion);
        i++;
    }

    n = i;

    //Analiza el archivo intermedio
    while (!archivo_intermedio.eof()) {
        for (i = 0; i < 20; i++){
            op[i] = 0;
            operando[i] = 0;
        }

        archivo_intermedio.getline(tmp, max_inst);
        buff2 = strtok(tmp, "$");

        while (buff2 != NULL) {
            buff1 = strncmp(buff2, ":", 1);
            buff = strncmp(buff2, "0x", 2);

            for (i = 0; i < 40; i++){
                if (strcmp(buff2, a[i]) == 0){
                    f1 = 0;
                    strcpy(op, a[i]);
                    break;
                }
                f1 = 1;
            }

            if ((buff1 != 0) && (buff != 0) && (f1 != 0)){
                strcpy(operando, buff2);
            }
            buff2 = strtok(NULL, "$");
        }

        if (strcmp(op, "n1.nop") == 0)
            codigo_objeto << "0x0" << endl;

        else if ((strcmp(op, "n1.mov") == 0) && (strcmp(operando, "s,e") == 0))
            codigo_objeto << "0x1" << endl;

        else if ((strcmp(op, "n1.mov") == 0) && (strcmp(operando, "a,e") == 0))
            codigo_objeto << "0x2" << endl;

        else if ((strcmp(op, "n1.mov") == 0) && (strcmp(operando, "b,e") == 0))
            codigo_objeto << "0x3" << endl;

        else if ((strcmp(op, "n1.mov") == 0) && (strcmp(operando, "a,f") == 0))
            codigo_objeto << "0x4" << endl;

        else if ((strcmp(op, "n1.mov") == 0) && (strcmp(operando, "b,f") == 0))
            codigo_objeto << "0x5" << endl;

        else if ((strcmp(op, "n1.mov") == 0) && (strcmp(operando, "f,a") == 0))
            codigo_objeto << "0x6" << endl;

        else if ((strcmp(op, "n1.mov") == 0) && (strcmp(operando, "f,b") == 0))
            codigo_objeto << "0x7" << endl;

        else if (strcmp(op, "n1.sal") == 0)
            codigo_objeto << "0x8" << endl;

        else if ((strcmp(op, "n1.cda") == 0) && (strncmp(operando, "a,",2)) == 0){
            codigo_objeto << "0x9" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                if (j == 1)
                    codigo_objeto << "0x" << pop << endl;
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }

        else if ((strcmp(op, "n1.cda") == 0) && (strncmp(operando, "b,",2)) == 0){
            codigo_objeto << "0xa" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                if (j == 1)
                    codigo_objeto << "0x" << pop << endl;
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }

        else if ((strcmp(op, "n1.cda") == 0) && (strncmp(operando, "s,",2)) == 0){
            codigo_objeto << "0xb" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                if (j == 1)
                    codigo_objeto << "0x" << pop << endl;
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }
        else if (strcmp(op, "n1.sum") == 0)
            codigo_objeto << "0xc" << endl;

        else if (strcmp(op, "n1.res") == 0)
            codigo_objeto << "0xd" << endl;

        else if (strcmp(op, "n1.mul") == 0)
            codigo_objeto << "0xe" << endl;

        else if (strcmp(op, "n1.div") == 0)
            codigo_objeto << "0xf" << endl;

        else if (strcmp(op, "n1.inc") == 0)
            codigo_objeto << "0x10" << endl;

        else if (strcmp(op, "n1.dec") == 0)
            codigo_objeto << "0x11" << endl;

        else if (strcmp(op, "n1.pot") == 0)
            codigo_objeto << "0x12" << endl;

        else if (strcmp(op, "n1.raiz") == 0)
            codigo_objeto << "0x13" << endl;

        else if (strcmp(op, "n1.traa") == 0)
            codigo_objeto << "0x14" << endl;

        else if (strcmp(op, "n1.trab") == 0)
            codigo_objeto << "0x15" << endl;

        else if (strcmp(op, "n1.set") == 0)
            codigo_objeto << "0x16" << endl;

        else if (strcmp(op, "n1.reset") == 0)
            codigo_objeto << "0x17" << endl;

        else if (strcmp(op, "n1.and") == 0)
            codigo_objeto << "0x18" << endl;

        else if (strcmp(op, "n1.or") == 0)
            codigo_objeto << "0x19" << endl;

        else if (strcmp(op, "n1.xor") == 0)
            codigo_objeto << "0x1a" << endl;

        else if (strcmp(op, "n1.comp") == 0)
            codigo_objeto << "0x1b" << endl;

        else if (strcmp(op, "n1.desi") == 0)
            codigo_objeto << "0x1c" << endl;

        else if (strcmp(op, "n1.desd") == 0)
            codigo_objeto << "0x1d" << endl;

        else if (strcmp(op, "n1.suma") == 0){
            codigo_objeto << "0x1e" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                switch (j) {
                case 0: codigo_objeto << "0x" << pop << endl; break;
                case 1: codigo_objeto << "0x" << pop << endl; break;
                default: continue; break;
                }
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }

        else if (strcmp(op, "n1.resta") == 0){
            codigo_objeto << "0x1f" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                switch (j) {
                case 0: codigo_objeto << "0x" << pop << endl; break;
                case 1: codigo_objeto << "0x" << pop << endl; break;
                default: continue; break;
                }
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }

        else if (strcmp(op, "n1.salt") == 0){
            codigo_objeto << "0x20" << endl;
            for (i = 0; i <= n; i++){
                if (strcmp(operando, simbolo[i]) == 0){
                    codigo_objeto << simb_dir[i] << endl;
                    break;
                }
            }
        }

        else if (strcmp(op, "n1.alto") == 0)
            codigo_objeto << "0x21" << endl;

    }


    fclose(archivo_sl);
    archivo_intermedio.close();
    codigo_objeto.close();
    return 0;
}

//Generación de codigo objeto para el núcleo 2.
int compilador_sintactico::analisis_sintactico_n2(){
    char a[][20] = {"n2.nop", "n2.mov", "n2.sal", "n2.cda",
                    "n2.sum", "n2.res", "n2.mul", "n2.div",
                    "n2.inc", "n2.dec", "n2.pot", "n2.raiz",
                    "n2.traa", "n2.trab", "n2.set", "n2.reset",
                    "n2.and", "n2.or", "n2.xor", "n2.comp",
                    "n2.desi", "n2.desd", "n2.suma", "n2.resta",
                    "n2.salt", "n2.alto"};

    //Se inicializan las variables en cero "0"
    f1 = 0; lc = 0; i = 0; j = 0;

    FILE *archivo_sl;

    //Se abre el archivo intermedio generado en el analisis léxico
    ifstream archivo_intermedio("archivo_intermedio.dat");

    //Se abre el archivo de simbolos generado en el analisis léxico
    archivo_sl = fopen("archivo_simbolos.dat", "r");

    //Se crea el archivo de sálida donde se generará el código objeto
    ofstream codigo_objeto("codigo_objeto_n2.dat");

    archivo_intermedio.getline(tmp, max_inst);

    //Se dividen las palabras de la línea
    buff2 = strtok(tmp, " .\t");

    while (buff2 != NULL) {
        if (strcmp(buff2, "INICIO") == 0){
            buff2 = strtok(NULL, " .\t");
            lc = atoi(buff2);
            codigo_objeto << lc << "\n";
        }
        buff2 = strtok(NULL, " .\t");
    }

    while (!feof(archivo_sl)) {
        fscanf(archivo_sl, "%s\t%s", etiqueta, direccion);
        longitud = strlen(etiqueta);

        if (etiqueta[longitud - 1] == ':'){
            etiqueta[longitud - 1] = '\0';
        }
        strcpy(simbolo[i], etiqueta);
        strcpy(simb_dir[i], direccion);
        i++;
    }

    n = i;

    //Analiza el archivo intermedio
    while (!archivo_intermedio.eof()) {
        for (i = 0; i < 20; i++){
            op[i] = 0;
            operando[i] = 0;
        }

        archivo_intermedio.getline(tmp, max_inst);
        buff2 = strtok(tmp, "$");

        while (buff2 != NULL) {
            buff1 = strncmp(buff2, ":", 1);
            buff = strncmp(buff2, "0x", 2);

            for (i = 0; i < 40; i++){
                if (strcmp(buff2, a[i]) == 0){
                    f1 = 0;
                    strcpy(op, a[i]);
                    break;
                }
                f1 = 1;
            }

            if ((buff1 != 0) && (buff != 0) && (f1 != 0)){
                strcpy(operando, buff2);
            }
            buff2 = strtok(NULL, "$");
        }

        if (strcmp(op, "n2.nop") == 0)
            codigo_objeto << "0x0" << endl;

        else if ((strcmp(op, "n2.mov") == 0) && (strcmp(operando, "s,e") == 0))
            codigo_objeto << "0x1" << endl;

        else if ((strcmp(op, "n2.mov") == 0) && (strcmp(operando, "a,e") == 0))
            codigo_objeto << "0x2" << endl;

        else if ((strcmp(op, "n2.mov") == 0) && (strcmp(operando, "b,e") == 0))
            codigo_objeto << "0x3" << endl;

        else if ((strcmp(op, "n2.mov") == 0) && (strcmp(operando, "a,f") == 0))
            codigo_objeto << "0x4" << endl;

        else if ((strcmp(op, "n2.mov") == 0) && (strcmp(operando, "b,f") == 0))
            codigo_objeto << "0x5" << endl;

        else if ((strcmp(op, "n2.mov") == 0) && (strcmp(operando, "f,a") == 0))
            codigo_objeto << "0x6" << endl;

        else if ((strcmp(op, "n2.mov") == 0) && (strcmp(operando, "f,b") == 0))
            codigo_objeto << "0x7" << endl;

        else if (strcmp(op, "n2.sal") == 0)
            codigo_objeto << "0x8" << endl;

        else if ((strcmp(op, "n2.cda") == 0) && (strncmp(operando, "a,",2)) == 0){
            codigo_objeto << "0x9" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                if (j == 1)
                    codigo_objeto << "0x" << pop << endl;
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }

        else if ((strcmp(op, "n2.cda") == 0) && (strncmp(operando, "b,",2)) == 0){
            codigo_objeto << "0xa" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                if (j == 1)
                    codigo_objeto << "0x" << pop << endl;
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }

        else if ((strcmp(op, "n2.cda") == 0) && (strncmp(operando, "s,",2)) == 0){
            codigo_objeto << "0xb" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                if (j == 1)
                    codigo_objeto << "0x" << pop << endl;
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }
        else if (strcmp(op, "n2.sum") == 0)
            codigo_objeto << "0xc" << endl;

        else if (strcmp(op, "n2.res") == 0)
            codigo_objeto << "0xd" << endl;

        else if (strcmp(op, "n2.mul") == 0)
            codigo_objeto << "0xe" << endl;

        else if (strcmp(op, "n2.div") == 0)
            codigo_objeto << "0xf" << endl;

        else if (strcmp(op, "n2.inc") == 0)
            codigo_objeto << "0x10" << endl;

        else if (strcmp(op, "n2.dec") == 0)
            codigo_objeto << "0x11" << endl;

        else if (strcmp(op, "n2.pot") == 0)
            codigo_objeto << "0x12" << endl;

        else if (strcmp(op, "n2.raiz") == 0)
            codigo_objeto << "0x13" << endl;

        else if (strcmp(op, "n2.traa") == 0)
            codigo_objeto << "0x14" << endl;

        else if (strcmp(op, "n2.trab") == 0)
            codigo_objeto << "0x15" << endl;

        else if (strcmp(op, "n2.set") == 0)
            codigo_objeto << "0x16" << endl;

        else if (strcmp(op, "n2.reset") == 0)
            codigo_objeto << "0x17" << endl;

        else if (strcmp(op, "n2.and") == 0)
            codigo_objeto << "0x18" << endl;

        else if (strcmp(op, "n2.or") == 0)
            codigo_objeto << "0x19" << endl;

        else if (strcmp(op, "n2.xor") == 0)
            codigo_objeto << "0x1a" << endl;

        else if (strcmp(op, "n2.comp") == 0)
            codigo_objeto << "0x1b" << endl;

        else if (strcmp(op, "n2.desi") == 0)
            codigo_objeto << "0x1c" << endl;

        else if (strcmp(op, "n2.desd") == 0)
            codigo_objeto << "0x1d" << endl;

        else if (strcmp(op, "n2.suma") == 0){
            codigo_objeto << "0x1e" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                switch (j) {
                case 0: codigo_objeto << "0x" << pop << endl; break;
                case 1: codigo_objeto << "0x" << pop << endl; break;
                default: continue; break;
                }
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }

        else if (strcmp(op, "n2.resta") == 0){
            codigo_objeto << "0x1f" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                switch (j) {
                case 0: codigo_objeto << "0x" << pop << endl; break;
                case 1: codigo_objeto << "0x" << pop << endl; break;
                default: continue; break;
                }
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }

        else if (strcmp(op, "n2.salt") == 0){
            codigo_objeto << "0x20" << endl;
            for (i = 0; i <= n; i++){
                if (strcmp(operando, simbolo[i]) == 0){
                    codigo_objeto << simb_dir[i] << endl;
                    break;
                }
            }
        }

        else if (strcmp(op, "n2.alto") == 0)
            codigo_objeto << "0x21" << endl;

    }


    fclose(archivo_sl);
    archivo_intermedio.close();
    codigo_objeto.close();
    return 0;
}

//Generación de código objeto para el núcleo 3.
int compilador_sintactico::analisis_sintactico_n3(){
    char a[][20] = {"n3.nop", "n3.mov", "n3.sal", "n3.cda",
                    "n3.sum", "n3.res", "n3.mul", "n3.div",
                    "n3.inc", "n3.dec", "n3.pot", "n3.raiz",
                    "n3.traa", "n3.trab", "n3.set", "n3.reset",
                    "n3.and", "n3.or", "n3.xor", "n3.comp",
                    "n3.desi", "n3.desd", "n3.suma", "n3.resta",
                    "n3.salt", "n3.alto"};

    //Se inicializan las variables en cero "0"
    f1 = 0; lc = 0; i = 0; j = 0;

    FILE *archivo_sl;

    //Se abre el archivo intermedio generado en el analisis léxico
    ifstream archivo_intermedio("archivo_intermedio.dat");

    //Se abre el archivo de simbolos generado en el analisis léxico
    archivo_sl = fopen("archivo_simbolos.dat", "r");

    //Se crea el archivo de sálida donde se generará el código objeto
    ofstream codigo_objeto("codigo_objeto_n3.dat");

    archivo_intermedio.getline(tmp, max_inst);

    //Se dividen las palabras de la línea
    buff2 = strtok(tmp, " .\t");

    while (buff2 != NULL) {
        if (strcmp(buff2, "INICIO") == 0){
            buff2 = strtok(NULL, " .\t");
            lc = atoi(buff2);
            codigo_objeto << lc << "\n";
        }
        buff2 = strtok(NULL, " .\t");
    }

    while (!feof(archivo_sl)) {
        fscanf(archivo_sl, "%s\t%s", etiqueta, direccion);
        longitud = strlen(etiqueta);

        if (etiqueta[longitud - 1] == ':'){
            etiqueta[longitud - 1] = '\0';
        }
        strcpy(simbolo[i], etiqueta);
        strcpy(simb_dir[i], direccion);
        i++;
    }

    n = i;

    //Analiza el archivo intermedio
    while (!archivo_intermedio.eof()) {
        for (i = 0; i < 20; i++){
            op[i] = 0;
            operando[i] = 0;
        }

        archivo_intermedio.getline(tmp, max_inst);
        buff2 = strtok(tmp, "$");

        while (buff2 != NULL) {
            buff1 = strncmp(buff2, ":", 1);
            buff = strncmp(buff2, "0x", 2);

            for (i = 0; i < 40; i++){
                if (strcmp(buff2, a[i]) == 0){
                    f1 = 0;
                    strcpy(op, a[i]);
                    break;
                }
                f1 = 1;
            }

            if ((buff1 != 0) && (buff != 0) && (f1 != 0)){
                strcpy(operando, buff2);
            }
            buff2 = strtok(NULL, "$");
        }

        if (strcmp(op, "n3.nop") == 0)
            codigo_objeto << "0x0" << endl;

        else if ((strcmp(op, "n3.mov") == 0) && (strcmp(operando, "s,e") == 0))
            codigo_objeto << "0x1" << endl;

        else if ((strcmp(op, "n3.mov") == 0) && (strcmp(operando, "a,e") == 0))
            codigo_objeto << "0x2" << endl;

        else if ((strcmp(op, "n3.mov") == 0) && (strcmp(operando, "b,e") == 0))
            codigo_objeto << "0x3" << endl;

        else if ((strcmp(op, "n3.mov") == 0) && (strcmp(operando, "a,f") == 0))
            codigo_objeto << "0x4" << endl;

        else if ((strcmp(op, "n3.mov") == 0) && (strcmp(operando, "b,f") == 0))
            codigo_objeto << "0x5" << endl;

        else if ((strcmp(op, "n3.mov") == 0) && (strcmp(operando, "f,a") == 0))
            codigo_objeto << "0x6" << endl;

        else if ((strcmp(op, "n3.mov") == 0) && (strcmp(operando, "f,b") == 0))
            codigo_objeto << "0x7" << endl;

        else if (strcmp(op, "n3.sal") == 0)
            codigo_objeto << "0x8" << endl;

        else if ((strcmp(op, "n3.cda") == 0) && (strncmp(operando, "a,",2)) == 0){
            codigo_objeto << "0x9" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                if (j == 1)
                    codigo_objeto << "0x" << pop << endl;
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }

        else if ((strcmp(op, "n3.cda") == 0) && (strncmp(operando, "b,",2)) == 0){
            codigo_objeto << "0xa" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                if (j == 1)
                    codigo_objeto << "0x" << pop << endl;
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }

        else if ((strcmp(op, "n3.cda") == 0) && (strncmp(operando, "s,",2)) == 0){
            codigo_objeto << "0xb" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                if (j == 1)
                    codigo_objeto << "0x" << pop << endl;
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }
        else if (strcmp(op, "n3.sum") == 0)
            codigo_objeto << "0xc" << endl;

        else if (strcmp(op, "n3.res") == 0)
            codigo_objeto << "0xd" << endl;

        else if (strcmp(op, "n3.mul") == 0)
            codigo_objeto << "0xe" << endl;

        else if (strcmp(op, "n3.div") == 0)
            codigo_objeto << "0xf" << endl;

        else if (strcmp(op, "n3.inc") == 0)
            codigo_objeto << "0x10" << endl;

        else if (strcmp(op, "n3.dec") == 0)
            codigo_objeto << "0x11" << endl;

        else if (strcmp(op, "n3.pot") == 0)
            codigo_objeto << "0x12" << endl;

        else if (strcmp(op, "n3.raiz") == 0)
            codigo_objeto << "0x13" << endl;

        else if (strcmp(op, "n3.traa") == 0)
            codigo_objeto << "0x14" << endl;

        else if (strcmp(op, "n3.trab") == 0)
            codigo_objeto << "0x15" << endl;

        else if (strcmp(op, "n3.set") == 0)
            codigo_objeto << "0x16" << endl;

        else if (strcmp(op, "n3.reset") == 0)
            codigo_objeto << "0x17" << endl;

        else if (strcmp(op, "n3.and") == 0)
            codigo_objeto << "0x18" << endl;

        else if (strcmp(op, "n3.or") == 0)
            codigo_objeto << "0x19" << endl;

        else if (strcmp(op, "n3.xor") == 0)
            codigo_objeto << "0x1a" << endl;

        else if (strcmp(op, "n3.comp") == 0)
            codigo_objeto << "0x1b" << endl;

        else if (strcmp(op, "n3.desi") == 0)
            codigo_objeto << "0x1c" << endl;

        else if (strcmp(op, "n3.desd") == 0)
            codigo_objeto << "0x1d" << endl;

        else if (strcmp(op, "n3.suma") == 0){
            codigo_objeto << "0x1e" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                switch (j) {
                case 0: codigo_objeto << "0x" << pop << endl; break;
                case 1: codigo_objeto << "0x" << pop << endl; break;
                default: continue; break;
                }
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }

        else if (strcmp(op, "n3.resta") == 0){
            codigo_objeto << "0x1f" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                switch (j) {
                case 0: codigo_objeto << "0x" << pop << endl; break;
                case 1: codigo_objeto << "0x" << pop << endl; break;
                default: continue; break;
                }
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }

        else if (strcmp(op, "n3.salt") == 0){
            codigo_objeto << "0x20" << endl;
            for (i = 0; i <= n; i++){
                if (strcmp(operando, simbolo[i]) == 0){
                    codigo_objeto << simb_dir[i] << endl;
                    break;
                }
            }
        }

        else if (strcmp(op, "n3.alto") == 0)
            codigo_objeto << "0x21" << endl;

    }


    fclose(archivo_sl);
    archivo_intermedio.close();
    codigo_objeto.close();
    return 0;
}

//Generación de código objeto para el núcleo 4.
int compilador_sintactico::analisis_sintactico_n4(){
    char a[][20] = {"n4.nop", "n4.mov", "n4.sal", "n4.cda",
                    "n4.sum", "n4.res", "n4.mul", "n4.div",
                    "n4.inc", "n4.dec", "n4.pot", "n4.raiz",
                    "n4.traa", "n4.trab", "n4.set", "n4.reset",
                    "n4.and", "n4.or", "n4.xor", "n4.comp",
                    "n4.desi", "n4.desd", "n4.suma", "n4.resta",
                    "n4.salt", "n4.alto"};

    //Se inicializan las variables en cero "0"
    f1 = 0; lc = 0; i = 0; j = 0;

    FILE *archivo_sl;

    //Se abre el archivo intermedio generado en el analisis léxico
    ifstream archivo_intermedio("archivo_intermedio.dat");

    //Se abre el archivo de simbolos generado en el analisis léxico
    archivo_sl = fopen("archivo_simbolos.dat", "r");

    //Se crea el archivo de sálida donde se generará el código objeto
    ofstream codigo_objeto("codigo_objeto_n4.dat");

    archivo_intermedio.getline(tmp, max_inst);

    //Se dividen las palabras de la línea
    buff2 = strtok(tmp, " .\t");

    while (buff2 != NULL) {
        if (strcmp(buff2, "INICIO") == 0){
            buff2 = strtok(NULL, " .\t");
            lc = atoi(buff2);
            codigo_objeto << lc << "\n";
        }
        buff2 = strtok(NULL, " .\t");
    }

    while (!feof(archivo_sl)) {
        fscanf(archivo_sl, "%s\t%s", etiqueta, direccion);
        longitud = strlen(etiqueta);

        if (etiqueta[longitud - 1] == ':'){
            etiqueta[longitud - 1] = '\0';
        }
        strcpy(simbolo[i], etiqueta);
        strcpy(simb_dir[i], direccion);
        i++;
    }

    n = i;

    //Analiza el archivo intermedio
    while (!archivo_intermedio.eof()) {
        for (i = 0; i < 20; i++){
            op[i] = 0;
            operando[i] = 0;
        }

        archivo_intermedio.getline(tmp, max_inst);
        buff2 = strtok(tmp, "$");

        while (buff2 != NULL) {
            buff1 = strncmp(buff2, ":", 1);
            buff = strncmp(buff2, "0x", 2);

            for (i = 0; i < 40; i++){
                if (strcmp(buff2, a[i]) == 0){
                    f1 = 0;
                    strcpy(op, a[i]);
                    break;
                }
                f1 = 1;
            }

            if ((buff1 != 0) && (buff != 0) && (f1 != 0)){
                strcpy(operando, buff2);
            }
            buff2 = strtok(NULL, "$");
        }

        if (strcmp(op, "n4.nop") == 0)
            codigo_objeto << "0x0" << endl;

        else if ((strcmp(op, "n4.mov") == 0) && (strcmp(operando, "s,e") == 0))
            codigo_objeto << "0x1" << endl;

        else if ((strcmp(op, "n4.mov") == 0) && (strcmp(operando, "a,e") == 0))
            codigo_objeto << "0x2" << endl;

        else if ((strcmp(op, "n4.mov") == 0) && (strcmp(operando, "b,e") == 0))
            codigo_objeto << "0x3" << endl;

        else if ((strcmp(op, "n4.mov") == 0) && (strcmp(operando, "a,f") == 0))
            codigo_objeto << "0x4" << endl;

        else if ((strcmp(op, "n4.mov") == 0) && (strcmp(operando, "b,f") == 0))
            codigo_objeto << "0x5" << endl;

        else if ((strcmp(op, "n4.mov") == 0) && (strcmp(operando, "f,a") == 0))
            codigo_objeto << "0x6" << endl;

        else if ((strcmp(op, "n4.mov") == 0) && (strcmp(operando, "f,b") == 0))
            codigo_objeto << "0x7" << endl;

        else if (strcmp(op, "n4.sal") == 0)
            codigo_objeto << "0x8" << endl;

        else if ((strcmp(op, "n4.cda") == 0) && (strncmp(operando, "a,",2)) == 0){
            codigo_objeto << "0x9" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                if (j == 1)
                    codigo_objeto << "0x" << pop << endl;
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }

        else if ((strcmp(op, "n4.cda") == 0) && (strncmp(operando, "b,",2)) == 0){
            codigo_objeto << "0xa" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                if (j == 1)
                    codigo_objeto << "0x" << pop << endl;
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }

        else if ((strcmp(op, "n4.cda") == 0) && (strncmp(operando, "s,",2)) == 0){
            codigo_objeto << "0xb" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                if (j == 1)
                    codigo_objeto << "0x" << pop << endl;
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }
        else if (strcmp(op, "n4.sum") == 0)
            codigo_objeto << "0xc" << endl;

        else if (strcmp(op, "n4.res") == 0)
            codigo_objeto << "0xd" << endl;

        else if (strcmp(op, "n4.mul") == 0)
            codigo_objeto << "0xe" << endl;

        else if (strcmp(op, "n4.div") == 0)
            codigo_objeto << "0xf" << endl;

        else if (strcmp(op, "n4.inc") == 0)
            codigo_objeto << "0x10" << endl;

        else if (strcmp(op, "n4.dec") == 0)
            codigo_objeto << "0x11" << endl;

        else if (strcmp(op, "n4.pot") == 0)
            codigo_objeto << "0x12" << endl;

        else if (strcmp(op, "n4.raiz") == 0)
            codigo_objeto << "0x13" << endl;

        else if (strcmp(op, "n4.traa") == 0)
            codigo_objeto << "0x14" << endl;

        else if (strcmp(op, "n4.trab") == 0)
            codigo_objeto << "0x15" << endl;

        else if (strcmp(op, "n4.set") == 0)
            codigo_objeto << "0x16" << endl;

        else if (strcmp(op, "n4.reset") == 0)
            codigo_objeto << "0x17" << endl;

        else if (strcmp(op, "n4.and") == 0)
            codigo_objeto << "0x18" << endl;

        else if (strcmp(op, "n4.or") == 0)
            codigo_objeto << "0x19" << endl;

        else if (strcmp(op, "n4.xor") == 0)
            codigo_objeto << "0x1a" << endl;

        else if (strcmp(op, "n4.comp") == 0)
            codigo_objeto << "0x1b" << endl;

        else if (strcmp(op, "n4.desi") == 0)
            codigo_objeto << "0x1c" << endl;

        else if (strcmp(op, "n4.desd") == 0)
            codigo_objeto << "0x1d" << endl;

        else if (strcmp(op, "n4.suma") == 0){
            codigo_objeto << "0x1e" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                switch (j) {
                case 0: codigo_objeto << "0x" << pop << endl; break;
                case 1: codigo_objeto << "0x" << pop << endl; break;
                default: continue; break;
                }
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }

        else if (strcmp(op, "n4.resta") == 0){
            codigo_objeto << "0x1f" << endl;
            pop = strtok(operando, ",h");
            j = 0;
            while (pop != NULL) {
                switch (j) {
                case 0: codigo_objeto << "0x" << pop << endl; break;
                case 1: codigo_objeto << "0x" << pop << endl; break;
                default: continue; break;
                }
                pop = strtok(NULL, ",h");
                j+=1;
            }
        }

        else if (strcmp(op, "n4.salt") == 0){
            codigo_objeto << "0x20" << endl;
            for (i = 0; i <= n; i++){
                if (strcmp(operando, simbolo[i]) == 0){
                    codigo_objeto << simb_dir[i] << endl;
                    break;
                }
            }
        }

        else if (strcmp(op, "n4.alto") == 0)
            codigo_objeto << "0x21" << endl;

    }


    fclose(archivo_sl);
    archivo_intermedio.close();
    codigo_objeto.close();
    return 0;
}
