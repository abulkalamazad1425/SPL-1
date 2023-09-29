
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
    int over;
    int wicket;
};

struct Details
{
    char name[30];
    struct Batsman batsman[11];
    struct Bowler bowler[11];
    int sixes;
    int fours;
    int Num_Wicket;
    int total_runs;

}team[2];

int number_of_overs=5;
int number_of_players;
int toss;


void ScoreUpdate()
{
    printf("Start Match\n\n ");

    int k=0;
    for(int i=0;i<number_of_overs;i++)
    {
            int temp;
            for(int j=1;j<=6;j++)
            {
                printf("\nOver %d.%d \nEnter  the score : ",i,j);
                scanf("%d",&temp);
                if(temp == 5)
                {
                    j--;
                    temp = 1;
                }
                else if(temp == 7)
                {
                  j--;
                  temp = rand()%6 + 1;



                }
                else if(temp == 8)
                {
                    temp = rand()%4 + 1;
                }
                else if(temp == 9)
                {
                  team[0].Num_Wicket++;
                  team[0].bowler[0].wicket++;
                }


                if(temp == 6 || temp ==7)
                {
                    team[0].sixes++;
                }
                else if(temp == 4 || temp == 5)
                {
                 team[0].fours++;
                }


                team[0].total_runs += temp;
                team[0].batsman[k].runsScored += temp;
                printf("\nplayer %d : run %d\n",k,team[0].batsman[k].runsScored);
                printf("Total %d\n",team[0].total_runs);
                if((temp<4 && temp%2 != 0) || j==6){
                    if(k == team[0].Num_Wicket){
                        k=k+1;
                    }
                    else{
                        k=team[0].Num_Wicket;
                    }

                }





            }

    }





}
int main(){
    ScoreUpdate();
    return 0;

}
