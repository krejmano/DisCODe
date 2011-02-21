/*!
 * \file cvGobanFinder
 * \brief Goban finder.
 */

#ifndef CVGOBANFINDER_PROCESSOR_HPP_
#define CVGOBANFINDER_PROCESSOR_HPP_

#include <cv.h>
#include <boost/shared_ptr.hpp>
#include "Component_Aux.hpp"
#include "Panel_Empty.hpp"
#include "Objects3D/GobanMarkers.hpp"
#include "Drawable.hpp"
#include "Timer.hpp"


namespace Processors {
namespace cvGobanFinder {


/*!
 * \brief cvGobanFinder properties
 */
struct cvGobanFinder_Props: public Base::Props
{
	cv::Size size;
	int height;

	/*!
	 * \copydoc Base::Props::load
	 */
	void load(const ptree & pt)
	{

		LOG(LTRACE) << "cvFindGoban::load()\n";
		//size= pt.get<cv::Size>("size");

	}

	/*!
	 * \copydoc Base::Props::save
	 */
	void save(ptree & pt)
	{
		LOG(LTRACE) << "cvFindGoban::load()\n";

	}

};

/*!
 * \class cvGobanFinder_Processor
 * \brief cvGobanFinder processor class.
 */
class cvGobanFinder_Processor: public Base::Component
{
public:
	/*!
	 * Constructor.
	 */
	cvGobanFinder_Processor(const std::string & name = "");

	/*!
	 * Destructor
	 */
	virtual ~cvGobanFinder_Processor();

	/*!
	 * Return window properties
	 */
	Base::Props * getProperties()
	{
		return &props;
	}

protected:

	/*!
	 * Connects source to given device.
	 */
	bool onInit();

	/*!
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*!
	 * Retrieves data from device.
	 */
	bool onStep();

	/*!
	 * Start component
	 */
	bool onStart();

	/*!
	 * Stop component
	 */
	bool onStop();

	/// Properties
	cvGobanFinder_Props props;

private:

	void	onNewImage();

	Base::EventHandler <cvGobanFinder_Processor> h_onNewImage;


	Base::DataStreamIn <cv::Mat> in_img;
	//img stream

	Base::DataStreamOut <Types::Objects3D::GobanMarkers> gobanOut;

	Base::Event *gobanFound;

	Base::Event *gobanNotFound;

	cv::Mat junctions;

	Common::Timer timer;

boost::shared_ptr<Types::Objects3D::GobanMarkers> goban;

};


}//: namespace cvGobanFinder
}//: namespace Processors


/*
 * Register processor component.
 */
REGISTER_PROCESSOR_COMPONENT("cvGobanFinder", Processors::cvGobanFinder::cvGobanFinder_Processor, Common::Panel_Empty)

#endif /* CVGOBANFINDER_PROCESSOR_HPP_ */
