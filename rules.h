#ifndef _RULES_H_
#define _RULES_H_

typedef struct		s_rules {
  int			index;
  char			*message;
}			t_rules;

/*
** Rules of probing (same order as fingerprints, of course baby)
*/

t_rules							rules[] = {
  {	1,	"MAIL FROM: foo@av.com"					},
  {	2,     	"HELO"							},
  {	3,     	"HELO av.com\nMAIL FROM: foo"				},
  {	4,     	"HELO av.com\nMAIL FROM: <>"				},
  {	5,     	"HELO av.com\nMAIL FROM: <foo@av.com"			},
  {	6,     	"HELO av.com\nMAIL FROM: <foo@av.bar>"			},
  {	7,     	"HELO av.com\nMAIL FROM: <foo@av.com>\nRCPT TO: foo"	},
  {	8,     	"HELO av.com\nHELP"					},
  {	9,     	"HELO av.com\nVRFY root"				},
  {	10,    	"HELO av.com\nEXPN root"				},
  {	11,    	"HELO av.com\nTURN"					},
  {	12,    	"HELO av.com\nSOML FROM: <foo@av.com>"			},
  {	13,    	"HELO av.com\nSAML FROM: <foo@av.com"			},
  {	14,    	"HELO av.com\nNOOP"					},
  {	15,    	"EHLO av.com"						}
};

#endif
