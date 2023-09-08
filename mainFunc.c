#include<stdio.h>
int main(){
    printf("\n\n\t\t\tCricket Score Board\n\n");
    int option=1;
    while(option){
            printf("1. Upcoming Matches.\n");
            printf("2. Schedule a Tournament.\n");
            printf("3. Player Information.\n");
            printf("Select One( 0 for quit) : ");
            scanf("%d",&option);

            if(option==1)
                UpcomingMatch();
            else if(option == 2)
                PremierLeagueScheduling();
            else if(option == 3);
                //PlayerInformation();
            else
                printf("Choose correctly");
    }
    return 0;
}
