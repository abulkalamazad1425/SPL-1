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
    char playerName[20];
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

int number_of_overs=2;
int B_team,F_team;
int toss;
int strk,Striker1 = 0,Striker2 = 1,bow = 0;

void getTeamAndPlayerNames()
{
    FILE *PNP;
    PNP = fopen("TeamAndPlaying11.txt","r");
    if(PNP == NULL)
    {
        printf("\n\"TeamAndPlaying11.txt\" file has an error\n");
        exit(1);
    }
    fscanf(PNP,"%s",team[0].name);
    printf("%s\n",team[0].name);
    fscanf(PNP,"%s",team[1].name);
    printf("%s\n",team[1].name);

    for(int i=0;i<2;i++)
    {
        for(int j=0;j<11;j++)
        {
            fscanf(PNP,"%s",team[i].batsman[j].playerName);
            printf("%s\n",team[i].batsman[j].playerName);
        }
        for(int j=0;j<5;j++){
            fscanf(PNP,"%s",team[i].bowler[j].playerName);
            printf("%s\n",team[i].bowler[j].playerName);
        }
    }
    fclose(PNP);
}
void ScoreUpdate()
{
    FILE *WS;
     WS = fopen("ScoreFile.txt","w");
    if(WS == NULL)
    {
        printf("Error occur ...\nCan't open ScoreFile.txt\n");
        exit(0);
    }
    B_team = 0;
    F_team = 1;
    printf("\n%s is going to bat now....\n\n",team[B_team].name);
    DisplayScoreBoard();
    for(int i=0;i<number_of_overs;i++)
    {
            team[B_team].total_over[0] = i;

            int temp;
            for(int j=1;j<=6;j++)
            {

                //printf("\nOver %d.%d \nEnter  the score : ",i,j);
                //scanf("%d",&temp);
                srand(time(0));
                temp = rand()%11;
                fprintf(WS,"Ball %d.%d : %d\t",i,j,temp);

                if(temp == 5)
                {
                    j--;
                    team[B_team].total_runs += 1;
                    team[F_team].bowler[bow].runsLossed += 1;

                    //temp = 1;
                    //team[B_team].batsman[k].runsScored -= temp;
                }
                else if(temp == 7)
                {
                      j--;
                      team[B_team].total_runs += 1;
                      team[F_team].bowler[bow].runsLossed += 1;


                      int extra = rand()%7 ;
                      fprintf(WS,"extra : %d\t",extra);
                      if (extra != 5)
                      {
                             //temp=6;
                            team[B_team].total_runs += extra;
                            team[F_team].bowler[bow].runsLossed += extra;
                            team[B_team].batsman[strk].runsScored += extra;
                            team[B_team].batsman[strk].played_ball++;

                      }
                      team[B_team].batsman[strk].played_ball++;
                      if(extra ==1 || extra ==3)
                      {
                            if(strk == Striker1)
                            {
                                strk = Striker2;
                            }
                            else
                            {
                                strk = Striker1;
                            }
                      }

                }
                else if(temp == 8)
                {
                    temp = rand()%4 + 1;
                    fprintf(WS,"By : %d\t",temp);
                    team[B_team].total_runs += temp;
                    team[F_team].bowler[bow].runsLossed += temp;
                    team[B_team].batsman[strk].runsScored += temp;
                    team[B_team].batsman[strk].played_ball++;
                }
                else if(temp == 9)
                {
                      //printf("Player %d has been out :");
                      team[B_team].Num_Wicket++;
                      team[B_team].batsman[strk].played_ball++;
                      team[F_team].bowler[bow].wicket++;
                      int out = rand()%2 +1;
                      fprintf(WS,"out %d\t",out);
                      if(strk = Striker1)
                      {
                            Striker1 = Striker2;
                            Striker2++;
                      }
                      else
                        Striker2++;

                      if(out == 1)
                      {
                            printf("\t\tBold Out\n");


                            strk = Striker2;
                      }
                      else if(out == 2)
                      {
                            printf("\n\t\tCatch Out\n");

                            int run_half = rand()%2;
                            if(run_half)
                            {
                                strk = Striker1;
                            }
                            else
                                strk = Striker2;
                      }

                      if(team[B_team].Num_Wicket==10)
                        break;

                }
                else if(temp ==10)
                {
                    printf("\n\t\tRun out\n");
                    team[B_team].batsman[strk].played_ball++;
                    team[B_team].Num_Wicket++;
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
                    if(team[B_team].Num_Wicket==10)
                        break;
                }
                else
                {
                        if(temp == 6)
                        {
                            team[B_team].sixes++;
                        }
                        else if(temp == 4 )
                        {
                            team[B_team].fours++;
                        }


                        team[B_team].total_runs += temp;
                        team[B_team].batsman[strk].runsScored += temp;
                        team[F_team].bowler[bow].runsLossed += temp;
                        team[B_team].batsman[strk].played_ball++;

                }
                team[B_team].total_over[1] = j;
                team[F_team].bowler[bow].over[1]=j;
                DisplayScoreBoard();



                if( temp==1 || temp ==3 )
                {
                    if(strk == Striker1)
                    {
                        strk = Striker2;
                    }
                    else
                        strk = Striker1;
                }

                fprintf(WS,"\n");
                //printf("\nNext..");
                //getchar();

            }
            if(team[B_team].Num_Wicket==10)
                        break;
            if(strk == Striker1)
            {
                strk = Striker2;
            }
            else
            {
                strk = Striker1;
            }
            team[F_team].bowler[bow].over[0]++;
            bow++;
            if(bow==5){
                bow=0;
            }
    }
    printf("\n%s set the target %d runs\n",team[B_team].name,team[B_team].total_runs+1);
    B_team = 1;
    F_team = 0;
    strk = 0;
    Striker1 = 0;
    Striker2 = 1;
    bow = 0;
    printf("\n%s is going to bat now....\n\n",team[B_team].name);
    DisplayScoreBoard();
    for(int i=0;i<number_of_overs;i++)
    {
            team[B_team].total_over[0] = i;

            int temp;
            for(int j=1;j<=6;j++)
            {
                team[B_team].total_over[1] = j;
                team[F_team].bowler[bow].over[1]=j;
                //printf("\nOver %d.%d \nEnter  the score : ",i,j);
                //scanf("%d",&temp);
                temp = rand()%11;
                fprintf(WS,"Ball %d.%d : %d\t",i,j,temp);

                if(temp == 5)
                {
                    j--;
                    team[B_team].total_runs += 1;
                    team[F_team].bowler[bow].runsLossed += 1;

                    //temp = 1;
                    //team[B_team].batsman[k].runsScored -= temp;
                }
                else if(temp == 7)
                {
                      j--;
                      team[B_team].total_runs += 1;
                      team[F_team].bowler[bow].runsLossed += 1;


                      int extra = rand()%7 ;
                      fprintf(WS,"extra : %d\t",extra);
                      if (extra != 5)
                      {
                             //temp=6;
                            team[B_team].total_runs += extra;
                            team[F_team].bowler[bow].runsLossed += extra;
                            team[B_team].batsman[strk].runsScored += extra;
                            team[B_team].batsman[strk].played_ball++;

                      }
                      team[B_team].batsman[strk].played_ball++;
                      if(extra ==1 || extra ==3)
                      {
                            if(strk == Striker1)
                            {
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
                    team[B_team].total_runs += temp;
                    team[F_team].bowler[bow].runsLossed += temp;
                    team[B_team].batsman[strk].runsScored += temp;
                    team[B_team].batsman[strk].played_ball++;
                }
                else if(temp == 9)
                {
                      //printf("Player %d has been out :");
                      team[B_team].Num_Wicket++;
                      team[B_team].batsman[strk].played_ball++;
                      team[F_team].bowler[bow].wicket++;
                      int out = rand()%2 +1;
                      fprintf(WS,"out %d\t",out);
                      if(strk = Striker1)
                      {
                            Striker1 = Striker2;
                            Striker2++;
                      }
                      else
                        Striker2++;

                      if(out == 1)
                      {
                            printf("\t\tBold Out\n");
                            strk = Striker2;
                      }
                      else if(out == 2)
                      {
                            printf("\n\t\tCatch Out\n");

                            int run_half = rand()%2;
                            if(run_half){
                                strk = Striker1;
                            }
                            else
                                strk = Striker2;
                      }

                      if(team[B_team].Num_Wicket==10)
                        break;

                }
                else if(temp ==10)
                {
                    printf("\n\t\tRun out\n");
                    team[B_team].batsman[strk].played_ball++;
                    team[B_team].Num_Wicket++;
                    int r_out = rand()%2+1;
                    if(r_out == 1)
                    {
                        Striker1 = Striker2;
                        Striker2++;
                    }
                    else
                        Striker2++;
                    int batting_end = rand()%2;
                    if(batting_end)
                    {
                        strk = Striker2;
                    }
                    else
                        strk = Striker1;
                    if(team[B_team].Num_Wicket==10)
                        break;
                }
                else{


                        if(temp == 6)
                        {
                            team[B_team].sixes++;
                        }
                        else if(temp == 4 )
                        {
                            team[B_team].fours++;
                        }


                        team[B_team].total_runs += temp;
                        team[B_team].batsman[strk].runsScored += temp;
                        team[F_team].bowler[bow].runsLossed += temp;
                        team[B_team].batsman[strk].played_ball++;

                }
                DisplayScoreBoard();
                if(team[B_team].total_runs>team[F_team].total_runs)
                {
                    //printf("\n\n\t\t\t\t%s win the match....\n\n",team[B_team].name);
                    //cout<<"\n\n\t\t\t\t"<<team[1].name<<" has beaten "<<team[0].name<<"........!";
                    //check=0;
                    break;
                }


                if( temp==1 || temp ==3 ){
                    if(strk == Striker1){
                        strk = Striker2;
                    }
                    else{
                        strk = Striker1;
                    }

                }
                fprintf(WS,"\n");
                //printf("\nNext..");
                //getchar();

            }
             if((team[B_team].Num_Wicket==10) || (team[B_team].total_runs > team[F_team].total_runs))
            {
                break;
            }
            if(strk == Striker1){
                strk = Striker2;
            }
            else{
                strk = Striker1;
            }
            team[F_team].bowler[bow].over[0]++;
            bow++;
            if(bow==5){
                bow=0;
            }
    }
    //if((team[B_team].Num_Wicket==10) || (team[B_team].total_runs > team[F_team].total_runs)){
                    if(team[B_team].total_runs > team[F_team].total_runs){
                        printf("\n\n\t\tCongratulations...\n\t\t%s win the match by %d wicket...\n",team[B_team].name,(10-team[B_team].Num_Wicket));
                    }
                    else if(team[B_team].total_runs == team[F_team].total_runs){
                        printf("\n\n\t\t\t\tMATCH DRAWN....\n");
                    }
                    else{
                        printf("\n\n\t\tCongratulations...\n\t\t%s win the match by %d runs...\n",team[F_team].name,(team[F_team].total_runs-team[B_team].total_runs));

                    }


            //}
    fclose(WS);
}
void DisplayScoreBoard(){
    printf("\n-------------------------------------------------------------------------------------\n");
    printf("%s vs  | %s | %d / %d.%d | \t",team[F_team].name,team[B_team].name,team[B_team].total_runs,team[B_team].total_over[0],team[B_team].total_over[1]);
    printf("%s | %d / %d.%d  |\n",team[F_team].bowler[bow].playerName,team[F_team].bowler[bow].runsLossed,team[F_team].bowler[bow].over[0],team[F_team].bowler[bow].over[1]);
    printf("-------------------------------------------------------------------------------------\n");
    printf("%s | %d / %d  | ",team[B_team].batsman[Striker1].playerName,team[B_team].batsman[Striker1].runsScored,team[B_team].batsman[Striker1].played_ball);
    printf("%s | %d / %d  |\n",team[B_team].batsman[Striker2].playerName,team[B_team].batsman[Striker2].runsScored,team[B_team].batsman[Striker2].played_ball);
    printf("-------------------------------------------------------------------------------------\n");

    printf("NEXT");
    getchar();
}
/*
int main(){
    getTeamAndPlayerNames();
    ScoreUpdate();
    return 0;
}
*/
