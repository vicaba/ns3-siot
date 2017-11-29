/*
 * mobility-adjacency.cpp
 *
 *  Created on: Nov 27, 2017
 *      Author: vcaballero
 */

#include "siot-application-mobility.h"

#include "ns3/siot-application.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE("SiotApplicationMobility");

NS_OBJECT_ENSURE_REGISTERED(SiotApplicationMobility);

TypeId SiotApplicationMobility::GetTypeId(void)
{
	static TypeId tid =
			TypeId("ns3::SiotApplicationMobility")
			.SetParent<Application>()
			.SetGroupName("Applications")
			.AddTraceSource ("NodeEntersRasssnge",
					"A node has entered physical range",
					MakeTraceSourceAccessor (&SiotApplicationMobility::m_nodeEntersRangeTrace),
					"ns3::SiotApplicationMobility::NodeEntersRangeCallback")
			.AddTraceSource ("NodeLeavesRange",
					"A node has leaved physical range",
					MakeTraceSourceAccessor (&SiotApplicationMobility::m_nodeLeavesRangeTrace),
					"ns3::SiotApplicationMobility::NodeLeavesRangeCallback");
	return tid;
}

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

std::vector<Ptr<const MobilityModel>> SiotApplicationMobility::GetInRange() {

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

	return inRangeVector;
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

void SiotApplicationMobility::DoDispose(void) {
	this->m_app = 0;
	Application::DoDispose();
}

SiotApplicationMobility::~SiotApplicationMobility() {
	// TODO Auto-generated destructor stub
}

} /* namespace ns3 */
