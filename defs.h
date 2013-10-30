#ifndef _DEFS_H_
#define _DEFS_H_

/* constants values */


#define	FINGERPRINT_FILE	"fingerprints"
#define	DEFAULT_PORT		25


/* functions */

#define	die(str)		{ perror(str); exit(1); }
#define die_on_error(str)	{ fprintf(stderr, "%s\n", str); exit(1); }

#endif
