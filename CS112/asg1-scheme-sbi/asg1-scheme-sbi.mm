.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.SIZE 12 14
.TITLE CMPS-112 Fall\~2018 Program\~1 "Functionally Scheme"
.tm title done
.RCS "$Id: asg1-scheme-sbi.mm,v 1.37 2018-10-10 13:58:22-07 - - $"
.PWD
.URL
.de RULE
.   IR \\$1 \|\|\[->]\|
.   shift
.   while \\n[.$] \{\
.      ds Prefix \f[I]
.      ds Suffix \f[R]
.      if '\\$1'{' .ds Prefix \f[R]
.      if '\\$1'}' .ds Prefix \f[R]
.      if '\\$1'[' .ds Prefix \f[R]
.      if '\\$1']' .ds Prefix \f[R]
.      if '\\$1'|' .ds Prefix \f[R]
.      if '\\$1'@' \{\
.         ds Prefix `\f[CB]
.         ds Suffix \f[R]'
.         shift
.      \}
\|\\*[Prefix]\\$1\\*[Suffix]\&
.      shift
.   \}
.   br
..
.EQ
delim $$
.EN
.H 1 "Overview"
Scheme is a dynamically typed (mostly) functional language
with a very simple syntax.
In this assignment, you will write a Silly Basic language
interpreter in Scheme.
The interpreter will read in an intermediate language program,
parse it, and then interpret it.
No looping constructs may be used,
so it is critical that certain parts use proper tail-recursion
to avoid nuking the function call stack.
.H 1 "A Silly Basic Interpreter"
.SH=BVL
.MANPAGE=LI "NAME"
sbi.scm \[em] a Silly Basic Interpreter
.MANPAGE=LI "SYNOPSIS"
.V= sbi.scm
.IR \|filename
.MANPAGE=LI "DESCRIPTION"
The SB interpreter reads in an SBIR program from the file whose
name is specified in the argument list,
stores it in a list,
and then interprets that intermediate representation.
During interpretation, numbers are read from the standard input
and results written to the standard output.
.P
Error messages are printed to the standard error.
The first error, whether during compilation or interpretation,
causes a message to be printed and the program to exit with
an exit code of 1.
.MANPAGE=LI "OPTIONS"
None.
.MANPAGE=LI "OPERANDS"
The single filename argument
specifies an SBIR program to be run.
.MANPAGE=LI "EXIT STATUS"
If the program completes without error, 0 is returned.
If not, 1 is returned.
.MANPAGE=LI "HISTORY"
BASIC (Beginner's All-purpose Symbolic Instruction Code)
was designed at Dartmouth College, NH,
by John Kemeny and Thomas Kurtz in 1965.
A variation of that language was ROM BASIC,
distributed by IBM on their original PC in 1980.
.P
(People used to spell the names of programming languages in all
upper case because keypunches,
such as the IBM 026 and 029,
did not have lower case.
Also, most printers usually had only upper case letters mounted,
such as the IBM LN print train.
A request to get upper and lower case, as with the IBM TN 
print train, would cause the job to go into an overnight queue.)
.P
This version of basic is somewhat related,
but no attempt is made to make it exactly the same.
This description of the Silly Basic programming language,
assumes that certain things are intuitively obvious.
There are only two data types in the language\(::
strings and real numbers.
Strings are used only in
.V= print
statements.
There are no string variables.
All variables are real numbers.
.MANPAGE=LI "EWD498"
And don't forget about what Dijkstra said about this language\(::
.P
Edsger W.\& Dijkstra\(::
``It is practically impossible to teach good programming to students
that have had a prior exposure to BASIC\(::
as potential programmers they are mentally mutilated beyond hope of
regeneration.''
\[em]
EWD498.
.P
The EWD manuscript archive is at
.V= http://www.cs.utexas.edu/\[ti]EWD/ .
.MANPAGE=LI "THE SBIR LANGUAGE"
This is a top-down definition of the SBIR language,
specified using a variation of Backus-Naur Form (BNF),
the format used to specify Algol-60, yet another one of
the ancient languages.
In the metanotation, 
brackets indicate that what they enclose is optional,
braces indicate that what they enclose is repeated zero or more times,
and a stick indicates alternation.
Italics indicate nonterminal symbols and token classes,
while quoted courier bold indicates literal tokens.
.P
.AL 1
.LI
.RULE Program @ ( { @ ( Linenr [ Label ] [ Statement ] @ ) } @ )
.P
A program consists of zero or more statements,
each of which
might be identified by a label.
Labels are kept in a name\%space separate from the
.IR Variable
namespace and do not conflict with each other.
The program terminates when control flows off the last statement.
A statement with neither a label nor a statement is considered
just a comment and not put into the statement list.
.LE
.MANPAGE=LI "STATEMENTS"
Statements are the only organizational structure in the language
and are executed one by one in sequence, 
except when a control transfer occurs.
There is no block structure or nesting.
.AL 1
.LI
.RULE Statement @ ( @ dim Variable Expression @ )
.P
The
.V= dim
statement creates an array given by
the variable name and inserts it into the Symbol table,
replacing any previous variable, array, or function already
in the Symbol table.
The dimension of the array is given by the expression.
.P
Unlike C,
the lower bound of the array is 1 and the upper bound is the
dimension, which may be an arbitrary expression.
The expression is rounded to the nearest integer before being
used as the bound, which must be positive.
.LI
.RULE Statement @ ( @ let Memory Expression @ )
.RULE Memory Array | Variable
.P
A
.V= let
statement makes an assignment to a variable.
The expression is first evaluated.
For a
.IR Variable ,
its value is stored into the Symbol table,
replacing whatever was there previously.
For an
.IR Array ,
the store message is sent to the vector representing the array.
If the Symbol table entry is not an array,
an error occurs.
.LI
.RULE Statement @ ( @ goto Label @ )
.P
Control transfers to the statement referred to by the
.IR Label .
An error occurs if the
.IR Label
is not defined.
.LI
.RULE Statement @ ( @ if @ ( Relop Expression Expression @ ) Label @ )
.RULE Relop @ = | @ < | @ > | @ <> | @ >= | @ <=
.P
The two
.IR Expression s
are compared according to the given
.IR Relop ,
and if the comparison is true,
control transfers to the statement, as for the
.V= goto
statement.
Note\(::
.V= <>
is the symbol for not equal.
The others should be obvious.
.LI
.RULE Statement @ ( @ print { Printable } @ )
.RULE Printable String | Expression
.P
Each of the operands is printed in sequence, with a space
before
.IR Expression
values.
A newline is output at the end of the
.V= print
statement.
.V= print
statements are the only place
.IR String s
may
occur in SBIR.
.LI
.RULE Statement @ ( @ input Memory { Memory } @ )
.P
Numeric values are read in and assigned to the input variables
in sequence.
Arguments might be elements of an array.
For each value read into a
.IR Variable,
the value is
inserted into the Symbol table under that variable's key.
For arrays, the array must already exist and the subscript not
be out of bounds.
.P
The variable
.V= inputcount
is inserted into the symbol table at
end of execution of this statement and initialized to the number
of values successfully read in.
A value of \-1 is used to indicate end of file.
If anything other than a number occurs, that token is discarded,
an error message is printed, and scanning continues.
.LE
.MANPAGE=LI "EXPRESSIONS"
Expressions consistitute the computational part of the language.
All values dealt with at the expression level are real numbers.
Invalid computations, such as division by zero and infinite results
do not cause computation to stop.
The value just propagates according to the rules of real arithmetic.
.AL 1
.LI
.RULE Expression @ ( Binop Expression Expression @ )
.RULE Expression @ ( Unop Expression @ )
.RULE Expression @ ( Function Expression @ )
.RULE Expression Constant
.RULE Expression Memory
.RULE Binop Unop | @ * | @ / | @ % | @ \[ha]
.RULE Unop @ + | @ \-
.P
.IR Constant s
are numbers.
Note that names of
.IR Function s,
.IR Array s,
and
.IR Variable s
all look like identifiers and their meaning is given by context.
In particular,
the syntax of a function call and an array subscript is ambiguous.
The code for both is just to send a message to the Symbol table
and get back a result.
.P
The expression
.V= "(% x y)"
is equivalent to
.V= "(- x (* (trunc (/ x y)) y))" .
.P
The expression
.V= "(\[ha] a b)"
is exponentiation, mathematically $ a sup b $.
.LE
.MANPAGE=LI "LEXICAL SYNTAX"
.IR Comment s
being with a semi-colon and end at the end of a line.
.IR String s
are delimited by double-quote marks
.RB ( \[Dq] ).
.IR Number s
consist of digits, an optional decimal point, and an optional exponent.
Keywords and
.IR Variable
names are atoms.
All of this is taken care of by Scheme's builtin
.V= read .
.MANPAGE=LI "BUILTIN SYMBOLS"
In addition to the operators that are part of the language,
the following functions are supported\(::
.V= abs ,
.V= acos ,
.V= asin ,
.V= atan ,
.V= ceil ,
.V= cos ,
.V= exp ,
.V= floor ,
.V= log ,
.V= log10 ,
.V= log2 ,
.V= round ,
.V= sin ,
.V= sqrt ,
.V= tan ,
.V= trunc .
There is no facility for the user to add functions to the symbol
table,
although they can be replaced.
The variables
.V= pi
and
.V= e
are also initially part of the symbol table,
and they, too, can be replaced.
.P
Thus, if you like, you can follow the law in Indiana,
according to
.IR "House Bill No.\~246, Indiana State Legislature, 1897",
which purportedly attempted to set the value of
.if t \[*p]
.if n pi
to 3
.=V [ http://en.wikipedia.org/wiki/Indiana_Pi_Bill ].
.H 1 "Program Structure"
The program will be read in by Scheme's
.V= read
function,
and represented internally as a list of statements,
each statement having its own structure.
After reading in the program,
all labels must be put into a hash table,
the key being the label itself and the value being the
particular statement it refers to.
.P
Interpretation will then proceed down the list from the
first statement to the last.
The interpreter stops when it runs off the end of the list.
A control transfer is executed by fetching the address of
a statement from the label table.
.P
All variables are either real numbers or vectors of real numbers.
Another hash table is used whose keys are variable names
and whose values are real numbers, vectors of real numbers,
or single parameter functions.
An array subscript operation and a function call are
syntactically ambiguous,
but are disambiguated at run time by checking the symbol table.
An uninitialized variable should be treated as 0.
.P
Your program should not crash,
no matter what the input.
If a detectable unforseen condition happens due to user error,
a message should be printed,
giving the name of the file and the statement number.
.P
The usual arithmetic results for infinities are printed
by the runtime system, and these should be generated wherever
possible.
Division by zero, for example, should produce one of these
quantities
.=V ( +inf.0 ,
.V= -inf.0 ,
.V= +nan.0 ).
Make sure to add 0.0 to the denominator to ensure that you
have a real number.
Also look at the functions to see which ones need special treatment.
While there is no way to input a complex number,
note that some computations, such as
.V= sqrt(-1) ,
may produce them, and thus will be written out in MzScheme's
complex number notation.
.P
The directory
.V= test-sbir
contains sample test data.
You may ignore the directory
.V= src-sb ,
which contains source code and a translator from Basic to SBIR.
You may also ignore the directory
.V= sbtran ,
which contains the SB to SBIR translator itself,
written in Ocaml.
.H 1 "Functional Style"
Programming should be done in entirely functional style,
except for maintenance of the symbol tables.
That means do not use any imperative functions except as outlined
below.
In Scheme, imperative functions end with a bang
.=V ( ! )
to indicate that an assignment is being made.
Symbol tables are created with
.V= make-hash
and updated with
.V= hash-set! .
The symbol tables are as follows\(::
.ALX a ()
.LI
.V= *identifier-table*
is used to hold all of the functions, which include the operators
as well.
This is initialized when the program begins using a
.V= for-each
loop containing a
.V= lambda .
(See the example
.V= symbols.scm ).
It also holds the value of all variables,
including
.V= pi
and
.V= e
and is updated as needed during interpretation of the program.
Arrays are created with
.V= make-vector
and updated with
.V= vector-set! .
.LI
.V= *label-table*
is used to hold addresses of each line, one level up from statements.
This is initialized by scanning the list returned by
.V= (read)
when the program begins.
.LE
.P
Except for
.V= hash-set!
and
.V= vector-set!
as outlined above,
no imperative functions are permitted.
Use functional style only.
.H 1 "Examples directory"
.VTCODE* 0 \
/afs/cats.ucsc.edu/courses/cmps112-wm/Languages/scheme/Examples/
.VTCODE* 0 \
http://www2.ucsc.edu/courses/cmps112-wm/:/Languages/scheme/Examples/
.H 1 "Running \f[CB]mzscheme\fP interactively"
It will be very convenient for you to run
.V= mzscheme 
interactively for testing purposes simply by invoking it from
the command line, as in\(::
.TVCODE* 1 "-bash-1\[Do] " "mzscheme"
.TVCODE* 1 "Welcome to Racket v6.1."
.TVCODE* 1 "> " "(expt 2 128)
.TVCODE* 1 "340282366920938463463374607431768211456"
.TVCODE* 1 "> " "\[ha]D"
To do this, be sure to put it in your 
.V= \[Do]PATH .
This can be done by putting the following lines in your
.V= \&.bashrc
or
.V= \&.bash_profile\(::
.VTCODE* 1 "export courses=/afs/cats.ucsc.edu/courses
.VTCODE* 1 "export cmps112=\[Do]courses/cmps112-wm
.VTCODE* 1 "export PATH=\[Do]PATH:\[Do]cmps112/usr/racket/bin
Of course, you may prefer to collapse these multiple shell
commands into a single line.
If you use a different shell,
then setting your
.V= \[Do]PATH
will be done differently.
.H 1 "What to Submit"
Submit two files\(::
.V= README
and
.V= sbi.scm .
It must be runnable by using it as the command word of any
shell command, and hence the execute bit must be turned on
.=V ( "chmod +x" ).
It will be run as a shell script,
and hence the first line must be the following hashbang\(::
.ds Schemeroot /afs/cats.ucsc.edu/courses/cmps112-wm/usr/racket
.VINDENT* "#!\*[Schemeroot]/bin/mzscheme -qr"
Also, make sure that the Unix command
.V= "which mzscheme"
responds with the same executable.
Important note\(::
This must be the
.E= first
line in your script, and your id should be after it.
Be sure there are no carriage return characters in the file.
.P
If you are doing pair programming, one partner should submit
.V= sbi.scm ,
but both should submit the
.V= README
and
.V= PARTNER
files, as specified in the pair programming guidlines.
.P
Be sure to use
.V= checksource
to verify basic formatting.
If you do something silly like edit using a M*cr*\[Do]*ft editor,
be sure to delete the carriage return characters before porting
to Unix.
.P
The
.V= .score/
subdirectory contains instructions to the graders.
Be sure your program runs with the test script.
If your program runs when typed in manually from the command line,
but not using the script,
you will receive no points for execution and testing.
.FINISH
