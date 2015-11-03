char rot13 (char c) {

  char aux;

  if ((c > 64) && (c < 91))
    {
       if((90-c)>= 13) {
	      aux = c + 13;
	      return aux;	
      } else {
	  aux = c - 13;
	  
	  return aux;
      }
    }
  else if ((c > 96) && (c < 123))
    {
      if((122-c)>= 13) {
	      aux = c + 13;
	      return aux;	
      } else {
	  aux = c - 13;
	  return aux;
      }
    }
  else
    return c;
}
