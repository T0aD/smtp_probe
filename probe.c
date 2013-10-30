#include <inc.h>
#include <rules.h>

/*
** Get the SMTP ret code
** hint: to compare with the fingerprint values
*/

int				get_code(char *answer)
{
  char				*p;
  p = strtok(answer, " ");
  return atoi(p);
}

/*
** Start the smtp probing, while adding answers to return
** a new data who will be the new fingerprint signature if unknows
*/

t_fingerprint			*start_probe(
					     char *ip, 
					     int port, 
					     t_fingerprint *fingerprints)
{
  t_fingerprint			*new_signature, *tmp_fp;
  t_return			*tmp_ret, *ret_list = 0;
  struct  sockaddr_in		addr;
  int				sock, sock_size, num, ret, ret_index = 1;
  char				*ptr, *np, *banner = 0;

  /* Networking general initialisation */

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(ip);
  memset(&(addr.sin_zero), 0, 8);
  sock_size = sizeof(struct sockaddr);

  /* Create the signature in memory */

  if (! (new_signature = malloc (sizeof(t_fingerprint))))
    die ("new_signature memory allocating");
  new_signature->next = 0;

  /* Looping on the basic rules in (t_rules *) rules */

  for (num = 0; num < sizeof(rules) / sizeof(t_rules); num++)
    {
      /* starting single connection */

      sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      if ((connect(sock, (struct sockaddr *) &addr, sock_size)) == -1)
	die ("connection with host failed.");

      if (! banner)
	{
	  printf("guilty claims to be %s\n", banner = getl(sock));
	  new_signature->version = banner;
	}
      else
	getl(sock);

      ptr = strdup(rules[num].message);
      np = addcr(strtok(ptr, "\n"));
      write(sock, np, strlen(np));

      while ((np = addcr(strtok(0, "\n"))))
	{
	  getl(sock);
	  write(sock, np, strlen(np));
	}

      /* getting the last code return */

      ret = get_code(getl(sock));

      /* adding ret code to the new signature */

      ret_list = add_ret(ret_list, new_ret(ret, ret_index));

      /* get rid off bad occurences */

      tmp_fp = fingerprints;
      while (tmp_fp)
	{
	  tmp_ret = tmp_fp->ret_list;
	  while (tmp_ret)
	    {
	      if (tmp_ret->index == ret_index)
		{
		  if (tmp_ret->ret == ret)
		    ;
		  /* printf("%s nice !\n", tmp_fp->version); */
		  else
		    fingerprints = del(fingerprints, tmp_fp);
		  break;
		}
	      else if (tmp_ret->index < ret_index)
		tmp_ret = tmp_ret->next;
	      else
		break;
	    }
	  tmp_fp = tmp_fp->next;
	}
 
      /* Free your mind ! (and the rest..) */

      ret_index++;
      close(sock);
      free(ptr);
      free(np);

      if (count(fingerprints) == 1)
	{
	  printf("smtp server real version: %s\n", fingerprints->version);
	  return 0;
	}
      else if (! count(fingerprints))
	{
	  printf("no matching signature found.\n");
	  new_signature->ret_list = ret_list;

	  return new_signature;
	}
    }

  /* final linking */
  new_signature->ret_list = ret_list;

  return new_signature;
}
