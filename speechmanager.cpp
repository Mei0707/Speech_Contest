#include "speechmanager.h"

//Constructor
SpeechManager::SpeechManager(){
    this->initSpeech();
    this->createSpeaker();
    this->m_Index = 1;
    this->loadRecord();
}

void SpeechManager::show_Menu() {
    cout << "**************************************************" << endl;
    cout << "********** Welcome to the Speech Contest ********" << endl;
    cout << "********** 1. Start the Contest *****************" << endl;
    cout << "********** 2. Contest Record ********************" << endl;
    cout << "********** 3. Clean the Record ******************" << endl;
    cout << "********** 0. Exit ******************************" << endl;
    cout << "*************************************************" << endl;
    cout << endl;
}

void SpeechManager::exitSystem() {
    cout << "Good Bye" << endl;
    system("pause");
    exit(0);
}

void SpeechManager::initSpeech() {
    this->v1.clear();
    this->v2.clear();
    this->vVictory.clear();
    this->m_Speaker.clear();


}

void SpeechManager::createSpeaker() {
    string nameSeed = "ABCDEFGHIJKL";
    for (int i = 0; i < nameSeed.size(); i++) {
        string name = "Speaker";
        name += nameSeed[i];

        //create specfic speaker
        Speaker sp;
        sp.m_Name = name;

        for(int j = 0; j < 2; j++) {
            sp.m_Score[j] = 0;
        }

        //create speaker number, and put in v1
        this->v1.push_back(i + 10001);
        //put in map
        this->m_Speaker.insert(make_pair(i + 10001, sp));
    }
}

void SpeechManager::startSpeech() {
    //First Round
    //1.draw
    this->speechDraw();
    //2.compete
    this->speechContest();
    //3.result
    this->showScore();
    //Second Round
    this->m_Index++;
    //1.draw
    this->speechDraw();
    //2.compete
    this->speechContest();
    //3.last result
    this->showScore();
    //4.save record
    this->saveRecord();

    cout << "All the contest finished!" << endl;
    system("pause");
    system("cls");
}

//draw
void SpeechManager::speechDraw(){
    cout << this->m_Index << " speech" << endl;
    cout << "-----------------------------" << endl;
    cout << "Draw Result: " << endl;

    std::random_device rd;
    std::mt19937 g(rd());

    if (this->m_Index == 1) {
        std::shuffle(v1.begin(), v1.end(), g);
        for(vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    } else {
        std::shuffle(v2.begin(), v2.end(), g);
        for(vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    }

    cout << "-----------------------------" << endl;
    system("pause");
    cout << endl;
}

//compete
void SpeechManager::speechContest() {
    cout << "--------" << this->m_Index << " round begin--------" << endl;

    //temporary store score
    multimap<double, int, greater<double> > groupScore;

    int num = 0;

    vector<int>v_Src;
    if (this->m_Index == 1) {
        v_Src = v1;
    } else {
        v_Src = v2;
    }

    //iterator
    for(vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
        num++;
        //score
        deque<double>d;
        for(int i = 0; i < 10; i++) {
            double score = (rand() % 401 + 600) / 10.f;
            // cout << score << " ";
            d.push_back(score);
        }
        // cout << endl;
        
        sort(d.begin(), d.end(), greater<double>());
        d.pop_front(); //remove greatest score
        d.pop_back(); //remove lowest score

        double sum = accumulate(d.begin(), d.end(), 0.0f);
        double avg = sum / (double)d.size();

        // cout << "number: " << *it << " name: " << this->m_Speaker[*it].m_Name << " score: " << avg << endl;

        this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

        groupScore.insert(make_pair(avg, *it));

        if (num % 6 == 0) {
            cout << "The " << num / 6 << " group score: " << endl;
            for (multimap<double, int, greater<double> >::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
                cout << "number: " << it->second << " name: " << this->m_Speaker[it->second].m_Name << " score: " << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
            }

            int count = 0;
            for (multimap<double, int, greater<double> >::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++) {
                if (this->m_Index == 1) {
                    v2.push_back((*it).second);
                } else {
                    vVictory.push_back((*it).second);
                }
            }

            groupScore.clear();
        }
    }

    cout << "--------The " << this->m_Index << " round completed!--------" << endl;
    system("pause");
}

//show score
void SpeechManager::showScore() {
    cout << "--------The " << this->m_Index << " round advanced speakers: " << endl;

    vector<int>v;
    if (this->m_Index == 1) {
        v = v2;
    } else {
        v = vVictory;
    }

    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        cout << "number: " << *it << " name: " << this->m_Speaker[*it].m_Name << " score: " << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
    }
    cout << endl;

    system("pause");
    system("cls");

    this->show_Menu();
}

//Record
void SpeechManager::saveRecord() {
    ofstream ofs;
    ofs.open("speech.csv", ios::out | ios::app);

    for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
        ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
    }
    ofs << endl;

    ofs.close();
    cout << "Record completed!" << endl;
}

//read record
void SpeechManager::loadRecord() {
    ifstream ifs("speech.csv", ios::in);
    if (!ifs.is_open()) {
        this->fileIsEmpty = true;
        cout << "The file is not exist." << endl;
        ifs.close();
        return;
    }

    char ch;
    ifs >> ch;
    if (ifs.eof()) {
        cout << "The file is empty." << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }

    this->fileIsEmpty = false;

    ifs.putback(ch);

    string data;
    int index = 0;

    while (ifs >> data) {

        vector<string>v;
        // cout << data << endl;
        int pos = -1;
        int start = 0;

        while (true) {
            pos = data.find(",", start);
            if (pos == -1) {
                break;
            }
            string temp = data.substr(start, pos - start);
            v.push_back(temp);
            start = pos + 1;
        }

        this->m_Record.insert(make_pair(index, v));
        index++;

    }

    ifs.close();

    for (map<int, vector<string> >::iterator it = m_Record.begin(); it != m_Record.end(); it++) {
        cout << it->first << "Top 1 number: " << it->second[0] << " score: " << it->second[1] << endl;
    }

}

//show Record
void SpeechManager::showRecord() {
    for (int i = 0; i < this->m_Record.size(); i++) {
        cout << "The " << i + 1 << " round" << "top 1 number: " << this->m_Record[i][0] << " score: " << this->m_Record[i][1]
        << "top 2 number: " << this->m_Record[i][2] << " score: " << this->m_Record[i][3]
        << "top 3 number: " << this->m_Record[i][4] << " score: " << this->m_Record[i][5] << endl;
    }

    system("pause");
    system("cls");
}

//clear record
void SpeechManager::clearRecord() {
    cout << "Are you sure you want to clear?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    
    int select = 0;
    cin >> select;

    if (select == 1) {
        ofstream ofs("sppech.csv", ios::trunc);
        ofs.close();

        this->initSpeech();
        this->createSpeaker();
        this->loadRecord();

        cout << "Successfully Clear!" << endl;
    }

    system("pause");
    system("cls");
}

//Destructor
SpeechManager::~SpeechManager(){

}

