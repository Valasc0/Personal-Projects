#include <iostream>
#include <string>
#include <vector>
using namespace std;

void checkDone(const vector<string>& list, const vector <char>& status);
void addList(vector<string>&, vector <char>& status , char undone);
void operateList(vector<string>&, vector <char>& status);

int main(){     
    char done = 'O';
    char undone = 'X';
      
    int input ;
    vector <string> list;
    vector <char> status;
    do
    {
        
        cout << "----------------" << endl;
        cout << "1-Add Task" << endl;
        cout << "2-Edit Task" << endl;
        cout << "3-Check List" << endl;
        cout << "4-Quit" << endl;
        cout << "----------------" << endl;

        cout << "Select an option: " ;
        cin >> input;
        switch (input)
        {
        case 1:
            addList(list, status, undone);
            break;
        case 2:
            operateList(list, status);
            break;
        case 3:
            checkDone(list,status);
            break;
        case 4:

            cout << "Thanks for using";
            
            break;
        default:
            cout << "SELECT VALID OPERATION";

        
            break;
        }
    } while (input != 4);
    
    return 0;
}

void checkDone(const vector<string>& list, const vector <char>& status){
    if (list.empty())
    {
        cout << "List is empty" << endl;
        return;
    }
    
    cout << "TO-DO LIST" << endl;

    for (int i = 0; i < list.size(); i++)
    {
        cout << i + 1 << "- [" << status[i] << "] " << list[i] << endl;
    }
    



}
void addList(vector<string>& list, vector <char>& status , char undone){

    string task;
    cout << "Please write a task: ";

    cin.ignore();
    getline(cin, task);

    list.push_back(task);
    status.push_back(undone);

    cout << "Task added Succesfully " << endl;
    
    
    
}
void operateList(vector<string>& list, vector <char>& status){

    if (list.empty())
    {
        cout << "Nothing to delete" << endl;
    }

    for (int i = 0; i < list.size(); i++)
    {
        cout << i + 1 << "- [" << status[i] << "] " << list[i] << endl; 
    }

    int choice;

    cout << "Select a task to manage: ";

    cin >> choice;

    if (choice > list.size() || choice < 1)
    {
        cout << "Invalid task number" << endl;
    }

    int index = choice - 1;
    int operation ;

    do
    {
        cout << "-------------------------" << endl;
        cout << "1- Delete task" << endl;
        cout << "2- Toggle task (Done/Undone)" << endl;
        cout << "Select an operatiion: " << endl;
        cin >> operation;
    

        if (operation == 1)
        {
            list.erase(list.begin() + index);
            status.erase(status.begin() + index);
            cout <<"Task deleted" << endl;
        }else if (operation == 2)
        {
            status[index] =(status[index] == 'X') ? 'O' : 'X';
            cout << "Task updated" << endl;
            
       
        } 
    }while (operation != 1 && operation != 2);
    
    
    
    
    
    
    

}

