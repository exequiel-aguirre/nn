/*
	This is the algorithm published by Stan Melax,
	http://pomax.nihongoresources.com/downloads/PolygonReduction.pdf	
*/

#ifndef DecimateDataStructureH
#define DecimateDataStructureH
#include <vector>
#include <assert.h>
#include "Point.h"

namespace nnd{

class Triangle;
class NPoint;

class Triangle{
 public:
	vector<NPoint*>	vertex;
	Point* normal;
	Triangle(NPoint* v1,NPoint* v2,NPoint* v3);
	~Triangle();
	void buildNormal();
	void replaceVertex(NPoint* vold,NPoint* vnew);
	bool hasVertex(NPoint* p);
	//mine
	void print();

};

class NPoint:public Point{
 public:
	int id;
	vector<NPoint*> neighbors;
	vector<Triangle*> face;
	float cost;
	NPoint* collapse;
	NPoint(Point p,int id);
	~NPoint();
	void removeIfNonNeighbor(NPoint* n);
	//mine
	void add(Triangle* t);	
	void remove(Triangle* t);
	void addUnique(NPoint* n);
	void remove(NPoint* n);
	void print();	
	bool contains(Triangle* t);
	bool contains(NPoint* p);
};

vector<NPoint* >   vertices;
vector<Triangle*> triangles;

Triangle::Triangle(NPoint* v1,NPoint* v2,NPoint* v3){
	assert(v1!=v2 && v1!=v3 && v2!=v3);
	vertex.push_back(v1);
	vertex.push_back(v2);
	vertex.push_back(v3);
	buildNormal();
	triangles.push_back(this);
	for(int i=0;i<3;i++){
		vertex[i]->add(this);
		for(int j=0;j<3;j++){
			if(i!=j)	vertex[i]->addUnique(vertex[j]);
		}
	}

}
Triangle::~Triangle(){
	//triangles.remove(this)
	vector<Triangle*>::iterator itt=std::find(triangles.begin(),triangles.end(),this);
	if(itt!=triangles.end()) triangles.erase(itt);

	for (int i=0;i<3;i++){
		if(vertex[i]) vertex[i]->remove(this);			
	}
	for(int i=0;i<3;i++){
		int i2=(i+1) % 3;
		if(!vertex[i] || !vertex[i2]) continue;
		vertex[i]->removeIfNonNeighbor(vertex[i2]);
		vertex[i2]->removeIfNonNeighbor(vertex[i]);
	}
}
bool Triangle::hasVertex(NPoint* p){	
		return vertex[0]==p || vertex[1]==p || vertex[2]==p;
	}
void Triangle::buildNormal(){
	Point v1=(*vertex[0]);
	Point v2=(*vertex[1]);
	Point v3=(*vertex[2]);
	Point n= ((v2-v1)^(v3-v1)).normalize();
	normal= new Point(n.x,n.y,n.z);
}
void Triangle::replaceVertex(NPoint* p1,NPoint* p2){
	assert(p1 && p2);
	assert(p1==vertex[0] || p1==vertex[1] || p1==vertex[2]);
	assert(p2!=vertex[0] && p2!=vertex[1] && p2!=vertex[2]);

	if(p1==vertex[0]){
		vertex[0]=p2;
	}else if(p1==vertex[1]){
		vertex[1]=p2;
	}else {
		assert(p1==vertex[2]);
		vertex[2]=p2;
	}
	p1->remove(this);
	assert(!p2->contains(this));
	p2->add(this);
	for(int i=0;i<3;i++){
		p1->removeIfNonNeighbor(vertex[i]);
		vertex[i]->removeIfNonNeighbor(p1);
	}
	for(int i=0;i<3;i++){
		assert(vertex[i]->contains(this));
		for(int j=0;j<3;j++){
			if(i!=j){
				vertex[i]->addUnique(vertex[j]);
			}
		}
	}
	buildNormal();
}

void Triangle::print(){
  std::cout << "("<<vertex[0]->id<<","<< vertex[1]->id<<","<< vertex[2]->id<<")\n";
}



NPoint::NPoint(Point p, int id){
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;
	this->id=id;

	vertices.push_back(this);
}
NPoint::~NPoint(){
	assert(face.size()==0);
	while(neighbors.size()!=0){
			neighbors[0]->remove(this);
			this->remove(neighbors[0]);
	}

	//vertices.remove(this)
	vector<NPoint*>::iterator itp=std::find(vertices.begin(),vertices.end(),this);
	if(itp!=vertices.end()) vertices.erase(itp);
}
void NPoint::removeIfNonNeighbor(NPoint* p){
	vector<NPoint*>::iterator itp=std::find(neighbors.begin(),neighbors.end(),p);
	if(itp==neighbors.end()) return;//not a neighbor
	for(int i=0;i<face.size();i++){
		if(face[i]->hasVertex(p)) return;//it's actually neighbor, so we don't remove it
	}

	//remove p
	neighbors.erase(itp);
}
//mine
void NPoint::add(Triangle* t){
	face.push_back(t);
}
void NPoint::remove(Triangle* t){
	vector<Triangle*>::iterator itt=std::find(face.begin(),face.end(),t);
	if(itt!=face.end()) face.erase(itt);

}
void NPoint::addUnique(NPoint* p){
	vector<NPoint*>::iterator itp=std::find(neighbors.begin(),neighbors.end(),p);
	if(itp==neighbors.end()){
		neighbors.push_back(p);		
	}
}
void NPoint::remove(NPoint* p){
	vector<NPoint*>::iterator itp=std::find(neighbors.begin(),neighbors.end(),p);
	if(itp!=neighbors.end()) neighbors.erase(itp);
}

bool NPoint::contains(Triangle* t){
	vector<Triangle*>::iterator itt=std::find(face.begin(),face.end(),t);
	return (itt!=face.end());
}
bool NPoint::contains(NPoint* p){
	vector<NPoint*>::iterator itp=std::find(neighbors.begin(),neighbors.end(),p);
	return (itp!=neighbors.end());
}

void NPoint::print(){
	std::cout << "("<<x<<","<< y<<","<< z<<")"<<" Cost:"<<cost<<" , neighbors:"<<neighbors.size() <<" , faces:"<<face.size() <<"\n";
}




//make these nnd::addVertex,etc
void addVertex(vector<Point>& moIndexedVertices){
	for(int i=0;i<moIndexedVertices.size();i++){
		NPoint* vertex=new NPoint(moIndexedVertices[i],i);
	}
}
void addFaces(vector<vector<int>> moIndexedTriangles){
	for(int i=0;i<moIndexedTriangles.size();i++){
			Triangle* t= new Triangle(
									vertices[moIndexedTriangles[i][0]],
									vertices[moIndexedTriangles[i][1]],
									vertices[moIndexedTriangles[i][2]]
									);
	}
}

float calculateCost(NPoint* p1,NPoint* p2){
	Point auxP1=*p1;
	Point auxP2=*p2;
	float edgeLength=(auxP2-auxP1).norm();
	float curvature=0;

	vector<Triangle* > sides;
	for(int i=0;i<p1->face.size();i++){
		if(p1->face[i]->hasVertex(p2)){
			sides.push_back(p1->face[i]);
		}
	}

	for(int i=0;i<p1->face.size();i++){
		float minCurvature=1;
		for(int j=0;j<sides.size();j++){
			auxP1=*(p1->face[i]->normal);
			auxP2=*(sides[j]->normal);
			float dotProduct=auxP1 * auxP2;
			minCurvature=std::min(minCurvature,(1-dotProduct)/2.0f);
		}
		curvature=std::max(curvature,minCurvature);
	}

	return edgeLength * curvature;
}

void calculateCostAtVertex(NPoint* p){
	if(p->neighbors.size()==0){
		p->collapse=NULL;
		p->cost=-0.01f;
		return;
	}

	p->collapse=NULL;
	p->cost=10000;
	for(int i=0;i<p->neighbors.size();i++){
		float cost;
		cost=calculateCost(p,p->neighbors[i]);
		if(cost<p->cost){
			p->collapse=p->neighbors[i];
			p->cost=cost;
		}
	}
}

void calculateAllCosts(){
	for(int i=0;i<vertices.size();i++){
		calculateCostAtVertex(vertices[i]);
	}
}

NPoint* getMinimumCostVertex(){
	NPoint* min=vertices[0];
	for(int i=0;i<vertices.size();i++){
		if(vertices[i]->cost<min->cost){
			min=vertices[i];
		}
	}
	return min;
}



void collapse(NPoint* p1,NPoint* p2){
	if(!p2){		
		delete(p1);
		return;
	}

	vector<NPoint*> tmp;
	for(int i=0;i<p1->neighbors.size();i++){
		tmp.push_back(p1->neighbors[i]);
	}

	for(int i=p1->face.size()-1;i>=0;i--){
		if(p1->face[i]->hasVertex(p2)){
			delete(p1->face[i]);
		}
	}

	for(int i=p1->face.size()-1;i>=0;i--){
		p1->face[i]->replaceVertex(p1,p2);
	}	
	delete(p1);

	for(int i=0;i<tmp.size();i++){
		calculateCostAtVertex(tmp[i]);
	}
}

vector<Point>& decimate(vector<Point>& moIndexedVertices,vector<vector<int>> moIndexedTriangles){
	std::cout << "decimating...\n";
	addVertex(moIndexedVertices);
	addFaces(moIndexedTriangles);

	calculateAllCosts();
	
	//decimate
	while(vertices.size() > 150) {
		NPoint* min=getMinimumCostVertex();
		//min->print();
		collapse(min,min->collapse);
	}
	
	//build the result
	vector<Point> decimatedVertices;
	for(int i=0;i<triangles.size();i++){
		Triangle* t=triangles[i];

		Point v1=*(t->vertex[0]);
		Point v2=*(t->vertex[1]);
		Point v3=*(t->vertex[2]);

		//if(vertices.size()>140) std::cout << "something went sideways!";
		decimatedVertices.push_back(v1);
		decimatedVertices.push_back(v2);
		decimatedVertices.push_back(v3);
	}
	return decimatedVertices;
}

}

#endif
