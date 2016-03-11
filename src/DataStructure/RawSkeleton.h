#ifndef RawSkeletonH
#define RawSkeletonH
#include <vector>
#include "Point.h"
//TODO:duplicated code.Similar code in the Joint class
struct RawAction {
    Point start;
    Point end;
    float duration;
};

struct RawJoint {
    unsigned int id;
	Point position;
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