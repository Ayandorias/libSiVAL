cmake_minimum_required(VERSION 3.16)

project(libsival LANGUAGES CXX)

# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(libsival STATIC

  include/sival/sival.hpp

  # include/sival/SiVALResponse.hpp

  include/sival/acousticsetup.hpp                   src/acousticsetup.cpp

  # include/sival/abstractions/coneexcursion.hpp      src/abstractions/coneexcursion.cpp
  include/sival/abstractions/driver.hpp             src/abstractions/driver.cpp
  include/sival/abstractions/enclosure.hpp          src/abstractions/enclosure.cpp
  # include/sival/abstractions/groupdelay.hpp         src/abstractions/groupdelay.cpp
  # include/sival/abstractions/impedance.hpp          src/abstractions/impedance.cpp
  # include/sival/abstractions/portair.hpp            src/abstractions/portair.cpp
  include/sival/abstractions/response.hpp           src/abstractions/response.cpp
  # include/sival/abstractions/spl.hpp                src/abstractions/spl.cpp

  #utilities
  include/sival/SiVALUtils.hpp
  include/sival/utils/siconverter.hpp               src/utils/siconverter.cpp

  # Driver
  include/sival/components/driver/factory.hpp src/components/driver/factory.cpp
  include/sival/components/driver/lowdriver.hpp src/components/driver/lowdriver.cpp

  include/sival/components/enclosure/factory.hpp src/components/enclosure/factory.cpp
  include/sival/components/enclosure/sealed.hpp  src/components/enclosure/sealed.cpp
  include/sival/components/enclosure/vented.hpp  src/components/enclosure/vented.cpp

  include/sival/core/exceptions.hpp
  include/sival/core/roleconfig.hpp
  README.md

  # Responses
  # include/sival/response/impedance/sealedimpedance.hpp    src/response/impedance/sealedimpedance.cpp

  # include/SiVALConeExcursion.hpp
  # include/sival/response/coneexcursion/sealed.hpp  src/response/coneexcursion/sealed.cpp
  # include/sival/response/coneexcursion/vented.hpp  src/response/coneexcursion/vented.cpp
  # include/sival/response/groupdelay/sealedgroupdelay.hpp  src/response/groupdelay/sealedgroupdelay.cpp

  # include/sival/response/portair/sealedportair.hpp      src/response/portair/sealedportair.cpp
  # include/sival/response/portair/ventedportair.hpp      src/response/portair/ventedportair.cpp
  # include/sival/response/spl/gain.hpp   src/response/spl/gain.cpp
  # include/sival/response/spl/sealedfrequency.hpp  src/response/spl/sealedfrequency.cpp
  # include/sival/response/spl/ventedfrequency.hpp  src/response/spl/ventedfrequency.cpp



)

# target_link_libraries(libsival PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(libsival PRIVATE LIBSIVAL_LIBRARY)
