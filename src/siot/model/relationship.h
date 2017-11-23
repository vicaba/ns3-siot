/*
 * a.h
 *
 *  Created on: Nov 23, 2017
 *      Author: vcaballero
 */

#ifndef SRC_SIOT_MODEL_RELATIONSHIP_H_
#define SRC_SIOT_MODEL_RELATIONSHIP_H_

#include "ns3/core-module.h"

#include "ns3/siot-application.h"


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
	Ptr<SiotApplication> GetRelatedTo() const;
	virtual const RelationshipType GetType() const = 0;

protected:
	RelationshipType m_relType;
	Ptr<SiotApplication> m_relNode;

};

}

#endif /* SRC_SIOT_MODEL_RELATIONSHIP_H_ */
