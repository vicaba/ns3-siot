/*
 * mobility-adjacency.cpp
 *
 *  Created on: Nov 27, 2017
 *      Author: vcaballero
 */

#include "siot-application-mobility.h"

#include "ns3/siot-application.h"

namespace ns3 {

SiotApplicationMobility::SiotApplicationMobility(uint32_t range, Ptr<SiotApplication> app) {
	this->m_range = range;
	this->m_app = app;
}

void SiotApplicationMobility::DoDispose (void)
{
	this->m_app = 0;
	Application::DoDispose();
}


SiotApplicationMobility::~SiotApplicationMobility() {
	// TODO Auto-generated destructor stub
}

std::vector<Ptr<Node>> SiotApplicationMobility::GetInRange()
{
	std::vector<Ptr<Node>> vec = {};
	return vec;
}

bool SiotApplicationMobility::IsNodeInRange(Ptr<Node>)
{



	return true;
}

} /* namespace ns3 */
