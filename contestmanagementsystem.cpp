#include <iostream>
using namespace std;
#include "speechmanager.h"
#include <string>

int main() {

    SpeechManager sm;
    sm.show_Menu();

    //test
    for(map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it!=sm.m_Speaker.end(); it++){
        cout << "Speaker number:" << it->first << "name:" << it->second.m_Name << "score:" << it->second.m_Score[0] << endl;
    }

    cout << "Choose the Number: " << endl;
    int choice = 0;

    while (true) {
        sm.show_Menu();

        cin >> choice;

        switch (choice)
        {
        case 1:
            sm.startSpeech();
            break;
        case 2:
            sm.showRecord();
            break;
        case 3:
            sm.clearRecord();
            break;
        case 0: //exit
            sm.exitSystem();
            break;
        
        default:
            system("cls");
            break;
        }
    }

    system("pause");
    return 0;
}