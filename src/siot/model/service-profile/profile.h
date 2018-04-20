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

#ifndef SRC_SIOT_MODEL_SERVICE_PROFILE_PROFILE_H_
#define SRC_SIOT_MODEL_SERVICE_PROFILE_PROFILE_H_

#include "ns3/core-module.h"

namespace ns3
{

  class Profile {

   public:
    Profile ();
    virtual
    ~Profile ();
    void
    SetId(int);
    void
    SetName(std::string);
    void
    SetPosition(Vector);
    int
    GetId();
    std::string
    GetName();
    Vector
    GetPosition();

   private:
    int id;
    std::string name;
    Vector initialPosition;
  };
}

#endif SRC_SIOT_MODEL_SERVICE_PROFILE_PROFILE_H_
