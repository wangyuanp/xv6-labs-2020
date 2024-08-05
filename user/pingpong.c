#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    if(fork()!=0)
    {

        write(p[1],"s",1);
        close(p[1]);
        wait(0);
        char ch[2];
        read(p[0],ch,1);
        // cout << ch[0] << endl << std::flush;

        int pid=getpid();
        fprintf(1,"%d: received pong\n",pid);
        exit(0);
    }else{
        //wait(0);
        int pid=getpid();
        char ch[2];
        read(p[0],ch,1);
        // cout<<ch<<endl;
        fprintf(1,"%d: received ping\n",pid);
        write(p[1],"f",1);

        close(p[1]);
        exit(0);


    }
}