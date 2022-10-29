#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define INITIAL_POINT "2"

int  player = 1;
char player_X, player_O;
int  win;
char move, mark;
char gameboard[10]; //it is a string

void choose_player();
void inputmove();
void newboard();
void printboard();
int  checkwin();
int  space_in_board();

int main()
{
    system("mkdir Learning_data");
    system("cls");

    while(1)
    {
        newboard();
        choose_player();
        do
        {
            if(player % 2)
            {
                player = 1;
                mark = 'X';
            }
            else
            {
                player = 2;
                mark = 'O';
            }
            system("cls");
            printboard();
            inputmove();

            if(move == '1' && gameboard[0] == ' ')
            {
                gameboard[0] = mark;
            }
            else if(move == '2' && gameboard[1] == ' ')
            {
                gameboard[1] = mark;
            }
            else if(move == '3' && gameboard[2] == ' ')
            {
                gameboard[2] = mark;
            }
            else if(move == '4' && gameboard[3] == ' ')
            {
                gameboard[3] = mark;
            }
            else if(move == '5' && gameboard[4] == ' ')
            {
                gameboard[4] = mark;
            }
            else if(move == '6' && gameboard[5] == ' ')
            {
                gameboard[5] = mark;
            }
            else if(move == '7' && gameboard[6] == ' ')
            {
                gameboard[6] = mark;
            }
            else if(move == '8' && gameboard[7] == ' ')
            {
                gameboard[7] = mark;
            }
            else if(move == '9' && gameboard[8] == ' ')
            {
                gameboard[8] = mark;
            }
            else
            {
                printf("\a\n\tINVALID MOVE!");
                fflush(stdin);
                getch();
                player --;
            }

            win = checkwin();
            if(win == 1)
            {
                system("cls");
                printboard();
                if(player == 1)
                {
                    printf("\n\n\t>> Player-X win! <<", player);
                }
                else
                {
                    printf("\n\n\t>> Player-O win! <<", player);
                }
            }
            else if(win == -1)
            {
                system("cls");
                printboard();
                printf("\n\n\t>> Draw! <<");
            }

            player ++;
        }while (win == 0);

        //Asking user if he/she wants to play again
        char ask;
        printf("\n\n\tPlay again? (y/n) --> ");
        while(1)
        {
            ask = getch();
            printf("%c",ask);
            if(ask == 'y' || ask == 'Y')
            {
                break;
            }
            else if(ask == 'n' || ask == 'N')
            {
                return 0;
            }
            else if(ask == 8)
            {
                printf(" \a");
            }
            else if(ask == 13)
            {
                printf("\t                      ");
                printf("\n\n\tPlay again? (y/n) --> ");
            }
            else
            {
                printf("\b \b\a");
            }
        }
    }
}

void choose_player()
{
    while(1)
    {
        printf("\n\n\tChoose Player-X: 1. Human");
        printf("\n\t                 2. Computer");
        printf("\n\n\t==> ");
        player_X = getch();
        printf("%c", player_X);
        if(player_X != '1' && player_X != '2')
        {
            printf("\n\tINVALID OPTION!\n");
            continue;
        }
        break;
    }

    while(1)
    {
        printf("\n\n\tChoose Player-O: 1. Human");
        printf("\n\t                 2. Computer");
        printf("\n\n\t==> ");
        player_O = getch();
        printf("%c", player_O);
        if(player_O != '1' && player_O != '2')
        {
            printf("\n\tINVALID OPTION!\n");
            continue;
        }
        break;
    }
}

void inputmove()
{
    //Input from human
    if((player == 1 && player_X == '1') || (player == 2 && player_O == '1'))
    {
        printf("\n\n\tEnter your move (1-9): ");
        move = getch();
    }

    //Input from computer
    else
    {
        FILE* file;

        //Creating folder inside learning data starts here
        char current_board[10], cmd[50] = "md Learning_data\\";
        int i, j = 0, k;

        for(i = 0; i <= 8; i ++)
        {
            if(gameboard[i] == ' ')
            {
                current_board[i] = '-';
            }
            else
            {
                current_board[i] = gameboard[i];
            }
        }
        current_board[9] = '\0';//end of string

        strcat(cmd, current_board);
        system(cmd);
        //Creating folder inside learning data ends here


        //Creating the .txt files inside "Learning_data\<FOLDER NAME>\...." starts here
        char path[50] = "Learning_data\\";
        char temp[2] = "i";
        char point[4]; //This is a string to store the point read from file
        int point_list[space_in_board()];
        int point_pose[space_in_board()];
        int sum_of_available_move_point = 0;

        for(i = 0; i < space_in_board(); i ++)
        {
            point_list[i] = 0;
            point_pose[i] = 0;
        }

        for(i = 0; i < 9; i ++)
        {
            if(gameboard[i] == ' ')
            {
                strcat(path, current_board);
                strcat(path, "\\");
                temp[0] = (char)(i + 1 + 48);
                strcat(path, temp);
                strcat(path, ".txt");
                file = fopen(path, "r");
                    if(file == NULL)//If file doesn't exist then creat file
                    {
                        file = fopen(path, "w");
                        fprintf(file, INITIAL_POINT);
                        fclose(file);

                        file = fopen(path, "r");
                        fgets(point, 3, file); 
                        sum_of_available_move_point += atoi(point);
                        point_list[j] = atoi(point);
                        fclose(file);
                    }
                    else
                    {
                        fgets(point, 3, file); 
                        sum_of_available_move_point += atoi(point);
                        point_list[j] = atoi(point);
                        fclose(file);
                    }
                    point_pose[j] = i;
                    j ++;
                if(i < 8) strcpy(path, "Learning_data\\");
            }
        }
        //Creating the .txt files inside "Learning_data\<FOLDER NAME>\...." ends here
       
        //Taking input from learning data
        int move_priority[sum_of_available_move_point];

        for(i = 0, j = 0; i < space_in_board(); i ++)
        {
            for(k = 0; k < point_list[i]; k ++)
            {
                move_priority[j] = point_pose[i] + 1;
                j ++;
            }
        }

        printf("\n\n\tEnter your move (1-9): ");
        srand(time(NULL));
        while(1)
        {
            //Note that: 1. 'move' is a char.
            //           2. adding 48 converts an int into a char.
            int move_pose = (rand() % sum_of_available_move_point);
            move = (char)(move_priority[move_pose] + 48);
            if(gameboard[(int)(move - 48) - 1] == ' ')//Accepting computer's input only if there is a blank space
            {
                gameboard[9] = '\0';
                break;
            }
            else continue;
        }
        printf("%c", move);
    }

}

void newboard()
{
    int i;
    for(i = 0; i <= 9; i ++)
    {
        if(i == 9) gameboard[i] = '\0';
        else        gameboard[i] = ' ';
    }
}

void printboard()
{
    if(player == 1)
    {
        printf("\n\tPlayer-X, your turn\n");
    }
    else
    {
        printf("\n\tPlayer-O, your turn\n");
    }

    printf("\n\t\t1|2|3");
    printf("\n\t\t4|5|6");
    printf("\n\t\t7|8|9\n");

    printf("\n\t       |       |       ");
    printf("\n\t   %c   |   %c   |   %c   ", gameboard[0], gameboard[1], gameboard[2]);
    printf("\n\t_______|_______|_______");
    printf("\n\t       |       |       ");
    printf("\n\t   %c   |   %c   |   %c   ", gameboard[3], gameboard[4], gameboard[5]);
    printf("\n\t_______|_______|_______");
    printf("\n\t       |       |       ");
    printf("\n\t   %c   |   %c   |   %c   ", gameboard[6], gameboard[7], gameboard[8]);
    printf("\n\t       |       |       ");
}

int checkwin()
{
    if     (gameboard[0] == 'X' && gameboard[1] == 'X' && gameboard[2] == 'X') return 1;
    else if(gameboard[3] == 'X' && gameboard[4] == 'X' && gameboard[5] == 'X') return 1;
    else if(gameboard[6] == 'X' && gameboard[7] == 'X' && gameboard[8] == 'X') return 1;
    else if(gameboard[0] == 'X' && gameboard[3] == 'X' && gameboard[6] == 'X') return 1;
    else if(gameboard[1] == 'X' && gameboard[4] == 'X' && gameboard[7] == 'X') return 1;
    else if(gameboard[2] == 'X' && gameboard[5] == 'X' && gameboard[8] == 'X') return 1;
    else if(gameboard[0] == 'X' && gameboard[4] == 'X' && gameboard[8] == 'X') return 1;
    else if(gameboard[2] == 'X' && gameboard[4] == 'X' && gameboard[6] == 'X') return 1;

    else if(gameboard[0] == 'O' && gameboard[1] == 'O' && gameboard[2] == 'O') return 1;
    else if(gameboard[3] == 'O' && gameboard[4] == 'O' && gameboard[5] == 'O') return 1;
    else if(gameboard[6] == 'O' && gameboard[7] == 'O' && gameboard[8] == 'O') return 1;
    else if(gameboard[0] == 'O' && gameboard[3] == 'O' && gameboard[6] == 'O') return 1;
    else if(gameboard[1] == 'O' && gameboard[4] == 'O' && gameboard[7] == 'O') return 1;
    else if(gameboard[2] == 'O' && gameboard[5] == 'O' && gameboard[8] == 'O') return 1;
    else if(gameboard[0] == 'O' && gameboard[4] == 'O' && gameboard[8] == 'O') return 1;
    else if(gameboard[2] == 'O' && gameboard[4] == 'O' && gameboard[6] == 'O') return 1;

    else if(gameboard[0] != ' ' && gameboard[1] != ' ' && gameboard[2] != ' ' && gameboard[3] != ' ' && gameboard[4] != ' ' && gameboard[5] != ' ' && gameboard[6] != ' ' && gameboard[7] != ' ' && gameboard[8] != ' ')
        return -1;

    else return 0;
}

int space_in_board()
{
    int i, spc = 0;
    for(i = 0; i < 9; i ++)
    {
        if(gameboard[i] == ' ') spc++;
    }
    return spc;
}