//P1-SSOO-22/23
/*El programa mywc abrirá un fichero especificado como argumento, contará el
número de lı́neas, palabras y bytes del mismo, y mostrará estas por la salida estándar (la
consola) utilizando las llamadas al sistema que considere oportunas.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>



int main(int argc, char *argv[]){

	//If less than two arguments (argv[0] -> program, argv[1] -> file to process) print an error y return -1
	if(argc < 2)
	{
		printf("Too few arguments\n");
		return -1;
	}

	// Abrimos el fichero pasado como parámetro
	int fd;
	fd = open(argv[1], O_RDONLY);

	if (fd < 0){
		perror("ERROR DE APERTURA");
		exit(-1);
	}

	// Leemos el contenido del fichero byte a byte

	char buf[1];
	int bytes;
	int contador_bytes, contador_palabras, contador_lineas;
	contador_bytes = 0;
	contador_palabras = 0;
	contador_lineas = 0;
	
	while ((bytes = read(fd, buf, 1)) > 0){ // Un char son 4 bytes

		contador_bytes++;

		if (buf[0] == '	' || buf[0] == '\t'){
			contador_palabras++;
		}
		if (buf[0] == '\n'){
			contador_lineas++;
			contador_palabras++;
		}
	}
	
	if (bytes < 0){
		perror("ERROR DE LECTURA");
		close(fd);
		exit(-1);
	}
	else if (bytes == 0){
		contador_palabras++;
	}

	printf("%d ", contador_lineas);
	printf("%d ", contador_palabras);
	printf("%d ", contador_bytes);
	printf("%s\n", argv[1]);

	close(fd);
	return 0;
}