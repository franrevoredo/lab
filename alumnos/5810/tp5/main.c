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

#include "http_worker.h"

pthread_mutex_t lock;

void *hilo (void *arg);

int
main (int argc, char *const *argv)
{

  long int sd, sd_conn;
  socklen_t addrlen;
  struct sockaddr_in cli_addr;
  
  pthread_t tid;
  int i = 0;

  struct addrinfo hints;
  struct addrinfo *result;

  memset (&hints, 0, sizeof (struct addrinfo));
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_family = AF_UNSPEC;	/* Allows IPv4 or IPv6 */
  hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;

  if (pthread_mutex_init(&lock, NULL) != 0)  {
	  printf("\n mutex init failed\n");
	  return 1;
  }
  
  
  
  if (getaddrinfo (NULL, "5000", &hints, &result) != 0)
    {
      perror ("getaddrinfo");
      return -1;
    }

  sd = socket (result->ai_family, result->ai_socktype, result->ai_protocol);
  
  if (sd < 0)
    {
      perror ("No se creo el socket");
      return -1;
    }

  int reuse = 1;
  if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (const char *) &reuse, sizeof (reuse)) < 0)
    perror ("setsockopt(SO_REUSEADDR) error");

  if (bind (sd, result->ai_addr, result->ai_addrlen) < 0)
    {
      perror ("No se pudo bindear el socket");
      return -1;
    }

  if (listen (sd, 5) < 0)
    {
      perror ("Error en listen.");
      return -1;
    }


  while ((sd_conn = accept (sd, (struct sockaddr *) &cli_addr, &addrlen)) > 0)
    {
      if (pthread_create (&tid, NULL, hilo, (void *) sd_conn) != 0)
	{
	  perror ("pthread_create()");
	  return -1;
	}

      i++;

    }

   close(sd_conn);

   pthread_mutex_destroy(&lock);
 
   return 0;
}


void *hilo (void *arg)
{
  long int sd_conn = (long int) arg;
  http_worker (sd_conn, (struct sockaddr *) &cli_addr);
  pthread_exit (NULL);
  return NULL;
}
