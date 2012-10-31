#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Starbucks.h"
#include "regojrStarbucks.h"

#include <iostream>
#include <fstream>
#include <io.h>
#include <stdio.h>

using namespace ci;
using namespace ci::app;
using namespace std;


class HW04App : public AppBasic {
  public:

		void setup();
		//void mouseDown( MouseEvent event );	
		//void update();
		void draw();
		

private:
	Entry* locationReader();
	regojrStarbucks* rsb;
	int numStarbucks;

};

Entry* HW04App::locationReader()
{
	Entry* entries;
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
		//console() << x1 << ",";
        char comma;
        fileIn.get(comma); //get comma
        double y1;
        fileIn >> y1;
		//console() << y1 << "," << endl;
        tester++;
		test2++;
    }
    
	// Create new array of entries using size
	ifstream file("C:/Users/Jake/Desktop/CSE274/HW04-regojr/HW04_regojr/resources/Starbucks_2006.csv");
	entries= new Entry[tester+1];
	console() << "Reading entries..." << endl;
	// for each spot in array, add values
	for( int i=0; i < tester-1; i++ ) {
		double percent = 100*((double)i/test2);
		console() << percent << "% complete." << endl;

		getline(file, line, ',');
		(entries)[i].identifier = line;

        double xIn;
        file >> xIn;
        (entries)[i].x = xIn;

        char comma;
        file.get(comma);

        double yIn;
        file >> yIn;
        (entries)[i].y = yIn;
	}

	console() << "Read completed." << endl;
	return entries;
}

void HW04App::setup()
{
	numStarbucks = 0;
	Entry* entries = locationReader();
	rsb = new regojrStarbucks();
	rsb->build(entries, numStarbucks);
	
	cout << "Setup Complete" << endl;
	cout << "THE NEAREST STARBUCKS: " << rsb->getNearest(0.1234567, 0.1234567)->identifier << endl;
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
