#include <inc.h>

/*
** merely read a line from file descriptor fd then returns it
*/

char			*getl(int fd)
{
  int			stat, size = 1;
  char			*buf, c;

  if (! (buf = malloc (sizeof(char) * size)))
    die ("error while allocating memory in getl()");

  while ((stat = read(fd, &c, 1)) == 1 && c != '\n')
    {
      buf = realloc (buf, ++size);
      buf[size - 2] = c;
      buf[size - 1] = 0;
    }

  /* end of file */

  if (! stat)
    return (0);

  return (buf);
}

/*
** add a '\n' at the tail of the string & returns the concatenated value
*/

char			*addcr(char *string)
{
  char			*buf;

  if (! string)
    return (0);

  if (! (buf = malloc(sizeof(char) * strlen(string) + 2)))
    die ("error while mallocin' in addcr()");
  strcpy(buf, string);
  strcat(buf, "\n");

  return buf;
}
