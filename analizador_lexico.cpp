/** Analizador léxico **/

#include "analizador_lexico.h"

compilador::compilador(){}

compilador::~compilador(){}

int compilador::analisis_lexico(string compilar_archivo){
    char a[][20] = {"nop", "mov", "sal", "cda",
                    "sum", "res", "mul", "div",
                    "inc", "dec", "pot", "raiz",
                    "traa", "trab", "set", "reset",
                    "and", "or", "xor", "comp",
                    "desi", "desd", "suma", "resta",
                    "salt", "alto"};

    //limpia el contenido del arreglo "nombre"
    for(i = 0; i < 80; i++){
        nombre[i] = 0;
    }

    //Se inicializan las variables en cero "0"
    f = 0; f1 = 0; lc = 0; s = 0; l = 0; i = 0;
    compilar_archivo.copy(nombre, 80, 0);

    //Abrir el archivo donde se encuentra el código a realizar el análisis
    ifstream archivo_entrada(nombre);

    //Crea el archivo donde se almacenarán las direcciones de etiquetas
    ofstream archivo_simbolos("archivo_simbolos");

    //Crea el archivo intermedio utilizado para realizar el análisis léxico
    ofstream archivo_intermedio("archivo_intermedio");

    while (archivo_entrada.peek() == ';') {
        archivo_entrada.ignore(255, '\n');
    }

    //Lee la primera línea
    archivo_entrada.getline(tmp, inst_max);

    //Divide las palabras en la línea
    pch = strtok(tmp, ".\t");

    while (pch !=NULL) {
        if (strcmp(pch, "INICIO") == 0){
            archivo_intermedio << pch << "\t";
            pch = strtok(NULL, ".\t");
            lc = atoi(pch);
            archivo_intermedio << lc << "\n";
        }

        pch = strtok(NULL, ".\t");
    }

    s = lc;

    //Revisa el archivo a compilar hasta el final del mismo
    while (!archivo_entrada.eof()) {

        while (archivo_entrada.peek() == ';') {
            archivo_entrada.ignore(255, '\n');
        }

        archivo_entrada.getline(tmp, inst_max);
        if (archivo_entrada.eof() == true){
            archivo_intermedio << "0x" << hex << lc << "\t";
        }
        i = 0;

        while (tmp[i] != '\0') {
            if (isspace(tmp[i])){
                tmp[i] = '$';
            }

            if (tmp[i] == ';'){
                while (tmp[i] != '\0') {
                    tmp[i] = '\0';
                    ++i;
                }
            }
            ++i;
        }

        //Se almacena el contenido de la línea, debido a que es modificada
        strcpy (respaldo, tmp);

        //Se dividen las palabras
        pch = strtok(tmp, "$");

        while (pch != NULL) {
            //Verifica si se trata de una etiqueta
            pch1 = strpbrk(pch, ":");

            if (pch1 != NULL){
                for (i = 0; i < n; i++){
                    if (strcmp(pch, b[i]) == 0){
                        f = 1;
                        break;
                    }
                    f = 0;
                }

                if (f == 0){
                    archivo_simbolos << pch << "\t" << "0x" << hex << lc << "\n";
                    strcpy(b[n++], pch);
                }
            }

            for (i = 0; i < 40; i++){
                if (strcmp(pch, a[i]) == 0){
                    f1 = 0;
                    break;
                }
                f1 = 1;
            }

            if (f1 == 0){

                if (strcmp(pch, "nop") == 0)
                    lc+=1;
                if (strcmp(pch, "mov") == 0)
                    lc+=1;
                if (strcmp(pch, "cda") == 0)
                    lc+=2;
                if (strcmp(pch, "sum") == 0)
                    lc+=1;
                if (strcmp(pch, "res") == 0)
                    lc+=1;
                if (strcmp(pch, "mul") == 0)
                    lc+=1;
                if (strcmp(pch, "div") == 0)
                    lc+=1;
                if (strcmp(pch, "inc") == 0)
                    lc+=1;
                if (strcmp(pch, "dec") == 0)
                    lc+=1;
                if (strcmp(pch, "pot") == 0)
                    lc+=1;
                if (strcmp(pch, "raiz") == 0)
                    lc+=1;
                if (strcmp(pch, "traa") == 0)
                    lc+=1;
                if (strcmp(pch, "trab") == 0)
                    lc+=1;
                if (strcmp(pch, "set") == 0)
                    lc+=1;
                if (strcmp(pch, "reset") == 0)
                    lc+=1;
                if (strcmp(pch, "and") == 0)
                    lc+=1;
                if (strcmp(pch, "or") == 0)
                    lc+=1;
                if (strcmp(pch, "xor") == 0)
                    lc+=1;
                if (strcmp(pch, "comp") == 0)
                    lc+=1;
                if (strcmp(pch, "desi") == 0)
                    lc+=1;
                if (strcmp(pch, "desd") == 0)
                    lc+=1;
                if (strcmp(pch, "suma") == 0)
                    lc+=3;
                if (strcmp(pch, "resta") == 0)
                    lc+=3;
                if (strcmp(pch, "salt") == 0)
                    lc+=2;
                if (strcmp(pch, "alto") == 0)
                    lc+=1;
            }
            pch = strtok(NULL, "$");
        }
        archivo_intermedio << respaldo << "\n";

        if (f == 1){
            cout << "Etiqueta duplicada \n";
        }
    }

    l = lc - s - 1;
    archivo_entrada.close();
    archivo_intermedio.close();
    archivo_simbolos.close();

    return 0;
}
