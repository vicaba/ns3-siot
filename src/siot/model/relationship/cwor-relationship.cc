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

const std::string CworRelationship::GetType() const {
	return "cwor";
}

} /* namespace ns3 */

