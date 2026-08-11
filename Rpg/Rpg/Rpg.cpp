
#include <iostream>
#include <string>
#include <ctime>


using namespace std;


class Player{
    public:
    string NAME;
    string CLASS;
    int LEVEL ;
    bool FREE = 1;
    double exp = 0;
    double maxHp ;
    double hp;
    

public:
    Player(string name, string classs, int level){

        this ->NAME = name;
        this ->CLASS = classs;
        this ->LEVEL = level; 
        this ->maxHp = 99 + level; 
        this ->hp = 99 + level;
    }
    
};


class Enemy {

    public : 
    string NAME ;
    int LEVEL ;
    double enemyHp ;

    public:

    Enemy(string name, int level){

        this -> NAME = name;
        this -> LEVEL = level;
        this -> enemyHp = 29 + level;
    }
    
};

auto EnemySpawner(int playerLevel){

    srand(time(0));
    int level = playerLevel;
    string enemyNames[15] = { "Griznak", "Skarsnik", "Zibbs", "Krik", "Sneek","Drogg", "Gorbag", "Muglok", "Kraz", "Trak","Fizle", "Glint", "Zazz", "Sprocket", "Blix"};

    int nameNumber = rand() % (15);
    int enemyLevel = rand() % playerLevel + 1;


   return Enemy(enemyNames[nameNumber] , enemyLevel);

    
}

void combat (double &enemyHp,double &hp, int enemyLevel, int level, bool &free, string &name, string &classs ){
    
    int input;
    bool isRunning = 1;
    
    do
    { 
        
        cout << "YOUR TURN" << endl;
        cout << "1-Attack" << endl;
        cout << "2-CHECK STATS" << endl;
        cout << "3-Surrender" << endl;
        cout << "Choose an action:" ;
        cin >> input;
        

        switch (input)
        {
        case 1: {
            double damage = rand() % (level*5) + 5 ;
            cout << "YOU ATTACKED" << endl;
            cout << "Your damage:" << damage << endl;
            enemyHp -= damage;
            cout << "Enemy hp :" << enemyHp << endl;
            
            break;
        }
        case 2: 
            
            cout << "----STATS----" << endl;
            cout << name << endl;
            cout << classs << endl;
            cout << "LEVEL " << level << endl;
            cout << hp << endl;
            cout << "-------------" << endl;

            
            break;
        
        case 3: 
            isRunning = 0;
            free = 0;
            cout << "You surrender" << endl;
            
            break;
        
        default:
            cout << "Choose valid number";
            break;
        }

        if (isRunning && hp > 0 && input != 2 && enemyHp > 0)
        {
            double damage = rand() % (enemyLevel*5) + 5 ;
            cout << "ENEMY ATTACKED" << endl;
            cout << "Enemy damage:" << damage << endl;
            hp -= damage;
            cout << "Enemy hp :" << hp << endl;
            
        }
        
        



        
    }while (hp > 0 && enemyHp > 0 && isRunning == 1 );
    

    
}



int main(){
    
    
    string name;
    string classs;
    int level = 1;
    double xp = 1;
    
    cout << "Enter character name: ";
    getline(cin, name);

    int input;
    do
    {
        
        cout << "Select a class" << endl;
        cout << "1-Warrior" << endl;
        cout << "2-Paladin" << endl;
        cout << "3-Wizard" << endl;
        cout << "4-Assasin" << endl;
        cout << "Your choice: ";
        cin >> input;
        
        switch (input)
        {
        case 1:
            classs = "Warrior";
            break;
        case 2:
            classs = "Paladin";
            break;
        case 3:
            classs = "Wizard";
            break;
        case 4:
            classs = "Assasin";
            break;
        default:
            cout << "Choose valid number";
            break;
        }

    } while (input < 1 || input > 4 );

    auto player = Player(name,classs,level);
    

    bool isRunning = 1;
    do
    {
        auto enemy = EnemySpawner(player.LEVEL);
        double xp = (enemy.LEVEL * 10)/player.LEVEL;
        int gain = 0;
        cout << "You fighting against " << enemy.NAME << " LvL:" << enemy.LEVEL << endl;
        cout << "Your Lvl:" << level << endl ;

        combat(enemy.enemyHp, player.hp , enemy.LEVEL , player.LEVEL, player.FREE, player.NAME, player.CLASS );
        if (player.hp > 0 && player.FREE == 1 )
        {
            player.exp += xp;
            player.hp = player.maxHp;

            if (player.exp >= 100)
            {
                do
                {
                    player.LEVEL += 1;
                    player.exp -= 100;
                    gain += 1;
                } while (player.exp >= 100);
                cout << "***YOU GOT " << gain << "LEVEL***" << endl;
            }
            
            cout << "***You got " << xp << "xp***" << endl;
            cout << endl;
            cout << endl;
            

        }else if (player.FREE == 0)
        {
            cout << "You became a prisoner" << endl;
            isRunning = 0;
        }else 
        {
            cout << "You die" << endl;
            isRunning = 0;
        }
        
        
        
    } while (isRunning);
    

    cout << "THX FOR PLAYING" << endl;
    
 






}
