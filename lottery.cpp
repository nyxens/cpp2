#include <iostream>
using namespace std;
int main(){
    int choice;
    int lottery;
    int attempt = 0;
    lottery = (rand() % 10) + 1;
    cout << "Welcome to the Lottery Game!" << endl;
    do{
        cout << " Enter your number (1 - 10): ";
        cin >> choice;
        if(choice < 1||choice > 10){
            cout << "Invalid number" << endl;
            continue;
        }
        attempt++;
        if(choice == lottery){
            cout << "You won! in " << attempt << " attempts" << endl;
            break;
        }else{
            cout << "Sorry Try again!" << endl;
        }
    }while(true);
    while(true){
        for(int i = 0;i <= 10; i++){
            if(i==lottery){
                cout << "The Lottery number was " << i << endl;
            }
        }
        break;
    }
    return 0;
}