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

#ifndef SIOT_SERVER_H
#define SIOT_SERVER_H

#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/address.h"

#include "ns3/relationship-module.h"
#include "ns3/service-profile.h"

namespace ns3
{

class Socket;
class Packet;

/**
 * \ingroup applications 
 * \defgroup siot SIoT
 */

/**
 * \ingroup siot
 * \brief A SIoT server
 *
 * Every packet received is sent back.
 */
class SiotApplication: public Application
{
public:
	/**
	 * \brief Get the type ID.
	 * \return the object TypeId
	 */
	static TypeId GetTypeId(void);
	SiotApplication();
	virtual ~SiotApplication();
	void SetServiceProfile(Ptr<ServiceProfile>);
	const Ptr<const ServiceProfile> GetProfile() const;
	void AddCworRelationship(const Ptr<CworRelationship>);
	void AddSorRelationship(const Ptr<SorRelationship>);
	const std::list<Ptr<CworRelationship>> GetCworRelationships();
	const std::list<Ptr<SorRelationship>> GetSorRelationships();

	typedef void (* RelationshipAddedCallback)(Ptr<const Relationship>, const SiotApplication&);

protected:
	virtual void
	DoDispose(void);

private:

	virtual void
	StartApplication(void);
	virtual void
	StopApplication(void);
	void NotifyRelationshipAdded(Ptr<const Relationship>);

	/**
	 * \brief Handle a packet reception.
	 *
	 * This function is called by lower layers.
	 *
	 * \param socket the socket the packet was received to.
	 */
	void HandleRead(Ptr<Socket> socket);

	uint16_t m_port; //!< Port on which we listen for incoming packets.
	Ptr<Socket> m_socket; //!< IPv4 Socket
	Ptr<Socket> m_socket6; //!< IPv6 Socket
	Address m_local; //!< local multicast address
	std::list<Ptr<CworRelationship>> m_cworRelationships;
	std::list<Ptr<SorRelationship>> m_sorRelationships;
	Ptr<ServiceProfile> m_serviceProfile;

	ns3::TracedCallback<Ptr<const Relationship>, const SiotApplication&> m_relationshipAddedTrace;
};


} // namespace ns3

#endif /* SIOT_SERVER_H */

