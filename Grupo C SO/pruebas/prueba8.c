#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/wait.h>

int main() {
    int i;
    pid_t pid;

    char *nombres[] = {"consulta1", "reserva1", "anulacion1", "pago1", "administracion1"};

    for (i = 0; i < 5; i++) {
	sleep(1);        
	pid = fork();
        if (pid == 0) {
            // Cambiar el nombre del proceso hijo
            char *nombre = nombres[i];
	    prctl(PR_SET_NAME, nombre);

            //printf("\nInicio --> Proceso: %s || PID: %d\n", nombre, getpid());
            long j = 0;
    	    long a = 0;
    	    int c = 0;
            for (j = 0; j < 300000000; j++) {
		a = j;
		if (c == 30) {
		   j = j-29;	
	   	c = 0;
		}
		c++;
    	   }

	    //printf("\nFin    --> Proceso: %s || PID: %d\n", nombre, getpid());
            // Terminar el proceso hijo
            return 0;
    	} 
    }
    return 0;

}
