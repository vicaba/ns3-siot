/*
 * relationship.h
 *
 *  Created on: Nov 2, 2017
 *      Author: vcaballero
 */

#ifndef RELATIONSHIP_H_
#define RELATIONSHIP_H_

#include "ns3/core-module.h"
#include "ns3/network-module.h"

namespace ns3
{

class SiotApplication;

enum RelationshipType
{
	POR, CLOR, CWOR, OOR, SOR
};

class Relationship: public Object
{
public:
	static std::string RelationshipTypeToString(RelationshipType);
	Relationship(Ptr<SiotApplication>);
	virtual ~Relationship();
	Ptr<Node> GetRelatedTo() const;
	virtual const RelationshipType GetType() const = 0;

protected:
	RelationshipType m_relType;
	Ptr<SiotApplication> m_relNode;

};

} /* namespace ns3 */

#endif /* RELATIONSHIP_H_ */
