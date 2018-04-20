/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2017 La Salle - Universitat Ramon Llull
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Víctor Caballero <vcaballero@salleurl.edu>
 */

#ifndef SRC_SIOT_MODEL_SERVICE_PROFILE_PROFILE_BAG_H_
#define SRC_SIOT_MODEL_SERVICE_PROFILE_PROFILE_BAG_H_

#include <unordered_map>
#include <experimental/optional>

#include "service-profile.h"

namespace ns3
{

    class ProfileBag {
     public:
      ProfileBag ();
      virtual
      ~ProfileBag ();
      void
      AddProfile (const std::string, const ServiceProfile);
      std::experimental::fundamentals_v1::optional<ServiceProfile>
      Search (const std::string, const std::string) const;
      //ServiceProfile DeleteProfile(const std::string, const std::string);

     private:

      std::unordered_map<std::string, std::vector<ServiceProfile>> m_bag;

    };

} /* namespace ns3 */

#endif /* SRC_SIOT_MODEL_SERVICE_PROFILE_PROFILE_BAG_H_ */
