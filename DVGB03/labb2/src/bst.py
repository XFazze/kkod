#!/usr/bin/env python3

import bt
import sys
import logging

log = logging.getLogger(__name__)

class BST(bt.BT):
    def __init__(self, value=None):
        '''
        Initializes an empty tree if `value` is None, else a root with the
        specified `value` and two empty children.
        '''
        self.set_value(value)
        if not self.is_empty():
            self.cons(BST(), BST())

    def is_member(self, v):
        '''
        Returns true if the value `v` is a member of the tree.
        '''
        if(self.is_empty()):
            return False
        if(self.get_value()==v):
            return True
        if(self.get_value()<v):
            if self.get_lc() == None:
                return False
            return self.get_lc().is_member(v)
        else:
            if self.get_rc() == None:
                return False
            return self.get_rc().is_member(v)
            

    def size(self):
        '''
        Returns the number of nodes in the tree.
        '''
        if(self.is_empty()):
            return 0
        size = 1
        if(self.get_lc() != None):
            size += self.get_lc().size()
        if(self.get_rc() != None):
            size += self.get_rc().size()
        
        return size 

    def height(self):
        '''
        Returns the height of the tree.
        '''
        if(self.is_empty()):
            return 0
        left, right = 0,0
        if(self.get_lc() != None):
            left = self.get_lc().height()
        if(self.get_rc() != None):
            right = self.get_rc().height()
        if (left > right):
            return left + 1 
        else:
            return right + 1 
            
    def preorder(self):
        '''
        Returns a list of all members in preorder.
        '''
        if self.is_empty():
            return []
        return [self.get_value()] + self.get_lc().preorder() + self.get_rc().preorder()

    def inorder(self):
        '''
        Returns a list of all members in inorder.
        '''
        if self.is_empty():
            return []
        return self.get_lc().inorder()+[self.get_value()]+self.get_rc().inorder()

    def postorder(self):
        '''
        Returns a list of all members in postorder.
        '''
        if self.is_empty():
            return []
        return self.get_lc().inorder()+self.get_rc().inorder()+[self.get_value()]

        
    def bfs_order_star(self):
        '''
        Returns a list of all members in breadth-first search* order, which
        means that empty nodes are denoted by "stars" (here the value None).

        For example, consider the following tree `t`:
                    10
              5           15
           *     *     *     20

        The output of t.bfs_order_star() should be:
        [ 10, 5, 15, None, None, None, 20 ]
        '''
        if(self.is_empty()):
            return []
        queue = [self]
        res = []
        height = self.height()
        while(len(set(queue)-{None}) != 0 and len(res) != 2**(height)-1 ):
            node = queue.pop(0)
            if(node==None):
                res.append(None)
                queue.extend([None,None])
            else:
                res.append(node.get_value())
                queue.extend([node.get_lc(), node.get_rc()])
         
        return res
        

    def add(self, v):
        '''
        Adds the value `v` and returns the new (updated) tree.  If `v` is
        already a member, the same tree is returned without any modification.
        '''
        if self.is_empty():
            self.__init__(value=v)
            return self
        if v < self.get_value():
            return self.cons(self.get_lc().add(v), self.get_rc())
        if v > self.get_value():
            return self.cons(self.get_lc(), self.get_rc().add(v))
        return self

    
    
    def _find_replace_child(self, head):
        '''
        Help function for `delete`. Finds and replaces the value passed in `head`. 
        Prioritized even length then left child.
        '''
        if(head.get_lc().get_value() != None ):
            if(head.get_rc().get_value() == None):
                # one left child
                head.set_value(head.get_lc().get_value())
                head.cons(head.get_lc().get_lc(),head.get_lc().get_rc())
                return self
        elif(head.get_rc().get_value() != None ):
            if(head.get_lc().get_value() == None):
                # one right child
                head.set_value(head.get_rc().get_value())
                head.cons(head.get_rc().get_lc(),head.get_rc().get_rc())
                return self
        else:
            # no children
            head.set_value(None)
            return self

        if(head.get_lc().height() >= head.get_rc().height()):
            # left tree is larger
            replace_parent = head.get_lc()
            if(replace_parent.get_rc().get_value()==None):
                head.set_value(replace_parent.get_value())
                head.cons(replace_parent.get_lc(), head.get_rc())
                return self

            # find most right child
            while(replace_parent.get_rc().get_value() != None and replace_parent.get_rc().get_rc().get_value() != None):
                replace_parent = replace_parent.get_rc()
                
            head.set_value(replace_parent.get_rc().get_value())
            if(replace_parent.get_rc().get_lc().get_value() != None):
                # got left child
                replace_parent.cons(replace_parent.get_lc(), replace_parent.get_rc().get_lc())
            else:
                replace_parent.cons(replace_parent.get_lc(), replace_parent.get_rc().get_rc())
                
                
        else:
            # right tree is larger
            replace_parent = head.get_rc()
            if(replace_parent.get_lc().get_value()==None):
                head.set_value(replace_parent.get_value())
                head.cons(head.get_lc(), replace_parent.get_rc())
                return self
            
            # find most left child
            while(replace_parent.get_lc().get_value() != None and replace_parent.get_lc().get_lc().get_value() != None):
                replace_parent = replace_parent.get_lc()
                
            head.set_value(replace_parent.get_lc().get_value())
            if(replace_parent.get_lc().get_rc().get_value() != None):
                # got right child
                replace_parent.cons(replace_parent.get_lc().get_rc(), replace_parent.get_rc().get_rc())
            else:
                replace_parent.cons(replace_parent.get_lc().get_lc(),  replace_parent.get_rc())


        
        return self
        
    def delete(self, v):
        '''
        Removes the value `v` from the tree and returns the new (updated) tree.
        If `v` is a non-member, the same tree is returned without modification.
        '''
        
        if(self.is_empty()):
            return self
        if(self.get_value()==v):
            return self._find_replace_child(self)
        if(self.get_value() > v):
            if self.get_lc().get_value() == None:
                return self
            if(self.get_lc().get_value() == v):               
                return self._find_replace_child(self.get_lc())
            self.get_lc().delete(v)
            return self 
        else:
            if self.get_rc().get_value() == None:
                return self
            if(self.get_rc().get_value() == v):
                return self._find_replace_child(self.get_rc())
            self.get_rc().delete(v)
            return self

if __name__ == "__main__":
    log.critical("module contains no main module")
    sys.exit(1)
