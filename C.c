#include<stdio.h>
#include<ncurses.h>
#include<curses.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

typedef struct{    // Structure for two paddles 
    int x, y;
}paddle;

typedef struct{     //Structure for ball movements
    float dx, dy;   // For the change in ball position.
    float bx, by;   // For Ball position
    int sx, sy;    // For Scores
}ball;

int main ()
{
    initscr(); // Start ncurses
    int k;
    do{
    srand(time(NULL));    // srand() function used to initialize or set seeds for rand() function , allowing us to generate                                                     //  different sequence of random numbers.
    paddle p1;
    paddle p2;
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);      // Figuring out the max dimensions of the terminal.
    p1.x=2;
    p1.y=2;
    p2.x=max_x-3;
    p2.y=2;
    ball b1;
    ball b2;
    b1.bx=max_x/2;
    b1.by=max_y/2;
    ball s1;
    ball s2;
    s1.sx=0;
    s2.sx=0;
    ball d1;
    d1.dx=1;
    d1.dy=(rand() % 2 == 0) ? 1: -1; // if(rand()%2==0){d1.dy=1;} else { d1.dy=-1;}  Known as ternary operator.
    cbreak(); 
    noecho();        //This will make it so that the inputed characters are not shown in window.
    keypad(stdscr, TRUE);   // This will enable things like function keys , numberpad and things like aroow keys.
    refresh();
    nodelay(stdscr, TRUE);
    refresh();
    mvprintw(max_y/2, max_x-4,"\nPress 'Q' to exit..");
    refresh();  //
    int c=0;
    while((k=getch()) != 'q' && k!= 'Q')
    {
        erase();
     switch(k)
     {
       case 'w':                       // To move the left side paddle with 'W' and 'S' . 
       if(p1.y>1){p1.y--;}
       break;
       case 's':
       if(p1.y<max_y-4){ p1.y++;}
       break;

       case KEY_UP:                       //To move the right side paddle with arrows.
       if(p2.y>1){ p2.y--;}
       break;
       case KEY_DOWN:
       if(p2.y<max_y-4){ p2.y++;}
       break;
      }
     box(stdscr, 0, 0);    //Create a border 

     // Creating paddles and the ball.
     mvprintw(p1.y, p1.x,"|");
     mvprintw(p1.y+1, p1.x,"|");
     mvprintw(p1.y+2, p1.x,"|");
     mvprintw(p2.y, p2.x,"|");
     mvprintw(p2.y+1, p2.x,"|");
     mvprintw(p2.y+2 ,p2.x,"|");
     mvprintw(b1.by, b1.bx,"o");
     c=c+1;      // Adding the frame counter to slow down the ball movement without needing to use larger usleep() which 
     if(c>8000){                        // delays the whole program.

     // For Ball movement
     b1.by=b1.by+d1.dy;
     b1.bx=b1.bx+d1.dx;
     c=0;


    // For ball bouncing off the paddles.
    if(b1.bx == p1.x && b1.by>=p1.y && b1.by<=p1.y+2){
        d1.dx=d1.dx*-1;
    }
    if(b1.bx==p2.x && b1.by>=p2.y && b1.by<=p2.y+2){
        d1.dx=d1.dx*-1;
    }
      // For ball bouncing off the walls.  
    if(b1.by>=max_y-2){
        d1.dy= d1.dy*-1;
    }
    else if(b1.by<=1){
        d1.dy= d1.dy*-1;
    }
     }         
    mvprintw(1, max_x/2-15,"Score:  1st Player | 2nd Player");
    if(b1.bx< p1.x){ 
        s2.sx=s2.sx+1;
        b1.bx=max_x/2;
        b1.by=max_y/2;}
    if(b1.bx> p2.x){ 
        s1.sx=s1.sx+1;
        b1.bx=max_x/2;
        b1.by=max_y/2;}
    mvprintw(2, max_x/2-2,"%d",s1.sx);
    mvprintw(2, max_x/2+11,"%d",s2.sx);
    
    if(s1.sx>=5 || s2.sx>=5){
        break;
    }
    refresh();
   }
   if(s1.sx>=5){
   mvprintw(max_y/2, max_x/2-5,"Winner is Player 1");
    }
   else if(s2.sx>=5){
     mvprintw(max_y/2, max_x/2-9,"Winner is Player 2");
     }
     mvprintw(max_y/2+2, max_x/2-12,"Press 'Q' to exit or 'R' to restart ");
     
    refresh();
    nodelay(stdscr, FALSE);
    k=getch();
    } while(k == 'r' || k == 'R'); 
    endwin();  // To end ncurses
    return 0;
}
  // Compile in linux using gcc project_name.c -o project_name -lncurses
  // ./project_name

  // In windows , linux virtual machine or WSL is useful
