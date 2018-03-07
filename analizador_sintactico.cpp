/** Analizador sintáctico **/
#include "analizador_sintactico.h"

compilador_sintactico::compilador_sintactico(){}

compilador_sintactico::~compilador_sintactico(){}

int compilador_sintactico::analisis_sintactico(){
    char a[][20] = {"nop", "mov", "sal", "cda",
                    "sum", "res", "mul", "div",
                    "inc", "dec", "pot", "raiz",
                    "traa", "trab", "set", "reset",
                    "and", "or", "xor", "comp",
                    "desi", "desd", "suma", "resta",
                    "salt", "alto"};

    //Se inicializan las variables en cero "0"
    f1 = 0; lc = 0; i = 0; j = 0;

    FILE *archivo_sl;

    //Se abre el archivo intermedio generado en el analisis léxico
    ifstream archivo_intermedio("archivo_intermedio.dat");

    //Se abre el archivo de simbolos generado en el analisis léxico
    archivo_sl = fopen("archivo_simbolos.dat", "r");

    //Se crea el archivo de sálida donde se generará el código objeto
    ofstream codigo_objeto("codigo_objeto.dat");

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
        for (i = 0; i < 15; i++){
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

        if (strcmp(op, "nop") == 0)
            codigo_objeto << "0x0" << endl;

        else if ((strcmp(op, "mov") == 0) && (strcmp(operando, "s,e")))
            codigo_objeto << "0x1" << endl;

        else if ((strcmp(op, "mov") == 0) && (strcmp(operando, "a,e")))
            codigo_objeto << "0x2" << endl;

        else if ((strcmp(op, "mov") == 0) && (strcmp(operando, "b,e")))
            codigo_objeto << "0x3" << endl;

        else if ((strcmp(op, "mov") == 0) && (strcmp(operando, "a,f")))
            codigo_objeto << "0x4" << endl;

        else if ((strcmp(op, "mov") == 0) && (strcmp(operando, "b,f")))
            codigo_objeto << "0x5" << endl;

        else if ((strcmp(op, "mov") == 0) && (strcmp(operando, "f,a")))
            codigo_objeto << "0x6" << endl;

        else if ((strcmp(op, "mov") == 0) && (strcmp(operando, "f,b")))
            codigo_objeto << "0x7" << endl;

        else if (strcmp(op, "sal") == 0)
            codigo_objeto << "0x8" << endl;

        else if ((strcmp(op, "cda") == 0) && (strncmp(operando, "a,",2)) == 0){
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

        else if ((strcmp(op, "cda") == 0) && (strncmp(operando, "b,",2)) == 0){
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

        else if ((strcmp(op, "cda") == 0) && (strncmp(operando, "s,",2)) == 0){
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
        else if (strcmp(op, "sum") == 0)
            codigo_objeto << "0xc" << endl;

        else if (strcmp(op, "res") == 0)
            codigo_objeto << "0xd" << endl;

        else if (strcmp(op, "mul") == 0)
            codigo_objeto << "0xe" << endl;

        else if (strcmp(op, "div") == 0)
            codigo_objeto << "0xf" << endl;

        else if (strcmp(op, "inc") == 0)
            codigo_objeto << "0x10" << endl;

        else if (strcmp(op, "dec") == 0)
            codigo_objeto << "0x11" << endl;

        else if (strcmp(op, "pot") == 0)
            codigo_objeto << "0x12" << endl;

        else if (strcmp(op, "raiz") == 0)
            codigo_objeto << "0x13" << endl;

        else if (strcmp(op, "traa") == 0)
            codigo_objeto << "0x14" << endl;

        else if (strcmp(op, "trab") == 0)
            codigo_objeto << "0x15" << endl;

        else if (strcmp(op, "set") == 0)
            codigo_objeto << "0x16" << endl;

        else if (strcmp(op, "reset") == 0)
            codigo_objeto << "0x17" << endl;

        else if (strcmp(op, "and") == 0)
            codigo_objeto << "0x1b" << endl;

        else if (strcmp(op, "or") == 0)
            codigo_objeto << "0x1c" << endl;

        else if (strcmp(op, "xor") == 0)
            codigo_objeto << "0x1d" << endl;

        else if (strcmp(op, "comp") == 0)
            codigo_objeto << "0x1e" << endl;

        else if (strcmp(op, "desi") == 0)
            codigo_objeto << "0x1f" << endl;

        else if (strcmp(op, "desd") == 0)
            codigo_objeto << "0x20" << endl;

        else if (strcmp(op, "suma") == 0){
            codigo_objeto << "0x21" << endl;
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

        else if (strcmp(op, "resta") == 0){
            codigo_objeto << "0x22" << endl;
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

        else if (strcmp(op, "salt") == 0){
            codigo_objeto << "0x23" << endl;
            for (i = 0; i <= n; i++){
                if (strcmp(operando, simbolo[i]) == 0){
                    codigo_objeto << simb_dir[i] << endl;
                    break;
                }
            }
        }

        else if (strcmp(op, "alto") == 0)
            codigo_objeto << "0x24" << endl;

    }


    fclose(archivo_sl);
    archivo_intermedio.close();
    codigo_objeto.close();
    return 0;
}
