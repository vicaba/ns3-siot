/*
 * a.h
 *
 *  Created on: Nov 23, 2017
 *      Author: vcaballero
 */

#ifndef SRC_SIOT_MODEL_RELATIONSHIP_H_
#define SRC_SIOT_MODEL_RELATIONSHIP_H_

#include "ns3/core-module.h"

namespace ns3
{

class SiotApplication;

class Relationship : public Object
{
public:

  enum class Type
  {
    POR, CLOR, CWOR, OOR, SOR
  };

  static std::string
  RelationshipTypeToString (Relationship::Type);
  Relationship (Ptr<SiotApplication>);
  virtual
  ~Relationship ();
  Ptr<SiotApplication>
  GetRelatedTo () const;
  virtual const Relationship::Type
  GetType () const = 0;

protected:
  //Relationship::Type m_relType;
  Ptr<SiotApplication> m_relNode;

};

}

#endif /* SRC_SIOT_MODEL_RELATIONSHIP_H_ */
