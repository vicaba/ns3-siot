/*
 * relationship.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: vcaballero
 */

#include "relationship.h"

namespace ns3
{

std::string Relationship::RelationshipTypeToString(RelationshipType rel)
{
	switch (rel)
	{
	case POR:
		return "Parental Object Relationship";
	case CLOR:
		return "Co-Location Object Relationship";
	case CWOR:
		return "Co-Work Object Relationship";
	case OOR:
		return "Ownership Object Relationship";
	case SOR:
		return "Social Object Relationship";
	default:
		return "Invalid Relationship";
	}
}

Relationship::Relationship(Ptr<Node> rel)
{
	this->m_relNode = rel;
}

Relationship::~Relationship()
{
}

Ptr<Node> Relationship::GetRelatedTo() const {
	return this->m_relNode;
}

} /* namespace ns3 */
