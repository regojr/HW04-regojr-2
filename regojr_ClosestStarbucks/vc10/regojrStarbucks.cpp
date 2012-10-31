#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "regojrStarbucks.h"
#include "regojrStarbucks.h"
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <io.h>
#include <iostream>

using namespace std;


kdnode::kdnode() {
	left_  = NULL;
	right_ = NULL;
	data_  = NULL;
}

kdnode::kdnode(Entry* e){
	left_  = right_ = NULL;
	data_  = e;
}

regojrStarbucks::regojrStarbucks()
{
	//k = NULL;
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
			k->left_ = insert(e, k->left_, !xLevel);
		else 
			k->right_ = insert(e, k->right_, !xLevel);
	}
	else {
		if(e->y < k->data_->y ) 
			k->left_ = insert(e, k->left_, !xLevel);
		else 
			k->right_ = insert(e, k->right_, !xLevel);	
	}
	
	return k;
}


double regojrStarbucks::calculateDistance( double x_, double y_, kdnode* k)
{
	if(k->data_ == NULL) return 2.0; //because all points that exist will be closer
	else {
		double aSq, bSq; 
		aSq = abs(x_ - (k->data_->x)) * abs(x_ - (k->data_->x));
		bSq = abs(y_ - (k->data_->y)) * abs(y_ - (k->data_->y));
		return sqrt(aSq + bSq);
	}
}


void regojrStarbucks::build(Entry* entry, int n)
{
	
	freshEntries = new Entry[n];
	
	for( int i = 0; i < n; i++ ) {
		cout << "added " << i << " entries to structure" << std::endl;
		/*(freshEntries[i]).identifier = (&entry[i])->identifier;
		(freshEntries[i]).x = (&entry[i])->x;
		(freshEntries[i]).y = (&entry[i])->y;*/
		freshEntries[i] = entry[i];
	}
	entry = freshEntries;
	
	k = new kdnode(entry);

	for( int j = 0; j < n; j++ ) {
		insert( &entry[j], k, true );
	}
}


kdnode* regojrStarbucks::checkTree(double x, double y, kdnode* k, bool xLevel)
{
	if( k == NULL ) return k;
	if((abs(k->data_->x-x)<=0.00001) && (abs(k->data_->y-y)<=0.00001)) 
		return k;

	foundLeft = NULL;
	foundRight = NULL;
	
	//decide which side to search in kd tree
	if(xLevel){
		if(k->data_->x > x)
			foundLeft = checkTree(x,y,k->left_,!xLevel);
		if(foundLeft == NULL)
			foundRight = checkTree(x,y,k->right_,!xLevel);
	}
	else{
		if(k->data_->y > y)
			foundLeft = checkTree(x,y,k->left_,!xLevel);
		if(foundLeft == NULL)
			foundRight = checkTree(x,y,k->right_,!xLevel);
	}

	if(foundLeft == NULL && foundRight == NULL)
		return k;

	//checr if we should checr another side depends on "which side is NULL!!!"
	if(xLevel){
		if(foundLeft==NULL){
			if(calculateDistance(x,y,foundRight) > calculateDistance(x,y,k))
				foundRight = k;
			//checr root and foundLeft, which one is more close, compare that one to ...
			if(abs(x-foundRight->data_->x) < calculateDistance(x,y,foundRight))
				foundLeft = checkTree(x,y,k->left_,!xLevel);
		}
		if(foundRight==NULL){
			if(calculateDistance(x,y,foundLeft) > calculateDistance(x,y,k))
				foundLeft = k;
			if(abs(x-foundLeft->data_->x) < calculateDistance(x,y,foundLeft))
				foundRight = checkTree(x,y,k->right_,!xLevel);
		}
	}
	else{
		if(foundLeft==NULL){
			if(calculateDistance(x,y,foundRight) > calculateDistance(x,y,k))
				foundRight = k;
			if(abs(y-foundRight->data_->y) < calculateDistance(x,y,foundRight))
				foundLeft = checkTree(x,y,k->left_,!xLevel);
		}
		if(foundRight==NULL){
			if(calculateDistance(x,y,foundLeft) > calculateDistance(x,y,k))
				foundLeft = k;
			if(abs(y-foundLeft->data_->y) < calculateDistance(x,y,foundLeft))
				foundRight = checkTree(x,y,k->right_,!xLevel);
		}
	}

	//decide which one should be returned
	if(foundLeft == NULL && foundRight != NULL){
		if(calculateDistance(x,y,k) > calculateDistance(x,y,foundRight))
			return foundRight;
		else
			return k;
	}
	else if(foundLeft != NULL && foundRight == NULL){
		if(calculateDistance(x,y,k) > calculateDistance(x,y,foundLeft))
			return foundLeft;
		else
			return k;
	}
	else{
		double shortestDistance = min(calculateDistance(x,y,k),min(calculateDistance(x,y,foundRight),calculateDistance(x,y,foundLeft)));
		if(shortestDistance == calculateDistance(x,y,k))
			return k;
		else if(shortestDistance == calculateDistance(x,y,foundRight))
			return foundRight;
		else
			return foundLeft;
	}
}

Entry* regojrStarbucks::getNearest(double x, double y)
{
	
	Entry* checkTreeResult = checkTree(x, y, k, true)->data_;
	Entry* ptrToEntry = checkTreeResult;
	
	return ptrToEntry;//was checkTreeResult
	
}



