#include <iostream>
#include "StepsGenerator.h"
#include <Windows.h>
using namespace std;

int main()
{
    if(!SetCurrentDirectoryA("../../JoinyGenerator/levels"))
        return 1;
    GenerateLevels(9,120,2,4);
    SaveCollection("collection_9x9_1.txt","puzzle_9x9_1.ad");
    SaveCollection("collection_9x9_2.txt","puzzle_9x9_2.ad");

    return 0;
}

