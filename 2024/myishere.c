/*
P1-SSOO-23/24
El programa myishere recibe el nombre de un directorio como primer argumento
y comprueba si el fichero cuyo nombre recibe como segundo argumento se encuentra en ese
directorio.
*/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>


int main(int argc, char *argv[])
{
	/* If less than three arguments (argv[0] -> program, argv[1] -> directory to search, argv[2] -> file to find) print an error y return -1 */
	if(argc < 3){
		printf("No hay suficientes argumentos\n");
		return -1;
	}
	else if(argc > 3){
		printf("Demasiados argumentos\n");
		return -1;
	}

	DIR *dd;
	/*Abrimos el directorio introducido como primer parámetro*/
	if ((dd = opendir(argv[1])) == NULL){
		perror("ERROR EN LA APERTURA DEL DIRECTORIO");
		return -1;
	}

	/*Leemos cada una de las entradas del directorio y comprobamos si alguna coincide con el segundo argumento*/
	struct dirent *dir;
	while((dir = readdir(dd)) != NULL){
		if(strcmp(dir->d_name, argv[2]) == 0){
			printf("File %s is in directory %s\n", argv[2], argv[1]);
			closedir(dd);
			return 0;
		}
	}

	/*Si hemos salido del bucle, quiere decir que el fichero no está en el directorio*/
	printf("File %s is not in directory %s\n", argv[2], argv[1]);
	closedir(dd);

	return 0;
}
