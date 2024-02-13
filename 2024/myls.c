/*
P1-SSOO-22/23
El programa myls, abrirá un directorio especificado como argumento (o el directorio
actual si no se especifica ningún directorio como argumento), y mostrará por pantalla el nombre
de todas las entradas de dicho directorio, imprimiendo una entrada por lı́nea.
*/

#include <stdio.h>		
#include <unistd.h>		
#include <sys/types.h>	
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

/* 
Definimos el tamaño máximo que puede llegar a tener la ruta del directorio
en caso de que ésta no esté ya definida.
*/
#ifndef PATH_MAX
#define PATH_MAX 255
#endif


int main(int argc, char *argv[]){
	
	DIR *dd;

	/* Si recibe más de un argumento imprime error y devuelve -1 */
	if(argc > 2)
	{
		printf("ERROR: Hay demasiados argumentos, debe recibir un directorio o nada\n");
		return -1;
	}

	/* Si no se especifica ningún directorio obtenemos el directorio actual */
	if (argc == 1){
		char buf[PATH_MAX];
		getcwd(buf, PATH_MAX);
		dd = opendir(buf);
	}
	/* Si no, abrimos el especificado como argumento */
	else{
		dd = opendir(argv[1]);
	}

	if (dd == NULL){
		perror("ERROR EN LA APERTURA DEL DIRECTORIO");
		return -1;
	}

	/* Leemos cada una de las entradas del directorio e imprimimos su nombre */
	struct dirent *dir;
	while((dir = readdir(dd)) != NULL){
		printf("%s\n", dir->d_name);
	}
	
	closedir(dd);
	return 0;
}
