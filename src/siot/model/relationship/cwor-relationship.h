/*
 * cwor-relationship.h
 *
 *  Created on: Nov 2, 2017
 *      Author: vcaballero
 */

#ifndef RELATIONSHIP_CWOR_RELATIONSHIP_H_
#define RELATIONSHIP_CWOR_RELATIONSHIP_H_

#include "ns3/core-module.h"
#include "ns3/network-module.h"

#include "ns3/relationship.h"

namespace ns3
{

class SiotApplication;

class CworRelationship: public Relationship
{
public:
	CworRelationship(Ptr<SiotApplication>);
	virtual ~CworRelationship();
	virtual const std::string GetType() const;


};

} /* namespace ns3 */

#endif /* RELATIONSHIP_CWOR_RELATIONSHIP_H_ */
