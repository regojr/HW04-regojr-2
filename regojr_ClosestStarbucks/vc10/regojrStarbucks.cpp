
#include "regojrStarbucks.h"
#include "regojrStarbucks.h"
#include <cmath>
#include <stdio.h>
#include <iostream>

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

regojrStarbucks::regojrStarbucks()
{
	k = NULL;
}

regojrStarbucks::~regojrStarbucks(void)
{
}

kdnode* regojrStarbucks::insert(Entry* e, kdnode* k, bool xLevel)
{
	if( k == NULL) return new kdnode(e);

	if( (abs( k->data_->x - e->x )<=0.00001) && (abs( k->data_->y - e->y )<=0.00001) )
		return k;

	if( xLevel ) {
		if( e->x < k->data_->x ) 
			k->left_ = insert(e, k, !xLevel);
		else 
			k->right_ = insert(e, k, !xLevel);
	}
	else {
		if(e->y < k->data_->y ) 
			k->left_ = insert(e, k, !xLevel);
		else 
			k->right_ = insert(e, k, !xLevel);	
	}
	
	return k;
}


double regojrStarbucks::calculateDistance( double x, double y, kdnode* k)
{
	double aSq = (x - k->data_->x) * (x - k->data_->x);
	double bSq = (y - k->data_->y) * (y - k->data_->y);
	return sqrt(aSq + bSq);
}


void regojrStarbucks::build(Entry* entry, int n)
{
	Entry* freshEntries = new Entry[n];
	
	for( int i = 0; i < n; i++ ) {
		freshEntries[i] = entry[i];
	}
	entry = freshEntries;
	k = new kdnode(entry);
	for( int j = 1; j < n; j++ ) {
		insert( &entry[j], k, true );
	}
}


kdnode* regojrStarbucks::checkTree(double x, double y, kdnode* k, bool xLevel)
{
	if( k == NULL ) return k;
	if((abs(k->data_->x-x)<=0.00001) && (abs(k->data_->y-y)<=0.00001)) 
		return k;

	kdnode* foundLeft = NULL;
	kdnode* foundright = NULL;
	
	//decide which side to search in kd tree
	if(xLevel){
		if(k->data_->x > x)
			foundLeft = checkTree(x,y,k->left_,!xLevel);
		if(foundLeft == NULL)
			foundright = checkTree(x,y,k->right_,!xLevel);
	}
	else{
		if(k->data_->y > y)
			foundLeft = checkTree(x,y,k->left_,!xLevel);
		if(foundLeft == NULL)
			foundright = checkTree(x,y,k->right_,!xLevel);
	}

	if(foundLeft == NULL && foundright == NULL)
		return k;

	//checr if we should checr another side depends on "which side is NULL!!!"
	if(xLevel){
		if(foundLeft==NULL){
			if(calculateDistance(x,y,foundright) > calculateDistance(x,y,k))
				foundright = k;
			//checr root and foundLeft, which one is more close, compare that one to ...
			if(abs(x-foundright->data_->x) < calculateDistance(x,y,foundright))
				foundLeft = checkTree(x,y,k->left_,!xLevel);
		}
		if(foundright==NULL){
			if(calculateDistance(x,y,foundLeft) > calculateDistance(x,y,k))
				foundLeft = k;
			if(abs(x-foundLeft->data_->x) < calculateDistance(x,y,foundLeft))
				foundright = checkTree(x,y,k->right_,!xLevel);
		}
	}
	else{
		if(foundLeft==NULL){
			if(calculateDistance(x,y,foundright) > calculateDistance(x,y,k))
				foundright = k;
			if(abs(y-foundright->data_->y) < calculateDistance(x,y,foundright))
				foundLeft = checkTree(x,y,k->left_,!xLevel);
		}
		if(foundright==NULL){
			if(calculateDistance(x,y,foundLeft) > calculateDistance(x,y,k))
				foundLeft = k;
			if(abs(y-foundLeft->data_->y) < calculateDistance(x,y,foundLeft))
				foundright = checkTree(x,y,k->right_,!xLevel);
		}
	}

	//decide which one should be returned
	if(foundLeft == NULL && foundright != NULL){
		if(calculateDistance(x,y,k) > calculateDistance(x,y,foundright))
			return foundright;
		else
			return k;
	}
	else if(foundLeft != NULL && foundright == NULL){
		if(calculateDistance(x,y,k) > calculateDistance(x,y,foundLeft))
			return foundLeft;
		else
			return k;
	}
	else{
		double shortestDistance = min(calculateDistance(x,y,k),min(calculateDistance(x,y,foundright),calculateDistance(x,y,foundLeft)));
		if(shortestDistance == calculateDistance(x,y,k))
			return k;
		else if(shortestDistance == calculateDistance(x,y,foundright))
			return foundright;
		else
			return foundLeft;
	}
}

Entry* regojrStarbucks::getNearest(double x, double y)
{

	Entry* checkTreeResult = checkTree(x, y, k, true)->data_;
	cout << "NEAREST: " << checkTreeResult->identifier << endl;
	return checkTreeResult;
	
	//return checked;

}



