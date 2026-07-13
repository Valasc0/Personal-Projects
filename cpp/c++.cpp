#include <iostream>

using namespace std;

void last(int num1, int num2);



int stepOne(int size, int array[]);
int stepTwo(int size, int array[]);



int main(){

    int index;
    int size;
    int nums[] = {6, 0, 1, 1, 0, 0, 0, 9, 9, 0, 1, 3, 9, 4, 2, 4, 3, 4, 4,};
    int myNum = 0;

    
    do
    {
       cout << "How many digit your number is: "; 
       cin >> size;
    } while (size <= 12 || size >= 19);
    
    
    
    for (int i = 0; i < size; )
    {
       do
       {
        cout << "Enter number " << i + 1 << "#";
        cin >> myNum;
        if (myNum > -1 && myNum < 10)
        {
            nums[i] = myNum;
            i++;
        }else{
            cout << "Invalid number";
        }
        
       } while (i < size);
       
       
        
        
    }           

    for (int num: nums){

        cout << num << endl;
    }
    

    int numsOrg[19];

    for (int i = 0; i < size; i++)
    {
        numsOrg[i] = nums[i];
    }
    
    
    
    int sum1 = stepOne(size, nums);
   
    

    int sum2 = stepTwo(size, numsOrg);

    

    last(sum1 ,sum2);
    


    return 0;
}

int stepOne(int size, int array[]){

    int temp = 0;
    int total = 0;

    for (int i = size - 2 ; i >= 0; i = i - 2)
    {
        array[i] = (array[i]) * 2;

        if (array[i] > 9 )
        {
           
             do
            { 
                array[i] = array[i] - 10;
                
                
                temp++;
                
            } while (array[i] > 9);

           
        }
        
        
        
        total += array[i];
    }
    
    
    return total + temp;
}

int stepTwo(int size , int array[]){

    int total = 0;

    for (int i = size - 1; i >= 0; i = i - 2)
    {
        
        total += array[i];
        
    }
    
    return total;

}

void last(int num1, int num2){

    int total = num1 + num2;

    if (total % 10 == 0)
    {
        cout << "It is valid" << total;
    }else
    {
        cout << "It is not valid"<< total;
    }
    
    
    
}


