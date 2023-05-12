#pragma once

#include "sys/stat.h"
#include "fstream"
#include "string"
#include "map"
#include "list"
#include "sstream"

#include "iostream"
#include "iomanip"
#include "algorithm"

namespace filemanager
{
    inline std::string fileName;
    inline std::fstream scorefile;
    inline std::string currentPlayer;
    inline float currentScore;
    inline float playerScore;
    inline std::map<std::string, std::list<float>> playerWeights;
    inline std::map<std::string, float> playerScores;

    //
    void init();
    bool fileExists();
    bool bestPlayer();
    bool update(std::string name, float score, std::list<float> weight); // update player scores and weight
    void createPlayer(std::string name);
    bool writeToFile(); // write player details to file
    bool readFile();    // read player names along with score and weight
    void addtoWeights(std::string name, std::list<float> tempWeight);
    void addtoScores(std::string name, float score);

}