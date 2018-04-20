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

#include "service-profile.h"

namespace ns3
{

    ServiceProfile::ServiceProfile (std::string identifier,
                                    std::unordered_map<std::string, std::string> energyProfile)
    {
      this->m_identifier = identifier;
      this->m_raw = energyProfile;

    }

    ServiceProfile::~ServiceProfile ()
    {
      m_raw.clear ();
    }

    std::unordered_map<std::string, std::string>
    ServiceProfile::GetRaw () const
    {
      return this->m_raw;
    }

    std::ostream &
    operator<< (std::ostream &outputStream, const ServiceProfile &sp)
    {

      auto raw = sp.GetRaw ();

      if (!raw.empty ())
        {

          outputStream << '{';

          for (auto it = raw.begin (); it != raw.end (); it++)
            {
              outputStream << "[" << it->first << " -> " << it->second << "]";
            }

          outputStream << '}' << std::endl;

        }
      else
        {
          outputStream << "{}" << std::endl;
        }

      return outputStream;
    }

    std::vector<std::string>
    ServiceProfile::GetValues () const
    {
      std::vector<std::string> v;
      for (auto it = this->m_raw.begin (); it != this->m_raw.end (); ++it)
        {
          v.push_back (it->second);
        }
      return v;
    }

} /* namespace ns3 */
