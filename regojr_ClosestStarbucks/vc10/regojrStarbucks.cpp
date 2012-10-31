#include "regojrStarbucks.h"
#include <cmath>

using namespace std;

kdnode::kdnode(){
	left_  = NULL;
	right_ = NULL;
	data_  = NULL;
}

kdnode::kdnode(Entry* e){
	left_  = NULL;
	right_ = NULL;
	data_  = e;
}

kdnode* regojrStarbucks::insert(Entry* e, kdnode* r, bool xLevel)
{

}

void regojrStarbucks::build(Entry* e, int n)
{

}

Entry* regojrStarbucks::getNearest(double x, double y)
{

}

regojrStarbucks::regojrStarbucks()
{
}

regojrStarbucks::~regojrStarbucks(void)
{
}
