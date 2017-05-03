# MashberryPi

Automated mash tun controller on the RaspberryPi

## Install WiringPi

This repository makes use of WiringPi 2.44, which is not included in standard
packages. It must be downloads and installed from the git source.

```
$ git clone git://git.drogon.net/wiringPi
$ cd wiringPi
$ git pull origin
$ ./build
```

## WiringPi CMake issues

Add the following file, named `FindWiringPi.cmake` to the directory 
`/usr/share/cmake-x.x/Modules`:

```
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
find_path(WIRINGPI_INCLUDE_DIRS NAMES wiringPi.h)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(wiringPi DEFAULT_MSG WIRINGPI_LIBRARIES WIRINGPI_INCLUDE_DIR)
```
