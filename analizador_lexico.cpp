/** Analizador léxico **/

#include "analizador_lexico.h"

compilador::compilador(){}

compilador::~compilador(){}

int compilador::analisis_lexico(string compilar_archivo){
    char a[][20] = {"n1.nop", "n1.mov", "n1.sal", "n1.cda",
                    "n1.sum", "n1.res", "n1.mul", "n1.div",
                    "n1.inc", "n1.dec", "n1.pot", "n1.raiz",
                    "n1.traa", "n1.trab", "n1.set", "n1.reset",
                    "n1.and", "n1.or", "n1.xor", "n1.comp",
                    "n1.desi", "n1.desd", "n1.suma", "n1.resta",
                    "n1.salt", "n1.alto"};

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

                if (strcmp(buff, "n1.nop") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.mov") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.cda") == 0)
                    lc+=2;

               else if (strcmp(buff, "n1.sum") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.res") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.mul") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.div") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.inc") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.dec") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.pot") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.raiz") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.traa") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.trab") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.set") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.reset") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.and") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.or") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.xor") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.comp") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.desi") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.desd") == 0)
                    lc+=1;

               else if (strcmp(buff, "n1.suma") == 0)
                    lc+=3;

               else if (strcmp(buff, "n1.resta") == 0)
                    lc+=3;

               else if (strcmp(buff, "n1.salt") == 0)
                    lc+=2;

               else if (strcmp(buff, "n1.alto") == 0)
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
