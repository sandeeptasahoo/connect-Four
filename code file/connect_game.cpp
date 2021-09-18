#include<iostream>
#include<vector>
#include<cmath>
#include<stdlib.h>
#include<time.h>
using namespace std;
/*
winning input for level 3
3 4 5 5 1 6 3 2 2 4 2

submitted by subham sai behera
*/


int row=7,col=6,AILevel=4;
vector<vector<int>> game(row,vector<int>(col,0));

int randomRange(int low,int high)
{

    srand(time(0));
    int ans=rand()%(high-low);
    //cout<<"random aaignment "<<low+ans<<endl;
    return low+ans;
}

int checkAvailability()
{
    for(int i=0;i<col;i++)
    {
        if(game[0][i]==0)
        {
            return i;
        }
    }
    return -1;
}

int ChooseRandomPosition()
{
    int final_col=randomRange(0,col);
    for(int i=0;i<10;i++)
    {
        if(game[0][final_col]!=0)
        {
            final_col=randomRange(0,col);
        }
        else
        {
            return final_col;
        }
    }
    return checkAvailability();
}

void PrintMatrix()
{
    int n=game.size();
    int m=game[0].size();
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cout<<game[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

}

bool corect_Input(int player1_slot)
{
    int maxLimit=col;
    int MinLimit=1;

    if(player1_slot>=1 && player1_slot<=6)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Insert_token(int value,int column)
{
    int i=0;
    while( i<row && game[i][column]==0 )
    {
        //cout<<"searching "<<i<<endl;
        i++;
    }
    i--;
    if(i<0)
    {
        cout<<"column id filled "<<endl<<"Choose Another Column"<<endl;
        return -1;
    }
    else
    {
        game[i][column]=value;
        return i;
    }

}

int insert_AI_token(int column,int value)
{
    int i=0;
    while( i<row && game[i][column]==0 )
    {
        //cout<<"searching "<<i<<endl;
        i++;
    }
    i--;
    if(i<0)
    {
        //cout<<"column id filled "<<endl<<"Choose Another Column"<<endl;
        return -1;
    }
    else
    {
        game[i][column]=value;

        return i;
    }
}

int checkToken(int v,int r,int c,int i,int j)
{
    int num=0;
    while(r+i>=0 && r+i<row && c+j>=0 && c+j<col && game[r+i][c+j]==v)
    {
        r=r+i;
        c=c+j;
        num++;
    }
    return num;

}

bool CheckWinner(int playerIndex,int r,int c)
{
    int w=checkToken(playerIndex,r,c,0,-1);
    int e=checkToken(playerIndex,r,c,0,1);
    int n=checkToken(playerIndex,r,c,-1,0);
    int s=checkToken(playerIndex,r,c,1,0);
    int se=checkToken(playerIndex,r,c,1,1);
    int ne=checkToken(playerIndex,r,c,-1,1);
    int sw=checkToken(playerIndex,r,c,1,-1);
    int nw=checkToken(playerIndex,r,c,-1,-1);
    //cout<<"w="<<w<<", e="<<e<<", n="<<n<<", s="<<s<<", se="<<se<<", ne="<<ne<<", sw="<<sw<<", nw="<<nw<<endl;
    if(n+s>=3 || w+e>=3 || se+nw>=3 || sw+ne>=3)
    {
        //cout<<"WINNER"<<r<<c<<endl;
        return true;
    }
    else
    {
        return false;
    }

}





int decide_future(int player,int times)
{
    if(times==0)
    {
        return 0;
    }


    int enemy;
    if(player==1)
    {
       enemy=2;
    }
    else
    {
       enemy=1;
    }


    int possible_way=0,decision;
    int prow,erow;
    int i,j;
    for(i=0;i<col;i++)
    {
        if(game[0][i]==0)
        {
            erow=Insert_token(enemy,i);
            if(CheckWinner(enemy,erow,i))
            {
                //PrintMatrix();
                game[erow][i]=0;
                return -1*times*col;
            }

            for(j=0;j<col;j++)
            {
                if(game[0][j]==0)
                {
                    prow=Insert_token(player,j);

                    if(CheckWinner(player,prow,j))
                    {
                        possible_way+=times;
                    }
                    else
                    {
                        decision=decide_future(player,times/(col*col));
                        //cout<<decision<<" ";
                        possible_way+=decision;
                    }
                    //PrintMatrix();
                    game[prow][j]=0;
                }
            }
            //cout<<endl;
            game[erow][i]=0;

        }
    }
    return possible_way;
}


int AI_decision(int player)
{
    int enemy;
    if(player==1)
    {
        enemy=2;
    }
    else
    {
        enemy=1;
    }
    int row,i,x,times=pow(col,AILevel);
    int possible_ways,final_col=ChooseRandomPosition(),max_possible_ways=-1*times*col;
    for( i=0;i<col;i++)
    {
        if(game[0][i]==0)
        {
            row=Insert_token(player,i);
            if(CheckWinner(player,row,i))
            {
                game[row][i]=0;
                final_col=i;
                break;
            }
            else
            {
               possible_ways=decide_future(player,times);
                cout<<possible_ways<<" ";
                if(max_possible_ways<possible_ways)
                {
                    max_possible_ways=possible_ways;
                    final_col=i;
                }

            }
            game[row][i]=0;
        }

    }
    cout<<endl;
    return final_col+1;


}



bool Player_turn(int playerIndex,bool AIType=false)
{
    PrintMatrix();
    cout<<"Player "<<playerIndex<<" Turn"<<endl;

    bool player_turn=true;
    int player_slot;
    int row=-1;
    bool winner=false;
    while(player_turn)
    {
        //cout<<"give input ";
        if(!AIType)
        {
            cin>>player_slot;
            //cout<<" slot ";
        }
        else
        {
            player_slot=AI_decision(playerIndex);
            cout<<player_slot<<endl;
        }
        if(corect_Input(player_slot))
        {
            player_slot;
            row=Insert_token(playerIndex,player_slot-1);
            if(row!=-1)
            {
                player_turn=false;
                //cout<<"row "<<row<<", col "<<player_slot<<endl;
                winner=CheckWinner(playerIndex,row,player_slot-1);
            }
        }
        else
        {
            cout<<"Input Must be 1 to 6 "<<endl;
            cin.clear();
            cin.ignore();

        }
    }

    return winner;
}




int main()
{
    bool gameState=true;
    cout<<"Welcome To Connect Four Game \n"<<endl;

    char input='x';
    while(input!='y' && input!='n')
    {
        cout<<"play with AI?"<<endl<<"Enter y for yes else n"<<endl;
        cin>>input;
        cout<<endl;
    }
    bool AI=false;
    if(input=='y')
    {
        AI=true;
    }


    while(gameState)
    {
        if(Player_turn(1))
        {
            PrintMatrix();
            cout<<"Player 1 is the winner"<<endl;
            gameState=false;
            continue;
        }
        else
        {
            if(checkAvailability()==-1)
            {
                cout<<"NO ONE WIN"<<endl<<"ITS A TIE"<<endl;
                gameState=false;
                continue;
            }
        }
        if(Player_turn(2,AI))
        {
            PrintMatrix();
            cout<<"player 2 is the winner"<<endl;
            gameState=false;
            continue;
        }
        else
        {
            if(checkAvailability()==-1)
            {
                cout<<"NO ONE WIN"<<endl<<"ITS A TIE"<<endl;
                gameState=false;
                continue;
            }
        }

    }
}
