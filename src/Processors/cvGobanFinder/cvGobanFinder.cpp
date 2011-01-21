/*!
 * \file
 * \brief
 */

#include <memory>
#include <string>

#include "cvGobanFinder.hpp"
#include "Common/Logger.hpp"

namespace Processors {
namespace cvGobanFinder {

cvGobanFinder_Processor::cvGobanFinder_Processor(const std::string & name) : Base::Component(name)
{
	LOG(LTRACE) << "Hello cvGobanFinder_Processor\n";
}

cvGobanFinder_Processor::~cvGobanFinder_Processor()
{
	LOG(LTRACE) << "Good bye cvGobanFinder_Processor\n";
}

bool cvGobanFinder_Processor::onInit()
{
	LOG(LTRACE) << "cvGobanFinder_Processor::initialize\n";

	// Register data streams, events and event handlers HERE!

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

}//: namespace cvGobanFinder
}//: namespace Processors
