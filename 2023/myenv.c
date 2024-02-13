//P1-SSOO-22/23
/*El programa myenv abrirá un fichero “env.txt” que contiene las variables
de entorno almacenadas. A continuación, buscará en el fichero todas las lı́neas 
que tienenocurrencia de la variable que se recibe como argumento y las escribirá 
en el fichero de salida, pasado por argumentos, imprimiendo una entrada por lı́nea.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Definimos el tamaño máximo del buf de escritura
#define BUF_MAX 2000


int main(int argc, char *argv[])
{

    // Si recibe menos o más de dos argumentos imprime error y devuelve -1
    if(argc < 3)
    {
    	printf("ERROR: No hay suficientes argumentos, ");
        printf("debe recibir una variable de entorno y un fichero de salida\n");
    	exit(-1);
    }
    else if(argc > 3)
	{
		printf("ERROR: Hay demasiados argumentos, ");
        printf("debe recibir una variable de entorno y un fichero de salida\n");
		exit(-1);
	}


    // Abrimos el fichero proporcionado "env.txt"
    int fd1;
    fd1 = open("env.txt", O_RDONLY);

    if (fd1 < 0){
        perror("ERROR DE APERTURA DEL FICHERO 'env.txt'");
        exit(-1);
    }

    // Abrimos el fichero de salida pasado como parámetro
	int fd2;
	fd2 = open(argv[2], O_RDWR);

    // Si no existe, lo creamos
	if (fd2 < 0){ 
        // Solo podrá ser modificado por el propietario: 0644
		if ((fd2 = creat(argv[2], 0644)) < 0){
            perror("ERROR DE CREACIÓN DEL FICHERO DE SALIDA");
            close(fd1);
            exit(-1);
        }
	}


    // Leemos el contenido del fichero letra a letra
	char buf[1];
	int bytes;
    int len = strlen(argv[1]) + 1;
    // Variable pasada como parémetro
    char variable[len];
    strcpy(variable, argv[1]);
    // Añadimos un "="
    strcat(variable, "=");
    // Contador de posicion de la letra en 'variable'
    int i = 0;
    // Indicador de haber escrito, por lo tanto coincidencia
    int escrito = 0;
    // Indicador de que en esa línea hay que seguir buscando
    // la variable
    int seguir_comprobando = 1;
    // Indicador de que es la primera iteración de la escritura
    int primera_iteracion = 1;
    // Buf de escritura del resultado
    char buf_escritura[BUF_MAX];
	
    // Se acabará el bucle si se acaba de leer el archivo y no ha habido
    // coincidencia o si la ha habido y ya se ha guardado el resultado
    // en el buf de salida
	while ((bytes = read(fd1, buf, 1)) > 0 && escrito == 0){ 
        
        // Buscamos coincidencia en la línea
        if (seguir_comprobando == 1){

            if (buf[0] == variable[i]){
                i++;
                seguir_comprobando = 1;
            }
            else{
                i = 0;
                seguir_comprobando = 0;
            }
        }
        // Si hemos llegado al final de la línea, seguimos buscando
        // en la siguiente
        else if (buf[0] == '\n'){
            seguir_comprobando = 1;
        }
        // Como ya sabemos que no hay coincidencia en esa línea,
        // la pasamos sin comprobar hasta acabar la línea
        else{
            seguir_comprobando = 0;
        }        

        // Si han coincidido todas las letras querrá decir que hemos
        // encontrado la variable
        if (i == len){
            seguir_comprobando = 0;
            // Ya hemos acabado de escribir las entradas
            if (buf[0] == '\n'){
                // Añadimos el salto de línea
                strcat(buf_escritura, "\n");
                escrito = 1;
            }
            else{
                // En la primera iteración añadimos el nombre de la variable
                // y el '='
                if (primera_iteracion == 1){
                    primera_iteracion = 0; 
                    strcpy(buf_escritura, variable);
                }
                // En las siguientes añadimos el primer caracter del buf 
                // al destino, más un carácter nulo de terminación con 'strncat'
                else{
                    strncat(buf_escritura, buf, 1);
                }
            }
        }
    }
	
	if (bytes < 0){
		perror("ERROR DE LECTURA DEL FICHERO 'env.txt'");
        close(fd1);
        close(fd2);
		exit(-1);
	}

    // Antes de empezar a escribir en el fichero, vacíamos su contenido
    if (ftruncate(fd2, 0) < 0){
        perror("ERROR DE VACIADO DEL FICHERO DE SALIDA");
        close(fd1);
        close(fd2);
        exit(-1);
    }
    // Escribimos el contenido del buf en el fichero de salida
    // El número de bytes a escribir será el tamaño de la cadena
    if (write(fd2, buf_escritura, strlen(buf_escritura)) < 0){
        perror("ERROR DE ESCRITURA EN EL FICHERO DE SALIDA");
        close(fd1);
        close(fd2);
        exit(-1);
    }

    close(fd2);
    close(fd1);
    return 0;
}
