#pragma once
#include "Starbucks.h"

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
	kdnode* insert(Entry* e, kdnode* r, bool xLevel);
	regojrStarbucks(void);
	virtual void build(Entry* entry, int n);
	virtual Entry* getNearest(double x, double y);
	~regojrStarbucks(void);

private:


};
