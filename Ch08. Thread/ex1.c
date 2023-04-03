#include <sys/types.h>
#include <sys/wait.h>
void pr_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d\n", WTERMSIG(status));
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

int main(void)
{
    pid_t pid;
    int status;

    if ((pid = fork()) < 0)
        printf("fork error");
    else if (pid == 0)
        exit(7);
    if (wait(&status) != pid)
        printf("wait error");
    pr_exit(status);

    if ((pid = fork()) < 0)
        printf("fork error");
    else if (pid == 0) /* child */
        abort();
    /* generates SIGABRT */
    if (wait(&status) != pid) /* wait for child */
        printf("wait error");
    pr_exit(status); /* and print its status */

    if ((pid = fork()) < 0)
        printf("fork error");
    else if (pid == 0) /* child */
        status /= 0;
    /* divide by 0 generates SIGFPE */
    if (wait(&status) != pid) /* wait for child */
        printf("wait error");
    pr_exit(status); /* and print its status */
}
