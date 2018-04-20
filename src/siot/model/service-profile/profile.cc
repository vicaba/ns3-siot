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

#include "profile.h"

namespace ns3
{

  Profile::Profile ()
  {

  }

  Profile::~Profile ()
  {
  }

  void
  Profile::SetId (const int id)
  {
    this->m_id = id;
  }

  void
  Profile::SetName (const std::string name)
  {
    this->m_name = name;
  }

  void
  Profile::SetInitialPosition (const ns3::Vector position)
  {
    this->m_initialPosition = position;
  }

  const int
  Profile::GetId() const
  {
    return this->m_id;
  }

  const std::string
  Profile::GetName() const
  {
    return this->m_name;
  }

  const Vector
  Profile::GetInitialPosition() const
  {
    return this->m_initialPosition;
  }

  std::ostream &
  operator<< (std::ostream &outputStream, const Profile &p)
  {
    outputStream << std::to_string ( p.GetId ()) << ", " << p.GetName () << ", " << std::to_string (this->m_initialPosition.x) << " " << std::to_string (this->m_initialPosition.y);
    return outputStream;
  }

} /* namespace ns3 */