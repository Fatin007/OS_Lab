#include<stdio.h>
#include<math.h>
int main(){
    int ma,mb,bs,np,total_f=0,total_ef=0;
    printf("Enter the total memory(in Bytes):");
    scanf("%d",&ma);
    printf("Enter the block size(in Bytes):");
    scanf("%d",&bs);
    printf("Enter the number of process:");
    scanf("%d",&np);
    int p[np],f[np];
    for(int i=0;i<np;i++){
        printf("Enter memory required for process %d (in bytes)--",i+1); scanf("%d",&p[i]);
        if(p[i]<=bs){
            f[i]=bs-p[i];
        }else{
            f[i]=0;
        }
    }
    printf("Number of block available in memory -- ");scanf("%d",&mb);
    printf("Process \t Memory Required \t Allocated \t Internal Fragmentation\n");
    for(int i=0;i<np;i++){
        if(ma>=p[i] && mb!=0){
            if(bs>=p[i]){
                printf("%d \t\t %d \t\t\t YES \t\t %d \n",i+1,p[i],f[i]); total_f+=bs-p[i]; ma-=bs; mb--;
            }else{
                printf("%d \t\t %d \t\t\t NO \t\t --- \n",i+1,p[i]);
            }
        }else{
            for(i;i<np;i++) total_ef+=p[i];
            printf("Memory is Full, Remaining Process can not be accommodated\n Total Internal Fragmentation is %d \n Total External Fregmentation is %d",total_f,total_ef);
        }
    }

}