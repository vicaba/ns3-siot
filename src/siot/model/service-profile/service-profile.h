/*
 * node-profile.h
 *
 *  Created on: Oct 30, 2017
 *      Author: vcaballero
 */

#ifndef NODE_PROFILE_H_
#define NODE_PROFILE_H_

#include <unordered_map>

#include "ns3/core-module.h"

namespace ns3
{

class ServiceProfile: public Object
{

public:

	ServiceProfile(std::string, std::unordered_map<std::string, std::string>);
	virtual ~ServiceProfile();
	std::unordered_map<std::string, std::string> GetRaw() const;
	friend std::ostream& operator <<(std::ostream& outputStream, const ServiceProfile& sp);

private:

	std::vector<std::string> GetValues() const;

	std::string m_identifier;
	std::unordered_map<std::string, std::string> m_raw;

};

} /* namespace ns3 */

#endif /* NODE_PROFILE_H_ */
