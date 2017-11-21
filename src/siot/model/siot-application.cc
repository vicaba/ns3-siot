/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright 2007 University of Washington
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

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("SiotApplication");

NS_OBJECT_ENSURE_REGISTERED(SiotApplication);

/*
static TypeId tid = TypeId ("ns3::MobilityModel")
  .SetParent<Object> ()
  .SetGroupName ("Mobility")
  .AddAttribute ("Position", "The current position of the mobility model.",
                 TypeId::ATTR_SET | TypeId::ATTR_GET,
                 VectorValue (Vector (0.0, 0.0, 0.0)),
                 MakeVectorAccessor (&MobilityModel::SetPosition,
                                     &MobilityModel::GetPosition),
                 MakeVectorChecker ())
  .AddAttribute ("Velocity", "The current velocity of the mobility model.",
                 TypeId::ATTR_GET,
                 VectorValue (Vector (0.0, 0.0, 0.0)), // ignored initial value.
                 MakeVectorAccessor (&MobilityModel::GetVelocity),
                 MakeVectorChecker ())
  .AddTraceSource ("CourseChange",
                   "The value of the position and/or velocity vector changed",
                   MakeTraceSourceAccessor (&MobilityModel::m_courseChangeTrace),
                   "ns3::MobilityModel::TracedCallback")

*/

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

SiotApplication::SiotApplication()
{
	NS_LOG_FUNCTION(this);
}

SiotApplication::~SiotApplication()
{
	NS_LOG_FUNCTION(this);
	this->m_cworRelationships.clear();
	this->m_sorRelationships.clear();
	m_socket = 0;
	m_socket6 = 0;
}

void SiotApplication::DoDispose(void)
{
	NS_LOG_FUNCTION(this);
	Application::DoDispose();
}

void SiotApplication::StartApplication(void)
{/*
 NS_LOG_FUNCTION(this);

 if (m_socket == 0)
 {
 TypeId tid = TypeId::LookupByName("ns3::UdpSocketFactory");
 m_socket = Socket::CreateSocket(GetNode(), tid);
 InetSocketAddress local = InetSocketAddress(Ipv4Address::GetAny(),
 m_port);
 if (m_socket->Bind(local) == -1)
 {
 NS_FATAL_ERROR("Failed to bind socket");
 }
 if (addressUtils::IsMulticast(m_local))
 {
 Ptr<UdpSocket> udpSocket = DynamicCast<UdpSocket>(m_socket);
 if (udpSocket)
 {
 // equivalent to setsockopt (MCAST_JOIN_GROUP)
 udpSocket->MulticastJoinGroup(0, m_local);
 }
 else
 {
 NS_FATAL_ERROR("Error: Failed to join multicast group");
 }
 }
 }

 if (m_socket6 == 0)
 {
 TypeId tid = TypeId::LookupByName("ns3::UdpSocketFactory");
 m_socket6 = Socket::CreateSocket(GetNode(), tid);
 Inet6SocketAddress local6 = Inet6SocketAddress(Ipv6Address::GetAny(),
 m_port);
 if (m_socket6->Bind(local6) == -1)
 {
 NS_FATAL_ERROR("Failed to bind socket");
 }
 if (addressUtils::IsMulticast(local6))
 {
 Ptr<UdpSocket> udpSocket = DynamicCast<UdpSocket>(m_socket6);
 if (udpSocket)
 {
 // equivalent to setsockopt (MCAST_JOIN_GROUP)
 udpSocket->MulticastJoinGroup(0, local6);
 }
 else
 {
 NS_FATAL_ERROR("Error: Failed to join multicast group");
 }
 }
 }

 m_socket->SetRecvCallback(MakeCallback(&SiotApplication::HandleRead, this));
 m_socket6->SetRecvCallback(MakeCallback(&SiotApplication::HandleRead, this));*/
}

void SiotApplication::StopApplication()
{
	/*	NS_LOG_FUNCTION(this);

	 if (m_socket != 0)
	 {
	 m_socket->Close();
	 m_socket->SetRecvCallback(MakeNullCallback<void, Ptr<Socket> >());
	 }
	 if (m_socket6 != 0)
	 {
	 m_socket6->Close();
	 m_socket6->SetRecvCallback(MakeNullCallback<void, Ptr<Socket> >());
	 }*/
}

void SiotApplication::HandleRead(Ptr<Socket> socket)
{
	/*	NS_LOG_FUNCTION(this << socket);

	 Ptr<Packet> packet;
	 Address from;
	 while ((packet = socket->RecvFrom(from)))
	 {
	 if (InetSocketAddress::IsMatchingType(from))
	 {
	 NS_LOG_INFO(
	 "At time " << Simulator::Now ().GetSeconds () << "s server received " << packet->GetSize () << " bytes from " << InetSocketAddress::ConvertFrom (from).GetIpv4 () << " port " << InetSocketAddress::ConvertFrom (from).GetPort ());
	 }
	 else if (Inet6SocketAddress::IsMatchingType(from))
	 {
	 NS_LOG_INFO(
	 "At time " << Simulator::Now ().GetSeconds () << "s server received " << packet->GetSize () << " bytes from " << Inet6SocketAddress::ConvertFrom (from).GetIpv6 () << " port " << Inet6SocketAddress::ConvertFrom (from).GetPort ());
	 }

	 packet->RemoveAllPacketTags();
	 packet->RemoveAllByteTags();

	 NS_LOG_LOGIC("Echoing packet");
	 socket->SendTo(packet, 0, from);

	 if (InetSocketAddress::IsMatchingType(from))
	 {
	 NS_LOG_INFO(
	 "At time " << Simulator::Now ().GetSeconds () << "s server sent " << packet->GetSize () << " bytes to " << InetSocketAddress::ConvertFrom (from).GetIpv4 () << " port " << InetSocketAddress::ConvertFrom (from).GetPort ());
	 }
	 else if (Inet6SocketAddress::IsMatchingType(from))
	 {
	 NS_LOG_INFO(
	 "At time " << Simulator::Now ().GetSeconds () << "s server sent " << packet->GetSize () << " bytes to " << Inet6SocketAddress::ConvertFrom (from).GetIpv6 () << " port " << Inet6SocketAddress::ConvertFrom (from).GetPort ());
	 }
	 }*/
}

void SiotApplication::SetServiceProfile(Ptr<ServiceProfile> sp)
{
	this->m_serviceProfile = sp;
}

const Ptr<const ServiceProfile> SiotApplication::GetProfile() const
{
	return this->m_serviceProfile;
}

void SiotApplication::AddCworRelationship(const Ptr<CworRelationship> rel)
{
	this->m_cworRelationships.push_front(rel);
	this->NotifyRelationshipAdded(rel);
}

void SiotApplication::AddSorRelationship(const Ptr<SorRelationship> rel)
{
	this->m_sorRelationships.push_front(rel);
	this->NotifyRelationshipAdded(rel);
}

const std::list<Ptr<CworRelationship>> SiotApplication::GetCworRelationships()
{
	return this->m_cworRelationships;
}

const std::list<Ptr<SorRelationship>> SiotApplication::GetSorRelationships()
{
	return this->m_sorRelationships;
}

void SiotApplication::NotifyRelationshipAdded(Ptr< const Relationship> rel)
{
	this->m_relationshipAddedTrace(rel, *this);
}

} // Namespace ns3
