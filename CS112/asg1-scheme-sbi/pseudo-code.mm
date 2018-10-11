.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.SIZE 12 14
.TITLE "Pseudocode Outline"
.RCS "$Id: pseudo-code.mm,v 1.1 2018-10-10 15:09:53-07 - - $"
.PWD
.URL
.de BULLETS
.   ALX \[bu] 0 "" 0 0
..
The data structure consists of a recursively nested list\(::
.BULLETS
.LI
The top level list consists of a sequence of lines.
Each line is pointed at by the
.V= car
of a cell in the opt level list.
.LI
Each line consists of a line number,
an optional label, which is always a
.V= symbol? ,
and an optional statement, which is always a
.V= pair? .
Use
.V= null?
to determine whether not something exists.
Do not use
.V= list? .
.LI
A statement consists of a keyword followed by operands,
mostly expressions.
.LI
An expression uses prefix notation in standard Scheme format.
.LE
.P
A suggested outline and description of some of the functions follows\(::
.ALX a ()
.LI
After reading in the program,
make one pass over the top level,
checking for a label in each line.
Each label should be inserted into the label hash
with a pointer to the top level node (not the line).
.LI
Write a function
.V= interpret-program
takes the top level list as an argument and
checks to see if there is a statement.
.BULLETS
.LI
If there is no statement,
call it recursively with the
.V= cdr
of the top level node.
.LI
If there is a statement, look up the keyword in the
statement hash and call
.VI interpret- statement ,
where
.IR statement
is the keyword found in the statement.
.LI
This funcion should return null
for a statement that is not a control transfer,
or for a statement that is a control transfer that is not taken.
.LI
If this function returns a null then call
.V= interpret-program
recursively with the
.V= cdr ,
as explained above.
.LI
If this function is a successful control transfer,
it should return the label to which to transfer,
and then
.V= interpret-program
calls itself recursively with the associated line.
.LE
.LI
Write separate functions
.VI interpret- statement
for each one of the keyword in the language.
.LI
The function
.V= evaluate-expression 
is called by a statement interpreter.
.BULLETS
.LI
It looks up the function in the function table.
.LI
It uses
.V= map 
to call
.V= evaluate-expression
for each of the arguments to the function.
.LI
Then use
.V= apply
to apply the function to the list of results obtained.
.LI
Subscripting arrays will require a special case.
.LE
.LI
Implementation may use one or two symbol tables\(::
Functions and identifiers may be placed into the same table,
or they may be separated into two tables.
There is an ambiguity in the notation for calling a function
and subscripting an array.
.LE
.FINISH
