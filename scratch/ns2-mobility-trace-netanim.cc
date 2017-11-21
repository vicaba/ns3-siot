/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2007 INRIA
 *               2009,2010 Contributors
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
 * Author: Martín Giachino <martin.giachino@gmail.com>
 *
 *
 * This example demonstrates the use of Ns2MobilityHelper class to work with mobility.
 *
 * Detailed example description.
 *
 *  - intended usage: this should be used in order to load ns2 movement trace files into ns3.
 *  - behavior:
 *      - Ns2MobilityHelper object is created, associated to the specified trace file. 
 *      - A log file is created, using the log file name argument.
 *      - A node container is created with the number of nodes specified in the command line.  For the default ns-2 trace, specify the value 2 for this argument.
 *      - the program calls the Install() method of Ns2MobilityHelper to set mobility to nodes. At this moment, the file is read line by line, and the movement is scheduled in the simulator.
 *      - A callback is configured, so each time a node changes its course a log message is printed.
 *  - expected output: example prints out messages generated by each read line from the ns2 movement trace file.
 *                     For each line, it shows if the line is correct, or of it has errors and in this case it will
 *                     be ignored.
 *
 * Usage of ns2-mobility-trace:
 *
 *  ./waf --run "ns2-mobility-trace \
 *        --traceFile=src/mobility/examples/default.ns_movements
 *        --nodeNum=2  --duration=100.0 --logFile=ns2-mobility-trace.log"
 *
 *  NOTE: ns2-traces-file could be an absolute or relative path. You could use the file default.ns_movements
 *        included in the same directory as the example file.
 *  NOTE 2: Number of nodes present in the trace file must match with the command line argument.
 *          Note that you must know it before to be able to load it.
 *  NOTE 3: Duration must be a positive number and should match the trace file. Note that you must know it before to be able to load it.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <unordered_map>
#include <math.h>

#include "ns3/core-module.h"
#include "ns3/mobility-module.h"
#include "ns3/ns2-mobility-helper.h"
#include "ns3/netanim-module.h"
#include "ns3/siot-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("SiotSim");

static int siotApplicationIndex = 0; // index of siot-server in nodes
static int proximityCheckInterval = 3; // seconds

static unsigned int WriteProfileHeadersToCsv(std::ostream &os, Ptr<Node> node) {

	std::unordered_map<std::string, std::string> profile =
			DynamicCast<SiotApplication>(
					node->GetApplication(siotApplicationIndex))->GetProfile()->GetRaw();

	for (auto it = profile.begin(); it != profile.end(); it++) {
		if (it == profile.begin())
			os << "nodeId," << it->first;
		else
			os << "," << it->first;
	}
	os << std::endl;
	return profile.size();

}

static void WriteProfileToCsv(std::ostream &os, NodeContainer &nodes,
		unsigned int headerColumns) {
	uint32_t containerSize = nodes.GetN();

	for (unsigned int i = 0; i < containerSize; i++) {
		std::unordered_map<std::string, std::string> profile =
				DynamicCast<SiotApplication>(
						nodes.Get(i)->GetApplication(siotApplicationIndex))->GetProfile()->GetRaw();

		NS_ASSERT_MSG(profile.size() == headerColumns,
				"Profile columns and header columns are not equal " << profile.size() << " != " << headerColumns);

		for (auto it = profile.begin(); it != profile.end(); it++) {
			if (it == profile.begin())
				os << nodes.Get(i)->GetId() << "," << it->second;
			else
				os << "," << it->second;
		}
		os << std::endl;

	}
}

static std::vector<std::string> getNextLineAndSplitIntoTokens(
		std::istream& str) {
	std::vector<std::string> result;
	std::string line;
	std::getline(str, line);

	std::stringstream lineStream(line);
	std::string cell;

	while (std::getline(lineStream, cell, ',')) {
		result.push_back(cell);
	}
	// This checks for a trailing comma with no data after it.
	if (!lineStream && cell.empty()) {
		// If there was a trailing comma then add an empty element.
		result.push_back("");
	}
	return result;
}

static std::vector<std::unordered_map<std::string, std::string>> ReadProfileCsv(
		std::istream& str) {

	std::vector<std::unordered_map<std::string, std::string>> profile;
	std::vector<std::string> headers;

	// Read Headers
	if (str.good()) {
		headers = getNextLineAndSplitIntoTokens(str);
	} else {
		return profile;
	}

	while (str.good()) {
		std::unordered_map<std::string, std::string> line;
		std::vector<std::string> values = getNextLineAndSplitIntoTokens(str);

		if (headers.size() == values.size()) {
			for (auto headerIt = headers.begin(), valueIt = values.begin();
					headerIt != headers.end(); headerIt++, valueIt++) {
				line.insert( { *headerIt, *valueIt });
				NS_LOG_DEBUG(
						"Reading Node profile... " << *headerIt << " : " << *valueIt);
			}
			profile.push_back(line);
		}

	}

	return profile;

}

/*
 static std::tuple<NodeContainer, NodeContainer> CreateCenters(double maxX,
 double maxY, NodeContainer& nodeContainer, uint16_t clusters)
 {
 // Calculate cluster boundaries
 std::vector<std::array<double, 6>> boundaries;
 NodeContainer clusterCenters;

 double baseX = maxX / clusters;
 double baseY = maxY / clusters;

 uint16_t xAxisLowerIndex = 0;
 uint16_t yAxisLowerIndex = 1;
 uint16_t xAxisUpperIndex = 2;
 uint16_t yAxisUpperIndex = 3;
 uint16_t xAxisCentroidIndex = 4;
 uint16_t yAxisCentroidIndex = 5;

 for (unsigned int i = 0; i < clusters; i++)
 {

 std::array<double, 6> quadrant;

 //Calculate region boundaries

 // Lower boundary
 quadrant[xAxisLowerIndex] = baseX * i;
 quadrant[yAxisLowerIndex] = baseY * i;

 // Upper boundary
 quadrant[xAxisUpperIndex] = baseX * (i + 1);
 quadrant[yAxisUpperIndex] = baseY * (i + 1);

 quadrant[xAxisCentroidIndex] = quadrant[xAxisLowerIndex]
 + ((quadrant[xAxisUpperIndex] - quadrant[xAxisLowerIndex]) / 2);
 quadrant[yAxisCentroidIndex] = quadrant[yAxisLowerIndex]
 + ((quadrant[yAxisUpperIndex] - quadrant[yAxisLowerIndex]) / 2);

 boundaries.push_back(quadrant);

 Ptr<PositionAllocator> pos = CreateObjectWithAttributes<
 RandomRectanglePositionAllocator>("X",
 StringValue(
 "ns3::ConstantRandomVariable[Constant="
 + std::to_string(quadrant[xAxisCentroidIndex])
 + "]"), "Y",
 StringValue(
 "ns3::ConstantRandomVariable[Constant="
 + std::to_string(quadrant[yAxisCentroidIndex])
 + "]"));

 Ptr<MobilityModel> mobility =
 CreateObject<ConstantPositionMobilityModel>();
 mobility->SetPosition(pos->GetNext());
 Ptr<Node> clusterCenter = CreateObject<Node>();
 clusterCenter->AggregateObject(mobility);
 clusterCenters.Add(clussecondterCenter);
 }

 return std::make_tuple(nodeContainer, clusterCenters);

 }
 */

static void RelationshipAdded(std::string context, Ptr<const Relationship> rel,
		const SiotApplication& thisNode) {
	auto sp = thisNode.GetProfile();
	NS_LOG_DEBUG(
			"Relationship profile: " << *(DynamicCast<SiotApplication>(rel->GetRelatedTo()->GetApplication(siotApplicationIndex))->GetProfile()));
}

static double DistanceBetweenNodes(Ptr<Node> node1, Ptr<Node> node2) {
	Ptr<MobilityModel> model1 = node1->GetObject<MobilityModel>();
	Ptr<MobilityModel> model2 = node2->GetObject<MobilityModel>();
	return model1->GetDistanceFrom(model2);
}

static void NodeContact(NodeContainer *nodes, std::ofstream *os) {
	int numberOfNodes = nodes->GetN();
	for (int i = 0; i < numberOfNodes; i++) {
		for (int j = 0; j < numberOfNodes; j++) {
			Ptr<Node> node1 = nodes->Get(i);
			Ptr<Node> node2 = nodes->Get(j);

			double distanceBetweenNodes = DistanceBetweenNodes(node1, node2);

			if (distanceBetweenNodes <= 10
					&& !(node1->GetId() == node2->GetId())) {

				// Add node contact to serv1
				Ptr<SiotApplication> serv1 = DynamicCast<SiotApplication>(
						node1->GetApplication(siotApplicationIndex));
				serv1->AddSorRelationship(Create<SorRelationship>(node2));

				// Add node contact to serv2
				Ptr<SiotApplication> serv2 = DynamicCast<SiotApplication>(
						node2->GetApplication(siotApplicationIndex));
				serv1->AddSorRelationship(Create<SorRelationship>(node1));

			}

		}
	}

	// Reschedule this operation
	Simulator::Schedule(Seconds(proximityCheckInterval), &NodeContact, nodes,
			os);
}

// Example to use ns2 traces file in ns3
int main(int argc, char *argv[]) {
	std::string animFile;
	std::string traceFile;
	std::string profileFile;
	std::string logFile;
	std::string distanceLogFile;
	std::string outputProfilesFile;

	int nodeNum;
	double duration;

	// Enable logging from the ns2 helper
	LogComponentEnable("Ns2MobilityHelper", LOG_LEVEL_DEBUG);

	// Parse command line attribute
	CommandLine cmd;
	cmd.AddValue("traceFile", "Ns2 movement trace file", traceFile);
	cmd.AddValue("profileFile", "Custom profile file", profileFile);
	cmd.AddValue("nodeNum", "Number of nodes", nodeNum);
	cmd.AddValue("duration", "Duration of Simulation", duration);
	cmd.AddValue("logFile", "Log file", logFile);
	cmd.AddValue("distanceLogFile", "Distance log file", distanceLogFile);
	cmd.AddValue("animationFile", "Animation file", animFile);
	cmd.AddValue("outputProfilesFile", "Profiles output", outputProfilesFile);
	cmd.Parse(argc, argv);

	// Check command line arguments
	if (traceFile.empty() || nodeNum <= 0 || duration <= 0 || logFile.empty()) {
		std::cout << "Usage of " << argv[0]
				<< " :\n\n"
						"./waf --run \"ns2-mobility-trace"
						" --traceFile=src/mobility/examples/default.ns_movements"
						" --nodeNum=2 --duration=100.0 --logFile=ns2-mob.log"
						" --distanceLogFile=distance.tr"
						" --animationFile=animation.xml\" \n\n"
						"NOTE: ns2-traces-file could be an absolute or relative path. You could use the file default.ns_movements\n"
						"      included in the same directory of this example file.\n\n"
						"NOTE 2: Number of nodes present in the trace file must match with the command line argument and must\n"
						"        be a positive number. Note that you must know it before to be able to load it.\n\n"
						"NOTE 3: Duration must be a positive number. Note that you must know it before to be able to load it.\n\n";

		return 0;
	}

	// Create Ns2MobilityHelper with the specified trace log file as parameter
	Ns2MobilityHelper ns2 = Ns2MobilityHelper(traceFile);

	// open log file for output
	std::ofstream os;
	os.open(logFile.c_str());

	// open log file for distance output
	std::ofstream osd;
	osd.open(distanceLogFile.c_str());

	// Create all nodes.
	NodeContainer stas;
	stas.Create(nodeNum);

	ns2.Install(stas.Begin(), stas.End()); // configure movements for each node, while reading trace file

	// Create SIoT app helper and install siot app on all nodes
	SiotApplicationHelper siot(9);
	ApplicationContainer appContainer = siot.Install(stas);

	for (unsigned int i = 0; i < stas.GetN(); i++) {
		Ptr<SiotApplication> serv1 = DynamicCast<SiotApplication>(
				stas.Get(i)->GetApplication(siotApplicationIndex));
		serv1->TraceConnect("RelationshipAdded", "context",
				MakeCallback(&RelationshipAdded));
	}

	// Open profile file to read node profiles from
	std::ifstream isProfile;
	isProfile.open(profileFile.c_str());

	// Read node profiles
	std::vector<std::unordered_map<std::string, std::string>> profiles =
			ReadProfileCsv(isProfile);

	// Close profile file
	isProfile.close();

	// Assign profiles to nodes
	uint32_t stasSize = stas.GetN();

	// Add profiles to SiotApplications
	for (unsigned int i = 0; i < stasSize; i++) {
		Vector3D pos = stas.Get(i)->GetObject<MobilityModel>()->GetPosition();
		profiles.at(i).insert( { "x_pos", std::to_string(pos.x) });
		profiles.at(i).insert( { "y_pos", std::to_string(pos.y) });
		profiles.at(i).insert( { "z_pos", std::to_string(pos.z) });
		Ptr<ServiceProfile> sp = CreateObject<ServiceProfile>("energy_profile",
				profiles.at(i));
		Ptr<SiotApplication> serv1 = DynamicCast<SiotApplication>(
				stas.Get(i)->GetApplication(siotApplicationIndex));
		serv1->SetServiceProfile(sp);
	}

	// Open file to log profiles and positios of nodes
	std::ofstream osProfiles;
	osProfiles.open(outputProfilesFile.c_str());

	// Write headers
	unsigned int headerCols = WriteProfileHeadersToCsv(osProfiles, stas.Get(0));

	// Write profiles to csv
	WriteProfileToCsv(osProfiles, stas, headerCols);

	// Close output profiles file
	osProfiles.close();

	/*
	 NodeContainer clusterCenters;


	 std::tie(stas, clusterCenters) = CreateCenters(12, 12, stas, 4);

	 for (unsigned int i = 0; i < 4; i++)
	 {
	 Ptr<MobilityModel> model1 = clusterCenters.Get(i)->GetObject<
	 ConstantPositionMobilityModel>();

	 NS_LOG_UNCOND("Mobility Model: " << model1);
	 NS_LOG_UNCOND("PosX: " << model1->GetPosition().x);
	 NS_LOG_UNCOND("PosY: " << model1->GetPosition().y);
	 }
	 */

	AnimationInterface anim(animFile);

	// Schedule operations
	Simulator::Schedule(Seconds(proximityCheckInterval), &NodeContact, &stas,
			&osd);

	Simulator::Stop(Seconds(duration));
	Simulator::Run();
	Simulator::Destroy();

	//osd.close();
	//os.close(); // close log file

	return 0;
}
