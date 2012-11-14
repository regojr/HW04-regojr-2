#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Starbucks.h"
#include "regojrStarbucks.h"
#include "Resources.h"
#include <iostream>
#include <fstream>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace ci;
using namespace ci::app;
using namespace std;


class HW04App : public AppBasic {
  public:
		void prepareSettings( Settings* windowSettings );
		void setup();
		void mouseDown( MouseEvent event );	
		void update();
		void draw();
		void locationReader( Entry** entries, int* length ); // was Entry*
		void markBlips( double x, double y, uint8_t* blip_pattern );

private:		
		Entry*				location; // freshly added
		regojrStarbucks		rsb;
		int					numStarbucks;
		int					length;
		Entry*				entries;
		
	/*** For phase 2 implementation ***/
		//Surface*			mapSurf_;  // the surface to hold the map
		Surface				usa_pic;
		gl::Texture*		mapTex_;	// texture to hold map

		uint8_t*			my_blips;  // the array to hold the pixel data
		uint8_t*			blip_data;
	/***		Screen Dimensions		 ***/
		static const int kAppWidth		= 1000;
		static const int kAppHeight		= 501;
		static const int kTextureSize	= 1024;
		
		double	xCoor;
		double	yCoor;
};

void HW04App::locationReader(Entry** entries, int* length) // was Entry* type
{
	string line, id, x, y;									
	ifstream fileIn( "../resources/Starbucks_2006.csv");  // file to be read in
	console() << "Loading .csv file..." << endl;
	
	/* To count the number of entries */
	while( !fileIn.eof() ) {			
		getline(fileIn, line, ',');        
		char comma;
		fileIn.get(comma);
		double x1;
        fileIn >> x1;        
		char comma2;
        fileIn.get(comma2); //get comma        
		double y1;
        fileIn >> y1;
		numStarbucks++;
    }
	console() << "Entries Counted. " << endl;
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
		
			/* Once each value is stored, Mark that spot on the map */
			uint8_t* pda = (usa_pic).getData();  // get the pixel info
			markBlips( xIn, yIn, pda);
		}
		catch(Exception e) {
			console() << "EXCEPTION FOUND!@!@!@!" << endl;
			// For debugging purposes
		}
	}
	console() << "Read completed." << endl;
}

/* This method will add a red marking on the map for each Starbucks
   location within the United States
*/
void HW04App::markBlips( double x, double y, uint8_t* blip_pattern )
{
	double mHeight = 450;
	double mWidth  = 900;
	Color8u blip = Color8u(255,0,0);

	// Convert x and y coordinates to relative map size (500 x 1000 pixels)
	double blipX	= x * mWidth;
	double blipY	= y * mHeight;
	int offset		= (3 * (blipX + blipY * kAppWidth)) * 1000 ;

	// Change the pixel color to red
	blip_pattern[(offset/1000)      ]	= blip.r;
	blip_pattern[(offset/1000) + 1  ]	= blip.g;
	blip_pattern[(offset/1000) + 2  ]	= blip.b;


}

void HW04App::prepareSettings( Settings* windowSettings )
{
	(*windowSettings).setWindowSize(kAppWidth, kAppHeight);
	(*windowSettings).setResizable(false);
}

void HW04App::setup()
{	
	/*********************For Phase 3 Implementation ***********************/
	usa_pic = ( loadImage( loadResource( RES_MAP, "IMAGE" ) ) );
	my_blips = new uint8_t[kAppWidth*kAppHeight*3];
	mapTex_ = new gl::Texture( usa_pic );
	
	blip_data = (usa_pic).getData();
	
	/* Setup to add blips */
	for( int yCoor=0; yCoor<kAppHeight; yCoor++ ){
		for( int xCoor=0; xCoor<kAppWidth; xCoor++ ){
			int offset = 3*( xCoor + yCoor*kAppWidth );
			my_blips[offset] = blip_data[offset];
		}
	}
	/**********************************************************************/

	numStarbucks = 0;
	console() << "Reading in locations..." << endl;
	locationReader(&entries, &length);

	console() << "Building K-D Tree..." << endl;
	rsb.build(entries, numStarbucks);	
	console() << "Build Complete." << endl;
	//delete [] entries;	

	console() << "Running Closest Starbucks Algorithm..." << endl;	
	Entry* resultLocation = rsb.getNearest(0.1234567, 0.1234567);
	console() << "Algorithm Complete. " << endl;
	console() << "Results Yielded: " << resultLocation->identifier 
		<< "  as the closest Starbucks to your location." << endl; 	

}

void HW04App::mouseDown( MouseEvent event )
{
}

void HW04App::update()
{
	// Get pixel array info
	Color8u markBlip = Color8u( 255, 0, 0 );
	uint8_t* blip_data = usa_pic.getData();

	(*mapTex_).update( usa_pic, (usa_pic).getBounds() );

}


void HW04App::draw()
{
	/* clear out the window with black */
	//gl::clear( Color( 0, 0, 0 ) ); 

	/* Draw the Surface with the map */
	gl::draw( *mapTex_ );

}

CINDER_APP_BASIC( HW04App, RendererGl )
