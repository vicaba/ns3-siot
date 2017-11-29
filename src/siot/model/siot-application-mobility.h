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
#include <set>
#include <tuple>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/application.h"

namespace ns3
{

class SiotApplication;

class SiotApplicationMobility : public Application
{
public:

  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId
  GetTypeId (void);

  SiotApplicationMobility (double range, Ptr<SiotApplication> app,
			   Ptr<MobilityModel> mobilityModel);

  /**
   *	\param nodes nodes to add to the watch list
   */
  void
  Watch (std::vector<Ptr<const MobilityModel>>);

  /**
   *	\returns the nodes that are currently in range
   *
   *	Calculates which nodes have entered or leaved range.
   *	Calls NodeEntersRange and NodeLeavesRange respectively.
   */
  std::vector<Ptr<const MobilityModel>>
  GetInRange ();

  virtual
  ~SiotApplicationMobility ();

  typedef void
  (*NodeEntersRangeCallback) (Ptr<SiotApplication>, Ptr<const MobilityModel>);
  typedef void
  (*NodeLeavesRangeCallback) (Ptr<SiotApplication>, Ptr<const MobilityModel>);

protected:

  virtual void
  DoDispose (void);

private:

  void
  NotifyEntersRange (Ptr<const MobilityModel>);
  void
  NotifyLeavesRange (Ptr<const MobilityModel>);

  std::tuple<bool, double>
  IsNodeInRange (Ptr<const MobilityModel>);
  bool
  hasNodeEnteredRange (Ptr<const MobilityModel>);
  bool
  hasNodeLeavedRange (Ptr<const MobilityModel>);

  double m_range;
  std::unordered_map<std::uint32_t, Ptr<const MobilityModel>> m_watching;
  std::set<uint32_t> m_inRange;

  Ptr<SiotApplication> m_app;
  Ptr<MobilityModel> m_mobilityModel;

  ns3::TracedCallback<Ptr<SiotApplication>, Ptr<const MobilityModel>> m_nodeEntersRangeTrace;
  ns3::TracedCallback<Ptr<SiotApplication>, Ptr<const MobilityModel>> m_nodeLeavesRangeTrace;

};

template<typename Container>
  bool
  contains (Container const& c, typename Container::const_reference v)
  {
    return std::find (c.begin (), c.end (), v) != c.end ();
  }

template<typename T>
  void
  remove (std::set<T> & v, const T & item)
  {
    for (auto it = v.begin (); it != v.end ();
    /* "it" updated inside loop body */)
      {
	if (*it == item)
	  {
	    // Erase the element matching the specified condition
	    // from the associative container.
	    it = v.erase (it);

	    // Note:
	    // erase() returns an iterator to the element
	    // that follows the last element removed,
	    // so we can continue the "for" loop iteration from that position.
	  }
	else
	  {
	    // Current element does _not_ satisfy erasing condition,
	    // so we can just move on to the next element.
	    ++it;
	  }
      }
  }

} /* namespace ns3 */

#endif /* SRC_SIOT_MOBILITY_ADJACENCY_H_ */
