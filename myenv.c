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

#define BUF_MAX 2000



int main(int argc, char *argv[])
{

    /* If less than two arguments (argv[0] -> program, argv[1] -> file to save environment) print an error y return -1 */
    if(argc < 3)
    {
    	printf("NO HAY SUFICIENTES ARGUMENTOS\n");
    	return -1;
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
    strcat(variable, "=");
    // Contador de posicion de la letra
    int i = 0;
    int escrito = 0;
    int seguir_comprobando = 1;
    int primera_iteracion = 1;
    // Buf de escritura del resultado
    char buf_escritura[BUF_MAX];
	
    // Leemos el contenido del fichero letra a letra:
    // Se acabará el while si se acaba de leer el archivo y no ha habido
    // coincidencia o si la ha habido y ya se ha escrito el resultado
    // en el fichero de salida
	while ((bytes = read(fd1, buf, 1)) > 0 && escrito == 0){ 

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
        else if (buf[0] == '\n'){
            seguir_comprobando = 1;
        }
        else{
            seguir_comprobando = 0;
        }        

        if (i == len){
            seguir_comprobando = 0;
            if (buf[0] == '\n'){
                // Añadimos el salto de línea
                strcat(buf_escritura, "\n");
                escrito = 1;
            }
            else{
                if (primera_iteracion == 1){
                    primera_iteracion = 0; 
                    strcpy(buf_escritura, variable);
                }
                else{
                    // Agregamos el primer caracteres del buf al destino, 
                    // más un carácter nulo de terminación con 'strncat'.
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

    printf("%s", buf_escritura);
    // Antes de empezar a escribir en el fichero, vacíamos su contenido
    if (ftruncate(fd2, 0) < 0){
        perror("ERROR DE VACIADO DEL FICHERO DE SALIDA");
        close(fd1);
        close(fd2);
        exit(-1);
    }
    // Escribimos el contenido del buf en el fichero de salida
    // El número de bytes a escribir será strlen del buf de escritura
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
