gtm-bindings
============

Javascript, python, ruby and R bindings to the M database

The goal of this project is to make the M database GT.M available from Javascript
and other languages.

It is common to use the M database from the M language. This project provides
equivalent bindings to GT.M from Javascript.

In Linux, for node.js bindings do: (NOTE - this is currently broken?)

    sudo apt-get install nodejs nodejs-dev openssl libssl-dev npm build-essential libv8-dev

    cmake . -DWRAP_NODEJS=ON

    make

If you want to wrap for Python you should do:

    sudo apt-get install python-dev swig cmake build-essential

    cmake . -DWRAP_NODEJS=OFF -DWRAP_PYTHON=ON

    make

If you want to wrap for R you should do:

    sudo apt-get install r-base r-base-dev swig cmake build-essential

    cmake . -DWRAP_NODEJS=OFF -DWRAP_R=ON

    make

If you want to wrap for Ruby you should do:

    sudo apt-get install ruby-dev swig cmake build-essential

    cmake . -DWRAP_NODEJS=OFF -DWRAP_RUBY=ON

    make

More details about R at:
http://cran.r-project.org/bin/linux/ubuntu/README

