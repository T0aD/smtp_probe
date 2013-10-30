#ifndef _FINGER_H_
#define _FINGER_H_

typedef struct		s_return {
  int			index;
  int			ret;
  struct s_return	*next;
}			t_return;

typedef struct		s_fingerprint {
  char			*version;
  t_return		*ret_list;
  struct s_fingerprint	*next;
}			t_fingerprint;

#endif

