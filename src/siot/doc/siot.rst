Example Module Documentation
----------------------------

.. include:: replace.txt
.. highlight:: cpp

.. heading hierarchy:
------------- Chapter
************* Section (#.#)
============= Subsection (#.#.#)
############# Paragraph (no number)

This is a suggested outline for adding new module documentation to |ns3|.
See ``src/click/doc/click.rst`` for an example.

The introductory paragraph is for describing what this code is trying to
model.

For consistency (italicized formatting), please use |ns3| to refer to
ns-3 in the documentation (and likewise, |ns2| for ns-2).  These macros
are defined in the file ``replace.txt``.

Model Description
*****************

The source code for the new module lives in the directory ``src/siot``.

Add here a basic description of what is being modeled.

Design
======

Briefly describe the software design of the model and how it fits into 
the existing ns-3 architecture. 

Scope and Limitations
=====================

What can the model do?  What can it not do?  Please use this section to
describe the scope and limitations of the model.

References
==========

Add academic citations here, such as if you published a paper on this
model, or if readers should read a particular specification or other work.

Usage
*****

This section is principally concerned with the usage of your model, using
the public API.  Focus first on most common usage patterns, then go
into more advanced topics.

Building New Module
===================

The minumim required c++ standard is C++14. This standard is hardcoded in
the main wscript. We will move to C++17 to remove experimental features.


Include this subsection only if there are special build instructions or
platform limitations.

Helpers
=======

What helper API will users typically use?  Describe it here.

Attributes
==========

What classes hold attributes, and what are the key ones worth mentioning?

Output
======

What kind of data does the model generate?  What are the key trace
sources?   What kind of logging output can be enabled?

Advanced Usage
==============

Go into further details (such as using the API outside of the helpers)
in additional sections, as needed.

Examples
========

One of the examples in this module uses Neo4j as the backend. We recomend using
a dockerized container of Neo4j and  `tmpfs <https://www.jamescoyle.net/how-to/943-create-a-ram-disk-in-linux>`_
(RAM partition) to speed up disk operations.
For example, you could create a ram filesystem in a directory 
``mount -t tmpfs -o size=5g tmpfs $HOME/neo4j/data`` .

And point dockerized Neo4j volume to that filesystem.

.. code-block:: bash
::

   docker run \
   --publish=7474:7474 --publish=7687:7687 \
   --volume=$HOME/neo4j/data:/data \
   neo4j
.. code-block:: none

Example queries:

This query returns nodes their relationships directly related to Node with id == 3, including this node.

.. code-block:: neo4j
::

   MATCH (n:Node {id:3})-[r]->(m:Node) RETURN n,r,m
.. code-block:: none

This query returns nodes their relationships directly (range 1) and indirectly (range 2) related to Node with id == 3, including this node (range 0).

.. code-block:: neo4j
::

   MATCH (n:Node {id:3})-[r*0..2]->(m:Node) RETURN n,r,m
.. code-block:: none

In order to get the id of nodes related to node with id == 3, we can count them with ``count()`` and ``distinct()``.

.. code-block:: neo4j
::

   MATCH (n:Node {id:3})-[r*0..2]->(m:Node) RETURN count(distinct(m))
.. code-block:: none

To omit the node which is being tested (id == 3), we can add a ``WHERE`` clause.

.. code-block:: neo4j
::

   MATCH (n:Node {id:3})-[r*0..2]->(m:Node) WHERE m.id <> 3 RETURN count(distinct(m))
.. code-block:: none

Query for time and relationship hops

.. code-block:: neo4j
::

   MATCH (n:Node {id:3})-[r*0..2]->(m:Node) WHERE all(rel in r WHERE rel.simT < 100) RETURN n,r,m
.. code-block:: none


Troubleshooting
===============

Add any tips for avoiding pitfalls, etc.

Validation
**********

Describe how the model has been tested/validated.  What tests run in the
test suite?  How much API and code is covered by the tests?  Again, 
references to outside published work may help here.
