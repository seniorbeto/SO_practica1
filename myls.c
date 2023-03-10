//P1-SSOO-22/23
/*El programa myls, abrirá un directorio especificado como argumento (o el directorio
actual si no se especifica ningún directorio como argumento), y mostrará por pantalla el nombre
de todas las entradas de dicho directorio, imprimiendo una entrada por lı́nea.*/

#include <stdio.h>		// Header file for system call printf
#include <unistd.h>		// Header file for system call gtcwd
#include <sys/types.h>	// Header file for system calls opendir, readdir y closedir
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

// Bla bla
#ifndef PATH_MAX
#define PATH_MAX 200
#endif

int main(int argc, char *argv[]){
	
	DIR *dd;
	if (argc == 1){
		char buf[PATH_MAX];
		getcwd(buf, PATH_MAX);
		dd = opendir(buf);
	}
	else{
		dd = opendir(argv[1]);
	}
	if (dd == NULL){
		perror("ERROR EN LA APERTURA DEL DIRECTORIO");
		return(-1);
	}

	struct dirent *dir;
	while((dir = readdir(dd)) != NULL){
		printf("%s\n", dir->d_name);
	}
	
	closedir(dd);
	return 0;
}
