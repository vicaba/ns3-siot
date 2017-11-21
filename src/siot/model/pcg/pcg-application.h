/*
 * pcg-application.h
 *
 *  Created on: Nov 8, 2017
 *      Author: vcaballero
 */

#ifndef SRC_SIOT_MODEL_PCG_PCG_APPLICATION_H_
#define SRC_SIOT_MODEL_PCG_PCG_APPLICATION_H_

#include "ns3/core-module.h"
#include "ns3/siot-module.h"

namespace ns3
{

class PcgApplication: public Object
{
public:
	PcgApplication();
	virtual ~PcgApplication();

private:

	bool m_isGroupLeader = false;
	std::vector<Ptr<PcgApplication>> m_group;
	Ptr<SiotApplication> m_siotApp;

};

} /* namespace ns3 */

#endif /* SRC_SIOT_MODEL_PCG_PCG_APPLICATION_H_ */
