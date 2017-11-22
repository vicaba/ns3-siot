/*
 * sor-relationship.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: vcaballero
 */

#include "sor-relationship.h"

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

const RelationshipType SorRelationship::GetType() const {
	return RelationshipType::SOR;
}

}/* namespace ns3 */
