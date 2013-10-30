#include <inc.h>

char				*resolve(char *hostname)
{
  struct hostent		*host;

  if (! (host = gethostbyname(hostname)))
    die_on_error ("cannot resolve hostname");
  return inet_ntoa(*(struct in_addr *)host->h_addr);
}
