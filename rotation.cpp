#include<iostream>
#include<cmath>
#include<string>
#include<cstdlib>
#include<ctime>
#include<chrono>
//#include<thread>
#include<SFML/Graphics.hpp>

#include "helper.h"
#include "framerate.h"
#include "reference_frame.h"
#include "base.h"
#include "vector_class2.h"

using namespace std;

//###################################################################
//###################################################################

class RBall : public Base
{
	private:
		sf::CircleShape ball;
		double x_, y_, r_;

	public:
		RBall(double x, double y, double r, sf::Color color);
		void move(double x, double y);
		void print();
};

RBall::RBall(double x, double y, double r, sf::Color color)
 :x_(x), y_(y), r_(r), ball(r) 
{
	ball.setFillColor(color);
	
	ball.setPosition((*RF)(x_-r_,'x'), (*RF)(y_+r_,'y')); 
}

//====================================================================

void RBall::move(double x, double y){
	ball.setPosition((*RF)(x-r_,'x'), (*RF)(y+r_,'y')); 
}

void RBall::print(){
	Window->draw(ball);
}

//####################################################################
//####################################################################
//####################################################################

int main(){
	srand(time(0));
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	//cout<<"Display settings: "<< sf::VideoMode::getDesktopMode().width << ", " << sf::VideoMode::getDesktopMode().height<<endl;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window",sf::Style::Default, settings);
   ReferenceFrame RF(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 1);

	RBall::set_rf(&RF);
	RBall::set_window(&window);
	RBall ball0(0.0, 0.0, 4, sf::Color(156, 86, 216));
	
	RBall ball(200.0, 200.0, 20, sf::Color(56, 186, 126));
	
	Vect<3> VX({7.0, -11.0, 8.0});
	Rotation<3> Rotacion(VX, 0.5);
	Vect<3> V({200.0, 200.0, 0.0});
	
	Vect<3> VX2({0, 0, 1});
	Rotation<3> Rotacion2(VX2, 0.5);
	Vect<3> V2({200.0, 200.0, 0.0});
	RBall ball2(200.0, 200.0, 20, sf::Color(246, 6, 116));

	FrameRate Framerate(4);
	double t;
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type==sf::Event::Closed)
			{
				window.close();
			}
		}

		if(Framerate()>=0){
			Framerate.reset();

			window.clear(sf::Color::White);
		  
			//################################################################
			//################################################################
			//draw things here ###############################################
		  	//###################### 
			//######################
			ball0.print();
			V=Rotacion(V);
			ball.move(V.get_coordinate(0), V.get_coordinate(1));
			ball.print();

			V2=Rotacion2(V2);
			ball2.move(V2.get_coordinate(0), V2.get_coordinate(1));
			ball2.print();
			/**/
			// END of drawing ###############################################
			//###############################################################
			//###############################################################
			t=0;
			Framerate.reset();
		}
		window.display();
		
	}
	

	return 0;
}


