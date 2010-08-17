/*!
 * \file ComponentManager.hpp
 * \brief File containing the ComponentManager class
 *
 * \author tkornuta
 * \date Feb 10, 2010
 */

#ifndef COMPONENTMANAGER_HPP_
#define COMPONENTMANAGER_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include <boost/foreach.hpp>
#include <boost/ptr_container/ptr_map.hpp>

#include "boost/filesystem.hpp"
using namespace boost::filesystem;

#include "Component_Aux.hpp"
#include "FraDIAException.hpp"
#include "SharedLibraryCommon.hpp"
#include "Utils.hpp"
#include "Logger.hpp"
#include "ComponentFactory.hpp"


using namespace boost::property_tree;

using namespace std;

namespace Core {

/*!
 * \class ComponentManager
 * \brief
 * \author tkornuta
 */
class ComponentManager
{
protected:
	/*!
	 * List of component factories properly loaded by the manager.
	 */
	boost::ptr_map <string, Core::ComponentFactory> component_factories;

	/*!
	 * List of created components
	 */
	std::map <string, Base::Component*> components;
	
	typedef std::pair<std::string, Base::Component *> comp_pair;

public:
	/*!
	 * Constructor
	 */
	ComponentManager()
	{
		LOG(TRACE) << "ComponentManager: Hello private \n";
	}

	/*!
	 * Public destructor.
	 */
	~ComponentManager()
	{
		LOG(TRACE) << "ComponentManager: Goodbye public\n";
	}
	
	void release() {
		BOOST_FOREACH(comp_pair comp, components)
			delete comp.second;
	}

	/*!
	 * Method tries to create components from all shared libraries loaded from the . directory.
	 */
	void initializeComponentsList()
	{
		// Retrieve node with default settings from configurator.
		//ptree * tmp_node = CONFIGURATOR.returnManagerNode(COMPONENT_TYPE);

		// Get filenames.
		vector <string> files = vector <string> ();
		getSOList(".", files);

		// Check number of so's to import.
		if (files.size() == 0) {
			// I think, that throwing here is much to brutal
			//throw Common::FraDIAException(string(MANAGER_NAME)+string("Manager: There are no dynamic libraries in the current directory."));
			LOG(WARNING) << "ComponentManager: There are no dynamic libraries in the current directory.\n";
			return;
		}

		// Iterate through so names and add retrieved components to list.
		BOOST_FOREACH(string file, files)
		{
			// Create component empty "shell".
			ComponentFactory* k = new ComponentFactory();
			// Try to initialize component.
			if (k->lazyInitialize(file))
			{
				// Add component to list.
				component_factories.insert(k->getName(), k);
			}
			else
				// Delete incorrect component.
				delete (k);
		}//: FOREACH

		// Check number of successfully loaded components.
		//if (!component_factories.size())
		//	throw Common::FraDIAException(string(MANAGER_NAME)+string("Manager: There are no compatible dynamic libraries in current directory."));
		LOG(NOTICE) << "Found " << component_factories.size() << " components\n";
	}

	/*!
	 *
	 */
	void deactivateComponentList() {
		component_factories.release();
	}

	/*!
	 *
	 * @param name
	 * @param type
	 * @return
	 */
	Base::Component* createComponent(const std::string & name, const std::string & type) {
		if (components.count(name) > 0) {
			LOG(WARNING) << "Module " << name << " already created. Returning previous one.\n";
			return components[name];
		}

		if (component_factories.count(type) < 1) {
			LOG(ERROR) << "Module type " << type << " not found!\n";
			throw Common::FraDIAException("createComponent");
		}

		components[name] = component_factories[type].create(name);
		LOG(INFO) << name << " (" << type << ") component created\n";
		return components[name];
	}

	/*!
	 *
	 * @param name
	 * @return
	 */
	Base::Component * getComponent(const std::string & name) {
		if (components.count(name) < 1) {
			LOG(ERROR) << "Module " << name << " can't be found!\n";
			throw Common::FraDIAException("getComponent");
		}

		return components[name];
	}

protected:

	/*!
	 *
	 * @param dir_
	 * @param files
	 */
	void getSOList(string dir_, vector <string>& files)
	{
		std::string regexp = "\\w*.";
		regexp += LIB_EXT;

		LOG(TRACE) << "LIB_EXT = " LIB_EXT << "\n";

		files = Utils::searchFiles(dir_, regexp);
	}

};

}//: namespace Core

#endif /* COMPONENTMANAGER_HPP_ */
