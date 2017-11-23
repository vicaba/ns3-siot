/*
 * a.h
 *
 *  Created on: Nov 23, 2017
 *      Author: vcaballero
 */

#ifndef SRC_SIOT_MODEL_A_H_
#define SRC_SIOT_MODEL_A_H_

#include "ns3/core-module.h"

#include "ns3/siot-application.h"

namespace ns3 {

class SiotApplication;

class A: public Object {
public:
	A();
	virtual ~A();

private:
	Ptr<SiotApplication> b;
};

} /* namespace ns3 */

#endif /* SRC_SIOT_MODEL_A_H_ */
