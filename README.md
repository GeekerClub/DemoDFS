How to build and run a self distributed system
===============================================

1. Install compilation tools
-----------------------------

On Ubuntu 16.04 LTS:

    $ sudo apt-get install scons
    $ git clone https://github.com/GeekerClub/blade
   
In blade directory, install blade:
   
    $ cd blade
    $ ./install

Then, configure the vim environment via:

    $ cd blade/plugins
    $ tar xzvf vim_config.tgz
    $ cp .vim/* ~/.vim/


2. Install the dependant libs
-----------------------------

    $ ./install_deps.sh

The script will install the toft (c++ common lib),
and thirdparty. Also, the rpc component, trident,
is also installed here.

There exist many useful tools into third-party
components. Here, it should be compiled and installed
is: protoc:

    $ cd thirdparty/protobuf-2.5.0/src
    $ blade build -pdebug :protoc.bin
    $ a
    $ cp protoc.bin ~/bin/protoc

Above command will build the protobuf compiler and copy
it to $PATH.

3. Build the codes for demo system
----------------------------------

3.1) prepare the BLADE_ROOT, the build root file.
You can also put some global configuration in the file.

    $ touch BLADE_ROOT

3.2) build the demo codes

    $ cd rsfs
    $ blade build -pdebug :rsfs_main



