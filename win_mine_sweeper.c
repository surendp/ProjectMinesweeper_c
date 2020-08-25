/*
NAME:               Surendra Pandey
Student Number:     1506419
PROJECT:            Minesweeper

*/

#include <stdio.h>
#include <stdlib.h>


int n = 10;                                                              //maximun size of array in each dimension

void random_n(int  array[n][n]);                                         // fills an array with random numbers

int input_mines(int  array[n][n], int z, int m);                         // changes some numbers in the array to -1

void printing(int array[n][n]);                                          // prints an array in the screen

void assign_solved(int array[n][n]);                                     // fills '*' in any two dimensional array

int * count_solved(int array[n][n]);                                     // counts the number of marked positions and the number of positions to be unlocked

int start_game(int p_array[n][n], int  s_array[n][n]);                  // asks the input and solves the logic of the game

int solve(int p[2], int p_array[n][n]);                                 //(p[2] holds position given by the user) solves the given position returns the solved integer value

void solve_zero(int x[2], int  s_array[n][n], int  p_array[n][n]);      // (x[2] holds position passed by solve function)if solved value[returned by solve function] is zero, it unlocks
																	    // the surrounding blocks
void game_over(int  p_array[n][n], int  s_array[n][n]);                 // assigns # to all the positions containing mines

void clean();														      //clean the buffer 

int main(void)
{

    int i = 0, j = 0;       // for controlling 'for' loops
    int input=0, choose=0;  // 'input' is for starting the game and 'choose' is for choosing the level of game
    int m ;                 //for counting total number of mines
    int problem[n][n];      //for making background board
    int solved[n][n];       // for making the for ground board

    int win_loose = 0;      // stores the win or loose value

    for(;;) // runs the game until the user presses the esc button
    {
        printf("1: Press enter key to play the game\n2: Press 'c' to change the level of the game!! \n3: Press esc to end game\n");		
		input = 0;
        if((input=getchar())!= 27) // if the user presses esc game ends
        {
            // condition for choosing the level
            if(input=='c'){
                for(;;){
                    system("cls");
                    printf("Choose the level:\n1: Beginner\n2: Medium\n3: Advance\n");

                    // flushes the standard input
                    clean();
                    choose = getchar();
                    //clears the dos screen
                    system("cls");
                    if(choose=='1'){n=5; break;}
                    else if(choose=='2'){n=8;break;}
                    else if(choose=='3'){n=10;break;}
                    else{printf("Invalid input!!\n");}
                }

            }
            system("cls");

            // assigning the array to certain character to diplay
            assign_solved(solved);

            m = 0;

            //to randomize the mines differently every time we open the game
            srand( (unsigned)time( NULL ));

            // fills random numbers in problem[n][n] array
            random_n(problem);


            //mining the problem array
            for(i=0; i<50 ; i++)
            {
                if(m<(int)(n+(n/2.5)))
                {
                    m = input_mines(problem, i, m);
                }
                else
                {
                    break;
                }
            }

            //starting the game
            //returns -1 and 1 as loose and win value
            win_loose = start_game(solved, problem);

            if(win_loose == -1)
            {
                system("cls");
                game_over(problem, solved);
                printing(solved);
                printf("You loose :( \n");
				clean();
            }
            else if(win_loose == 1)
            {
				system("cls");
				printing(solved);
                printf("victory :)\n");
				clean();

            }

        }
        else
        {
            break;
        }
    }


    return 0;

}

//fills the array with random numbers
void random_n(int  array[n][n])
{

    int i = 0, j = 0;   // handling for loops

    for(i = 0; i < n; i++)
    {
        for(j = 0; j<n ; j++)
        {
            array[i][j] = ( rand() % n*5 );   // distributes the random number between 0 to (n*5) in the array
        }
    }
}



// for filling mines in the array (z holds the number that should be converted to mine , m holds the number of mines planted)
int input_mines(int  array[n][n], int z, int m){

    int i = 0, j = 0;   // for  handeling loops
    int x = 0;          //for replacing numbers with mines

    for(i = 0; i < n; i++)
    {
        for(j = 0; j<n ; j++)
        {           
            if(m <(int) (n+n/2.5))  //checks if the number of mines is not exceeding the limit
            {                
                if((z%2) == 0)      // if z is even number mining is done from the beginning and if z is odd number mining is done from the end
                {
                   
                    if((x = (int) array[i][j]) == z)
                    {
                       array[i][j] = -1;
                        m++;		// increases the number of mines planted 
                    }

                }
               
                else                
                {
                    x =(int) array[(n-1-i)][(n-1-j)];

                    if(x == z)
                    {
                        array[n-1-i][n-1-j] = -1;  // selecting the position from the end
                        m++;
                    }
                }

            }

        }
    }

    return m;   // returning the number of mines planted 
}


//prints the array in two dimensional format
void printing(int array[n][n])
{

    int i = 0, j = 0;//controls for loops

    for( i = -1; i < n; i++)
    {
        for( j = -1; j<n ; j++)
        {           
			if((i == -1) || (j == -1)){  //for giving the position numbers

				if(i == -1 && j == -1){printf("P%d ", 0);}

				else if(i == -1){
                        if(j<(n-1))
                                printf("P%d  ", (j+1));
                        else
                                printf("P%d\n\n", (j+1));
                }
				else if(j == -1){printf("P%d ", (i+1));}

			}

            else if(j!=(n-1))       // if the value of j is not last position of the row in the array printing is done in following format
            {

                if(array[i][j] == '*'  || array[i][j] == '#' || array[i][j] == '@') // checks if the position in the array holds characters to be printed
                {
                    printf("%c   ", array[i][j]);
                }
                else       // checks if the position in the array holds integer to be printed
                {
                    printf("%d   ", array[i][j]);
                }
            }
            else		 // if the value of j is last position of the row in the array printing is done in following format
            {
                if(array[i][j] == '*' || array[i][j] == '#' || array[i][j] == '@')
                {
                    printf("%c\n\n", array[i][j]);
                }
                else
                {
                    printf("%d\n\n", array[i][j]);
                }

            }
        }
    }
}


// assigns character * in the array to be shown
void assign_solved(int array[n][n])
{
    int i = 0, j = 0;

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            array[i][j] = '*';
        }
    }
}

//count_solved function returns a pointer to heap memory with two positions. it is used in start_game function
//counts the number of marked positions and the number of positions to be unlocked
//first position of heap memory holds marked positions and the second holds positions to be unlocked
int * count_solved(int array[n][n])
{
    int i = 0, j = 0; 
    int * k; // k for  storing the number of * remaining

	k = (int *) malloc(sizeof(int)*2);
	
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(array[i][j] == '@')
            {
                k[0] = k[0]+1;
            }else if(array[i][j] == '*'){
				k[1] = k[1]+1;				
			}
        }
    }
    return k;
}


// asks the input and solves the logic of the game
int start_game(int  s_array[n][n], int  p_array[n][n])
{

	int * mine_count;				 // pointer for storing the address of array returned by count_solved function
    int i = 0, j = 0;                // for handling loops
    int y[2], a=0, b=0;      	     // holds the position which is passed to the solve_zero function
    int solution = 0;                // holds the solution of the position
    int r_value = 0;                 // holds win or loose value( 1 for win and -1 for loose)
    int x[2]; 				 // for holding the position given by the player
	
    printf("Find %d mines!!\n", (int)(n+n/2.5));
    
    printing(s_array);               //printing the initial state of the game

    for(;;)
    {
		mine_count = count_solved(s_array);													 //counts the number of found mines
        if((*(mine_count + 0)==(int)(n+n/2.5)) && (*(mine_count + 1 ) == 0))				 //(mine_count + 0) holds number of marked mines and (mine_count + 1) holds remaining positions to be unlocked
        {
			free(mine_count); //free the allocated heap memory
            return 1;
        }
		
		free(mine_count);//free the allocated heap memory
        printf("give the position you want to unlock\n(For normal selection:(int1 int2 0) and For marking the position:(int1 int2 1)): ");

        for(i = 0; i<3; i++)			
        {
            scanf("%d", &x[i]);				// storing the user input to x[3] array
        }


        if(x[0] == -1 || x[1] == -1 || x[2] == -1) // if any of the input is -1 the game ends
        {
			clean();
            break;
        }
        
        if((x[0]-1)<n && (x[0]-1)>= 0 && (x[1]-1)<n && (x[1]-1)>=0) //checks if the position is valid or not
        {			
            
            if(s_array[x[0]-1][x[1]-1] == '*' || s_array[x[0]-1][x[1]-1] == '@') // for checking if the position is already selected or not
            {
				if(x[2] == 1){								//checking either to mark or open the position(if x[2] is 1 'mark' position)
					s_array[x[0]-1][x[1]-1] = '@';
					system("cls");
					printf("Find %d mines!!\n", (int)(n+n/2.5));
					printing(s_array);
				}
				else if(x[2]==0){
					solution = solve(x, p_array);			// solving the givien position

					if(solution == -1)						// checks if the solution is mine or not
					{
						s_array[x[0]-1][x[1]-1] = -1;
						r_value = -1;
						break;
					}
					else if(solution == 0)				    // checks if the solution is 0
					{
						s_array[x[0]-1][x[1]-1] = solution;							
						solve_zero(x, s_array, p_array);	// unlocks places around 0


					}
					else									
					{
						s_array[x[0]-1][x[1]-1] = solution;	
						system("cls");
						printf("Find %d mines!!\n", (int)(n+n/2.5));
						printing(s_array);
					}
				}
            }
            else
            {
                printf("Position already selected!!! \n");
            }
        }
        else
        {
            system("cls");
            printf("Invalid input!!!\n");
            printf("Find %d mines!!\n", (int)(n+n/2.5));
            printing(s_array);
        }

    }
    return r_value;		

}

//helper function for start_game function
//(p[2] holds position given by the user) solves the given position returns the solved integer value
int solve(int p[2], int  p_array[n][n])
{
    int i = 0, j = 0;   // for handeling 'for' loops
    int value = 0;      // for storing the solved value
    int x = 0, y = 0;   // for holding positions  present in the array

    for(i = -1; i<=1; i++)
    {
        for(j = -1; j<=1; j++)
        {
            x = (int) p[0];
            y = (int) p[1];

            if(p_array[x-1][y-1] == -1) // checks if the given position contains mine (if mine loop breaks)
            {
                value = -1;
                break;
            }

            x = (x - 1 +i);
            y = (y - 1 +j);

            if(!(i == 0 && j == 0))
            {                
                if((x < 0) || (x > (n-1)) || (y < 0) || (y > (n-1)))  // checking if the position is beyond boundaries
                {
                    continue;
                }
                else
                {
                    if(p_array[x][y] == -1)
                    {
                        value++;
                    }

                }

            }
        }
    }
    return value;
}

//helper function for start_game function
//(x[2] holds position given by the user) solves the given position returns the solved integer value
//it is a recursive function
void solve_zero(int x[2], int  s_array[n][n], int  p_array[n][n])
{

    int i = 0, j = 0, a = 0, b = 0;  
    int y[2], solution = 0;			// y[2] is for holding the position which is currently in process
    
    for(i=-1; i<=1; i++)            // unlocking other places around the zero
    {
        for(j=-1; j<=1; j++)
        {
            if(!(i == 0 && j == 0)) // skipping the position passed as the parameter of the function
            {
                a = x[0];
                b = x[1];

                y[0] = (a+i);       // holds the position going to be solved 
                y[1] = (b+j);
                
                if(!(((y[0]-1) < 0) || ((y[0]-1) > (n-1)) || ((y[1]-1)< 0) || ((y[1]-1) > (n-1))))// checking if the position is within the board
                {
					if(s_array[y[0]-1][y[1]-1]=='*'){  			// checks if the position is selected or not
						solution = solve(y,p_array);		
						s_array[y[0]-1][y[1]-1]=solution; 		// stores the solution to the array that is printed in the screen
						
						if(solution==0){            			// if the solution is zero again 
							solve_zero(y, s_array, p_array);	// same function is called and inception happens and all the positions aroud zero are unlocked
						}
					}
                }
            }
        }

    }
    system("cls");
    printf("Find %d mines!!\n", (int)(n+n/2.5));
    printing(s_array);

}

// assigns # to all the positions containing mines
void game_over(int  p_array[n][n], int  s_array[n][n]){ 

	int i = 0, j = 0;

    for(i = 0;i<n;i++){
        for(j=0;j<n;j++){
            if(p_array[i][j] == -1){
                s_array[i][j] = '#';
            }
        }
    }

}

// to clean the input buffer after getchar function is used
void clean(){
	int a;
	while((a=getchar())!= '\n'){a=0;};
}
