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
	//kdnode* k;
	
	
	regojrStarbucks(void);

	virtual void build(Entry* entry, int n);
	virtual Entry* getNearest(double x, double y);
	
	~regojrStarbucks(void);
	
private:
	kdnode* insert(Entry* e, kdnode* r, bool xLevel);
	double calculateDistance(double x_, double y_, kdnode* k);
	kdnode* checkTree(double x, double y, kdnode* k, bool xLevel);
	
	Entry* freshEntries;
	Entry* checkResult;
	kdnode* k;
	double x;
	double y;
	regojrStarbucks* rsb;
};
