#ifndef RawSkeletonH
#define RawSkeletonH
#include <vector>
#include "Point.h"
//TODO:duplicated code.Similar code in the Joint class
struct RawAction {
    Point position;
    float duration;
};

struct RawCycle {
    std::string id;
    std::vector<RawAction> actions;
};

struct RawJoint {
    std::string id;
    std::vector<RawCycle> cycles;
};

struct RawBone{
    std::string aId;
    std::string bId;
};

struct RawSkeleton{
    std::vector<RawJoint> joints;
    std::vector<RawBone> bones;
};

#endif