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
int B_team,F_team;
int toss;
int strk,Striker1 = 0,Striker2 = 1,bow = 0;


void ScoreUpdate()
{
    FILE *WS;
     WS = fopen("ScoreFile.txt","w");
    if(WS == NULL){
        printf("Error occur ...\nCan't open ScoreFile.txt\n");
        exit(0);
    }

    printf("Start Match\n\n ");

    B_team = 0;
    F_team = 1;
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
                temp = rand()%11;
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
                            team[0].batsman[strk].runsScored += extra;
                            team[0].batsman[strk].played_ball++;

                      }
                      team[0].batsman[strk].played_ball++;
                      if(extra ==1 || extra ==3){
                            if(strk == Striker1){
                                strk = Striker2;
                            }
                            else{
                                strk = Striker1;
                            }
                      }

                }
                else if(temp == 8)
                {
                    temp = rand()%4 + 1;
                    fprintf(WS,"By : %d\t",temp);
                    team[0].total_runs += temp;
                    team[0].bowler[bow].runsLossed += temp;
                    team[0].batsman[strk].runsScored += temp;
                    team[0].batsman[strk].played_ball++;
                }
                else if(temp == 9)
                {
                      //printf("Player %d has been out :");
                      team[0].Num_Wicket++;
                      team[0].batsman[strk].played_ball++;
                      team[0].bowler[bow].wicket++;
                      int out = rand()%2 +1;
                      fprintf(WS,"out %d\t",out);
                      if(strk = Striker1){
                            Striker1 = Striker2;
                            Striker2++;
                      }
                      else
                        Striker2++;

                      if(out == 1){
                            printf("\t\tBold Out\n");


                            strk = Striker2;
                      }
                      else if(out == 2){
                            printf("\n\t\tCatch Out\n");

                            int run_half = rand()%2;
                            if(run_half){
                                strk = Striker1;
                            }
                            else
                                strk = Striker2;
                      }

                      if(team[0].Num_Wicket==10)
                        break;

                }
                else if(temp ==10){
                    printf("\n\t\tRun out\n");
                    team[0].batsman[strk].played_ball++;
                    team[0].Num_Wicket++;
                    int r_out = rand()%2+1;
                    if(r_out == 1){
                        Striker1 = Striker2;
                        Striker2++;
                    }
                    else
                        Striker2++;
                    int batting_end = rand()%2;
                    if(batting_end){
                        strk = Striker2;
                    }
                    else
                        strk = Striker1;
                    if(team[0].Num_Wicket==10)
                        break;
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
                        team[0].batsman[strk].runsScored += temp;
                        team[0].bowler[bow].runsLossed += temp;
                        team[0].batsman[strk].played_ball++;

                }
                DisplayScoreBoard();



                if( temp==1 || temp ==3 ){
                    if(strk == Striker1){
                        strk = Striker2;
                    }
                    else{
                        strk = Striker1;
                    }

                }
                fprintf(WS,"\n");
                printf("\nNext..");
                getchar();

            }
            if(team[0].Num_Wicket==10)
                        break;
            if(strk == Striker1){
                strk = Striker2;
            }
            else{
                strk = Striker1;
            }
            team[0].bowler[bow].over[0]++;
            bow++;
            if(bow==5){
                bow=0;
            }
    }
    B_team = 1;
    F_team = 0;
    strk = 0;
    Striker1 = 0;
    Striker2 = 1;
    bow = 0;
    printf("\n\n2nd INNings\n\n");
    for(int i=0;i<number_of_overs;i++)
    {
            team[1].total_over[0] = i;

            int temp;
            for(int j=1;j<=6;j++)
            {
                team[1].total_over[1] = j;
                team[0].bowler[bow].over[1]=j;
                //printf("\nOver %d.%d \nEnter  the score : ",i,j);
                //scanf("%d",&temp);
                temp = rand()%11;
                fprintf(WS,"Ball %d.%d : %d\t",i,j,temp);

                if(temp == 5)
                {
                    j--;
                    team[1].total_runs += 1;
                    team[0].bowler[bow].runsLossed += temp;

                    //temp = 1;
                    //team[0].batsman[k].runsScored -= temp;
                }
                else if(temp == 7)
                {
                      j--;
                      team[1].total_runs += 1;
                      team[0].bowler[bow].runsLossed += 1;


                      int extra = rand()%7 ;
                      fprintf(WS,"extra : %d\t",extra);
                      if (extra != 5){
                             //temp=6;
                            team[1].total_runs += extra;
                            team[0].bowler[bow].runsLossed += extra;
                            team[1].batsman[strk].runsScored += extra;
                            team[1].batsman[strk].played_ball++;

                      }
                      team[1].batsman[strk].played_ball++;
                      if(extra ==1 || extra ==3){
                            if(strk == Striker1){
                                strk = Striker2;
                            }
                            else{
                                strk = Striker1;
                            }
                      }

                }
                else if(temp == 8)
                {
                    int temp = rand()%4 + 1;
                    fprintf(WS,"By : %d\t",temp);
                    team[1].total_runs += temp;
                    team[0].bowler[bow].runsLossed += temp;
                    team[1].batsman[strk].runsScored += temp;
                    team[1].batsman[strk].played_ball++;
                }
                else if(temp == 9)
                {
                      //printf("Player %d has been out :");
                      team[1].Num_Wicket++;
                      team[1].batsman[strk].played_ball++;
                      team[0].bowler[bow].wicket++;
                      int out = rand()%2 +1;
                      fprintf(WS,"out %d\t",out);
                      if(strk = Striker1){
                            Striker1 = Striker2;
                            Striker2++;
                      }
                      else
                        Striker2++;

                      if(out == 1){
                            printf("\t\tBold Out\n");


                            strk = Striker2;
                      }
                      else if(out == 2){
                            printf("\n\t\tCatch Out\n");

                            int run_half = rand()%2;
                            if(run_half){
                                strk = Striker1;
                            }
                            else
                                strk = Striker2;
                      }

                      if(team[1].Num_Wicket==10)
                        break;

                }
                else if(temp ==10){
                    printf("\n\t\tRun out\n");
                    team[1].batsman[strk].played_ball++;
                    team[1].Num_Wicket++;
                    int r_out = rand()%2+1;
                    if(r_out == 1){
                        Striker1 = Striker2;
                        Striker2++;
                    }
                    else
                        Striker2++;
                    int batting_end = rand()%2;
                    if(batting_end){
                        strk = Striker2;
                    }
                    else
                        strk = Striker1;
                    if(team[1].Num_Wicket==10)
                        break;
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


                        team[1].total_runs += temp;
                        team[1].batsman[strk].runsScored += temp;
                        team[0].bowler[bow].runsLossed += temp;
                        team[1].batsman[strk].played_ball++;

                }
                DisplayScoreBoard();



                if( temp==1 || temp ==3 ){
                    if(strk == Striker1){
                        strk = Striker2;
                    }
                    else{
                        strk = Striker1;
                    }

                }
                fprintf(WS,"\n");
                printf("\nNext..");
                getchar();

            }
            if(team[1].Num_Wicket==10)
                        break;
            if(strk == Striker1){
                strk = Striker2;
            }
            else{
                strk = Striker1;
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
    printf("Total : %d\tWicket : %d\tPlayer[%d]\tRun Lossed : %d\n",team[0].total_runs,team[0].Num_Wicket,strk,team[0].batsman[strk].runsScored);
    printf("over %d.%d\n",team[0].bowler[bow].over[0],team[0].bowler[bow].over[1]);
    return;
}
/*int main(){
    ScoreUpdate();
    return 0;
}*/
