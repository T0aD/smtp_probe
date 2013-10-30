#include <inc.h>

void			debug_fingerprints(t_fingerprint *list);

int			main(int ac, char **av)
{
  t_fingerprint		*index, *fingerprint_return;
  char			*hostname, *str, *ip;
  int			port, fd, cnt = 0;

  if (ac != 3 && ac != 2)
    die_on_error ("syntax: ./smtp_probe hostname port");

  index = 0;
  hostname = av[1];
  if (ac == 3)
    port = atoi(av[2]);
  else
    port = DEFAULT_PORT;

  printf("smtp_probe started. from a work of julien bordet\n");

  /* Reading our fingerprints */

  if ((fd = open(FINGERPRINT_FILE, O_RDONLY)) == -1)
    die ("error while reading fingerprints' file");

  while ((str = getl(fd)))
    {
      ++cnt;
      /*      printf("\rread %d fingerprints", ++cnt); */
      index = add(index, new(str));
    }
  printf("read %d fingerprints", cnt);
  close(fd);
  printf("\n");

  /* Starting the game */

  ip = resolve(hostname);
  printf("probing smtp server on %s (%s) on port %d\n", hostname, ip, port);
  display_fingerprint(fingerprint_return = start_probe(ip, port, index));

  free(fingerprint_return);
  free(index);

  return (0);
}
