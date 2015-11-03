#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <getopt.h>

#include "hijo.h"

int rot, parse;

void sig1(int sig) {
	rot = 1;
}

void sig2(int sig) {
	parse = 1;
}

int main (int argc, char **argv)
{
  int rstatus;
  pid_t cpid;
  int c;
  int leido;
  int pah[2];
  char buff[500];
  int hap[2];
  
  char pal[100];

  
  if (pipe (pah) == -1)
    {
      perror ("Error al abrir el pipe pah");
      return -1;
    }

  if (pipe (hap) == -1)
  {
      perror ("Error al abrir el pipe hap");
      return -1;
    }

  signal(SIGUSR1, sig1);
  signal(SIGUSR2, sig2);

  while ((c = getopt (argc, argv, "rp:")) != -1)
    switch (c)
      {
      
      case 'r':
	kill(0, SIGUSR1);	
	break;

      case 'p':
	kill(0, SIGUSR2);
	strncpy(pal, optarg, strlen(optarg)+1);
	break;

      default:
	printf("\n No se ingresaron parametros \n");
	return 0;
      }


  while ((leido = read (0, buff, sizeof (buff))) > 0)
    {
      write (pah[1], buff, leido);
    }

  close (pah[1]);

  switch ((cpid = fork ()))
    {
    case 0:
      hijo(pah, hap, pal);
      break;

    case -1:
      perror ("Error en el Fork");
      return -1;
      break;

    default:

      waitpid (cpid, &rstatus, 0);
      printf ("Soy el padre\n");

      while ((leido = read (hap[0], buff, sizeof (buff))) > 0)
	{
	  write (1, buff, leido);
	}
      close (hap[0]);
      close (hap[1]);
      close (pah[0]);
      break;

    }

  return 0;
}
