/*
 * node-profile.cc
 *
 *  Created on: Oct 30, 2017
 *      Author: vcaballero
 */

#include "service-profile.h"

namespace ns3
{

ServiceProfile::ServiceProfile(std::string identifier, std::unordered_map<std::string, std::string> energyProfile)
{
	this->m_identifier = identifier;
	this->m_raw = energyProfile;

}

ServiceProfile::~ServiceProfile()
{
	m_raw.clear();
}

std::unordered_map<std::string, std::string> ServiceProfile::GetRaw() const
{
	return this->m_raw;
}

std::ostream& operator <<(std::ostream& outputStream, const ServiceProfile& sp)
{

	auto raw = sp.GetRaw();

	if (!raw.empty()) {

		outputStream << '{';

		for (auto it = raw.begin(); it != raw.end(); it++) {
			outputStream << "[" << it->first << " -> " << it->second << "]";
		}

		outputStream << '}' << std::endl;

	} else {
		outputStream << "{}" << std::endl;
	}

	return outputStream;
}

std::vector<std::string> ServiceProfile::GetValues() const {
	std::vector<std::string> v;
	for(auto it = this->m_raw.begin(); it != this->m_raw.end(); ++it) {
	  v.push_back(it->second);
	}
	return v;
}

} /* namespace ns3 */
