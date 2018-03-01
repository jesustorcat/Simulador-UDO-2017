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
    ofstream archivo_simbolos("archivo_simbolos.dat");

    //Crea el archivo intermedio utilizado para realizar el análisis léxico
    ofstream archivo_intermedio("archivo_intermedio.dat");

    while (archivo_entrada.peek() == ';') {
        archivo_entrada.ignore(255, '\n');
    }

    //Lee la primera línea
    archivo_entrada.getline(tmp, inst_max);

    //Divide las palabras en la línea
    buff = strtok(tmp, " .\t");

    while (buff !=NULL) {
        if (strcmp(buff, "INICIO") == 0){
            archivo_intermedio << buff << "\t";
            buff = strtok(NULL, " .\t");
            lc = atoi(buff);
            archivo_intermedio << lc << "\n";
        }

        buff = strtok(NULL, " .\t");
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
        buff = strtok(tmp, "$");

        while (buff != NULL) {
            //Verifica si se trata de una etiqueta
            buff1 = strpbrk(buff, ":");

            if (buff1 != NULL){
                for (i = 0; i < n; i++){
                    if (strcmp(buff, b[i]) == 0){
                        f = 1;
                        break;
                    }
                    f = 0;
                }

                if (f == 0){
                    archivo_simbolos << buff << "\t" << "0x" << hex << lc << "\n";
                    strcpy(b[n++], buff);
                }
            }

            for (i = 0; i < 40; i++){
                if (strcmp(buff, a[i]) == 0){
                    f1 = 0;
                    break;
                }
                f1 = 1;
            }

            if (f1 == 0){

                if (strcmp(buff, "nop") == 0)
                    lc+=1;

               else if (strcmp(buff, "mov") == 0)
                    lc+=1;

               else if (strcmp(buff, "cda") == 0)
                    lc+=2;

               else if (strcmp(buff, "sum") == 0)
                    lc+=1;

               else if (strcmp(buff, "res") == 0)
                    lc+=1;

               else if (strcmp(buff, "mul") == 0)
                    lc+=1;

               else if (strcmp(buff, "div") == 0)
                    lc+=1;

               else if (strcmp(buff, "inc") == 0)
                    lc+=1;

               else if (strcmp(buff, "dec") == 0)
                    lc+=1;

               else if (strcmp(buff, "pot") == 0)
                    lc+=1;

               else if (strcmp(buff, "raiz") == 0)
                    lc+=1;

               else if (strcmp(buff, "traa") == 0)
                    lc+=1;

               else if (strcmp(buff, "trab") == 0)
                    lc+=1;

               else if (strcmp(buff, "set") == 0)
                    lc+=1;

               else if (strcmp(buff, "reset") == 0)
                    lc+=1;

               else if (strcmp(buff, "and") == 0)
                    lc+=1;

               else if (strcmp(buff, "or") == 0)
                    lc+=1;

               else if (strcmp(buff, "xor") == 0)
                    lc+=1;

               else if (strcmp(buff, "comp") == 0)
                    lc+=1;

               else if (strcmp(buff, "desi") == 0)
                    lc+=1;

               else if (strcmp(buff, "desd") == 0)
                    lc+=1;

               else if (strcmp(buff, "suma") == 0)
                    lc+=3;

               else if (strcmp(buff, "resta") == 0)
                    lc+=3;

               else if (strcmp(buff, "salt") == 0)
                    lc+=2;

               else if (strcmp(buff, "alto") == 0)
                    lc+=1;
            }
            buff = strtok(NULL, "$");
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
