#include<dirent.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char* argv[])
{
    DIR *d;
    struct dirent *dir;
    if(argc!=2)
    {
        fprintf(stdout,"USAGE: %s <directory path>\n",argv[0]);
        exit(1);
    }
    d = opendir(argv[1]);
    if(d!=NULL)
    {
        while((dir = readdir(d)) != NULL)
        {
            fprintf(stdout,"%s\n",dir->d_name);
        }
    }
    else
    {
        fprintf(stderr,"ERROR: directory doesn't exist\n");
    }
    return 0;
}