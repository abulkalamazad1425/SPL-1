#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct Batsman
{
    char playerName[20];
    int runsScored;
    int played_ball;
};

struct Bowler
{
    char playerName;
    int runsLossed;
    int over[2];
    int wicket;
};

struct Details
{
    char name[30];
    struct Batsman batsman[11];
    struct Bowler bowler[11];
    int sixes;
    int total_over[2];
    int fours;
    int Num_Wicket;
    int total_runs;

}team[2];

int number_of_overs=5;
int number_of_players;
int toss;
int k=0,bow=0;


void ScoreUpdate()
{
    printf("Start Match\n\n ");
    FILE *WS;
     WS = fopen("ScoreFile.txt","w");
    if(WS == NULL){
        printf("Error occur ...\nCan't open ScoreFile.txt\n");
        exit(0);
    }


    for(int i=0;i<number_of_overs;i++)
    {
            team[0].total_over[0] = i;

            int temp;
            for(int j=1;j<=6;j++)
            {
                team[0].total_over[1] = j;
                team[0].bowler[bow].over[1]=j;
                //printf("\nOver %d.%d \nEnter  the score : ",i,j);
                //scanf("%d",&temp);
                temp = rand()%10;
                fprintf(WS,"Ball %d.%d : %d\t",i,j,temp);

                if(temp == 5)
                {
                    j--;
                    team[0].total_runs += 1;
                    team[0].bowler[bow].runsLossed += temp;

                    //temp = 1;
                    //team[0].batsman[k].runsScored -= temp;
                }
                else if(temp == 7)
                {
                      j--;
                      team[0].total_runs += 1;
                      team[0].bowler[bow].runsLossed += 1;


                      int extra = rand()%7 ;
                      fprintf(WS,"extra : %d\t",extra);
                      if (extra != 5){
                             //temp=6;
                            team[0].total_runs += extra;
                            team[0].bowler[bow].runsLossed += extra;
                            team[0].batsman[k].runsScored += extra;
                            team[0].batsman[k].played_ball++;

                      }
                      team[0].batsman[k].played_ball++;

                }
                else if(temp == 8)
                {
                    temp = rand()%4 + 1;
                    fprintf(WS,"By : %d\t",temp);
                    team[0].total_runs += temp;
                    team[0].bowler[bow].runsLossed += temp;
                    team[0].batsman[k].runsScored += temp;
                    team[0].batsman[k].played_ball++;
                }
                else if(temp == 9)
                {
                      printf("Player %d has been out :");
                      int out = rand()%3 +1;
                      fprintf(WS,"out %d\t",out);

                      if(out == 1){
                        printf("\t\tBold Out\n");
                        team[0].bowler[bow].wicket++;
                        k=k+2;
                      }
                      else if(out == 2){
                        printf("\n\t\tCatch Out\n");
                        team[0].bowler[bow].wicket++;
                        k+= rand()%2+1;
                      }
                      else{
                            printf("\n\t\tRun Out\n");
                            k+= rand()%2+1;
                      }

                      team[0].Num_Wicket++;


                }
                else{


                        if(temp == 6)
                        {
                            team[0].sixes++;
                        }
                        else if(temp == 4 )
                        {
                            team[0].fours++;
                        }


                        team[0].total_runs += temp;
                        team[0].batsman[k].runsScored += temp;
                        team[0].bowler[bow].runsLossed += temp;
                        team[0].batsman[k].played_ball++;

                }
                DisplayScoreBoard();



                if( temp==1 || temp ==3 ){
                    if(k == team[0].Num_Wicket){
                        k=k+1;
                    }
                    else{
                        k=team[0].Num_Wicket;
                    }

                }
                fprintf(WS,"\n");
                 printf("\nNext..");
                 getchar();

            }

            if(k == team[0].Num_Wicket)
            {
                k=k+1;
            }
            else
            {
                k=team[0].Num_Wicket;
            }
            team[0].bowler[bow].over[0]++;
            bow++;
            if(bow==5){
                bow=0;
            }




    }
    fclose(WS);
}
void DisplayScoreBoard(){
    printf("Team - 1: \n");
    printf("Total : %d\tWicket : %d\tPlayer[%d]\tRun Lossed : %d\n",team[0].total_runs,team[0].Num_Wicket,k,team[0].batsman[k].runsScored);
    printf("over %d.%d\n",team[0].bowler[bow].over[0],team[0].bowler[bow].over[1]);
    return;
}
/*int main(){
    ScoreUpdate();
    return 0;
}*/
