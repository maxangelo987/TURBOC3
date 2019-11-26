#ifndef FGENERATORNODE_H
#define FGENERATORNODE_H

#include "FlowPoint.h"
#include <vector>
#include <map>
#define USE_TWO_SHUFFLE
//#define THREE_BLOCK_SHUFFLE

typedef std::pair<FlowPoint, FlowPoint> FlowStartEnd;
#include "Binary.h"

inline InputBinaryStream& operator>>(InputBinaryStream& is, FlowStartEnd& s)
{
    is >> s.first >> s.second;
    return is;
}

inline OutputBinaryStream& operator<<(OutputBinaryStream& os, const FlowStartEnd& s)
{
    os << s.first << s.second;
    return os;
}


typedef std::vector<FlowStartEnd> FlowTask;


FlowTask generate(const Cordinate width, const Cordinate height);

typedef int TraceID;
typedef std::map<TraceID, FlowStartEnd> FlowTaskMap;
typedef std::vector<TraceID> TRow;
typedef std::vector<TRow> Table;

#endif // FGENERATORNODE_H
