/*
 * cwor-relationship.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: vcaballero
 */

#include "cwor-relationship.h"

#include "ns3/siot-application.h"


namespace ns3
{

CworRelationship::CworRelationship(Ptr<SiotApplication> rel): Relationship(rel)
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

