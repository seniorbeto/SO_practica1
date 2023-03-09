//P1-SSOO-22/23
/*El programa myenv abrirá un fichero “env.txt” que contiene las variables
de entorno almacenadas. A continuación, buscará en el fichero todas las lı́neas que tienen
ocurrencia de la variable que se recibe como argumento y las escribirá en el fichero de salida,
pasado por argumentos, imprimiendo una entrada por lı́nea.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>



int main(int argc, char *argv[])
{

    /* If less than two arguments (argv[0] -> program, argv[1] -> file to save environment) print an error y return -1 */
    if(argc < 3)
    {
    	printf("Too few arguments\n");
    	return -1;
    }

    // Abrimos el fichero proporcionado "env.txt"
    int fd1;
    fd1 = open("/home/natalia/Escritorio/SO_practica1/env.txt", O_RDONLY);

    if (fd1 < 0){
        perror("ERROR DE APERTURA DEL FICHERO 'env.txt'");
        exit(-1);
    }

    // Abrimos el fichero de salida pasado como parámetro
	int fd2;
	fd2 = open(argv[2], O_RDWR);

	if (fd2 < 0){
		perror("ERROR DE APERTURA DEL FICHERO DE SALIDA");
		exit(-1);
	}

    
	char buf[1];
	int bytes;
    int len = strlen(argv[1]) + 1;
    // Variable pasada como parémetro
    char variable[len];
    strcpy(variable, argv[1]);
    // Añadimos un "="
    char igual[1] = "=";
    strcat(variable, igual);
    // Contador de posicion de la letra
    int i = 0;
    int escrito = 0;
    int seguir_comprobando = 1;
    int primera_iteracion = 1;
    // Buf de escritura del resultado
    char buf_escritura[1000]; // cte??
	
    // Leemos el contenido del fichero letra a letra:
    // Se acabará el while si se acaba de leer el archivo y no ha habido
    // coincidencia o si la ha habido y ya se ha escrito el resultado
    // en el fichero de salida
    printf("valor de len: %d \n", len);
    printf("valor de variable: %s \n", variable);
	while ((bytes = read(fd1, buf, 1)) > 0 && escrito == 0){ 

        if (seguir_comprobando == 1){

            if (buf[0] == variable[i]){
                printf("sumando i\n");
                printf("valor de buf: %c \n", buf[0]);
                i++;
                printf("valor de i: %d \n", i);
                seguir_comprobando = 1;
            }
            else{
                printf("igualando i a 0 \n");
                i = 0;
                seguir_comprobando = 0;
            }
        }
        else if (buf[0] == '\n'){
            seguir_comprobando = 1;
        }
        else{
            seguir_comprobando = 0;
        }        

        if (i == len){
            printf("variable encontrada \n");
            seguir_comprobando = 0;
            if (buf[0] == '\n'){
                escrito = 1;
            }
            else{
                if (primera_iteracion == 1){
                primera_iteracion = 0; 
                strcpy(buf_escritura, variable);
                }
                else{
                    printf("metiendo en el buffer: %d \n", putchar(buf[0]));
                    strcat(buf_escritura, putchar(buf[0]));
                }
            }
        }
    }
	
	if (bytes < 0){
		perror("ERROR DE LECTURA DEL FICHERO 'env.txt'");
		exit(-1);
	}
    printf("%s", buf_escritura);
    // Escribimos el contenido del buf en el fichero de salida
    if (write(fd2, buf_escritura, sizeof(buf_escritura)) < 0){
        perror("ERROR DE ESCRITURA EN EL FICHERO DE SALIDA");
        exit(-1);
    }

    close(fd2);
    close(fd1);
    return 0;
}
