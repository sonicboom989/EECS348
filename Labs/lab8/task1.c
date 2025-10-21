#include <stdio.h>

int main(){

    int target = 0;

    while (1) {
        printf("Enter the NFL score (Enter 1 to stop): ");
        scanf("%d", &target);

        if (target == 1) {
            break;
        }

        for (int td2 = 0; td2*8 <= target; td2++){
            for(int tdfg = 0; td2*8 +tdfg*7 <= target; tdfg++){
                for(int td = 0; td2*8 + tdfg*7 + td*6 <= target; td++){
                    for(int fg = 0; td2*8 + tdfg*7 + td*6 + fg*3 <= target; fg++){

                        int used = td2*8 + tdfg*7 + td*6 + fg*3;
                        int remainder = target - used;

                        if (remainder % 2 ==0){
                        int safety = remainder / 2;
                        printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", td2, tdfg, td, fg, safety);
                        }
                    }

                }

            }

        }



    
    }

}