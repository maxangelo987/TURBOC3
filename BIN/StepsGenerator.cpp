#include "StepsGenerator.h"
#include <sstream>
#include <string>
#include <fstream>
using namespace std;


bool areNeighboors(const FlowPoint& a, const FlowPoint& b)
{
    if(a.x() == b.x() && (a.y()+1 == b.y() || b.y()+1 == a.y()))
        return true;
    if(a.y() == b.y() && (a.x()+1 == b.x() || b.x()+1 == a.x()))
        return true;
    return false;
}



bool operator<(const FlowTask& a, const FlowTask& b)
{
    return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}

bool operator<(const JoinyPair& a, const JoinyPair& b)
{
    if(a.getColor() < b.getColor())
        return true;
    else if(a.getColor() == b.getColor())
        return a.getPoints() < b.getPoints();
    return false;
}

bool isGoodJoiny(const JoinyTask& task,JoinyInfo& info)
{
    //Score precision = info.getGold()/25;
    if(info.getBronze()!=0 && info.getSilver()!=0 &&
            info.getGold()!=0)
    {
//        if(info.getBronze() + precision <= info.getSilver() &&
//                info.getSilver() <= info.getGold())
//        {
//            info.setBronze(info.getBronze()*0.7);
//            return true;
//        }
//        else
//            return false;
        return true;
    }
    else
        return false;
}

bool isGooTask(const FlowTask& task)
{
    //return task.size() <= (N-1) && N > 0;
    for(FlowTask::const_iterator it = task.begin(); it!=task.end(); ++it)
    {
        const FlowStartEnd& s = *it;
        //        if(s.size() != 2)
        //            return false;
        if(areNeighboors(s.first, s.second))
            return false;
    }
    return true;
}
void tabulate(unsigned int generated, unsigned int good, unsigned int unique)
{
    cout << "Generated: " << generated << ", \t Good: " << good << ", \t Unique: " << unique << endl;
}

bool operator<(const JoinyInfo& a, const JoinyInfo& b)
{
    if(a.getBronze() < b.getBronze())
        return true;
    else if(a.getBronze() == b.getBronze())
    {
        if(a.getSilver() < b.getSilver())
            return true;
        else if(a.getSilver() == b.getSilver())
        {
            return a.getGold() < b.getGold();
        }
    }
    return false;
}

bool operator==(const JoinyInfo& a, const JoinyInfo& b)
{
    return a.getBronze() == b.getBronze() && a.getSilver() == b.getSilver() && a.getGold() == b.getGold();

}

bool operator<(const JoinyPuzzle& a, const JoinyPuzzle& b)
{
    if(a._info < b._info)
        return true;
    else if(a._info == b._info)
    {
        return a._task < b._task;
    }
    return false;
}
JoinyInfo mergeInfo(const JoinyInfo a, const JoinyInfo b)
{
    assert(a.getSilver() >= a.getBronze());

    unsigned int gold = std::max(a.getGold(), b.getGold());
    Score precision = gold/10;

//    unsigned int step = a.getSilver() - a.getBronze();
//    if(step >= 1000)
//        step /= 2;

    unsigned int bronze1 = std::min(a.getBronze(), b.getBronze());
    unsigned int bronze2 = gold*0.7;

    unsigned int silver1 = std::min(a.getSilver(), b.getSilver());
    unsigned int silver2 = gold - precision;

    unsigned int bronze = std::min(bronze1, bronze2);
    unsigned int silver = std::min(silver1, silver2);

    if(silver - bronze < precision ||
            gold - silver < precision)
    {
        silver = (gold + bronze)/2;
    }
    JoinyInfo res(bronze,
                  silver,
                  gold);

    if(a.getGold() > b.getGold())
        res.setPathes(a.getPathes());
    else
        res.setPathes(b.getPathes());
    return res;
}
void GenerateLevels(const unsigned int tablo_size,
                    const unsigned int level_number,
                    const unsigned int min_colors,
                    const unsigned int max_colors)
{

    srand(time(0));
    unsigned int joiny_size = tablo_size;
    unsigned int N = level_number;
    unsigned int generated = 0;
    unsigned int good = 0;
    unsigned int max = max_colors;
    unsigned int min = min_colors;
    std::set<JoinyPuzzle> good_tasks;


    while(good_tasks.size() < N)
    {

        FlowTask t = generate(joiny_size,joiny_size);
        std::sort(t.begin(), t.end());

        if(isGooTask(t))
        {
            unsigned int colors = max;

            if(t.size() == 2)
                colors = 2;
            else if(t.size() == 3)
                colors = 3;
            else
            {
                //TODO: correct
                colors = min + (rand() % (unsigned int)(max - min + 1));
            }

            JoinyTask task = flowToJoiny(t, colors, true);
            //std::sort(task.begin(), task.end());


            JoinyInfo info_old = solveJoiny(task,
                                            joiny_size,
                                            joiny_size,
                                            false);

            JoinyTask task_origin = flowToJoinyStaightforward(t);
            JoinyInfo info_origin = solveJoiny(task_origin,
                                               joiny_size,
                                               joiny_size,
                                               true);

            if(info_origin.getGold() == 0)
            {
                std::cout << "No solution" << std::endl;
            }
            else
            {

                JoinyInfo info = mergeInfo(info_old, info_origin);

                if(info.getGold() > 1000000)
                {
                    std::cout << "Bug!!" << endl;
                }
                else if(isGoodJoiny(task, info))
                {

                    //std::sort(task.begin(), task.end());
                    JoinyPuzzle puzzle(task, info);
                    //JoinyPuzzle puzzle(task,info_origin);

                    good_tasks.insert(puzzle);
                    ++good;

                }
            }
        }
        generated++;
        if(generated % 100 == 0)
            tabulate(generated, good, good_tasks.size());
    }

    //suffle levels
    std::vector<JoinyPuzzle> puzzle_vector(good_tasks.begin(),
                                           good_tasks.end());
    std::random_shuffle(puzzle_vector.begin(),puzzle_vector.end());

    //write in file all ell from the set
    unsigned int num = 0;
    for(std::vector<JoinyPuzzle>::iterator it = puzzle_vector.begin();
        it != puzzle_vector.end();
        ++it)
    {
        JoinyPuzzle puzzle = *it;

        std::stringstream fname;
        fname << joiny_size << "x" << joiny_size << "_" << num << ".ad";
        ++num;

        std::ofstream file;
        file.open(fname.str().c_str(), ios::out | ios::binary);
        OutputBinaryStream os(file, BinaryStream::MaxProtocolVersion);

        os << puzzle;
    }

    tabulate(generated, good, good_tasks.size());

}



void SaveCollection(std::string plan_file,
                    std::string coll_save_name)
{

    Palete _past_palete;
    Palete _curr_palete;

    //get info about main settings for collection
    std::ifstream infile(plan_file);
    std::string line;

    std::getline(infile, line);
    std::string tablo_width = line;
    uint32_t tablo_width_i = std::stoi(tablo_width);

    std::getline(infile, line);
    std::string tablo_height = line;
    uint32_t tablo_height_i = std::stoi(tablo_height);

    std::getline(infile, line);
    std::string level_num = line;
    uint32_t level_num_i = std::stoi(level_num);

    std::getline(infile,line);
    std::string collection_color = line;
    std::string r = "";
    std::string g = "";
    std::string b = "";

    //get collection color
    istringstream iss(collection_color);
    iss >> r;
    iss >> g;
    iss >> b;

    //convert coll colors from string to uint32
    uint32_t r_uint = std::stoi(r);
    uint32_t g_uint = std::stoi(g);
    uint32_t b_uint = std::stoi(b);


    // read is this collection open or close
    std::getline(infile, line);
    std::string open_or_close = line;
    uint32_t open_or_close_i = std::stoi(open_or_close);

    //one more white line
    std::getline(infile,line);

    std::vector<std::string> level_files_name;
    for(unsigned int i=0; i<level_num_i; ++i)
    {
        std::getline(infile, line);
        level_files_name.push_back(line);
    }


    //open level files and save info to std::vector<JoinyPuzzle>
    std::vector<JoinyPuzzle> good_tasks;
    for(unsigned int i=0; i<level_files_name.size(); ++i)
    {
        JoinyPuzzle puzzle;
        std::ifstream file;
        file.open(level_files_name[i], ios::in | ios::binary);
        InputBinaryStream is(file);

        is >> puzzle;

        good_tasks.push_back(puzzle);

    }

    //recolor puzzle
    int i=0;
    for(std::vector<JoinyPuzzle>::iterator it = good_tasks.begin();
        it != good_tasks.end();
        ++it)
    {
        JoinyPuzzle * puzzle_ptr = &(*it);


        _past_palete = _curr_palete;
        _curr_palete = getPalete(*it);

        if(_past_palete == _curr_palete)
        {
            recolorJoiny(puzzle_ptr->getJoinyTask(),
                         _curr_palete);
            _curr_palete = getPalete(*it);
        }
        cout<<"recolored "<<i<<endl;
        i++;

    }


    //write all other important info to collection binary file
    //create collection
    std::stringstream fname;
    fname << coll_save_name;
    std::ofstream file;
    file.open(fname.str().c_str(), ios::out | ios::binary);
    OutputBinaryStream os(file, BinaryStream::MaxProtocolVersion);

    //save width and height
    os << tablo_width_i;
    os << tablo_height_i;

    //level num
    os << level_num_i;

    //level color
    os << r_uint;
    os << g_uint;
    os << b_uint;

    //open or close
    os << open_or_close_i;

    //levels
    os << good_tasks;
}
const Palete getPalete(JoinyPuzzle& puzzle)
{
    JoinyTask task = puzzle.getJoinyTask();
    JoinyPair pair;
    Palete palete;
    std::set<unsigned int> palete_set;

    for(unsigned int i=0; i<task.size(); ++i)
    {
        pair = task[i];
        palete_set.insert(pair.getColor());
    }

    //copy unique colors from set to Palete
    for(std::set<unsigned int>::iterator it = palete_set.begin();
        it != palete_set.end(); ++it)
    {
        palete.push_back(*it);
    }

    return palete;
}
