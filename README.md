gtm-bindings
============

Javascript, python 2, ruby and R bindings to the M database

The goal of this project is to make the M database GT.M available from Javascript
and other languages.

It is common to use the M database from the M language. This project provides
equivalent bindings to GT.M from Javascript.

For any of these bindings, copy "Source/_gtmaccess.m" and "Source/gtm_access.ci" to your M scripts folder.

You need to set the GTMCI environment variable to the location of gtm_access.ci

In bash shell do: export GTMCI=/path/to/gtm_access.ci

node.js
-------

In Linux, for node.js bindings do: (NOTE - this is currently broken?)

    sudo apt-get install nodejs nodejs-dev openssl libssl-dev npm build-essential libv8-dev

    cmake . -DWRAP_NODEJS=ON

    make

Look in Wrapping/NodePackage/README for more info.

Python 2
--------

If you want to wrap for Python 2 you should do:

    sudo apt-get install python-dev swig cmake build-essential

    cmake . -DWRAP_NODEJS=OFF -DWRAP_PYTHON=ON

    make

Unfortunately the egg distribution instructions in Wrapping/PythonPackage/README seem to be broken.

Copy lib/gtm.py and build/Release/_gtm.so to somewhere your python script can find. Load using "import gtm" in python.

Further usage instructions are in Wrapping/PythonPackage/dist/README

R
-

If you want to wrap for R you should do:

    sudo apt-get install r-base r-base-dev swig cmake build-essential

    cmake . -DWRAP_NODEJS=OFF -DWRAP_R=ON

    make

Ruby
----

If you want to wrap for Ruby you should do:

    sudo apt-get install ruby-dev swig cmake build-essential

    cmake . -DWRAP_NODEJS=OFF -DWRAP_RUBY=ON

    make

More details about R at:
http://cran.r-project.org/bin/linux/ubuntu/README

