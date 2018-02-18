# -*- coding: utf-8 -*-
"""
:Module: ````
:Author: `Adrian Letchford <http://www.dradrian.com>`_
:Organisation: `Warwick Business School <http://www.wbs.ac.uk/>`_, `University of Warwick <http://www.warwick.ac.uk/>`_.
:Created On: Sun Mar 22 18:45:36 2015
"""

# Import build in modules
import sys
import os.path

# Import external modules
import nose
from nose.tools import *

# Import custom modules
sys.path.append('../')
from funcache import Cache, string2name, function2name

def test_nothing():
    assert True == True
    
def test_turning_object_into_name():
    
    string = 'lol'
    name = string2name(string)
    
    assert type(name) == str
    assert len(name) > 0
    
class TestCache:
    
    def setup(self):
        self.cache = Cache('mycache_575728')
 
    def teardown(self):
        try:
            os.remove(self.cache.filename)
        except OSError:
            pass # file didn't exist
        assert os.path.isfile(self.cache.filename) == False
    
    def test_archive_created(self):  
       self.cache.save('somename', 'somedata')       
       assert os.path.isfile(self.cache.filename)
    
    def test_returning_data(self):
        self.cache.save('somename', 'somedata')       
        assert self.cache.load('somename') == 'somedata'
        
    def test_saving_2_data(self):
        self.cache.save('somename1', 'somedata1')    
        self.cache.save('somename2', 'somedata2')  
        assert self.cache.load('somename1') == 'somedata1'
        assert self.cache.load('somename2') == 'somedata2'

    @raises(IOError)
    def test_sanity_check_fail_when_no_cache_saved(self):
        self.cache._check_is_cache()
    
    
    def test_data_does_not_exist(self):        
        self.cache.save('one_thing', 'another_thing')        
        assert self.cache.is_cached('nothing') == False

    def test_that_run_returns_right_answer(self):
        
        def func(d):
            return {'one', d}
            
        assert self.cache.run(func, 2) == func(2)
        
        
    def test_that_run_caches_data(self):
        
        def func(d):
            return {'one': d}
            
        self.cache.run(func, 2)
        
        name = function2name(func, 2)
        
        assert self.cache.is_cached(name)
        
        
        
if __name__ == '__main__':
    # Run all the tests in this file
    module_name = sys.modules[__name__].__file__
    result = nose.run(argv=[sys.argv[0], module_name, '-v'])