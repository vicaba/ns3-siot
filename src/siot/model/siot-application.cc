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


#include "siot-application.h"

#include "ns3/log.h"
#include "ns3/ipv4-address.h"
#include "ns3/ipv6-address.h"
#include "ns3/address-utils.h"
#include "ns3/nstime.h"
#include "ns3/inet-socket-address.h"
#include "ns3/inet6-socket-address.h"
#include "ns3/socket.h"
#include "ns3/udp-socket.h"
#include "ns3/simulator.h"
#include "ns3/socket-factory.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/ptr.h"

namespace ns3 {


NS_LOG_COMPONENT_DEFINE("SiotApplication");

NS_OBJECT_ENSURE_REGISTERED(SiotApplication);

TypeId SiotApplication::GetTypeId(void)
{
	static TypeId tid =
			TypeId("ns3::SiotApplication")
			.SetParent<Application>()
			.SetGroupName("Applications")
			.AddConstructor<SiotApplication>()
			.AddAttribute("Port", "Port on which we listen for incoming packets.",
					UintegerValue(9),
					MakeUintegerAccessor(&SiotApplication::m_port),
					MakeUintegerChecker<uint16_t>())
			.AddTraceSource ("RelationshipAdded",
					"The value of the relationship added",
					MakeTraceSourceAccessor (&SiotApplication::m_relationshipAddedTrace),
					"ns3::SiotApplication::RelationshipAddedCallback");
	return tid;
}

SiotApplication::SiotApplication ()
{
  NS_LOG_FUNCTION(this);
}

SiotApplication::~SiotApplication ()
{
  NS_LOG_FUNCTION(this);
  this->m_cworRelationships.clear ();
  this->m_sorRelationships.clear ();
  m_socket = 0;
  m_socket6 = 0;
}

void
SiotApplication::DoDispose (void)
{
  NS_LOG_FUNCTION(this);

  Application::DoDispose ();
}

void
SiotApplication::StartApplication (void)
{
}

void
SiotApplication::StopApplication ()
{
}

void
SiotApplication::HandleRead (Ptr<Socket> socket)
{
}

void
SiotApplication::SetServiceProfile (Ptr<ServiceProfile> sp)
{
  this->m_serviceProfile = sp;
}

const Ptr<const ServiceProfile>
SiotApplication::GetProfile () const
{
  return this->m_serviceProfile;
}

void
SiotApplication::AddCworRelationship (const Ptr<CworRelationship> rel)
{
  this->m_cworRelationships.push_front (rel);
  this->NotifyRelationshipAdded (rel);
}

void
SiotApplication::AddSorRelationship (const Ptr<SorRelationship> rel)
{
  this->m_sorRelationships.push_front (rel);
  this->NotifyRelationshipAdded (rel);
}

const std::list<Ptr<CworRelationship>>
SiotApplication::GetCworRelationships ()
{
  return this->m_cworRelationships;
}

const std::list<Ptr<SorRelationship>>
SiotApplication::GetSorRelationships ()
{
  return this->m_sorRelationships;
}

void
SiotApplication::NotifyRelationshipAdded (Ptr<const Relationship> rel)
{
  this->m_relationshipAddedTrace (this, rel);
}

} /* namespace ns3 */
