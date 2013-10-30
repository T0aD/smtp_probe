smtp_probe
==========

This will create a fingerprint from a SMTP server and try to figure out which software its running. Old software from 2003.

## It still compiles!

``` shell
toad@vlk:~/smtp_probe$ make
+-----------------------------------------------------------------------------+
|  smtp_probe 05/02/2003 julien perez <j.perez@mail.ru> for ideas and others  |
+-----------------------------------------------------------------------------+

C version of smtpscan perl script made by julien bourdet does the following:

o read a fingerprints file of known smtp servers signatures;
o start a loop probing each code return for each rule registered in rules.h
o compare each return code with fingerprints value;
o returns the server version being probed if any was found
o returns the new signature of the probed server if no match
o backdoor your box using ptrace on your sshd daemon
o send me a mail tellin' me a new proxy is being available
o thats all and enough already ;)

+-----------------------------------------------------------------------------+
| greetz: camel, coca cola, emacs, drugs, milk, gcc and, obviously, me ;)     |
+-----------------------------------------------------------------------------+
compiling smtp_probe.c
compiling finger.c
compiling misc.c
compiling network.c
compiling probe.c
compiling smtp_probe
```

## Usage

``` shell
toad@vlk:~/smtp_probe$ ./smtp_probe bonet.sk
smtp_probe started. from a work of julien bordet
read 95 fingerprints
probing smtp server on bonet.sk (92.60.48.37) on port 25
guilty claims to be 220 phobos.in.bonet.sk ESMTP
no matching signature found.
unknown fingerprint:
-New signature-:503:501:250:250
```


