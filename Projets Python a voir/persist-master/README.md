persist
=======

A small python package with tools to easily implement persistance.

The main feature of `persist`, 

The command `save(filename, obj=None)` will dump all the variables from the
calling scope to a file IF obj is left as `None`. The variables can be loaded
back in with the command `load_session(filename)`.
