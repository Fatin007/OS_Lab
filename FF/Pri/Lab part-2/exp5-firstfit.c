#include <stdio.h>

int main() {
    int nb, nf, b[10], f[10], frag[10], i, j;
    int bf[10];   
    printf("Enter the number of blocks: ");
    scanf("%d", &nb);

    printf("Enter the number of files: ");
    scanf("%d", &nf);

    printf("Enter the size of the blocks:\n");
    for (i = 1; i <= nb; i++) {
        printf("Block %d: ", i);
        scanf("%d", &b[i]);
    }

    printf("Enter the size of the files:\n");
    for (i = 1; i <= nf; i++) {
        printf("File %d: ", i);
        scanf("%d", &f[i]);
    }

    
    for (i = 1; i <= nf; i++) {
        bf[i] = -1;  
        for (j = 1; j <= nb; j++) {
            if (b[j] >= f[i]) {   
                bf[i] = j;
                frag[i] = b[j] - f[i];
                b[j] = -1; 
                break;    
            }
        }
    }

    printf("\nFile No\tFile Size\tBlock No\tBlock Size\tFragment\n");
    for (i = 1; i <= nf; i++) {
        if (bf[i] != -1)
            printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i, f[i], bf[i], f[i] + frag[i], frag[i]);
        else
            printf("%d\t%d\t\tNot Allocated\n", i, f[i]);
    }

    return 0;
}
