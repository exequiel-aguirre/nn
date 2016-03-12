#ifndef RawSkeletonH
#define RawSkeletonH
#include <vector>
#include "Point.h"
//TODO:duplicated code.Similar code in the Joint class
struct RawAction {
    Point position;
    float duration;
};

struct RawJoint {
    unsigned int id;
    std::vector<RawAction> actions;
};

struct RawBone{
    unsigned int aId;
    unsigned int bId;
};

struct RawSkeleton{
    std::vector<RawJoint> joints;
    std::vector<RawBone> bones;
};

#endif