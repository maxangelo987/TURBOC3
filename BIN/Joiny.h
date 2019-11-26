#ifndef JOINY_H
#define JOINY_H
#include "FGenerator.h"
#include "Binary.h"

#include "Flow/JoinyPair.h"

typedef std::vector<unsigned int> Palete;
typedef std::map<unsigned int, std::vector<Palete> > AllPaletes;


const unsigned int getColor(std::map<unsigned int,unsigned int>& mymap);

JoinyTask flowToJoiny(const FlowTask& task,
                      const unsigned int colors,
                      bool mode);

JoinyTask flowToJoiny(const FlowTask& task,
                      const unsigned int colors);

JoinyTask flowToJoinyStaightforward(const FlowTask& task);

JoinyInfo solveJoiny(const JoinyTask& task,
                     const unsigned int width,
                     const unsigned int height, bool full_board_solution=false);

JoinyTask recolorJoiny(JoinyTask &joiny_task,
                       const Palete &bad_palete);

const Palete& getColorSchemeExceptBadPalete(const Palete& bad_palete);



bool operator==(const Palete& p1, const Palete& p2);

void JoinyColorSchemeInit();
const Palete& getColorScheme(unsigned int color_num);



#endif // JOINY_H
