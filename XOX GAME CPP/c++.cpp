#include <iostream>
#include <ctime>

using namespace std;

void drawTiles(char array[]);
bool checkWinner(char *moves, char player, char computer);
bool checkTie(char *moves);

void playerMove(char array[], char player);
void computerMove(char array[], char computer);

int main(){

    char moves[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};

    char player = 'X';
    char computer = 'O';

    bool running = true;
    
    drawTiles(moves);

    while (running)
    {
        
        playerMove(moves,player);
        drawTiles(moves);
        if (checkWinner(moves, player,computer))
        {
            running = false;
            break;
        }else if (checkTie(moves))
        {
            running = false;
            break;
        }
        
         
        computerMove(moves,computer);
        drawTiles(moves);
        if (checkWinner(moves, player,computer))
        {
            running = false;
            break;
        }else if (checkTie(moves))
        {
            running = false;
            break;
        }
        
    }
    cout << "THANKS FOR PLAYING";


}

void drawTiles(char array[]){

    cout << array [0] << "|" << array[1] << "|" << array[2] << endl;
    cout << "-|-|-" << endl;
    cout << array [3] << "|" << array[4] << "|" << array[5] << endl;
    cout << "-|-|-" << endl;
    cout << array [6] << "|" << array[7] << "|" << array[8] << endl;
}
bool checkWinner(char *moves,char player, char computer){

    if ((moves[0] != ' ') && (moves[0] == moves[1]) && (moves[1] == moves[2]))
    {
        moves[0] == player ? cout << "YOU WIN" << endl : cout << "YOU LOSE" << endl;
         return true;
    }else if ((moves[3] != ' ') && (moves[3] == moves[4]) && (moves[4] == moves[5]))
    {
        moves[0] == player ? cout << "YOU WIN" << endl : cout << "YOU LOSE" << endl;
         return true;
    }else if ((moves[6] != ' ') && (moves[6] == moves[7]) && (moves[7] == moves[8]))
    {
        moves[0] == player ? cout << "YOU WIN" << endl : cout << "YOU LOSE" << endl;
         return true;
    }else if ((moves[0] != ' ') && (moves[0] == moves[3]) && (moves[3] == moves[6]))
    {
        moves[0] == player ? cout << "YOU WIN" << endl : cout << "YOU LOSE" << endl;
         return true;
    }else if ((moves[1] != ' ') && (moves[1] == moves[4]) && (moves[4] == moves[7]))
    {
        moves[0] == player ? cout << "YOU WIN" << endl : cout << "YOU LOSE" << endl;
         return true;
    }else if ((moves[2] != ' ') && (moves[2] == moves[5]) && (moves[5] == moves[8]))
    {
        moves[0] == player ? cout << "YOU WIN" << endl : cout << "YOU LOSE" << endl;
         return true;
    }else if ((moves[0] != ' ') && (moves[0] == moves[4]) && (moves[4] == moves[8]))
    {
        moves[0] == player ? cout << "YOU WIN" << endl : cout << "YOU LOSE" << endl;
         return true;
    }else if ((moves[2] != ' ') && (moves[2] == moves[4]) && (moves[4] == moves[6]))
    {
        moves[0] == player ? cout << "YOU WIN" << endl : cout << "YOU LOSE" << endl;
        return true;
    }
    return false;
    
    

}
bool checkTie(char *moves){

    for (int i = 0; i < 9; i++)
    {
        if (moves[i] == ' ')
        {
            return false;
        }

        
    }
    cout << "Its a tie";
    return true;
    
}

void playerMove(char array[], char player){

    int input;
    do
    {
        cout << "Please choose a tile (1-9): ";
        cin >> input;
        if (array[input - 1] == ' ')
        {
            array[input - 1] = player;
            break;
        }else {
            input = 100;
        }
        
       
    } while (input < 0 || input > 9);
    

    

}
void computerMove(char array[], char computer){

    srand(time(0));
    int input ;

    while (true)
    {
        input = rand()  % 9;
        if (array[input] == ' ')
        {
            array[input] = computer;
            break;
        }
        
    }
    
    
}