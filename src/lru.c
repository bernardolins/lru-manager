/* C program to implement least recently used algorithm */

#include<stdio.h> 
#include<stdlib.h>

void lru(int num_window){

	int page[100] = {0},frame[50][2] = {0},i=0,j,k=0,l=0,n,a,found,pf=0,x,min,ch;
        char c;
        FILE *fp;
        fp=fopen("fifo.txt","r");
        while(fscanf(fp,"%d%c",&a,&c)!=EOF)
                page[i++]=a;
                n=i;k=1,found=0;

	for(i=0;i<num_window;i++){
                frame[i][0]=0;
                frame[i][1]=-1;
        }

        for(i=0;i<n;i++){
                found=0;
                for(j=0;j<num_window;j++)
                if(page[i]==frame[j][1]){
                        found=1;
                        x=j;
                        frame[x][0]=k++;
                }
                if(found==0){
                        min=n+1;
                        for(j=0;j<num_window;j++)
                                if(min>frame[j][0]){
                                        min=frame[j][0];
                                        x=j;
                                }
                        frame[x][1]=page[i];
                        frame[x][0]=k++;
                        pf++;
                }

                for(l=0;l<num_window;l++){
                        if(frame[l][1]==-1)
                                printf("|  ");
                        else
                                printf("|%d ",frame[l][1]);
                }
                if(found==0)
                        printf("Page Fault\n");
                else
                        printf("No page fault\n");
                        printf("\n\n");
	}
        printf("\nTotal page faults=%d\n",pf);
        pf=0;
}


int main(int argc, char *argv[]){ 
	
	if(argc!=2){printf("\n ERRO: FALTA PARAMETRO\n");return 1;}
	
	int num_window = atoi(argv[1]);
	lru(num_window);
	return 0;
}
