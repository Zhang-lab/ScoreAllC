#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

int usage();

int main(int argc, char *argv[])
{
    if(argc!=3)
        return usage();
    FILE *in, *bed, *regions, *summary;
    char line[1000], chr[100], bedchr[100], sequence[1000], field[1000];
    int start=0, end=0, pos=0, posmc=0, linepos=0, fieldpos=0, postc=0,regionmcg=0,regiontcg=0,regionmch=0,regiontch=0,totalmcg=0,totaltcg=0, totalmch=0,totaltch=0,totalmCCC=0,totaltCCC=0;
    
    in=fopen(argv[1],"r");
    bed=fopen(argv[2],"r");
    regions=fopen(strcat(argv[1],".regions.txt"),"w");
    summary=fopen(strcat(argv[1],".summary.txt"),"w");
    
    fprintf(regions,"chr\tstart\tend\tmethyl_CH\ttotal_CH\tratio_mCH\tmethylCG\ttotalCG\tratio_mCG\n");
    fprintf(summary,"sample\tmCCC\tCCC\tmCH\tCH\tmCG\tCG\tmCCC_ratio\tmCH_ratio\tmCG_ratio\n");
    
    fgets(line,1000,in);
    while(line[linepos]!='\t')
    {
        chr[linepos]=line[linepos];
        linepos++;
    }
    chr[linepos]='\0';
    linepos++;
    while(line[linepos]!='\t')
    {
        field[fieldpos]=line[linepos];
        linepos++;
        fieldpos++;
    }
    field[fieldpos]='\0';
    pos=atoi(field);
    fieldpos=0;
    linepos++;
    while(line[linepos]!='\t')
        linepos++;
    linepos++;
    while(line[linepos]!='\t')
    {
        sequence[fieldpos]=line[linepos];
        linepos++;
        fieldpos++;
    }
    linepos++;
    fieldpos=0;
    while(line[linepos]!='\t')
    {
        field[fieldpos]=line[linepos];
        linepos++;
        fieldpos++;
    }
    field[fieldpos]='\0';
    linepos++;
    fieldpos=0;
    posmc=atoi(field);
    while(line[linepos]!='\t')
    {
        field[fieldpos]=line[linepos];
        linepos++;
        fieldpos++;
    }
    field[fieldpos]='\0';
    linepos++;
    fieldpos=0;
    postc=atoi(field);
    
    while(!feof(bed))
    {
        fgets(line,1000,bed);
        linepos=fieldpos=0;
        while(line[linepos]!='\t')
        {
            bedchr[linepos]=line[linepos];
            linepos++;
        }
        bedchr[linepos]='\0';
        linepos++;
        while(line[linepos]!='\t')
        {
            field[fieldpos]=line[linepos];
            linepos++;
            fieldpos++;
        }
        field[fieldpos]='\0';
        start=atoi(field);
        linepos++;
        fieldpos=0;
        while(line[linepos]!='\0' && line[linepos]!='\n' && line[linepos] != EOF)
        {
            field[fieldpos]=line[linepos];
            fieldpos++;
            linepos++;
        }
        field[fieldpos]='\0';
        end=atoi(field);
        
        //Score region
        regionmcg=regiontcg=regionmch=regiontch=0;
        while(strcmp(chr,bedchr)==0 && pos>=start && pos<end && !feof(in))
        {
            if(sequence[1]=='G')
            {
                regionmcg+=posmc;
                regiontcg+=postc;
            }
            else
            {
                regionmch+=posmc;
                regiontch+=postc;
            }
            if(sequence[1]=='C' && sequence[2]=='C')
            {
                totalmCCC+=posmc;
                totaltCCC+=postc;
            }
            fgets(line,1000,in);
            linepos=fieldpos=0;
            while(line[linepos]!='\t')
            {
                chr[linepos]=line[linepos];
                linepos++;
            }
            chr[linepos]='\0';
            linepos++;
            while(line[linepos]!='\t')
            {
                field[fieldpos]=line[linepos];
                linepos++;
                fieldpos++;
            }
            field[fieldpos]='\0';
            pos=atoi(field);
            fieldpos=0;
            linepos++;
            while(line[linepos]!='\t')
                linepos++;
            linepos++;
            while(line[linepos]!='\t')
            {
                sequence[fieldpos]=line[linepos];
                linepos++;
                fieldpos++;
            }
            linepos++;
            fieldpos=0;
            while(line[linepos]!='\t')
            {
                field[fieldpos]=line[linepos];
                linepos++;
                fieldpos++;
            }
            field[fieldpos]='\0';
            linepos++;
            fieldpos=0;
            posmc=atoi(field);
            while(line[linepos]!='\t')
            {
                field[fieldpos]=line[linepos];
                linepos++;
                fieldpos++;
            }
            field[fieldpos]='\0';
            linepos++;
            fieldpos=0;
            postc=atoi(field);
        }
        fprintf(regions,"%s\t%d\t%d\t%d\t%d\t%f\t%d\t%d\t%f\n",bedchr,start,end,regionmch,regiontch, 1.0*regionmch/regiontch,regionmcg,regiontcg,1.0*regionmcg/regiontcg);
        totalmcg+=regionmcg;
        totaltcg+=regiontcg;
        totalmch+=regionmch;
        totaltch+=regiontch;
        
    }
    fprintf(summary,"%s\t%d\t%d\t%d\t%d\t%d\t%d\t%f\t%f\t%f\n",argv[1],totalmCCC,totaltCCC,totalmch,totaltch,totalmcg,totaltcg,1.0*totalmCCC/totaltCCC,1.0*totalmch/totaltch,1.0*totalmcg/totaltcg);
    
    return 0;
}

int usage()
{
    fprintf(stdout,"\n\tScoreAllC <allc.tsv> <regions.bed>\n\n");
    return 0;
}
