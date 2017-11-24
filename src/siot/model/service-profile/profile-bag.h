/*
 * profile-bag.h
 *
 *  Created on: Nov 8, 2017
 *      Author: vcaballero
 */

#ifndef SRC_SIOT_MODEL_SERVICE_PROFILE_PROFILE_BAG_H_
#define SRC_SIOT_MODEL_SERVICE_PROFILE_PROFILE_BAG_H_

#include <unordered_map>
#include <experimental/optional>

#include "service-profile.h"


namespace ns3
{

class ProfileBag
{
public:
	ProfileBag();
	virtual ~ProfileBag();
	void AddProfile(const std::string, const ServiceProfile);
	std::experimental::fundamentals_v1::optional<ServiceProfile> Search(const std::string, const std::string) const;
	//ServiceProfile DeleteProfile(const std::string, const std::string);

private:

	std::unordered_map<std::string, std::vector<ServiceProfile>> m_bag;

};

} /* namespace ns3 */

#endif /* SRC_SIOT_MODEL_SERVICE_PROFILE_PROFILE_BAG_H_ */
