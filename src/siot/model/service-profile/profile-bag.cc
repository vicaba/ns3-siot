/*
 * profile-bag.cpp
 *
 *  Created on: Nov 8, 2017
 *      Author: vcaballero
 */

#include "profile-bag.h"

namespace ns3
{

ProfileBag::ProfileBag ()
{

}

ProfileBag::~ProfileBag ()
{
  this->m_bag.clear ();
}

void
ProfileBag::AddProfile (const std::string, const ServiceProfile)
{

}

std::experimental::fundamentals_v1::optional<ServiceProfile>
ProfileBag::Search (const std::string category, const std::string identifier) const
{
  //auto s = this->m_bag.find(category);
  return std::experimental::fundamentals_v1::nullopt;

}

/*ServiceProfile ProfileBag::DeleteProfile(const std::string, const std::string)
 {
 return this->m_bag.at("a");
 }*/

} /* namespace ns3 */
