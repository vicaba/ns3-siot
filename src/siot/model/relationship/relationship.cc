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

std::string Relationship::RelationshipTypeToString(Relationship::Type rel)
{
	switch (rel)
	{
	case Relationship::Type::POR:
		return "POR";
	case Relationship::Type::CLOR:
		return "CLOR";
	case Relationship::Type::CWOR:
		return "CLOR";
	case Relationship::Type::OOR:
		return "CLOR";
	case Relationship::Type::SOR:
		return "CLOR";
	default:
		return "None";
	}
}

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
