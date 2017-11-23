/*
 * a.cc
 *
 *  Created on: Nov 23, 2017
 *      Author: vcaballero
 */

#include "relationship.h"

#include "ns3/siot-application.h"


namespace ns3
{

/*std::string Relationship::RelationshipTypeToString(RelationshipType rel)
{
	switch (rel)
	{
	case RelationshipType::POR:
		return "Parental Object Relationship";
	case RelationshipType::CLOR:
		return "Co-Location Object Relationship";
	case RelationshipType::CWOR:
		return "Co-Work Object Relationship";
	case RelationshipType::OOR:
		return "Ownership Object Relationship";
	case RelationshipType::SOR:
		return "Social Object Relationship";
	default:
		return "Invalid Relationship";
	}
}*/

Relationship::Relationship(Ptr<SiotApplication> rel)
{
	this->m_relNode = rel;
}

Relationship::~Relationship()
{
}

Ptr<SiotApplication> Relationship::GetRelatedTo() const {
	return this->m_relNode;
}

} /* namespace ns3 */
