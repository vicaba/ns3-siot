/*
 * sor-relationship.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: vcaballero
 */

#include "sor-relationship.h"

#include "ns3/siot-application.h"


namespace ns3
{

SorRelationship::SorRelationship(Ptr<SiotApplication> rel): Relationship(rel)
{
	// TODO Auto-generated constructor stub

}

SorRelationship::~SorRelationship()
{
	// TODO Auto-generated destructor stub
}

const Relationship::Type SorRelationship::GetType() const {
	return Relationship::Type::SOR;

}

}/* namespace ns3 */

