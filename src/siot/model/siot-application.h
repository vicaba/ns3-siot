/*
 * b.h
 *
 *  Created on: Nov 23, 2017
 *      Author: vcaballero
 */

#ifndef SRC_SIOT_MODEL_SIOT_APPLICATION_H_
#define SRC_SIOT_MODEL_SIOT_APPLICATION_H_


#include "ns3/core-module.h"
#include "ns3/application.h"

#include "ns3/relationship.h"
#include "ns3/cwor-relationship.h"
#include "ns3/sor-relationship.h"

#include "ns3/service-profile.h"

namespace ns3 {

class Socket;
class Address;

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

	typedef void (* RelationshipAddedCallback)(Ptr<const SiotApplication>, Ptr<const Relationship>);

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

	ns3::TracedCallback<Ptr<const SiotApplication>, Ptr<const Relationship>> m_relationshipAddedTrace;
};


} // namespace ns3

#endif /* SRC_SIOT_MODEL_SIOT_APPLICATION_H_ */
