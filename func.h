#ifndef _FUNC_H_
#define _FUNC_H_

/* probe.c */

int			get_code(char *answer);
t_fingerprint		*start_probe(char *ip, int port, t_fingerprint *fp);

/* network.c */

char			*resolve(char *hostname);


/* misc.c */

char			*getl(int fd);
char			*addcr(char *string);

/* finger.c */

t_fingerprint		*new(char *string);
t_fingerprint		*add(t_fingerprint *list, t_fingerprint *new);
t_fingerprint		*del();
t_return		*new_ret(int ret_code, int index);
t_return		*add_ret(t_return *list, t_return *new);
void			display_fingerprint(t_fingerprint *fp);
int			count(t_fingerprint *list);


#endif
