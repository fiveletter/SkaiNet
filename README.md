# **SkaiNet: Self-tracking Tripod**
----
SkaiNet is a tracking tripod mount that will follow a given target using computer vision techologies. The system utilizes two brushless motors that are controlled by inputs given from a Raspberry Pi 3. The Raspberry Pi 3 utilizes OpenCV open source library to caluclate the deviation of a tracked object from the center of its view. It will then control the motors to correct the camera position such that the target will always be in the center of the video. The mount will be able to hold point-and-shoot cameras or smartphones for video recording.

[Link to project documentation](http://www.socialledge.com/sjsu/index.php?title=S16:_SkyNet)

# **Development Libraries and Tools**
-----
* WiringPi      - GPIO interface library
* Scons         - Build System for projects

## **Purpose and Dependency Installation Instructions (from scratch)**
### **WiringPi**
This is a gpio interface library that allows access to raspberry pi's pins.

[WiringPi Homepage](http://wiringpi.com/)
#### First time installation Instructions on Debian releases:
Install git if you have not yet:

    $ sudo apt-get install git-core 

Run the following commands to clone and build wiringPi project:

    $ git clone git://git.drogon.net/wiringPi
    $ cd wiringPi
    $ git pull origin
    $ ./build

Verify correct installation by checking version number:

    $ gpio -v

Verify correct installation by reading current configration of raspberry Pi pins:

    $ gpio readall

#### Use Instructions:
[WiringPi Documentation](http://wiringpi.com/reference/)

### **Scons**
Build system for the project. (Akin to cmake) Do note that to use scons 

[Scons Homepage](http://scons.org/)
#### First time installation Instructions on Linux:
Install python if you have not yet:

    $ sudo apt-get install python

Install scons using apt-get:

    $ sudo apt-get install scons

#### Use Instructions:
To use scons to build the project navigate to SkaiNet directory and run:

    $ scons

To clean directory run: 

    $ scons -c
or

    $ scons --clean

[Scons Documentation](http://scons.org/doc/HTML/scons-user.html)
