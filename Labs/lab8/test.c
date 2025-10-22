#include <stdio.h>

int main(){
    int n, i, a=0, b=1, nextTerm;
    printf("Enter terms: ");
    scanf("%d", &n);
    printf("Series: ");
    printf("%d %d ", a,b );
    for (i = 3; i <=n; ++i){
        nextTerm = a+b;
        printf("%d ", nextTerm);
        a = b;
        b = nextTerm;
    }

}