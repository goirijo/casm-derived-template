# casm-derived-template
Say goodbye to pulling your hair out figuring out compile flags. We all love casm, but sometimes you want to do something very specific that isn't in the main executables. You've got the libraries, so why not write your own executable? It all goes well until you try to compile/link. That's where this repository comes in to save the day.

###Prerequisites

The build system here depends heavily on autotools. Since there is no actual executable, the burden on creating all the Makefiles and configure scripts falls on you. Don't worry! It's easy to set up. You just need to install a few packages:

* autoconf
* automake
* libtool (?)
* autoconf-archive

These should all be readily available via ```brew``` and ```apt-get```.

###Installing your executable

The repository serves as a template for an executable that isn't written yet and is intended only for small executables that can be written in a single ```main.cpp``` file. If you're doing anything more complicated than that, consider contributing to [```goirijo/casm-utilities```](https://github.com/goirijo/casm-utilities), or [```CASM``` itself](https://github.com/prisms-center/CASMcode) if you have something more significant still.

####Clone the repository
```
git clone git@github.com:goirijo/casm-derived-template.git
```

####Edit main.cpp
The executable depends on a single file located in ```src/main.cpp```. Include whatever library headers you need and go to town. Make some supercells, use symmetry, do whatever cluster magic you want.

####Create configure and Makefiles
Once you've got all your code written up, you can prepare to compile it. Go to the root of the directory and run
```
./bootstrap.sh
```
This will generate a bunch of files needed by ```make``` and the configure script.

####Configure the compilation environment
If you're familiar with the usual autotools protocols to compile packages you can go do your usual thing. If you're unsure, follow these recommended steps:
```
mkdir build
cd build
```
At this poing you're ready to run ```../configure```, but there's a few flags you want to be aware of:
* ```--prefix``` will determine where you want your executable installed. For example, I like keeping my own executables away from the root folders that require admin privileges, so I tend to do ```--prefix=$HOME/.local```.
* ```LDFLAGS``` will set the ```-L``` flags for the compiler. You'll need to specify directories with this flag if you want the compiler to look anywhere for libraries. Unless you've installed the casm libraries in a particular manner, the configure script won't be able to find them. You'll probably need to do something like ```LDFLAGS=-L$HOME/.local/lib```
* ```CPPFLAGS``` will set preprocessor flags for you, namely ```-I``` for the compiler. Unless you've got the casm headers in a standard location, or have defined their path in ```CPLUS_INCLUDE_PATH```, ```make``` will be unable to include any headers. You'll need something like ```CPPFLAGS=-I$HOME/.local/include```.
* ```--program-transform-name``` will let you rename the resulting executable, which by default is called ```casm-derived```. If you'd rather it be named ```casm-fantastic``` you can do ```--program-transform-name='s/casm-derived/casm-fantastic```

Once you've decided what flags to use you can run the configure script:
```
CPPFLAGS=-I$HOME/.local/include LDFLAGS=-L$HOME/.local/lib ../configure --prefix=$HOME/.local --program-transform-name='s/casm-derived/casm-fantastic/'
```
Depending on your setup, you may need ```LDFLAGS``` to also include ```-ldl``` for the configure script to find the casm libraries.

####Make and install your executable
This one is easy:
```
make && make install
```

Provided the target install directory is within your ```PATH``` environment variable, you should be able to run ```casm-fantastic``` (or whatever you named it) now.
