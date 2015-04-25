#ifndef ASSERT_HPP_INCLUDED
#define ASSERT_HPP_INCLUDED

/*
#define ASSERT(cond, msg) do \
{ if (!(cond)) { std::ostringstream str; str << msg; std::cerr << str.str(); std::abort(); } \
} while(0)
*/


#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <cstdlib>
///
/// \file assert.h
/// \brief Support for C and C++ assertion-based guard clauses and debugging.
///
/// This file includes defines that report probable errors via \c STDERR
/// including execution context (file and line number). Inline functions that
/// do the actual printing are included here for speed.
/// \version 1.0
/// \example examples/assert.c
///

/**
\mainpage Using assert.h
The assert.h macro set is intended for "antibugging", i.e.,
proactive coding to avoid potential runtime problems.
One embeds macros into one's code to check for preconditions,
so that at runtime, the program dies with an error message
if preconditions aren't met.
\section Using ASSERT
The \c ASSERT macro allows one to print an error message and die if
an assertion fails. For example, suppose that the line

    ASSERT(foo>=0);

is line 42 of the file "foo.c".
If foo>=0, the assertion has no effect. If not, the message:

    Assertion foo>=0 failed at line 42 of file foo.c

is printed and the program terminates with exit code 1.

\section POSIT
\c POSIT differs from \c ASSERT only in whether the program terminates.
A call to \c POSIT reports assertion failure without terminating the
program in question. For example, in the same situation as the above,
the line

    POSIT(foo>=0)

prints the same thing as the above, but the program continues.

\section DIE
\c DIE allows the programmer to check more complex assertions than are possible
in an inline function. For example, suppose that

    DIE("list not well-formed");

occurs at line 42 of file "foo.c". This will print

    Fatal error: list not well-formed at line 42 of foo.c

and the program will terminate with exit code 1.

\section CARP
\c CARP allows the programmer to report non-fatal errors without
terminating the program. For example,

    CARP("list not well-formed");

will print

    Non-fatal error: list not well-formed at line 42 of foo.c

and the program will continue.

*/

///
/// Print the result of an expression, including execution context.
/// \param[in] bool An expression to test, which should represent an
///            integer value.
/// \pre \c bool is a boolean expression that evaluates to an integer
/// \post Whether \c bool represents success or failure is printed to \c STDERR.
/// \test \c CHECK(0) should print
///       "ERROR: 0 failed in line ??? of file ???"
///       where ??? are the appropriate file name and line number, respectively.
/// \test \c CHECK(1) should print
///       "1 succeeded in line ??? of file ???"
///       where \c ??? are the appropriate file name and line number,
///       respectively.
///

#define CHECK(bool)   check((bool),#bool,__FILE__,__LINE__)

///
/// Test an expression and exit the program if it is false.
/// \param[in] bool An expression to test, which should represent an
///            integer value.
/// \pre  \c bool is a boolean expression that evaluates to an integer
/// \post If \c bool evaluates to 0 (FALSE), error is printed to \c STDERR
///       and the program terminates
/// \test \c ASSERT(1) should print nothing.
/// \test \c ASSERT(0) should print
///       "Assertion 0 failed in line ??? of file ???"
///       where \c ??? are the appropriate file name and line number,
///       respectively. It should then terminate execution with exit code 1.
///

#define ASSERT(bool)  assert((bool),#bool,__FILE__,__LINE__)

///
/// Test an expression and print a warning if it is false.
/// \param[in] bool An expression to test, which should represent an
///            integer value.
/// \pre  \c bool is a boolean expression that evaluates to an integer
/// \post If \c bool evaluates to 0 (FALSE), a warning is printed to \c STDERR.
/// \test \c POSIT(1) should print nothing and continue execution.
/// \test \c POSIT(0) should print
///       "Assertion 0 failed in line ??? of file ???"
///       where ??? are the appropriate file name and line number, respectively.
///       Unlike \c ASSERT(0), it should continue execution.
///

#define POSIT(bool)   posit((bool),#bool,__FILE__,__LINE__)

///
/// Print a fatal error message and exit the program, with execution context.
/// \param[in] reason A text string explaining why the program died.
/// \pre  \c reason is a null-terminated character string.
/// \post The reason is printed to \c STDERR with file and line context,
///       and the program terminates with exit code 1.
/// \test DIE("for no good reason") should print
///       "Fatal error: for no good reason at line ??? of file ???"
///       where ??? are the appropriate file name and line number, respectively.
///       The program should terminate with exit code 1.
///

#define DIE(reason)   die((reason),__FILE__,__LINE__)

///
/// Print an error message with execution context, but continue execution.
/// \param[in] reason An informative text string.
/// \pre  \c reason is a null-terminated character string.
/// \post \c reason is printed to \c STDERR with file and line context.
/// \test CARP("for no good reason") should print
///       "Non-fatal error: for no good reason at line ??? of file ???"
///       where ??? are the appropriate file name and line number, respectively.
///

#define CARP(reason)  carp((reason),__FILE__,__LINE__)

///
/// \brief Print the result of a boolean expression to \c STDERR.
///
/// This function prints the result of a boolean expression on
/// \c STDERR, with both file and line context information. It is
/// called only by the \c CHECK(expr) macro, which instantiates
/// parameters 2-4 from its context.
/// \param[in] boolean A boolean expression to test.
/// \param[in] boolstr The stringification of the expression, for printing.
/// \param[in] file The file in which the assertion is checked.
/// \param[in] line The line number of the file at which the assertion occurs.
/// \pre  Assured by the \c CHECK(expr) macro.
/// \post Whether \c bool represents success or failure is printed to
/// \c STDERR.
///

inline void check(int boolean, char *boolstr, char *file, int line) {
    if (!boolean) {
        fprintf(stderr,"ERROR: %s failed in line %d of file %s\n",
                boolstr,line,file);
    } else {
	fprintf(stderr,"%s succeeded in line %d of file %s\n",
                boolstr,line,file);
    }
}

///
/// \brief Test a boolean assertion and exit the program if it fails.
///
/// This function checks a boolean assertion and prints detailed information
/// on any failures to \c STDERR, before it exits. It is called only from the
/// \c ASSERT macro, which instantiates parameters 2-4 from its context.
/// \param[in] boolean A boolean expression to test.
/// \param[in] boolstr The stringification of the expression, for printing.
/// \param[in] file The file in which the assertion is checked.
/// \param[in] line The line number of the file at which the assertion occurs.
/// \pre  Assured by the \c ASSERT macro.
/// \post If \c bool evaluates to 0 (FALSE), error is printed to \c STDERR
///       and the program terminates
/// \test assert(1,"foobar", "/bin/foo.c", 42) should print nothing and return.
/// \test assert(0,"foobar", "/bin/foo.c", 42) should print
///       "Assertion foobar failed in line 42 of file /bin/foo.c"
///       and then the program should terminate with exit code 1.
///

inline void assert(int boolean, char *boolstr, char *file, int line) {
    if (!boolean) {
        FILE * pFile;

        // Open file in 'append' mode
        pFile = fopen ("Assert.txt","a");

        // Print warning
        fprintf(pFile,"Assertion %s failed in line %d of file %s\n",
                boolstr,line,file);

        fclose (pFile);
        printf("\n\nAssertion %s failed in line %d of file %s\n",
                boolstr,line,file);
        // forced program pause instead of exit
        while(1){}
        //exit(1);        /* exit(0) means correct execution! */
    }
}

///
/// \brief Test a boolean assertion and report any failures without exiting.
///
/// This function checks a boolean assertion and prints detailed information
/// on any failures to \c STDERR, but does not exit. It is called only from the
/// \c POSIT macro, which instantiates parameters 2-4 from its context.
/// \param[in] boolean A boolean expression to test.
/// \param[in] boolstr The stringification of the expression, for printing.
/// \param[in] file The file in which the assertion is checked.
/// \param[in] line The line number of the file at which the assertion occurs.
/// \pre  Assured by the \c POSIT macro.
/// \post If \c bool evaluates to 0 (FALSE), a warning is printed to \c STDERR.
///       Otherwise nothing happens and execution continues.
/// \test posit(1, "foobar", "/bin/foo.c", 42) should print nothing and return.
/// \test posit(0, "foobar", "/bin/foo.c", 42) should print
///       "Assertion foobar failed in line 42 of file /bin/foo.c",
///       after which execution continues.
///

inline int posit(int boolean, char *boolstr, char *file, int line) {
    if (!boolean)
        fprintf(stderr,"Assertion %s failed in line %d of file %s\n",
                boolstr,line,file);
    return boolean;
}

///
/// \brief Log a fatal error to \c STDERR and exit the program.
///
/// This function prints a message to \c STDERR and dies.
/// It is called only from the \c DIE macro, which instantiates
/// parameters 2-3 from its context.
/// \param[in] condition A description of the failure condition.
/// \param[in] file The file in which the assertion is checked.
/// \param[in] line The line number of the file at which the assertion occurs.
/// \pre  Assured by the \c DIE macro.
/// \post The reason is printed to \c STDERR with file and line context,
///       and the program terminates with exit code 1.
/// \test die("for no reason", "/bin/foo.c", 42) should print
///       "Fatal error: for no reason at line 42 of file /bin/foo.c"
///       and the program should terminate with exit code 1.
///
/*
inline void die(char *condition, char *file, int line) {
    fprintf(stderr,"Fatal error: %s at line %d of file %s\n",
        condition,line,file);
    exit(1);
}
*/
///
/// \brief Log a non-fatal error to \c STDERR, including file and line information.
///
/// This function prints a message to \c STDERR with both file and line
/// information included. It is called only from the \c CARP macro,
/// which instantiates parameters 2-3 from the context in which it is called.
/// \param[in] condition A description of the failure condition.
/// \param[in] file The file in which the assertion is checked.
/// \param[in] line The line number of the file at which the assertion occurs.
/// \pre  Assured by the \c CARP macro.
/// \post The reason is printed to \c STDERR with file and line context.
/// \test carp("for no reason", "/bin/foo.c", 42) should print
///       "Non-fatal error: for no reason at line 42 of file /bin/foo.c"
///       and the program should terminate with exit code 1.
///

inline void carp(char *condition, char *file, int line) {
    fprintf(stderr,"Non-fatal error: %s at line %d of file %s\n",
	condition,line,file);
}


#endif // ASSERT_HPP_INCLUDED
