/*
 * a.h
 *
 *  Created on: Nov 23, 2017
 *      Author: vcaballero
 */

#ifndef SRC_SIOT_MODEL_RELATIONSHIP_H_
#define SRC_SIOT_MODEL_RELATIONSHIP_H_

#include "ns3/core-module.h"
#include "ns3/network-module.h"



namespace ns3
{

enum class RelationshipType
{
	POR, CLOR, CWOR, OOR, SOR
};

class Relationship: public Object
{
public:
	//static std::string RelationshipTypeToString(RelationshipType);
	Relationship(Ptr<Node>);
	virtual ~Relationship();
	Ptr<Node> GetRelatedTo() const;
	virtual const std::string GetType() const = 0;

protected:
	RelationshipType m_relType;
	Ptr<Node> m_relNode;

};


}

#endif /* SRC_SIOT_MODEL_RELATIONSHIP_H_ */
