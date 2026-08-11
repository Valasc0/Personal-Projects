#include <iostream>
#include <ctime>

using namespace std;

int setPlayerBox(int* box); // set Player box number
int setPlayerPrizes(int* prize); // set Player box's prize
void getPlayerChoie(int choiceNum, int* box, int* prizes); // Get choices from player as many as Choice Num
void makeOffer(int* prize , int round); // Make offer to player
void showPlayerBox(int pNum); // Show players box Number
void showPlayerPrize(int pPrize);// Show Player box's prize 
char decide();

int main()
{   
    srand(time(0));
    
    int playerBox = NULL;
    int playerPrize = NULL;
    
    bool isRunning = true;
    
    char decision;
    
    int boxes[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22}; // Box nums
    int prizes[] ={1,10,25,50,100,250,500,750,1000,2500,5000,10000,25000,50000,100000,250000,500000,750000,1000000,1500000,2500000,5000000}; // prizes
    playerBox = setPlayerBox(boxes); // return player box num
    playerPrize = setPlayerPrizes(prizes); // return player prize
    do
    {
        cout << "Welcome to Deal or No Deal!" << endl;
        showPlayerBox(playerBox); // Show the player box num
        getPlayerChoie(5 ,boxes, prizes);
        makeOffer(prizes, 1);
        decision = decide();
        if (decision == 'y' || decision == 'Y')
        {
            break;
        }
        getPlayerChoie(4 ,boxes, prizes);
        makeOffer(prizes, 2);
        decision = decide();
        if (decision == 'y' || decision == 'Y')
        {
            break;
        }
        getPlayerChoie(4 ,boxes, prizes);   
        makeOffer(prizes, 3);
        decision = decide();
        if (decision == 'y' || decision == 'Y')
        {
            break;
        }
        getPlayerChoie(4 ,boxes, prizes);
        makeOffer(prizes, 4);
        decision = decide();
        if (decision == 'y' || decision == 'Y')
        {
            break;
        }
        getPlayerChoie(3 ,boxes, prizes);
        makeOffer(prizes, 5);
        decision = decide();
        if (decision == 'y' || decision == 'Y')
        {
            break;
        }
        getPlayerChoie(1 ,boxes, prizes);
        showPlayerPrize(playerPrize);
        isRunning = false;
    }
    while (isRunning);
    
    cout << "Thank you for playing!" << endl;
    
}

int setPlayerBox(int* box)
{
    int playerBox = rand() % 22 ; // Randomly select a box number index between 0 and 21
    int boxNum = box[playerBox]; // Set boxNum to selected num
    box[playerBox] = 0;  // Set the selected box number to 0 in array
    return boxNum; // return box number
}
int setPlayerPrizes(int* prize)
{
    int playerPrize = rand() % 22 ; // Randomly select a prize amount
    int prizeAmount = prize[playerPrize];// Set prize amount to selected amount
    //prize[playerPrize] = 0; // Set the selected prize number to 0 in array
    return playerPrize; // return prize amount
}
void showPlayerBox(int pNum)
{
    cout << "Your box number: " << pNum << endl;
}
void showPlayerPrize(int pPrize)
{
    cout << "Your box's prize: " << pPrize << endl;
}
void getPlayerChoie(int choiceNum , int* box, int* prizes)
{
    int choice;
    cout << "Remain prizes: " << endl;
    for (int i = 0 ; i < 22 ; i++)
    {
        
        if (prizes[i] != 0)
        {
            cout << "$" << prizes[i] << endl;
        }
        
    }
    cout << "Remain boxes: " << endl;
    for (int i = 0 ; i < 22 ; i++)
    {
        
        if (box[i] != 0)
        {
            cout << box[i] << endl;
        }
    }
    for (int i = 0; i < choiceNum; i++)
    {
        int prize;
        do
        {
            cout << "Make your choice " << i + 1 << ": ";
            do
            {
                cin >> choice;
            }
            while (choice < 1 || choice > 22);
        }
        while (box[choice - 1] == 0);
        do
        {
            prize = rand() % 22;
        }
        while (prizes[prize] == 0);
        cout << "Box " << box[choice - 1] <<" have $" << prizes[prize] <<  endl;
        prizes[prize] = 0;
        box[choice - 1] = 0;
        
    }
}
void makeOffer(int* prize, int round)
{
    double total = 0;
    double remainBox = 0;
    
    for (int i = 0 ; i < 22 ; i++)
    {
        if (prize[i] != 0)
        {
            total += prize[i];
            remainBox++;
        }
        
    }
    switch (round)
    {
        case 1:cout << "Bank's offer: $" << ((total / remainBox)*15)/100 << endl; break;
        case 2:cout << "Bank's offer: $" << ((total / remainBox)*25)/100 << endl; break;
        case 3:cout << "Bank's offer: $" << ((total / remainBox)*45)/100 << endl; break;
        case 4:cout << "Bank's offer: $" << ((total / remainBox)*70)/100 << endl; break;
        case 5:cout << "Bank's offer: $" << ((total / remainBox)*95)/100 << endl; break;
    }
    
}
char decide()
{
    char choice;
    do
    {
        cout << "Are you want to accept the offer? (y/n): ";
        cin >> choice;
    }
    while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');
    return choice;
}