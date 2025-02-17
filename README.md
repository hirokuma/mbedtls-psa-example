# PSA Mbed TLS example

## build and run

```console
$ make depend
$ make
$ make leak
valgrind --tool=memcheck --leak-check=full -s ./tst
==585939== Memcheck, a memory error detector
==585939== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==585939== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==585939== Command: ./tst
==585939== 
PSA crypto version: 1.0

test1 start.
...... done.

test2 start.
...... done.

test3 start.
...... done.
done.
==585939== 
==585939== HEAP SUMMARY:
==585939==     in use at exit: 0 bytes in 0 blocks
==585939==   total heap usage: 14 allocs, 14 frees, 7,818 bytes allocated
==585939== 
==585939== All heap blocks were freed -- no leaks are possible
==585939== 
==585939== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
