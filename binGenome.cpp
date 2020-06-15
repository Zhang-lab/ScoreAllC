#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cstdlib>

using namespace std;

int usage();

int main(int argc, char *argv[])
{
    if (argc!=4)
        return usage();
    
    FILE *in, *out;
    
    char line[1000], chrname[1000], s_chrlen[1000];
    int i_chrlen=0, start=0, linepos=0, fieldpos=0, binsize=0;
    
    in=fopen(argv[1], "r");
    out=fopen(argv[2],"w");
    binsize=atoi(argv[3]);
    
    while(!feof(in))
    {
        fgets(line,1000,in);
        if(!feof(in))
        {
            linepos=fieldpos=0;
            while(line[linepos]!='\t')
            {
                chrname[linepos]=line[linepos];
                linepos++;
            }
            chrname[linepos]='\0';
            linepos++;
            while(linepos<strlen(line))
            {
                s_chrlen[fieldpos]=line[linepos];
                linepos++;
                fieldpos++;
            }
            s_chrlen[fieldpos]='\0';
            i_chrlen=atoi(s_chrlen);
            fprintf(stdout,"%s\t%d\n",chrname,i_chrlen);
            for (int i=0; i<i_chrlen-binsize; i+=binsize)
                fprintf(out,"%s\t%d\t%d\n",chrname,i,i+binsize);
            fprintf(out,"%s\t%d\t%d\n",chrname,i_chrlen-(i_chrlen%binsize),i_chrlen);
        }
    }
    return 0;
    
}

int usage()
{
    fprintf(stdout,"\n\tbinGenome <in.chr.names.sizes> <out.bin.bed> <binsize>\n\n");
    return 0;
}
