#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>


#include "http_worker.h"


/*signal_callback_handler(int signum){
	
	        printf("Caught signal SIGPIPE %d\n",signum);
return 0;
}
*/



int
main (int argc, char *const *argv)
{

  int sd, sd_conn;
  socklen_t addrlen;
  struct sockaddr_in srv_addr;
  struct sockaddr_in cli_addr;


  
 struct sigaction sigchld_action = {
	   .sa_handler = SIG_DFL,
	     .sa_flags = SA_NOCLDWAIT
 };
 
 sigaction(SIGCHLD, &sigchld_action, NULL);
  
  
  
  sd = socket (AF_INET, SOCK_STREAM, 0);

  if (sd < 0)
    {
      perror ("Error al abrir el SOCKET");
      exit (EXIT_FAILURE);
    }


  int reuse = 1;
  if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (const char *) &reuse, sizeof (reuse)) < 0)
	  perror ("setsockopt(SO_REUSEADDR) error");

  srv_addr.sin_family = AF_INET;
  srv_addr.sin_addr.s_addr = INADDR_ANY;
  srv_addr.sin_port = htons (5000);


  if (bind (sd, (struct sockaddr *) &srv_addr, sizeof (srv_addr)) == -1)
    {
      perror ("Error en el BIND");
      exit (EXIT_FAILURE);
    }


  if (listen (sd, 5) < 0)
    {
      perror ("Error en listen.");
      return -1;
    }


  while ((sd_conn = accept (sd, (struct sockaddr *) &cli_addr, &addrlen)) > 0)
    {
      switch (fork ())
	{
	case 0:		// hijo
	  http_worker (sd_conn, (struct sockaddr *) &cli_addr);
	  return 0;

	case -1:		// error
	  perror ("Error Fork()");
	  break;

	default:		// padre
	  close (sd_conn);
	  break;
	}
    }

  wait(NULL);
  return 0;
}
