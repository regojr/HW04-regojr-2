#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Starbucks.h"
#include "regojrStarbucks.h"

#include <iostream>
#include <fstream>
#include <io.h>
#include <stdio.h>
#include <string>

using namespace ci;
using namespace ci::app;
using namespace std;


class HW04App : public AppBasic {
  public:

		void setup();
		//void mouseDown( MouseEvent event );	
		//void update();
		void draw();
		Entry* entries; // was private

private:
	void locationReader(); // was Entry*
	Entry* location; // freshly added
	regojrStarbucks rsb;
	int numStarbucks;
	
};

void HW04App::locationReader() // was Entry* type
{
	//Entry* entries;
	string line, id, x, y;									
	int index = 0;								// holding array index position
	int size = 500;								// keeping track of the number of Entry's in the array
	int tester = 0;
	double percent = 0;
	int test2 = 0 ;
	ifstream fileIn( "../resources/Starbucks_2006.csv");  // file to be read in
	console() << "Loading .csv file..." << endl;
	
	// console() # entries
	while( !fileIn.eof() ) {			
		getline(fileIn, line, ',');
        double x1;
        fileIn >> x1;
		console() << x1 << ",";
        char comma;
        fileIn.get(comma); //get comma
        double y1;
        fileIn >> y1;
		console() << y1 << "," << endl;
        tester++;
		test2++;
    }
    
	// Create new array of entries using size
	ifstream file("C:/Users/Jake/Desktop/CSE274/HW04-regojr/HW04_regojr/resources/Starbucks_2006.csv");
	entries= new Entry[tester+1];
	//console() << "Reading entries..." << endl;
	// for each spot in array, add values
	for( int i=0; i < tester; i++ ) {
		double percent = 100*((double)i/test2);
		
		getline(file, id, ',');
		(entries)[i].identifier = id;

        double xIn;
        file >> xIn;
        (entries)[i].x = xIn;

        char comma;
        file.get(comma);
		
        double yIn;
        file >> yIn;
        (entries)[i].y = yIn;

		// To check values read in
		console() << "Index: " << (i+1) << "	id: " << (entries)[i].identifier << "; xCoord: " << (entries)[i].x
				<< "; yCoord: " << (entries)[i].y <<endl;
	}

	console() << "Read completed." << endl;
	//return entries;
}

void HW04App::setup()
{
	
	numStarbucks = 0;
	console() << "Reading in locations..." << endl;
	locationReader();

	console() << "Building K-D Tree..." << endl;
	rsb.build(entries, numStarbucks);	
	console() << "Build Complete." << endl;

	//delete [] entries;

	console() << "Running Closest Starbucks Algorithm..." << endl;
	rsb.getNearest(0.1234567, 0.1234567);

	console() << "Algorithm Complete. " << endl;

	console() << "Results Yielded		" //<< (*location).identifier 
		<< "	as the closest Starbucks to your location." << endl; 
	
}

/*
void HW04App::mouseDown( MouseEvent event )
{
}

void HW04App::update()
{
}
*/
void HW04App::draw()
{
	// clear out the window with black
	//gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( HW04App, RendererGl )
