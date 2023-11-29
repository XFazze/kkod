#!/usr/bin/env python3

import sys
import logging

log = logging.getLogger(__name__)

from math import inf
from adjlist import AdjacencyList


def warshall(adjlist):
    """
    Returns an NxN matrix that contains the result of running Warshall's
    algorithm.

    Warshall's algorithm is similar to Floyd's, but gives the transitive closure
    instead of the minimum distances.

    Pre: adjlist is not empty.
    """
    res = adjlist.adjacency_matrix()
    for i in range(len(res)):
        res[i][i] = 0
    for k in range(0, adjlist.node_cardinality()):
        for i in range(0, adjlist.node_cardinality()):
            for j in range(0, adjlist.node_cardinality()):
                res[i][j] = min(res[i][j], res[i][k] + res[k][j])

    for i in range(0, adjlist.node_cardinality()):
        for j in range(0, adjlist.node_cardinality()):
            res[i][j] = 1 if res[i][j] != inf else 0
    return res


def floyd(adjlist):
    """
    Returns an NxN matrix that contains the result of running Floyd's algorithm.

    Floyd's algorithm is similar to Warshall's, but gives the minimum distances
    instead of transitive closure.

    Pre: adjlist is not empty.
    """
    res = adjlist.adjacency_matrix()
    for i in range(len(res)):
        res[i][i] = 0
    for k in range(0, adjlist.node_cardinality()):
        for i in range(0, adjlist.node_cardinality()):
            for j in range(0, adjlist.node_cardinality()):
                res[i][j] = min(res[i][j], res[i][k] + res[k][j])

    return res


def dijkstra(adjlist: AdjacencyList, start_node):
    """
    Returns the result of running Dijkstra's algorithm as two N-length lists:
    1) distance d: here, d[i] contains the minimal cost to go from the node
    named `start_node` to the i:th node in the adjacency list.
    2) edges e: here, e[i] contains the node name that the i:th node's shortest
    path originated from.

    If the index i refers to the start node, set the associated values to None.

    Pre: start_node is a member of adjlist.

    === Example ===
    Suppose that we have the following adjacency matrix:

      a b c
    -+-----
    a|* 1 *
    b|* * 2
    c|* * *

    For start node "a", the expected output would then be:

    d: [ None, 1, 3]
    e: [ None, 'a', 'b' ]
    """
    d = [inf for _ in range(0, adjlist.node_cardinality())]
    e = [None for _ in range(0, adjlist.node_cardinality())]
    adjacency_matrix = adjlist.adjacency_matrix()
    visited = [None for _ in range(0, adjlist.node_cardinality())]
    node_origin = start_node
    d[adjlist.node_index(node_origin)] = 0
    while True:
        index = adjlist.node_index(node_origin)
        visited[index] = True
        for i, v in enumerate(adjacency_matrix[index]):
            if visited[i]:
                pass
            elif d[i] > d[index] + adjacency_matrix[index][i]:
                d[i] = d[index] + adjacency_matrix[index][i]
                e[i] = node_origin

        lowest = inf
        for i, (v, vis) in enumerate(zip(d, visited)):
            if v < lowest and not vis:
                node_origin = adjlist.get_node_at_index(i)
                lowest = d[i]

        if lowest == inf:
            break

    index = adjlist.node_index(start_node)
    d[index] = None
    e[index] = None
    return d, e


def prim(adjlist, start_node):
    """
    Returns the result of running Prim's algorithm as two N-length lists:
    1) lowcost l: here, l[i] contains the weight of the cheapest edge to connect
    the i:th node to the minimal spanning tree that started at `start_node`.
    2) closest c: here, c[i] contains the node name that the i:th node's
    cheapest edge orignated from.

    If the index i refers to the start node, set the associated values to None.

    Pre: adjlist is setup as an undirected graph and start_node is a member.

    === Example ===
    Suppose that we have the following adjacency matrix:

      a b c
    -+-----
    a|* 1 3
    b|1 * 1
    c|3 1 *

    For start node "a", the expected output would then be:

    l: [ None, 1, 1]
    c: [ None, 'a', 'b' ]
    """
    l = [None for i in range(0, adjlist.node_cardinality())]
    c = [None for i in range(0, adjlist.node_cardinality())]
    adjacency_matrix = adjlist.adjacency_matrix()
    index = adjlist.node_index(start_node)
    visited = [
        False if i != index else True for i in range(0, adjlist.node_cardinality())
    ]
    while visited.count(False) > 0:
        smallest_edge = inf
        edge_destination = None
        edge_source = None
        for source_i, v in enumerate(visited):
            if not v:
                continue
            for desitnation_i, v2 in enumerate(visited):
                if not v2 and adjacency_matrix[source_i][desitnation_i] < smallest_edge:
                    edge_destination = desitnation_i
                    edge_source = adjlist.get_node_at_index(source_i)
                    smallest_edge = adjacency_matrix[source_i][desitnation_i]
        l[edge_destination] = smallest_edge
        c[edge_destination] = edge_source
        visited[edge_destination] = True
    return l, c


if __name__ == "__main__":
    logging.critical("module contains no main")
    sys.exit(1)
