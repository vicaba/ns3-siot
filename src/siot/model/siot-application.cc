/*
 * b.cc
 *
 *  Created on: Nov 23, 2017
 *      Author: vcaballero
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

void SiotApplication::StartApplication(void){}

void SiotApplication::StopApplication() {}

void SiotApplication::HandleRead(Ptr<Socket> socket){}

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

} /* namespace ns3 */
