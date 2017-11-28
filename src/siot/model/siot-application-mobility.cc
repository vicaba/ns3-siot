/*
 * mobility-adjacency.cpp
 *
 *  Created on: Nov 27, 2017
 *      Author: vcaballero
 */

#include "siot-application-mobility.h"

#include "ns3/siot-application.h"

namespace ns3 {

SiotApplicationMobility::SiotApplicationMobility(double range,
		Ptr<SiotApplication> app) {
	this->m_range = range;
	this->m_app = app;
}

void SiotApplicationMobility::Watch(
		std::vector<Ptr<const MobilityModel>> nodes) {
	for (auto n : nodes) {
		m_watching.insert( { n->GetObject<Node>()->GetId(), n });
	}
}

void SiotApplicationMobility::DoDispose(void) {
	this->m_app = 0;
	Application::DoDispose();
}

SiotApplicationMobility::~SiotApplicationMobility() {
	// TODO Auto-generated destructor stub
}

std::vector<Ptr<Node>> SiotApplicationMobility::GetInRange() {

	std::vector<Ptr<const MobilityModel>> inRangeVector;

	for (auto n : m_watching) {
		bool inRange;
		double distance;

		std::tie(inRange, distance) = this->IsNodeInRange(n.second);

		if (inRange == true) {
			inRangeVector.push_back(n.second);
			if (!contains(m_inRange, n.first)) {
				m_inRange.insert(n.first);
				this->NotifyEntersRange(n.second);
			}
		} else { // inRange == false
			remove(m_inRange, n.first);
			this->NotifyLeavesRange(n.second);
		}

	}

	std::vector<Ptr<Node>> vec = { };
	return vec;
}

std::tuple<bool, double> SiotApplicationMobility::IsNodeInRange(
		Ptr<const MobilityModel> other) {
	double distance = this->m_mobilityModel->GetDistanceFrom(other);

	if (distance <= this->m_range) {
		return std::make_tuple(true, distance);
	} else {
		return std::make_tuple(false, distance);;
	}

}

void SiotApplicationMobility::NotifyEntersRange(Ptr<const MobilityModel> node) {
	this->m_nodeEntersRangeTrace(m_app, node);
}

void SiotApplicationMobility::NotifyLeavesRange(Ptr<const MobilityModel> node) {
	this->m_nodeLeavesRangeTrace(m_app, node);
}

} /* namespace ns3 */
