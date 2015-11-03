#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>
#include "http_worker.h"
#include "checkget.h"
#include "checkext.h"

#define RES_LEN 256

void
http_worker (int sd_conn, struct sockaddr *cli_addr)
{

  typedef struct http_req
  {
    char method[6];
    char url[RES_LEN];
    char ver[10];
  } http_req_t;


  extern pthread_mutex_t lock;

  char delim[] = "\n";
  char delim2[] = " ";
  char *token;
  char *token2;
  char urlaux[256];
  http_req_t req;
  int i = 0;
  int leido = 0;
  int len;
  int fd, mime;
  int http_ok = 0;

  char rpdf[] = "HTTP/1.1 200 OK\nContent-Type: application/pdf;\nConnection:close\n\n";
  char rtxt[] = "HTTP/1.1 200 OK\nContent-Type: text/plain;\nConnection:close\n\n";
  char rjpg[] = "HTTP/1.1 200 OK\nContent-Type: image/jpeg; charset=utf-8\nConnection:close\n\n";
  char rhtml[] = "HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8\nConnection:close\n\n"; 
  char rico[] = "HTTP/1.1 200 OK\nContent-Type: image/x-icon; charset=utf-8\nConnection:close\n\n";



char buff[4096];

  read (sd_conn, buff, sizeof buff);

  pthread_mutex_lock (&lock);

  token = strtok (buff, delim);

  for (token2 = strtok (token, delim2); token2;
       token2 = strtok (NULL, delim2))
    {

      len = strlen (token2) + 1;

      switch (i) {
	      
	      case 0: 
		      strncpy(req.method,token2,len);
		      break;

	      case 1: 
		      strncpy(req.url,token2,len);
		      break;

	      case 2:
		      strncpy(req.ver,token2,len);
		      break;

      }

//        printf("Token: %s (%d) %d\n", head[i], len, i);
      i++;

    }

  pthread_mutex_unlock (&lock);

  if (checkget(req.method))   {

      write (1, "Ok (Method)\n", 12);
      http_ok++;

      if (req.url[0] == '/' && (strlen (req.url) == 1))
	{
	  mime = 1;
	  fd = open ("index.html", O_RDONLY, 0777);
	}
      else
	{
	  len = 0;
	  len = strlen(req.url);
	  

	  for (i = 1; i < len; i++)
	    {
	      urlaux[i - 1] = req.url[i];
	    }

	  mime = checkext (urlaux);

	  if (mime == -1)
	    {
	      write (sd_conn, "501 Not Implemented\n", 20);
	      printf ("MIME no valido (%s)\n", urlaux);
	      

	    }
	  else
	    {
	      fd = open (urlaux, O_RDONLY, 0777);
	    }
	}

      if (fd < 0)
	{
	  write (sd_conn, "404 File Not Found\n", 19);
	  perror ("Destination open()");
	  
	}
      else
	{
	  write (1, "Ok (File)\n", 10);
	  http_ok++;
	}

    }
  else
    {

      write (sd_conn, "400 Bad request\n", 16);
      
    }


  if (http_ok == 2)
    {
      switch (mime)
	{
	case 1:
	  write (sd_conn, rhtml, strlen(rhtml));
	  memset (buff, 0, sizeof buff);
	  while ((leido = read (fd, buff, sizeof buff)) > 0)
	    {
	      write (sd_conn, buff, sizeof buff);
	    }
	  write (sd_conn, "\n\n", 2);
	  break;

	case 2:
	  write (sd_conn, rjpg, strlen(rjpg));
	  memset (buff, 0, sizeof buff);
	  while ((leido = read (fd, buff, sizeof buff)) > 0)
	    {
	      write (sd_conn, buff, sizeof buff);
	    }
	  write (sd_conn, "\n\n", 2);
	  break;

	case 3:
	  write (sd_conn, rtxt, strlen(rtxt));
	  memset (buff, 0, sizeof buff);
	  while ((leido = read (fd, buff, sizeof buff)) > 0)
	    {
	      write (sd_conn, buff, leido);
	    }
	  write (sd_conn, "\n\n", 2);
	  break;

	case 4:
	  write (sd_conn, rpdf, strlen(rpdf));
	  memset (buff, 0, sizeof buff);
	  while ((leido = read (fd, buff, sizeof buff)) > 0)
	    {
	      write (sd_conn, buff, sizeof buff);
	    }
	  write (sd_conn, "\n\n", 2);
	  break;

	case 5:
	  write (sd_conn, rico, strlen(rico));
	  memset (buff, 0, sizeof buff);
	  while ((leido = read (fd, buff, sizeof buff)) > 0)
	    {
	      write (sd_conn, buff, sizeof buff);
	    }
	  write (sd_conn, "\n\n", 2);
	  break;


	}
    }

  close (fd);
  close (sd_conn);
}
