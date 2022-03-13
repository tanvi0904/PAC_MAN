#include <stdio.h> 
#include <conio.h> 
#include <windows.h>
#include <stdbool.h>
#include <time.h>

#define H 30
#define W 60
#define NR_GHOSTS 10

struct coord
{
   int x;
   int y;
};

struct PacMan 
{
   struct coord position;
   int vx;
   int vy;
   int lives;
   int food_collected;
};


struct Ghost 
{
   struct coord position;
   int vx;
   int vy;
};


struct Ghost allGhosts[NR_GHOSTS];

struct PacMan myPacMan = {
                           {
                              .x = 1,
                              .y = 1,
                           },
                           .vx = 0,
                           .vy = 0,
                           .lives = 3,
                           .food_collected = 0
                         };

char playfield[H][W] = 
{
   { "############################################################" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#        # # # # #      # # # # #        # # # # #         #" },
   { "#        #       #      #               #                  #" },
   { "#        #       #      #               #                  #" },
   { "#        # # # # #      #               #                  #" },
   { "#        #              # # # #           # # # #          #" },
   { "#        #              #                         #        #" },
   { "#        #              #                         #        #" },
   { "#        #              #                         #        #" },
   { "#        #              # # # # #        # # # # #         #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#            # # # # # #     # # # # #                     #" },
   { "#            #              #                              #" },
   { "#            #              #                              #" },
   { "#            #              #                              #" },
   { "#            #                # # # #                      #" },
   { "#            #                        #                    #" },
   { "#            #                        #                    #" },
   { "#            #                        #                    #" },
   { "#            # # # # # #     # # # # #                     #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "############################################################" }
}; 


void initialize()
{
    //food 
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if (playfield[i][j]==' ')
            playfield[i][j] = '.';
		}
	}
	
   // ghosts
   for (int i = 0; i < NR_GHOSTS; i++)
   {
		allGhosts[i].vx = 0;
		allGhosts[i].vy = 0;

		//position of ghosts
		int x,y;
		x = (rand() % (59)) + 1;
		y = (rand() % (28)) + 1;

		allGhosts[i].position.x = x;
		allGhosts[i].position.y = y;
		playfield[y][x] = 'G';
   }
}

//to use keyboard arrows
void user_input()
{
   if (_kbhit()) //check if key has been pressed 
   {
	   
        char c1 = getch();

        myPacMan.vx = 0;
        myPacMan.vy = 0;

        switch (c1)
        {
            case 72: myPacMan.vy = -1; break; // cursor up
            case 80: myPacMan.vy = +1; break; // cursor down
            case 75: myPacMan.vx = -1; break; // cursor left
            case 77: myPacMan.vx = +1; break; // cursor right
        }
	}
}


int move_figures()
{
	int rc=0; //check status of game
	
   //delete PacMan from old position
   playfield[myPacMan.position.y][myPacMan.position.x] = ' ';

   //new position coordinates
   int nx = myPacMan.vx + myPacMan.position.x;
   int ny = myPacMan.vy + myPacMan.position.y;

   //stop at wall
   if (playfield[ny][nx] == '#')
   {
      myPacMan.vx = 0;
      myPacMan.vy = 0;
   }
   
   //decreament lives on touching ghosts
   if (playfield[ny][nx] == 'G')
   {
      myPacMan.vx = 0;
      myPacMan.vy = 0;
	  myPacMan.lives--;
   }
   
   
   //to terminate game if lives = 0
   if(myPacMan.lives != 0)
   {
	   
	   //update PacMan's coordinate
	   myPacMan.position.x += myPacMan.vx;
	   myPacMan.position.y += myPacMan.vy;

	   //score 
	   if (playfield[ny][nx] == '.')
	   {
		  myPacMan.food_collected++;
	   }

	   playfield[myPacMan.position.y][myPacMan.position.x] = 'P';
	    
	   rc = 1;  //game is continuing
   }
   
   return rc;
}

void show_playfield()
{
   for (int i = 0; i < H; i++)
   {
      for (int j = 0; j < W; j++)
      {
         printf("%c", playfield[i][j]);
      }
      printf("\n");
   }

   printf("Score: %d\n", myPacMan.food_collected);
   printf("Lives: %d\n", myPacMan.lives);
}

//Set cursor position 
void set_cursor_position(int x, int y)
{
   COORD coord = { x, y };
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}


int main()
{
   system("cls");
   srand(time(0)); //to have different positions for ghosts 
   hidecursor();
   initialize();

   while (1)
   {
      user_input();
	  if(1 == move_figures())
	  {
		show_playfield();
		Sleep( 1000 / 30 );
		set_cursor_position(0,0);
	  }
	  
	  //set cursor and print final score below the playfield
	  else 
	  {
		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				printf("%c", playfield[i][j]);
			}
			printf("\n");
		}
		printf("SCORE= %d \n",myPacMan.food_collected);
		printf("GAME ENDED");
		return 0;
	  }
   }
}
