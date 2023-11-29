#!/usr/bin/env python3

#
# Recommended order to get started:
# 1) AdjacencyList.{add_node,node_cardinality}
# 2) AdjacencyList._add_edge, Edge.add - note: if you run in debug mode, you
# will get all edges printed when selecting 'v: view' in the menu.
# 3) AdjacencyList.find_edge, Edge.find
#

import sys
import logging

log = logging.getLogger(__name__)

from math import inf


class AdjacencyList:
    """
    A linked-list implementation of an adjacency list that keeps its nodes and
    edges lexicographically ordered at all times.
    """

    def __init__(self, name=None, info=None):
        """
        Initializes a new adjacency list.  It is considered empty if no head
        node is provided.  Optionally, a node can also have associated info.
        """
        self._name = name  # head node name
        self._info = info  # head node info
        if not self.is_empty():
            self._tail = AdjacencyList()  # empty tail
            self._edges = Edge()  # empty list of edges

    def is_empty(self):
        """
        Returns true if this adjacency list is empty.
        """
        return self._name is None

    def get_head(self):
        """
        Returns the head of this adjacency list.
        """
        return self

    def get_tail(self):
        """
        Returns the tail of this adjacency list.
        """
        return self._tail

    def get_name(self):
        """
        Returns the node name.
        """
        return self._name

    def get_info(self):
        """
        Returns auxilirary node info.
        """
        return self._info

    def get_edges(self):
        """
        Returns the edge head.
        """
        return self._edges

    def cons(self, tail):
        """
        Returns the head of this adjacency list with a newly attached tail.
        """
        self._tail = tail
        return self

    def set_tail(self, tail):
        """
        Returns the head of this adjacency list with a newly attached tail.
        Alias for cons().
        """
        return self.cons(tail)

    def set_name(self, name):
        """
        Sets the node name to `name`.

        Returns an adjacency list head.
        """
        self._name = name
        return self

    def set_info(self, info):
        """
        Sets the auxilirary info of this node to `info`.

        Returns an adjacency list head.
        """
        self._info = info
        return self

    def set_edges(self, edges):
        """
        Sets the edge head of this node to `edges`.

        Returns an adjacency list head.
        """
        self._edges = edges
        return self

    ###
    # Node operations
    ###
    def add_node(self, name, info=None):
        """
        Adds a new node named `name` in lexicographical order.  If node `name`
        is a member, its info-field is updated based on `info`.

        Returns an adjacency list head.
        """
        if self.is_empty():
            # Empty head
            new_head = AdjacencyList(name=name, info=info)
            return new_head

        elif self.get_name() > name:
            # Can only be true for head
            new_head = AdjacencyList(name=name, info=info)
            new_head.set_tail(self)
            return new_head

        elif self.get_tail().is_empty():
            # Add to end of list
            new_node = AdjacencyList(name=name, info=info)
            self.set_tail(new_node)

        elif self.get_tail().get_name() > name:
            # Add node between self and tail
            new_node = AdjacencyList(name=name, info=info)
            new_node.set_tail(self.get_tail())
            self.set_tail(new_node)

        else:
            self.get_tail().add_node(name, info=info)

        return self

    def delete_node(self, name):
        """
        Deletes the node named `name` if it is a member.

        Returns an adjacency list head.
        """
        if self.is_empty():
            return self

        node = self
        while not node.is_empty():
            edge = node.get_edges()
            edge.delete(name)
            node = node.get_tail()

        if self.get_name() == name:
            # Can only happen if head is the target
            return self.get_tail()
        elif self.get_tail().is_empty():
            # Node not in list
            pass
        elif self.get_tail().get_name() == name:
            # Tail is node to be deleted
            self.set_tail(self.get_tail().get_tail())
        else:
            self.get_tail().delete_node(name)
        return self

    def _find_node_return(self, name):
        if self.is_empty():
            return AdjacencyList()
        if name == self.get_name():
            return self
        return self.get_tail()._find_node_return(name)

    def find_node(self, name):
        """
        Returns True if the node named `name` is a member.
        """
        if self.is_empty():
            return False
        if name == self.get_name():
            return True
        return self.get_tail().find_node(name)

    def node_cardinality(self):
        """
        Returns the number of nodes.
        """
        if self.is_empty():
            return 0
        if self.get_tail().is_empty():
            return 1
        return self.get_tail().node_cardinality() + 1

    def node_index(self, target):
        """
        Returns the index of  `target` in adjlist.
        Pre: target is in adjlist
        """
        if target == self.get_name():
            return 0
        return self.get_tail().node_index(target) + 1

    def get_node_at_index(self, index):
        """
        Returns the name of node at  `index` in adjlist.
        Pre: index is in adjlist
        """
        if index == 0:
            return self.get_name()
        return self.get_tail().get_node_at_index(index - 1)

    ###
    # Edge operations
    ###
    def add_edge(self, src, dst, weight=1):
        """
        Adds or updates an edge from node `src` to node `dst` with a given
        weight `weight`.  If either of the two nodes are non-members, the same
        adjacency list is returned without any modification.

        Returns an adjacency list head.
        """
        if not self.find_node(dst):
            return self
        elif not self.find_node(src):
            return self
        return self._add_edge(src, dst, weight)

    def _add_edge(self, src, dst, weight):
        """
        Adds a new (or updates an existing) edge from node `src` to node `dst`,
        setting the weight to `weight`.

        Returns an adjacency list head.

        Pre: `dst` and `src` is a member of this adjacency list.
        """
        src_node = self._find_node_return(src)
        edge_head = src_node.get_edges()
        src_node.set_edges(edge_head.add(dst, weight))
        return self

        edge_duplicate = edge_head._find_return(dst)
        if not edge_duplicate.is_empty():
            edge_duplicate.set_weight(weight)
        elif edge_head.is_empty():
            edge_head.set_dst(dst)
            edge_head.set_weight(weight)
            edge_head.set_tail(Edge())

        elif edge_head.get_dst() > dst:
            edge = Edge(dst=dst, weight=weight)
            edge.set_tail(edge_head)
            src_node.set_edges(edge)

        else:
            loop_edge = edge_head
            while not loop_edge.is_empty():
                if loop_edge.get_tail().is_empty():
                    loop_edge.set_tail(Edge(dst=dst, weight=weight))
                    break
                elif loop_edge.get_tail().get_dst() > dst:
                    edge = Edge(dst=dst, weight=weight)
                    edge.set_tail(loop_edge.get_tail())
                    loop_edge.set_tail(edge)
                    break
                loop_edge = loop_edge.get_tail()

    def delete_edge(self, src, dst):
        """
        Deletes an edge from node `src` to node `dst` if it exists.

        Returns an adjacency list head.
        """
        if not self.find_node(src):
            return self
        else:
            src_node = self._find_node_return(src)
            src_node.set_edges(src_node.get_edges().delete(dst))
        return self

    def delete_edges(self, name):
        """
        Deletes all edges towards the node named `name`.

        Returns an adjacency list head.
        """
        if self.is_empty():
            return self
        else:
            self.delete_edge(self.get_name(), name)
        # print("next", self.get_name())
        if not self.get_tail().is_empty():
            self.get_tail().delete_edges(name)
        return self

    def find_edge(self, src, dst):
        """
        Returns True if there's an edge from node `src` to node `dst`.
        """
        node = self._find_node_return(src)
        if node.is_empty():
            return False
        return node.get_edges().find(dst)

    def edge_cardinality(self):
        """
        Returns the number of edges.
        """
        edges = 0
        node = self
        while not node.is_empty():
            edge = node.get_edges()
            while not edge.is_empty():
                edges += 1
                edge = edge.get_tail()
            node = node.get_tail()
        return edges

    def self_loops(self):
        """
        Returns the number of loops in this adjacency list.  Note that a loop is
        defined as a node that has an edge towards itself, e.g., A->A.
        """
        loops = 0
        node = self
        while not node.is_empty():
            edge = node.get_edges()
            if edge.find(node.get_name()):
                loops += 1
            node = node.get_tail()
        return loops

    def adjacency_matrix(self):
        """
        Returns this adjacency list as an adjacency matrix.  For example,
        consider the following adjacency list where all edges have weight=1.

        a: a->b->c
        |
        v
        b: a->b
        |
        v
        c: c

        Then we would expect the following 3x3 adjacency matrix:

          a b c
        -+-----
        a|1 1 1
        b|1 1 *
        c|* * 1

        Where the corresponding python-matrix is:

        [ [1,1,1], [1,1,inf], [inf,inf,1] ]

        Note that inf indicates that there is no path between two nodes.  Also,
        all rows and columns are lexicographically ordered based on node names.

        Hint: depending on your solution, you may need to add a helper method
        that maps a node's name to it's numeric position in the adjacency list.
        """
        if self.is_empty():
            return [[]]

        # In case you'd like to create an inf-initialized n x n matrix
        n = self.node_cardinality()
        matrix = [[inf] * n for i in range(n)]
        if self.is_empty():
            return matrix
        nodes = self.list_nodes()
        node = self
        node_index = 0
        while not node.is_empty():
            edge = node.get_edges()
            while not edge.is_empty():
                matrix[node_index][nodes.index(edge.get_dst())] = edge.get_weight()
                edge = edge.get_tail()
            node_index += 1
            node = node.get_tail()
        return matrix

    def list_nodes(self):
        """
        Returns a list of node names in lexicographical order.
        """
        head, node_names = self, []
        while not head.is_empty():
            node_names += [head.get_name()]
            head = head.get_tail()
        return node_names

    def list_edges(self):
        """
        Returns a list of edges in lexicographical order.
        """
        if self.is_empty():
            return []

        return self.get_edges().list(self.get_name()) + self.get_tail().list_edges()


class Edge:
    """
    A linked-list implementation of edges that originate from an implicit source
    node.  Each edge has a weight and goes towards a given destination node.
    """

    def __init__(self, dst=None, weight=1):
        """
        Initializes a new edge sequence.  It is considered empty if no head edge
        is provided, i.e., dst is set to None.
        """
        self._dst = dst  # where is this edge's destination
        self._weight = weight  # what is the weight of this edge
        if not self.is_empty():
            self._tail = Edge()  # empty edge tail

    def is_empty(self):
        """
        Returns true if this edge is empty.
        """
        return self._dst is None

    def get_head(self):
        """
        Returns the head of this edge.
        """
        return self

    def get_tail(self):
        """
        Returns the tail of this edge.
        """
        return self._tail

    def get_dst(self):
        """
        Returns the node name that this edge goes towards.
        """
        return self._dst

    def get_weight(self):
        """
        Returns the weight of this edge.
        """
        return self._weight

    def cons(self, tail):
        """
        Returns the head of this sequence with a newly attached tail.
        """
        self._tail = tail
        return self

    def set_tail(self, tail):
        """
        Returns the head of this sequence with a newly attached tail.
        """
        self._tail = tail
        return self

    def set_dst(self, dst):
        """
        Sets the destination of this edge to `dst`.

        Returns an edge head.
        """
        self._dst = dst
        return self

    def set_weight(self, weight):
        """
        Sets the weight of this edge to `weight`.

        Returns an edge head.
        """
        self._weight = weight
        return self

    ###
    # Operations
    ###
    def add(self, dst, weight=1):
        """
        Adds a new edge towards `dst` in lexicographical order.  If such an
        edge exists already, the associated weight-field is updated instead.

        Returns an edge head.
        """
        edge_duplicate = self._find_return(dst)
        if not edge_duplicate.is_empty():
            edge_duplicate.set_weight(weight)
        elif self.is_empty():
            self = Edge(dst, weight)
            self.set_tail(Edge())

        elif self.get_dst() > dst:
            edge = Edge(dst=dst, weight=weight)
            edge.set_tail(self)
            return edge  # new head

        else:
            loop_edge = self
            while not loop_edge.is_empty():
                if loop_edge.get_tail().is_empty():
                    loop_edge.set_tail(Edge(dst=dst, weight=weight))
                    break
                elif loop_edge.get_tail().get_dst() > dst:
                    edge = Edge(dst=dst, weight=weight)
                    edge.set_tail(loop_edge.get_tail())
                    loop_edge.set_tail(edge)
                    break
                loop_edge = loop_edge.get_tail()
        return self

    def _delete_recursively(self, dst):
        if self.get_tail().is_empty():
            return
        elif self.get_tail().get_dst() == dst:
            if self.get_tail().is_empty():
                self.set_tail(Edge())
            else:
                self.set_tail(self.get_tail().get_tail())
        else:
            self.get_tail()._delete_recursively(dst)

    def delete(self, dst):
        """
        Deletes the edge that goes towards `dst` if it exists.

        Returns an edge head.
        """
        if self.is_empty():
            return self
        elif self.get_dst() == dst:
            if self.get_tail().is_empty():
                return Edge()
            else:
                return self.get_tail()
        else:
            self._delete_recursively(dst)

        return self

    def _find_return(self, dst):
        if self.is_empty():
            return Edge()
        elif self.get_dst() == dst:
            return self
        else:
            return self.get_tail()._find_return(dst)

    def find(self, dst):
        """
        Returns True if there is an edge towards `dst` in this sequence.
        """
        if self.is_empty():
            return False
        elif self.get_dst() == dst:
            return True
        else:
            return self.get_tail().find(dst)

    def cardinality(self):
        """
        Returns the number of edges in this sequence.
        """
        if self.is_empty():
            return 0
        n = 0
        edge = self
        while not edge.is_empty():
            n += 1
            edge = edge.get_tail()
        return n

    def list(self, src):
        """
        Returns a list of edges in lexicographical order, e.g., if `src`
        goes to nodes A and B, the returned list would be:
            [ (src, A), (src, B) ]
        """
        if self.is_empty():
            return []
        return [(src, self.get_dst(), self.get_weight())] + self.get_tail().list(src)


if __name__ == "__main__":
    log.critical("module contains no main method")
    sys.exit(1)
