#include <iostream>
#include<deque>
#include<cstdlib>
#include<ctime>
#include<conio.h>
#include<windows.h>
using namespace std;

struct snake{
   static pair<int,int>head;
   static deque<pair<int,int>>tail;
    static int tail_length;
    char dir='w';

    void push_tail(){
        tail.push_front(head);
    }

    void move(){
        push_tail();
        if(_kbhit())
            dir=_getch();
       if(dir=='w')head.second--;
        else if(dir=='s')head.second++;
        else if(dir=='a')head.first--;
        else if(dir=='d')head.first++;
        else exit(0);

    }

};
pair<int,int>snake::head={20,10};
int snake::tail_length=1;
deque<pair<int,int>>snake::tail;

struct gmap:snake{
    int width,height;
    pair<int,int>fruit;
    int score;
    gmap(){
        width=50;
        height=20;
        fruit={10,10};
        score=0;
    }
    void location_of_fruit(){
        if(head.first==fruit.first&&head.second==fruit.second){
        srand(time(0));
        fruit={rand()%(width-3)+1,rand()%(height-3)+1};
        score+=10;
        tail_length++;
        }
    }
    void print(){
        system("cls");
        for(int j=0;j<height;++j){
            for(int i=0;i<width;++i){
                if(j==0||j==height-1)cout<<"*";
                else if(i==0||i==width-1)cout<<"*";
                else if(i==head.first&&j==head.second)cout<<"O";
                else if(i==fruit.first&&j==fruit.second)cout<<"$";
                else {
                         bool enter=0;
                    for(int z=0;z<tail_length;z++){
                        if(tail[z].first==i&&tail[z].second==j){
                            enter=1;
                            cout<<"o";
                            break;
                        }
                    }
                    if(enter==0)cout<<" ";
                }
            }
            cout<<"\n";
            }
            location_of_fruit();
            cout<<"Score : "<<score<<endl;
    }

    bool isLoser(){
        for(int i=0;i<tail_length;++i){
            if(tail[i].first==head.first&&tail[i].second==head.second)
                return 1;
        }
        return (head.first==0||head.first==width-1||head.second==0||head.second==height-1);
    }
};




int main()
{
    gmap m;
    snake s;

    while(!m.isLoser()){
      m.print();
      s.move();
    }
}
