#pragma once
#include "Starbucks.h"

using namespace std;

class kdnode
{
public:
	kdnode* left_;
	kdnode* right_;
	Entry* data_;

	kdnode();
	kdnode(Entry* e);
};

class regojrStarbucks : public Starbucks
{
public:
	kdnode* k;
	kdnode* insert(Entry* e, kdnode* r, bool xLevel);
	regojrStarbucks(void);
	virtual void build(Entry* entry, int n);
	virtual Entry* getNearest(double x, double y);
	double calculateDistance(double x, double y, kdnode* k);
	kdnode* checkTree(double x, double y, kdnode* k, bool xLevel);
	~regojrStarbucks(void);

	
private:
	Entry* location;
	//kdnode* k;
	double x;
	double y;
	regojrStarbucks* rsb;
};
