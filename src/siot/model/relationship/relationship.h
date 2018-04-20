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

#ifndef SRC_SIOT_MODEL_RELATIONSHIP_H_
#define SRC_SIOT_MODEL_RELATIONSHIP_H_

#include "ns3/core-module.h"

namespace ns3
{

    class SiotApplication;

    class Relationship : public Object {
     public:

      enum class Type {
        POR, CLOR, CWOR, OOR, SOR
      };

      static std::string
      RelationshipTypeToString (Relationship::Type);
      Relationship (Ptr<SiotApplication>);
      virtual
      ~Relationship ();
      Ptr<SiotApplication>
      GetRelatedTo () const;
      virtual const Relationship::Type
      GetType () const = 0;

     protected:
      //Relationship::Type m_relType;
      Ptr<SiotApplication> m_relNode;

    };

}

#endif /* SRC_SIOT_MODEL_RELATIONSHIP_H_ */
