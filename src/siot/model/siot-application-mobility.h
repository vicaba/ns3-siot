/*
 * mobility-adjacency.h
 *
 *  Created on: Nov 27, 2017
 *      Author: vcaballero
 */

#ifndef SRC_SIOT_MOBILITY_ADJACENCY_H_
#define SRC_SIOT_MOBILITY_ADJACENCY_H_

#include <unordered_map>
#include <vector>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/application.h"

namespace ns3 {

class SiotApplication;

class SiotApplicationMobility: public Application {
public:
	SiotApplicationMobility(uint32_t, Ptr<SiotApplication>);
	virtual ~SiotApplicationMobility();
	std::vector<Ptr<Node>> GetInRange();

	typedef void (* NodeEntersRange)(Ptr<const SiotApplication>, Ptr<const Node>);
	typedef void (* NodeLeavesRange)(Ptr<const SiotApplication>, Ptr<const Node>);

protected:

	  virtual void DoDispose (void);

private:

	bool IsNodeInRange(Ptr<Node>);

	std::uint32_t m_range;
	std::unordered_map<std::uint32_t, Ptr<Node>> m_adjacencies;
	Ptr<SiotApplication> m_app;

	ns3::TracedCallback<Ptr<const SiotApplication>, Ptr<const Node>> m_nodeEntersRangeTrace;
	ns3::TracedCallback<Ptr<const SiotApplication>, Ptr<const Node>> m_nodeLeavesRangeTrace;

};

} /* namespace ns3 */

#endif /* SRC_SIOT_MOBILITY_ADJACENCY_H_ */
