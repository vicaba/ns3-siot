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

#include "siot-application-mobility.h"

#include "ns3/siot-application.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("SiotApplicationMobility");

NS_OBJECT_ENSURE_REGISTERED(SiotApplicationMobility);

TypeId
SiotApplicationMobility::GetTypeId (void)
{
  static TypeId tid =
      TypeId ("ns3::SiotApplicationMobility").SetParent<Application> ().SetGroupName (
	  "Applications").AddTraceSource (
	  "NodeEntersRange", "A node has entered physical range",
	  MakeTraceSourceAccessor (&SiotApplicationMobility::m_nodeEntersRangeTrace),
	  "ns3::SiotApplicationMobility::NodeEntersRangeCallback").AddTraceSource (
	  "NodeLeavesRange", "A node has leaved physical range",
	  MakeTraceSourceAccessor (&SiotApplicationMobility::m_nodeLeavesRangeTrace),
	  "ns3::SiotApplicationMobility::NodeLeavesRangeCallback");
  return tid;
}

SiotApplicationMobility::SiotApplicationMobility (double range, Ptr<SiotApplication> app,
						  Ptr<MobilityModel> mobilityModel)
{
  this->m_range = range;
  this->m_app = app;
  this->m_mobilityModel = mobilityModel;
}

void
SiotApplicationMobility::Watch (std::vector<Ptr<const MobilityModel>> nodes)
{
  for (auto n : nodes)
    {
      if (n != this->m_mobilityModel)
	{
	  m_watching.insert (
	    { n->GetObject<Node> ()->GetId (), n });
	}
    }
}

std::vector<Ptr<const MobilityModel>>
SiotApplicationMobility::GetInRange ()
{

  std::vector<Ptr<const MobilityModel>> inRangeVector;

  for (auto n : m_watching)
    {
      bool inRange;
      double distance;

      std::tie (inRange, distance) = this->IsNodeInRange (n.second);

      if (inRange == true)
	{
	  inRangeVector.push_back (n.second);
	  if (!contains (m_inRange, n.first))
	    {
	      m_inRange.insert (n.first);
	      this->NotifyEntersRange (n.second);
	    }
	}
      else
	{ // inRange == false
	  remove (m_inRange, n.first);
	  this->NotifyLeavesRange (n.second);
	}

    }

  return inRangeVector;
}

std::tuple<bool, double>
SiotApplicationMobility::IsNodeInRange (Ptr<const MobilityModel> other)
{
  double distance = this->m_mobilityModel->GetDistanceFrom (other);

  if (distance <= this->m_range)
    {
      return std::make_tuple (true, distance);
    }
  else
    {
      return std::make_tuple (false, distance);;
    }

}

void
SiotApplicationMobility::NotifyEntersRange (Ptr<const MobilityModel> node)
{
  this->m_nodeEntersRangeTrace (m_app, node);
}

void
SiotApplicationMobility::NotifyLeavesRange (Ptr<const MobilityModel> node)
{
  this->m_nodeLeavesRangeTrace (m_app, node);
}

void
SiotApplicationMobility::DoDispose (void)
{
  this->m_app = 0;
  Application::DoDispose ();
}

SiotApplicationMobility::~SiotApplicationMobility ()
{
  // TODO Auto-generated destructor stub
}

} /* namespace ns3 */
