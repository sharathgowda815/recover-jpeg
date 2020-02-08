#include<stdio.h>

int main(int argc , char* argv[])
{
    if(argc != 2)
    {
        printf("Please give infile\n");
        return 1;
    }

    char *infile = argv[1];

    FILE *inptr = fopen(infile,"r");

    if(inptr == NULL)
    {
        printf("Unable to open file \n");
        return 2;
    }

    int count=0;
    char filename[8];
    unsigned char buffer[512];

    FILE *outptr = NULL;

    while(!feof(inptr))
    {
        int nobyte = fread(buffer,sizeof(char),512,inptr);

        if(nobyte == 512)
        {
            if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3]==0xe0 || buffer[3]==0xe1 || buffer[3]==0xe2 || buffer[3]==0xe3 || buffer[3]==0xe4 || buffer[3]==0xe5 || buffer[3]==0xe6 || buffer[3]==0xe7 || buffer[3]==0xe8 || buffer[3]==0xe9 || buffer[3]==0xea || buffer[3]==0xeb || buffer[3]==0xec || buffer[3]==0xed || buffer[3]==0xee || buffer[3]==0xef))
            {
                if(count!=0)
                {
                    fclose(outptr);
                }
            
                sprintf(filename , "%03d.jpg" , count++);
                outptr = fopen(filename,"w");

            }
        }
        else if(!feof(inptr) && nobyte != 512)
        {
            printf("Raw file corrupted in middle somewhere\n");
            return 3;
        }
        
        if(outptr != 0)
        {
            fwrite(buffer,sizeof(char),512,outptr);
        }
    }


    fclose(outptr);
    fclose(inptr);

    printf("%03d JPEG's Were Recovered\n",count);

    return 0;

}