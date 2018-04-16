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

#ifndef SRC_SIOT_SIOT_APPLICATION_H_
#define SRC_SIOT_SIOT_APPLICATION_H_

#include "ns3/core-module.h"
#include "ns3/application.h"

#include "ns3/relationship.h"
#include "ns3/cwor-relationship.h"
#include "ns3/sor-relationship.h"

#include "ns3/service-profile.h"

namespace ns3
{

class Socket;
class Address;

class SiotApplication : public Application
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId
  GetTypeId (void);
  SiotApplication ();
  virtual
  ~SiotApplication ();
  void
  SetServiceProfile (Ptr<ServiceProfile>);
  const Ptr<const ServiceProfile>
  GetProfile () const;
  void
  AddCworRelationship (const Ptr<CworRelationship>);
  void
  AddSorRelationship (const Ptr<SorRelationship>);
  const std::list<Ptr<CworRelationship>>
  GetCworRelationships ();
  const std::list<Ptr<SorRelationship>>
  GetSorRelationships ();

  typedef void
  (*RelationshipAddedCallback) (Ptr<const SiotApplication>, Ptr<const Relationship>);

protected:
  virtual void
  DoDispose (void);

private:

  virtual void
  StartApplication (void);
  virtual void
  StopApplication (void);
  void
  NotifyRelationshipAdded (Ptr<const Relationship>);

  /**
   * \brief Handle a packet reception.
   *
   * This function is called by lower layers.
   *
   * \param socket the socket the packet was received to.
   */
  void
  HandleRead (Ptr<Socket> socket);

  uint16_t m_port; //!< Port on which we listen for incoming packets.
  Ptr<Socket> m_socket; //!< IPv4 Socket
  Ptr<Socket> m_socket6; //!< IPv6 Socket
  Address m_local; //!< local multicast address
  std::list<Ptr<CworRelationship>> m_cworRelationships;
  std::list<Ptr<SorRelationship>> m_sorRelationships;
  Ptr<ServiceProfile> m_serviceProfile;
  //MobilityAdjacency m_mobilityAdjacency;

  ns3::TracedCallback<Ptr<const SiotApplication>, Ptr<const Relationship>> m_relationshipAddedTrace;
};

} // namespace ns3

#endif /* SRC_SIOT_MODEL_SIOT_APPLICATION_H_ */
