/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2017 La Salle - Universitat Ramon Llull
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Víctor Caballero <vcaballero@salleurl.edu>
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

    class SiotApplicationMobility : public Application {
     public:

      /**
       *  \brief Get the type ID.
       *  \return the object TypeId
       */
      static TypeId
      GetTypeId (void);

      SiotApplicationMobility (double range, Ptr<SiotApplication> app,
                               Ptr<MobilityModel> mobilityModel);

      /**
       *  \param nodes nodes to add to the watch list
       */
      void
      Watch (std::vector<Ptr<const MobilityModel>>);

      /**
       *  \returns the nodes that are currently in range
       *
       *	Calculates which nodes have entered or leaved range.
       *	Calls NotifyNodeEntersRange and NotifyNodeLeavesRange respectively.
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
      NotifyNodeEntersRange (Ptr<const MobilityModel>);
      void
      NotifyNodeLeavesRange (Ptr<const MobilityModel>);

      std::tuple<bool, double>
      IsNodeInRange (Ptr<const MobilityModel>);
      bool
      hasNodeEnteredRange (Ptr<const MobilityModel>);
      bool
      hasNodeLeavedRange (Ptr<const MobilityModel>);

      double m_range;
      std::unordered_map<std::uint32_t, Ptr<const MobilityModel>> m_watching;

      /**
       *  Keeps track of nodes that are currently in range
       */
      std::set<uint32_t> m_inRange;

      Ptr<SiotApplication> m_app;
      Ptr<MobilityModel> m_mobilityModel;

      ns3::TracedCallback<Ptr<SiotApplication>, Ptr<const MobilityModel>> m_nodeEntersRangeTrace;
      ns3::TracedCallback<Ptr<SiotApplication>, Ptr<const MobilityModel>> m_nodeLeavesRangeTrace;

    };

    template<typename Container>
    bool
    contains (Container const &c, typename Container::const_reference v)
    {
      return std::find (c.begin (), c.end (), v) != c.end ();
    }

    template<typename T>
    void
    remove (std::set<T> &v, const T &item)
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
