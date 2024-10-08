#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include "math.h"
#include "ctype.h"
#include "string.h"

//Maze Generator on dCode.fr [online website], retrieved on 2024-09-12, 

#define OPEN 0
#define CLOSED 1

#define ROW 41
#define COL 41
#define N 0
#define E 1
#define S 2
#define W 3
#define ALL_WALLS 0
#define REMEMBER_WALLS 1
#define NO_WALLS 2

void draw_maze(int n_rows, int n_columns, int maze[ROW][COL],int x,int y,int display_mode,int visibility_matrix[ROW][COL])
{
    if(display_mode!=NO_WALLS)
    {
      
        char symbols[2];
        symbols[OPEN]=   ' ';
        symbols[CLOSED]= 'O';

        int isVisible = 1;

        
        for(int k = 0;k<ROW+2;k++){
                printf("%c ",symbols[CLOSED]);
            }
            printf("\n");
            for(int i = 0;i<COL;i++){
                
                
                //printf("|%d|",i);
                printf("%c ",symbols[CLOSED]);
                for(int k = 0;k<ROW;k++){

                    if(display_mode==REMEMBER_WALLS)
                    {
                        isVisible=visibility_matrix[i][k];
                    }

                    if(i==y && k==x){
                        printf("%c ",'P');
                    }
                    else if(k==ROW-1 && i==COL-1){
                        printf("G ");
                    }
                    else{
                        if(isVisible==1)
                        {
                            printf("%c ",symbols[maze[k][i]]);
                        }
                        else{
                            printf("%c ",symbols[0]);
                        }
                        
                    }
                    
                    //printf("%d",maze[i][k]);
                }
                printf("%c ",symbols[CLOSED]);
                printf("\n");

                

        }
        for(int k = 0;k<ROW+2;k++){
                printf("%c ",symbols[CLOSED]);
            }
            printf("\n");
    }
}


void get_walls(int n_rows, int n_columns, int maze[ROW][COL], int *dirs,int x,int y)
{
    //North
    if(y==0){
        dirs[N]=CLOSED;
    }
    else{
        dirs[N]=maze[x][y-1];
    }

    //South
    if(y==n_rows){
        dirs[S]=CLOSED;
    }
    else{
        dirs[S]=maze[x][y+1];
    }

    //East
    if(x==n_columns){
        dirs[E]=CLOSED;
    }
    else{
        dirs[E]=maze[x+1][y];
    }

    //West
    if(x==0){
        dirs[W]=CLOSED;
    }
    else{
        dirs[W]=maze[x-1][y];
    }
    
}

void update_visibility_matrix(int n_rows, int n_columns, int visibility_matrix[ROW][COL], int x,int y)
{
    
    /*1 2*/
    /* X */ /*Numbering goes clockwise from top-left*/
    /*0 3*/

    /*Initially assume all diagonals are drawable*/
    int drawable_places[4]={1,1,1,1};


    if(x==0)
    {
        drawable_places[1]=0;
        drawable_places[0]=0;
    }
    else if(x==n_columns)
    {
        drawable_places[2]=0;
        drawable_places[3]=0;
    }
    if(y==0)
    {
        drawable_places[1]=0;
        drawable_places[2]=0;
    }
    else if(x==n_rows)
    {
        drawable_places[3]=0;
        drawable_places[0]=0;
    }

    if(drawable_places[0]==1)
    {
        visibility_matrix[y-1][x-1]=1;
    }
    if(drawable_places[1]==1)
    {
        visibility_matrix[y+1][x-1]=1;
    }
    if(drawable_places[2]==1)
    {
        visibility_matrix[y+1][x+1]=1;
    }
    if(drawable_places[3]==1)
    {
        visibility_matrix[y-1][x+1]=1;
    }
    
    
    visibility_matrix[y][x]=1;
    if(x>0)
    {
        visibility_matrix[y][x-1]=1;
    }
    if(x<n_columns)
    {
        visibility_matrix[y][x+1]=1;
    }
    if(y>0)
    {
        visibility_matrix[y-1][x]=1;
    }
    if(y<n_rows)
    {
        visibility_matrix[y+1][x]=1;
    }
    }

int main(){
    
    int display_mode = NO_WALLS;

    printf("To see the whole maze, enter A.\nTo see only the parts of the maze you have already visited, enter R.\nTo see no walls other than those next to you, enter C\n");

    int visibility_matrix[ROW][COL] = {0};

    /*
    int maze[ROW][COL]= {{1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                         {1, 0, 1, 0, 1, 1, 1, 0, 1, 1 },
                         {1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
                         {0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
                         {1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
                         {1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
                         {1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
                         {1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                         {1, 1, 0, 0, 0, 0, 1, 0, 0, 1 }};*/

    int maze[ROW][COL]={{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                        {0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
                        {1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1},
                        {1,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1},
                        {1,1,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1},
                        {1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                        {1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1},
                        {1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1},
                        {1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1},
                        {1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,1},
                        {1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1},
                        {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1},
                        {1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1},
                        {1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1},
                        {1,1,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1},
                        {1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1},
                        {1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1},
                        {1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1},
                        {1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1},
                        {1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,1},
                        {1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1},
                        {1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1},
                        {1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,1,1,1,1,0,1},
                        {1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1},
                        {1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1},
                        {1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1},
                        {1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,0,1},
                        {1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
                        {1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1},
                        {1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1},
                        {1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1},
                        {1,0,1,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1},
                        {1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1},
                        {1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
                        {1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1},
                        {1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1},
                        {1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,0,1},
                        {1,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1},
                        {1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1},
                        {1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
                        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0}};
    int x = 0;
    int y = 0;

    char player_char = 'P';

    char nssymbols[2];
    nssymbols[OPEN]=' ';
    nssymbols[CLOSED]='O';

    char ewsymbols[2];
    ewsymbols[OPEN]=' ';
    ewsymbols[CLOSED]='O';

    

    int goal[2]={ROW-1,COL-1};

    char player_input='d';

    while(player_input!='q')
    {
        printf("\n");

        update_visibility_matrix(ROW, COL, visibility_matrix, x, y);

        
        draw_maze(ROW, COL,maze, x, y,display_mode,visibility_matrix);

        

        
        
        if(x==goal[0] && y==goal[1])
        {
            printf("\n=========================\n          YOU WIN\n=========================\n");
            return 1;
        }

        int dirs[4]={0,0,0,0};

        get_walls(ROW, COL,maze,dirs, x, y);

        printf("\n  %c\n",nssymbols[dirs[N]]);
        //printf("  |\n");
        printf("%c P %c\t(%d,%d)\n",ewsymbols[dirs[W]],ewsymbols[dirs[E]],x,y);
        //printf("  |\n");
        printf("  %c\n\n",nssymbols[dirs[S]]);
        printf("Input next direction (N,S,E,W) or q to quit:");
        scanf("%c",&player_input);

        if(player_input=='n'||player_input=='N')
        {
            if(dirs[N]==OPEN)
            {
                y-=1;
            }
            else{
                printf("\nCannot proceed North");
            }
        }
        else if(player_input=='s'||player_input=='S')
        {
            if(dirs[S]==OPEN)
            {
                y+=1;
            }
            else{
                printf("\nCannot proceed South");
            }
        }

        else if(player_input=='e'||player_input=='E')
        {
            if(dirs[E]==OPEN)
            {
                x+=1;
            }
            else{
                printf("\nCannot proceed East");
            }
        }
        else if(player_input=='w'||player_input=='W')
        {
            if(dirs[W]==OPEN)
            {
                x-=1;
            }
            else{
                printf("\nCannot proceed West\n");
            }
        }
        else if(player_input=='a'||player_input=='A')
        {
            display_mode=ALL_WALLS;
        }
        else if(player_input=='r'||player_input=='R')
        {
            display_mode=REMEMBER_WALLS;
        }
        else if(player_input=='c'||player_input=='C')
        {
            display_mode=NO_WALLS;
        }

    }

    

    
    return 1;
    
}

