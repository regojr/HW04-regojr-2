#pragma once
#include "Starbucks.h"

class regojrStarbucks : public Starbucks
{
public:
	regojrStarbucks(void);
	virtual void build(Entry* entry, int n);
	virtual Entry* getNearest(double x, double y);
	~regojrStarbucks(void);

private:


};

void regojrStarbucks::build(Entry* entry, int n)
{

}

Entry* regojrStarbucks::getNearest(double x, double y)
{

}