#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
void sieve(int fd)
{
    int n_prime;
    if( read(fd,&n_prime,sizeof(int))==0){
        exit(0);
    }
    fprintf(2,"prime %d\n",n_prime);
    int p[2];
    pipe(p);
    if(fork()==0)
    {
        close(p[1]);
        close(fd); // 关闭旧管道的读取端
        sieve(p[0]);

    }
    else {
        close(p[0]);
        int num;
        while(read(fd,&num,sizeof(int)))
        {
            if(num%n_prime!=0)
            {
                write(p[1],&num,sizeof(int));
            }
        }
        close(p[1]);
        close(fd);
        wait(0);

    }

}
int main()
{
    int p[2];
    pipe(p);
    if(fork()==0)
    {
        close(p[1]);
        sieve(p[0]);
    }
    else{
        close(p[0]);
        for(int i=2;i<36;i++)
        {
            write(p[1],&i,sizeof(int));
        }
        close(p[1]);
        wait(0);
        exit(0);
    }
    exit(0);
}