/*
 * cwor-relationship.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: vcaballero
 */

#include "cwor-relationship.h"

namespace ns3
{

CworRelationship::CworRelationship(Ptr<Node> rel): Relationship(rel)
{
	// TODO Auto-generated constructor stub

}

CworRelationship::~CworRelationship()
{
	// TODO Auto-generated destructor stub
}

const RelationshipType CworRelationship::GetType() const {
	return RelationshipType::CWOR;
}

} /* namespace ns3 */

