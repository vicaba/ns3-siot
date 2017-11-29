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

#ifndef NODE_PROFILE_H_
#define NODE_PROFILE_H_

#include <unordered_map>

#include "ns3/core-module.h"

namespace ns3
{

class ServiceProfile : public Object
{

public:

  ServiceProfile (std::string, std::unordered_map<std::string, std::string>);
  virtual
  ~ServiceProfile ();
  std::unordered_map<std::string, std::string>
  GetRaw () const;
  friend std::ostream&
  operator << (std::ostream& outputStream, const ServiceProfile& sp);

private:

  std::vector<std::string>
  GetValues () const;

  std::string m_identifier;
  std::unordered_map<std::string, std::string> m_raw;

};

} /* namespace ns3 */

#endif /* NODE_PROFILE_H_ */
