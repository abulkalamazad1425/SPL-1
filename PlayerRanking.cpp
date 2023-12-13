#include<bits/stdc++.h>
using namespace std;

typedef struct Batsman{
    string name;
    double run;
    double innings;
    double sR;
    string opponent;
    double rating;
}Batsman;

Batsman batsman[1000];
int num_batsman=0;

double computeRating(Batsman batter ){

    if(batter.opponent == "strong"){
        return 3*(batter.run * 0.5 + batter.innings * 0.3 + batter.sR * 0.2);
    }
    else if(batter.opponent == "medium"){
        return 2*(batter.run * 0.5 + batter.innings * 0.3 + batter.sR * 0.2);
    }
    else
        return (batter.run * 0.5 + batter.innings * 0.3 + batter.sR * 0.2);

}

int main(){
    freopen("BatsmanRank.txt", "r", stdin);

    for(int i=0;1;i++){
        cin >> batsman[i].name;
        if(batsman[i].name == "END"){
            break;
        }
        num_batsman++;
        cin >> batsman[i].run;
        cin >> batsman[i].innings;
        cin >> batsman[i].sR;
        cin >> batsman[i].opponent;
        batsman[i].rating = computeRating(batsman[i]);

    }
    for(int i=1;i<num_batsman;i++){
        for(int j=num_batsman;j-i>=0;j++){
            if(batsman[j].rating > batsman[j-1].rating){
                 Batsman B = batsman[j-1];
                batsman[j-1] = batsman[j];
                batsman[j] = B;
            }

        }
    }
    for(int i=0;i<num_batsman;i++){
        cout << batsman[i].rating;
    }

}
