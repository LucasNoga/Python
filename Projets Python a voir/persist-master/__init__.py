# -*- coding: utf-8 -*-
"""
:Package: ``persist``
:Author: `Adrian Letchford <http://www.dradrian.com>`_
:Organisation: `Warwick Business School <http://www.wbs.ac.uk/>`_, `University of Warwick <http://www.warwick.ac.uk/>`_.
:Created On: Fri Jul 18 11:29:28 2014

Description
-----------

"""

import pickle as pickle
import shelve
import inspect

#------------------------------------------------------------------------------
# Utility Methods
#------------------------------------------------------------------------------

def shelve_dict(fname, dictionary, disp=False):
    """
    Description
    -----------
    Dumps a dictionary to a file. The dictionary's values can be any object
    that can be pickled.
    """
    
    my_shelf = shelve.open(fname,'n') # 'n' for new

    for key in dictionary.iterkeys():
        try:
            my_shelf[key] = dictionary[key]
            if disp:
                print "Shelved: {0}".format(key)
        except Exception, e:
            if disp:
                print('ERROR shelving: {0}'.format(key))
    my_shelf.close()   
    
    
def unshelve_dict(fname, disp=False):
    """
    Description
    ----------- 
    Loads a dictionary saved by shelve_dict.
    """
    
    my_shelf = shelve.open(fname)
    
    new_dict = {}
    
    for key in my_shelf:
        try:
            new_dict[key]=my_shelf[key]
            if disp:
                print 'Unshelved {0}'.format(key)
        except Exception, e:
            if disp:
                print 'Error unshelving {0}'.format(key)
                print e
    my_shelf.close()
    
    return new_dict
    

#------------------------------------------------------------------------------
# Universal Methods
#------------------------------------------------------------------------------

def save_session(fname, global_vars=None, disp=False):
    """
    Description
    -----------
    Dumps all the variables in the current scope to a file.
    """

    if global_vars is None:
        global_vars = inspect.currentframe().f_back.f_locals
        
    shelve_dict(fname, global_vars, disp)

def load_session(fname, disp=False):
    """
    Description
    -----------
    Loads all the variables saved with save_session into the current scope.
    """
    stored_variables = unshelve_dict(fname, disp)
    
    variable_space = inspect.currentframe().f_back.f_locals
    variable_space.update(stored_variables)    
   

def save_obj(fname, obj):
    with open(fname, 'wb') as file:
        pickle.dump(obj, file)

def load_obj(fname):
    with open(fname, 'rb') as file:
        return pickle.load(file)

def save(fname, obj=None):
    if obj is None:
        save_session(fname, global_vars = inspect.currentframe().f_back.f_locals)
    else:
        save_obj(fname, obj)
            

#------------------------------------------------------------------------------
# Object specific methods
#------------------------------------------------------------------------------

def save_dict(fname, obj):

    with open(fname, 'w') as file:
        for item in obj.iteritems():
            
            file.write(str(item).encode('utf8') + '\n')
            
def load_dict(fname):
    
     D = {}
    
     with open(fname, 'r') as file:
         
         for line in file:
             item = eval(line.decode('utf8'))
             
             D[item[0]] = item[1]
             
     return D
             
            

def dict_append(fname, item):
    with open(fname, 'a') as file:
        file.write(str(item).encode('utf8') + '\n')
        

def load_split_dictionary(fname, key_name):

    D = {}
    
    with open(fname, 'r') as file:
        
        for line in file:
        
            d = eval(line.decode('utf8'))
            
            D[d[key_name]] = d
        
    return D

        
def save_split_dictionary(fname, d):
    
    with open(fname, 'w') as file:
        
        for key, value in d.iteritems():
            
            file.write(str(value).encode('utf8') + '\n')