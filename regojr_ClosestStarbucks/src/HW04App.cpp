#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Starbucks.h"
#include "regojrStarbucks.h"

#include <iostream>
#include <fstream>

using namespace ci;
using namespace ci::app;
using namespace std;



class HW04App : public AppBasic {
  public:
	void setup();

	//void mouseDown( MouseEvent event );	
	//void update();
	//void draw();

private:


};

void HW04App::setup()
{
	cout << "HEY SNITCHES" << endl;
	cin.get();
}
/*
void HW04App::mouseDown( MouseEvent event )
{
}

void HW04App::update()
{
}

void HW04App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}
*/
CINDER_APP_BASIC( HW04App, RendererGl )
