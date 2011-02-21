/*
 * GobanFinder
 * brief goban finding
 * created: 21.01.11
 * author: kaji
 */

#include <memory>
#include <string>
#include "cvGobanFinder.hpp"
#include "Common/Logger.hpp"



namespace Processors {
namespace cvGobanFinder {

using namespace std;
using namespace boost;
using namespace cv;
using namespace Types::Objects3D;


cvGobanFinder_Processor::cvGobanFinder_Processor(const std::string & name) : Base::Component(name)
{
	LOG(LTRACE) << "cvGobanFinder_Processor born\n";
}

cvGobanFinder_Processor::~cvGobanFinder_Processor()
{
	LOG(LTRACE) << "cvGobanFinder_Processor killed\n";
}

bool cvGobanFinder_Processor::onInit()
{
	LOG(LTRACE) << "cvGobanFinder_Processor::initialize\n";

	h_onNewImage.setup(this, &cvGobanFinder_Processor::onNewImage);
		registerHandler("onNewImage", &h_onNewImage);

	registerStream("in_img", &in_img);
	registerStream("out_model", &gobanOut);

	gobanFound = registerEvent("GobanFound");
	gobanNotFound = registerEvent("GobanNotFound");

	goban = boost::shared_ptr <GobanMarkers>(new GobanMarkers(props.size));

	vector <Point3f> modelpoints;

	for (int i=0; i < props.height; i++)
		for(int j=0; j < props.height; j++)
		{
			modelpoints.push_back(Point3f(-j * props.height, -i * props.height, 0));
		}

	LOG(LTRACE) << "component initialing done\n";
	return true;
}

bool cvGobanFinder_Processor::onFinish()
{
	LOG(LTRACE) << "cvGobanFinder_Processor::finish\n";

	return true;
}

bool cvGobanFinder_Processor::onStep()
{
	LOG(LTRACE) << "cvGobanFinder_Processor::step\n";
	return true;
}

bool cvGobanFinder_Processor::onStop()
{
	return true;
}

bool cvGobanFinder_Processor::onStart()
{
	return true;
}

void cvGobanFinder_Processor::onNewImage()
{
	LOG(LTRACE) << "New image arrived, processing commences";

	Mat image = in_img.read();
	Size tmp = image.size();
	timer.restart();

	Mat image_gray, image_out;

	Canny( image, image_gray, 50, 200, 3 );
	vector<Vec2f> lines;
	vector<Point> board;
	
	Point pt1, pt2;

	HoughLines(image_gray, lines, 1, CV_PI/180, 125, 0, 0 );

	for( size_t(i) = 0; i < lines.size(); i++ )
	    {
	        float rho = lines[i][0], rho2 = lines[i+1][0];
		float theta = lines[i][1], theta2 = lines[i+1][1];
		
		double a1 = cos(theta), b1 = sin(theta), a2 = cos(theta2), b2 = sin(theta2);
//		pt1.x = cvRound(x0 + 1000*(-b));
//		pt1.y = cvRound(y0 + 1000*(a));
		pt1.x = (b1 - b2)/(a2 - a1)*cvRound(rho);
		pt1.y = (a2 * b1 - b2 * a1) / (a2 - a1)*cvRound(rho2);
		if ((pt1.x > 0 && pt1.y > 0) && (pt1.x < tmp.width && pt1.y < tmp.height))
		board.push_back(pt1);

	    }

//=============================SAME POINTS FILTERING=================================
		
     	 for (size_t(j) = 0; j < board.size() ; j++ )
	
            {
	     	for (size_t(i) = j+1; i < board.size() ; i++ )
		 {
	                if ((board[j].x == board[i].x && board[j].y == board[i].y))
		           {
		//               std::cout << "lol, powtarzaja sie po raz: " << k << std::endl;
		                 pt2 = board[i];
		                 board[i] = board[board.size()];
		                 board[board.size()] = pt2;
		                 board.pop_back();
		                 
		           }

	          }

	     }


//========================SIMILAR POINT FILTERING=======================================


        for (size_t(j) =0; j < board.size(); j++ )
	  {
           for (size_t(i) = j+1; i < board.size(); i++ )
             {
	      if( ( sqrt(((board[j].x - board[i].x)*(board[j].x - board[i].x)) + ((board[j].y - board[i].y)*(board[j].y - board[i].y))) ) < 15 )
	        {
//	            std::cout << "lol, podobne punkty. Punkt nr : " << j << " i " << i << std::endl;

  	           while( ( sqrt(((board[board.size()].x - board[i].x)*(board[board.size()].x - board[i].x)) + ((board[board.size()].y - board[i].y)*(board[board.size()].y - board[i].y))) ) < 15 )
		     {
//		       std::cout << "lol, ostatni punkt jest podobny " << std::endl;
                       board.pop_back();
		     }

		   pt2 = board[i];
		   board[i] = board[board.size()];
		   board.pop_back();
               
	       }
	     }

	   }


}
}//: namespace cvGobanFinder
}//: namespace Processors
