#include <iostream>
#include "FGenerator.h"
#include <cstdlib>
#include <ctime>
#include <set>
#include <algorithm>
#include "Binary.h"
#include "Joiny.h"
#include <fstream>
#include <sstream>
struct Color
{
public:
    Color(unsigned int r, unsigned int g, unsigned int b):
        _red(r), _green(g), _blue(b)
    {

    }

private:
    unsigned int _red;
    unsigned int _green;
    unsigned int _blue;

};


bool areNeighboors(const FlowPoint& a, const FlowPoint& b);
bool operator<(const FlowTask& a, const FlowTask& b);
bool operator<(const JoinyPair& a, const JoinyPair& b);
bool isGoodJoiny(const JoinyTask& task, JoinyInfo &info);
bool isGooTask(const FlowTask& task);
bool isGooTask(const FlowTask& task, unsigned int N);
void tabulate(unsigned int generated, unsigned int good, unsigned int unique);
bool operator<(const JoinyInfo& a, const JoinyInfo& b);
bool operator==(const JoinyInfo& a, const JoinyInfo& b);
bool operator<(const JoinyPuzzle& a, const JoinyPuzzle& b);
JoinyInfo mergeInfo(const JoinyInfo a, const JoinyInfo b);

void GenerateLevels(const unsigned int tablo_size,
                const unsigned int level_number,
                const unsigned int min_colors,
                const unsigned int max_colors);

void SaveCollection(std::string plan_file, std::string coll_save_name);
const Palete getPalete(JoinyPuzzle &puzzle);
