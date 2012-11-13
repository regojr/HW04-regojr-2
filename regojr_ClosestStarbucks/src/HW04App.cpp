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
		//Entry* entries; // was private
		void locationReader(Entry** entries, int* length); // was Entry*

private:
		
		Entry* location; // freshly added
		regojrStarbucks rsb;
		int numStarbucks;
		int length;
		Entry* entries;
		
};

void HW04App::locationReader(Entry** entries, int* length) // was Entry* type
{

	string line, id, x, y;									
	ifstream fileIn( "../resources/Starbucks_2006.csv");  // file to be read in
	console() << "Loading .csv file..." << endl;
	
	// console() # entries
	while( !fileIn.eof() ) {			
		getline(fileIn, line, ',');
        
		char comma;
		fileIn.get(comma);

		double x1;
        fileIn >> x1;
		//console() << x1 << ",";
        
		char comma2;
        fileIn.get(comma2); //get comma
        
		double y1;
        fileIn >> y1;
		//console() << y1 << "," << endl;
        
		numStarbucks++;

    }
    
	fileIn.close();

	// Create new array of entries using size
	ifstream file("../resources/Starbucks_2006.csv");
	*entries = new Entry[numStarbucks];

	// for each spot in array, add values
	for( int i=0; i < numStarbucks; i++ ) {
		try
		{		
			id = "";
			getline(file, id, ',');
			(*entries)[i].identifier = id;
			//console() << "read identifier: "<< id << endl; // For testing
			char comma;
			file.get(comma);
			//console() << "reading in comma: " << comma << endl; // For testing			
			double xIn;			
			file >> xIn;
			(*entries)[i].x = xIn;
			//console() << "read x: " << xIn << endl; // For testing			
			file.get(comma);
			//console() << "reading in comma: " << comma << endl; // For testing		
			double yIn;
			file >> yIn;
			(*entries)[i].y = yIn;
			//console() << "read in y: " << yIn << endl; // For testing
		}
		catch(Exception e) {
			console() << "EXCEPTION FOUND!@!@!@!" << endl;
			// For debugging purposes
		}
	}
	console() << "Read completed." << endl;
}

void HW04App::setup()
{	
	numStarbucks = 0;
	console() << "Reading in locations..." << endl;
	locationReader(&entries, &length);

	console() << "Building K-D Tree..." << endl;
	rsb.build(entries, numStarbucks);	
	console() << "Build Complete." << endl;
	//delete [] entries;	

	console() << "Running Closest Starbucks Algorithm..." << endl;	
	Entry* result = rsb.getNearest(0.1234567, 0.1234567);
	console() << "Algorithm Complete. " << endl;
	console() << "Results Yielded: " << result->identifier 
		<< "  as the closest Starbucks to your location." << endl; 	

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
