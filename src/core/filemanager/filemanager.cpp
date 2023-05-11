#include "filemanager.h"

void filemanager::init()
{
    fileName = "playerweights.txt";

    bool exists = fileExists();

    if (!exists)
    {
        std::ofstream outfile(fileName);
    }

    return;
}

bool filemanager::fileExists()
{
    struct stat buffer;

    int te = stat(fileName.c_str(), &buffer);

    bool exists = (te == 0);

    return exists;
}

bool filemanager::writeToFile()
{
    // data is stored in format:
    //  [name] [\t] [score,...weights]
    // Ex: Kurt     30.0,0.2,0.5,0.7,9.4,4.2,3.0

    // open the file in write mode
    std::ofstream outfile(fileName);
    std::stringstream temp;

    std::map<std::string, std::list<float>>::iterator it;
    // stringify each entry and push to stream

    for (it = playerWeights.begin(); it != playerWeights.end(); it++)
    {
        // std::cout << it->first << " - write HS " << it->second << std::endl;
        temp << it->first << "\t" << std::setprecision(2) << playerScores[it->first];

        // loop through weights
        for (std::list<float>::iterator subit = (it->second).begin(); subit != (it->second).end(); subit++)
        {
            temp << "," << std::setprecision(2) << *subit;
        }

        temp << std::endl;
    }

    outfile << temp.str();
}
bool filemanager::readFile()
{

    std::ifstream infile(fileName);

    std::string word;     // line in file
    std::string subword;  // sub line in line[word], uses \t as a delimiter
    std::string subscore; // score in line "20,90,0.4" - uses comma as a delimiter

    // string streams
    std::istringstream st;
    std::istringstream subst;
    std::string pname; // player name
    float score;

    // holders
    std::list<float> tempWeight;
    std::list<float>::iterator scoreit;

    while (std::getline(infile, word))
    {
        // for each line check for tab delemiting
        // st(word);
        st = std::istringstream(word);

        while (std::getline(st, subword, '\t'))
        {
            subst = std::istringstream(subword);

            while (std::getline(subst, subscore, ','))
            {
                if (std::stringstream(subscore) >> score)
                {
                    // append scores
                    score = std::stof(subscore);
                    tempWeight.push_back(score);
                }
                else
                {
                    pname = subword;
                }
            }
        }

        // get player score,add to map of players and scores
        scoreit = tempWeight.begin();
        std::advance(scoreit, 0); // score is at index 0

        // add to map of player and score
        addtoScores(pname, *scoreit);

        // remove from holder
        tempWeight.erase(scoreit);

        // add to weight map
        addtoWeights(pname, tempWeight);

        // clear for next iteration
        tempWeight.clear();
    }
}

void filemanager::addtoWeights(std::string name, std::list<float> tempWeight)
{
    std::pair<std::string, std::list<float>> tempPair;
    tempPair.first = name;
    tempPair.second = tempWeight;

    // add to map of players and weight
    playerWeights.insert(tempPair);
}
void filemanager::addtoScores(std::string name, float score)
{
    std::pair<std::string, float> tempPair;
    tempPair.first = name;
    tempPair.second = score;

    playerScores.insert(tempPair);
}

bool filemanager::update(std::string name, float score, std::list<float> weights)
{
    // update in memory maps
    for (std::map<std::string, float>::iterator it = playerScores.begin(); it != playerScores.end(); it++)
    {
        if (it->first == name)
        {
            playerScores[name] = score;
            playerWeights[name] = weights;
            return true;
        }
    }
    return false;
}

void filemanager::createPlayer(std::string name)
{
    if (playerScores.find(name) == playerScores.end())
    {
        // player does not already exist
        playerScores[name] = 0.0;
        playerWeights[name] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    }
    currentPlayer = name;
    playerScore = playerScores[name];
}
