#include <inc.h>

void			display_fingerprint(t_fingerprint *sig)
{
  t_return		*tmp_ret;

  if (! sig)
    return ;
  tmp_ret = sig->ret_list;
  printf("unknown fingerprint:\n");
  printf("-New signature-");
  while (tmp_ret->next)
    {
      printf(":%d", tmp_ret->ret);
      tmp_ret = tmp_ret->next;
    }

  printf("\n");
}

void			debug_fingerprints(t_fingerprint *list)
{
  t_fingerprint		*tmp;
  t_return		*tmp_ret;

  tmp = list;
  while (tmp)
    {
      tmp_ret = tmp->ret_list;
      while (tmp_ret)
	{
	  /* printf("index %d - ret:  %d\n", tmp_ret->index, tmp_ret->ret); */
	  tmp_ret = tmp_ret->next;
	}
      tmp = tmp->next;
    }
}


int			count(t_fingerprint *list)
{
  int			count;
  t_fingerprint		*tmp;

  count = 0;
  if (! list)
    return (count);


  tmp = list;
  while (tmp)
    {
      count++;
      tmp = tmp->next;
    }

  return count;
}

t_return		*new_ret(int ret_code, int index)
{
  t_return		*new;

  if (! (new = malloc(sizeof(t_return))))
    {
      fprintf(stderr, "%s:%d Can't malloc new in new_ret()\n",
	      __FILE__, __LINE__);
      exit (1);
    }

  new->index = index;
  new->ret = ret_code;
  new->next = 0;
  return (new);
}


t_return		*add_ret(t_return *list, t_return *new)
{
  t_return		*tmp;

  if (! list)
    return (new);
  if (! new)
    return (list);

  tmp = list;
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = new;

  return (list);
}


/*
** t_fingerprint *new(char *string)
**
** string is a line of a fingerprint entry in the fingerprint file
*/

/* create a new fingerprint entry */

t_fingerprint		*new(char *string)
{
  t_fingerprint		*new;
  t_return		*ret_list;
  char			*p;
  int			index = 1;

  if (! (new = (t_fingerprint *) malloc(sizeof(t_fingerprint))))
    {
      fprintf(stderr, "%s:%d Can't malloc in new()\n",  __FILE__, __LINE__);
      exit(1);
    }

  ret_list = 0;
  p = strtok(string, ":");
  new->version = strdup(p);
  while ((p = strtok(0, ":")))
    ret_list = add_ret(ret_list, new_ret(atoi(p), index++));
  new->ret_list = ret_list;
  new->next = 0;
  return (new);
}


/* add an existing fingerprint entry to an existing or not index */

t_fingerprint		*add(t_fingerprint *list, t_fingerprint *new)
{
  if (! list)
    return (new);
  if (! new)
    return (list);

  new->next = list;
  return (new);
}


/* delete an entry from a fingerprint list */

t_fingerprint		*del(t_fingerprint *list, t_fingerprint *destroy)
{
  int			first = 1;
  t_fingerprint		*save;
  t_fingerprint		*tmp;

  tmp = list;

  while (tmp)
    {
      if (tmp == destroy)
	{
	  if (first == 1)
	    {
	      /* we re destroying the list  */
	      if (! tmp->next)
		return (0);
	      else
		/* we're jumping on the next one  */
		return (tmp->next);
	    }
	  else	/* not the first */
	    {
	      /* if followed */
	      if (tmp->next)
		{
		  save->next = tmp->next;
		  return (list);
		}
	      else	/* not followed */
		{
		  save->next = 0;
		  return (list);
		}
	    }
	}
      first = 0;
      save = tmp;
      tmp = tmp->next;
    }

  return (tmp);
}
