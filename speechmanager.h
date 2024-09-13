#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include "speaker.h"
#include <algorithm>
#include <random>
#include <deque>
#include <functional>
#include <numeric>
#include <string>
#include <fstream>

class SpeechManager {
    public:
        SpeechManager();

        //menu
        void show_Menu();

        //exit
        void exitSystem();

        //destructor
        ~SpeechManager();

        //default
        void initSpeech();

        //create speaker
        void createSpeaker();

        //start
        void startSpeech();

        //draw
        void speechDraw();

        //compete
        void speechContest();

        //show score
        void showScore();

        //record
        void saveRecord();

        //read record
        void loadRecord();

        bool fileIsEmpty;

        map<int, vector<string> >m_Record;

        //clear record
        void clearRecord();

        //show record
        void showRecord();

        //display funny board
        void displayLeaderboard();

        //first round speaker
        vector<int>v1;

        //first round winner
        vector<int>v2;

        //top 3 winner
        vector<int>vVictory;

        //speaker number
        map<int, Speaker>m_Speaker;

        //compete round
        int m_Index;

        //board data
        vector<string> titles;
        multimap<double, int, greater<double>> groupScore;


};
