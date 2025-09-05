#include <stdio.h>
#include "f2c.h"

#ifdef _WIN32
#include <stdlib.h>
#include <process.h>  // for getpid()
#include <io.h>       // for _isatty()
#define isatty _isatty
#else
#include <unistd.h>   // for getpid(), isatty()
#include <signal.h>   // for signal()
#endif

#define PAUSESIG 15

extern VOID f_exit(void);

#ifdef __cplusplus
extern "C" {
#endif

    static VOID waitpause(int sig) {
        (void)sig;
        return;
    }

    static VOID s_1paus(FILE* fin) {
        fprintf(stderr, "To resume execution, type go.  Other input will terminate the job.\n");
        fflush(stderr);

        if (getc(fin) != 'g' || getc(fin) != 'o' || getc(fin) != '\n') {
            fprintf(stderr, "STOP\n");
#ifdef NO_ONEXIT
            f_exit();
#endif
            exit(0);
        }
    }

    int s_paus(char* s, ftnlen n) {
        fprintf(stderr, "PAUSE");
        if (n > 0)
            fprintf(stderr, " %.*s", (int)n, s);
        fprintf(stderr, " statement executed\n");
    
        if (isatty(_fileno(stdin))) {
            s_1paus(stdin);
        }
        else {
#ifdef _WIN32
            FILE* fin = fopen("con", "r");
            if (!fin) {
                fprintf(stderr, "s_paus: can't open con!\n");
                fflush(stderr);
                exit(1);
            }
            s_1paus(fin);
            fclose(fin);
#else
            fprintf(stderr,
                "To resume execution, execute a   kill -%d %d   command\n",
                PAUSESIG, getpid());
            signal(PAUSESIG, waitpause);
            fflush(stderr);
            pause();  // this is POSIX-specific
#endif
        }

        fprintf(stderr, "Execution resumes after PAUSE.\n");
        fflush(stderr);
        return 0;
    }
#ifdef __cplusplus
}
#endif

