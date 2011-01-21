/*!
 * \file
 * \brief
 */

#ifndef CVGOBANFINDER_PROCESSOR_HPP_
#define CVGOBANFINDER_PROCESSOR_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "Panel_Empty.hpp"
#include "DataStream.hpp"
#include "Props.hpp"

namespace Processors {
namespace cvGobanFinder {

/*!
 * \brief cvGobanFinder properties
 */
struct cvGobanFinder_Props: public Base::Props
{

	/*!
	 * \copydoc Base::Props::load
	 */
	void load(const ptree & pt)
	{

	}

	/*!
	 * \copydoc Base::Props::save
	 */
	void save(ptree & pt)
	{

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

};

}//: namespace cvGobanFinder
}//: namespace Processors


/*
 * Register processor component.
 */
REGISTER_PROCESSOR_COMPONENT("cvGobanFinder", Processors::cvGobanFinder::cvGobanFinder_Processor, Common::Panel_Empty)

#endif /* CVGOBANFINDER_PROCESSOR_HPP_ */
