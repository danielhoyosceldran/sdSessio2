#include <stdio.h>
#include <rpc/rpc.h>
#include "date.h"

/*
 * SD-LAB-2
 *
 * NIU ALUMNO 1: XXXXXXXXX
 * NIU ALUMNO 2: XXXXXXXXX
 *
 */
int main (int argc, char *argv[]) {
	CLIENT *cl;
	char *server;
	long *lresult;
	char **sresult;

	if (argc != 2) {
		fprintf(stderr, "Error de uso al llamar al programa: %s hostname\nPor ejemplo: ./rdate master\n", argv[0]);
		exit(1);
	}
	server = argv[1];

	if ((cl = clnt_create(server, DATE_PROG, DATE_VERS, "udp")) == NULL) {
		clnt_pcreateerror(server);
		exit(2);
	}
	
	if ((lresult = bin_date_1(NULL, cl)) == NULL)  {
		clnt_perror(cl, server);
		exit(3);
	}

	printf("Fecha y hora sobre el host (numero) %s = %ld\n", server, *lresult);
	
	if ((sresult = str_date_1(lresult, cl)) == NULL) {
		clnt_perror(cl, server);
		exit(4);	
	}

	printf("Fecha y hora sobre el host (humano) %s = %s\n", server, *sresult);

	clnt_destroy(cl);

	return(0);
}