/*
 * sor-relationship.h
 *
 *  Created on: Nov 2, 2017
 *      Author: vcaballero
 */

#ifndef RELATIONSHIP_SOR_RELATIONSHIP_H_
#define RELATIONSHIP_SOR_RELATIONSHIP_H_

#include "ns3/relationship.h"

#include "ns3/core-module.h"
#include "ns3/network-module.h"

namespace ns3
{

class SorRelationship : public Relationship
{
public:
  SorRelationship (Ptr<SiotApplication>);
  virtual
  ~SorRelationship ();
  virtual const Relationship::Type
  GetType () const;
};

} /* namespace ns3 */

#endif /* RELATIONSHIP_SOR_RELATIONSHIP_H_ */

