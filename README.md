REU-SanMarcos
=============

REU Graph Theory Summer 2012

To make executables.
--------------------
::

   make

To make test.

::

   make test

To make tables.

::
   
   make tables

Also..

::
   
   make clean

Running the Program
-------------------
Main Program takes a diameter parameter and an optional lower bound.

::

   ./executables/average_case d b

Tests.

::
   
   ./executables/test

Tables takes size parameters for the coefficient tables. 

C = (x, y, z) = diameter (same as in main program)

M = (alpha, beta, gamma) 

G = (a, b, c)

::

   ./executables/tables C M G

Hint
----
View debugging output leisurely.

::

   ./executables/blah blah > test.txt 

To run multiple tests, edit the runtests executable and run.

::

   ./runtest

Please refer to your headers and classes in the makefile, placing executables in the /executables directory.
