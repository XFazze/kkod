#!/usr/bin/env python3

import sys
import bst
import logging

log = logging.getLogger(__name__)

class AVL(bst.BST):
    def __init__(self, value=None):
        '''
        Initializes an empty tree if `value` is None, else a root with the
        specified `value` and two empty children.
        '''
        self.set_value(value)
        if not self.is_empty():
            self.cons(AVL(), AVL())

    def add(self, v):
        '''
        Example which shows how to override and call parent methods.  You
        may remove this function and overide something else if you'd like.
        '''
        self = super().add(v)
        self = self.balance()
        return self
    
    def delete(self, v):
        '''
        Example which shows how to override and call parent methods.  You
        may remove this function and overide something else if you'd like.
        '''
        self = super().delete(v)
        self = self.balance()
        return self

    def balance(self):
        '''
        AVL-balances around the node rooted at `self`.  In other words, this
        method applies one of the following if necessary: slr, srr, dlr, drr.
        '''
        if(self.is_empty()):
            return self
        
        if(self.get_lc().height()-1>self.get_rc().height()):
            # left heavy
            if(self.get_lc().get_rc().height()>self.get_lc().get_lc().height()):
                # inner heavy
                self = self.drr()
            else:
                # outer heavy & default
                self = self.srr()
                
        elif(self.get_rc().height()-1>self.get_lc().height()):
            # right heavy
            if(self.get_rc().get_lc().height()>self.get_rc().get_rc().height()):
                # inner heavy
                self = self.dlr()
            else:
                # outer heavy & default
                self = self.slr()
                
        return self

    def slr(self):
        '''
        Performs a single-left rotate around the node rooted at `self`.
        '''
        middle_child = self.get_rc().get_lc()
        new_root = self.get_rc()
        if(new_root.get_value()==None):
            print("bad call to slr")
            return self
        new_root.cons(self,new_root.get_rc())
        self.cons(self.get_lc(), middle_child)
        self = new_root
        return self

    def srr(self):
        '''
        Performs a single-right rotate around the node rooted at `self`.
        '''
        middle_child = self.get_lc().get_rc()
        new_root = self.get_lc()
        if(new_root.get_value()==None):
            print("bad call to srr")
            return self
        new_root.cons( new_root.get_lc(),self)
        self.cons(middle_child,self.get_rc())
        self = new_root
        return self


    def dlr(self):
        '''
        Performs a double-left rotate around the node rooted at `self`.
        '''
        self.cons(self.get_lc(), self.get_rc().srr())
        self = self.slr()
        return self

    def drr(self):
        '''
        Performs a double-right rotate around the node rooted at `self`.
        '''
        self.cons(self.get_lc().slr(), self.get_rc())
        self = self.srr()
        return self

if __name__ == "__main__":
    log.critical("module contains no main module")
    sys.exit(1)
