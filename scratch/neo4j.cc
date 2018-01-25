/*
 * neo4j.cc
 *
 *  Created on: Nov 20, 2017
 *      Author: vcaballero
 */

extern "C" {
#include <neo4j-client.h>
#include <errno.h>
#include <stdio.h>
}

#include "ns3/core-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("ScratchSimulator");

int
main (int argc, char *argv[])
{

  neo4j_client_init();

  /* use NEO4J_INSECURE when connecting to disable TLS */
  neo4j_connection_t *connection =
          neo4j_connect("neo4j://neo4j:neo4jx@localhost:7687", NULL, NEO4J_INSECURE);
  if (connection == NULL)
  {
      neo4j_perror(stderr, errno, "Connection failed");
      return EXIT_FAILURE;
  }

  neo4j_result_stream_t *results =
          neo4j_run(connection, "OPTIONAL MATCH (n:Node {id: {node1Id}}), (m:Node {id: {node2Id}}) MERGE (n)-[r:REL {relT: {relT}, simT: {simT}}]->(m)", neo4j_null);

  if (results == NULL)
  {
      neo4j_perror(stderr, errno, "Failed to run statement");
      return EXIT_FAILURE;
  }

  neo4j_result_t *result = neo4j_fetch_next(results);
  if (result == NULL)
  {
      neo4j_perror(stderr, errno, "Failed to fetch result");
      return EXIT_FAILURE;
  }

  neo4j_result_stream_t *results =
          neo4j_run(connection, "OPTIONAL MATCH (n:Node {id: {node1Id}}), (m:Node {id: {node2Id}}) MERGE (n)-[r:REL {relT: {relT}, simT: {simT}}]->(m)", neo4j_null);

  if (results == NULL)
  {
      neo4j_perror(stderr, errno, "Failed to run statement");
      return EXIT_FAILURE;
  }

  neo4j_result_t *result = neo4j_fetch_next(results);
  if (result == NULL)
  {
      neo4j_perror(stderr, errno, "Failed to fetch result");
      return EXIT_FAILURE;
  }

  neo4j_value_t value = neo4j_result_field(result, 0);
  char buf[128];
  printf("%s\n", neo4j_tostring(value, buf, sizeof(buf)));

  neo4j_close_results(results);
  neo4j_close(connection);
  neo4j_client_cleanup();

  NS_LOG_UNCOND ("Scratch Simulator");

  Simulator::Run ();
  Simulator::Destroy ();
}
