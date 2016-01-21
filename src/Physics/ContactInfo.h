#ifndef ContactInfoH
#define ContactInfoH
#include "../DataStructure/Point.h"

struct ContactInfo{
    bool hasCollided=false;//TODO:avoid this, maybe creating a nullContactPoint?
    Point impactNormal;
    Point impactPoint;
    Point r1;
    Point r2;
    float penetration=0.0;
};

#endif