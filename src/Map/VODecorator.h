#ifndef VODecoratorH
#define VODecoratorH
#include "IMap.h"

//TODO:change name
class VODecorator :public IMap {  
  private:
    IMap* map;
    int lats;
    int longs;
  public:
	  VODecorator(IMap* map,int lats,int longs){
        this->map=map;
        this->lats=lats;
        this->longs=longs;
      }    
            
    Point* get(float u,float v){ return map->get(u,v);}
    
    Point* getNormal(float u,float v){ return map->getNormal(u,v);}

    float getUFrom(){ return map->getUFrom(); }
    float getUTo(){ return map->getUTo(); }
    float getVFrom(){ return map->getVFrom(); } 
    float getVTo(){ return map->getVTo(); }

    int getLats(){
        if(lats<map->getLats()){
            return lats;
        }else{
            return map->getLats();
        }
    }
    
    int getLongs(){
        if(longs<map->getLongs()){
            return longs;
        }else{
            return map->getLongs();
        }
    }

};


#endif
