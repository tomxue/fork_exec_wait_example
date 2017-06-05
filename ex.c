#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void waitprocess();

// tomxue: this is also what system() does,
// but use below process, we may have more control points
int main(int argc, char *argv[])
{
    waitprocess();
}

void waitprocess()
{
    int status = -1;
    pid_t parent = getpid();
    pid_t pid = fork();

    if (pid == -1)
    {
        // error, failed to fork()
    } 
    else if (pid > 0)
    {
        printf("this is parent, pid = %d\n", getpid());
        // -1: meaning wait for any child process.
        waitpid(-1, &status, 0);
//        wait(&status);
    }
    else 
    {
        // we are the child
        printf("this is child , pid = %d , ppid = %d\n", getpid(), getppid());
        // exec系列的函数可以将当前进程替换掉, 其后面的语句不会被执行到，成功返回0, 失败返回-1
//        execl("/bin/ls", "ls", "-al", NULL);
        sleep(1);
        _exit(6);   // exec never returns
    }

    printf("child exit status is %d\n", WEXITSTATUS(status));   //status是按位存储的状态信息，需要调用相应的宏来还原一下
    printf("end of program from pid = %d\n", getpid());
}
