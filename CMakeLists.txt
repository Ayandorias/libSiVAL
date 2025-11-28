# cmake_minimum_required(VERSION 3.16)

# project(libsival LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# add_library(libsival STATIC

#   include/sival/sival.hpp

#   # include/sival/SiVALResponse.hpp

#   include/sival/acousticsetup.hpp                   src/acousticsetup.cpp

#   # include/sival/abstractions/coneexcursion.hpp      src/abstractions/coneexcursion.cpp
#   include/sival/abstractions/driver.hpp             src/abstractions/driver.cpp
#   include/sival/abstractions/enclosure.hpp          src/abstractions/enclosure.cpp
#   # include/sival/abstractions/groupdelay.hpp         src/abstractions/groupdelay.cpp
#   # include/sival/abstractions/impedance.hpp          src/abstractions/impedance.cpp
#   # include/sival/abstractions/portair.hpp            src/abstractions/portair.cpp
#   include/sival/abstractions/response.hpp           src/abstractions/response.cpp
#   # include/sival/abstractions/spl.hpp                src/abstractions/spl.cpp

#   #utilities
#   include/sival/SiVALUtils.hpp
#   include/sival/utils/siconverter.hpp               src/utils/siconverter.cpp

#   # Driver
#   include/sival/components/driver/factory.hpp src/components/driver/factory.cpp
#   include/sival/components/driver/lowdriver.hpp src/components/driver/lowdriver.cpp

#   include/sival/components/enclosure/factory.hpp src/components/enclosure/factory.cpp
#   include/sival/components/enclosure/sealed.hpp  src/components/enclosure/sealed.cpp
#   include/sival/components/enclosure/vented.hpp  src/components/enclosure/vented.cpp

#   include/sival/core/exceptions.hpp
#   include/sival/core/roleconfig.hpp
#   README.md
#   include/sival/abstractions/abstractdriverresolver.hpp
#   include/sival/core/environment.hpp src/core/environment.cpp

#   # Responses
#   # include/sival/response/impedance/sealedimpedance.hpp    src/response/impedance/sealedimpedance.cpp

#   # include/SiVALConeExcursion.hpp
#   # include/sival/response/coneexcursion/sealed.hpp  src/response/coneexcursion/sealed.cpp
#   # include/sival/response/coneexcursion/vented.hpp  src/response/coneexcursion/vented.cpp
#   # include/sival/response/groupdelay/sealedgroupdelay.hpp  src/response/groupdelay/sealedgroupdelay.cpp

#   # include/sival/response/portair/sealedportair.hpp      src/response/portair/sealedportair.cpp
#   # include/sival/response/portair/ventedportair.hpp      src/response/portair/ventedportair.cpp
#   # include/sival/response/spl/gain.hpp   src/response/spl/gain.cpp
#   # include/sival/response/spl/sealedfrequency.hpp  src/response/spl/sealedfrequency.cpp
#   # include/sival/response/spl/ventedfrequency.hpp  src/response/spl/ventedfrequency.cpp



# )

# target_compile_definitions(libsival PRIVATE LIBSIVAL_LIBRARY)

































cmake_minimum_required(VERSION 3.16)

project(libsival LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Lädt die Standard-Pfade für Linux (z.B. /usr/lib)
include(GNUInstallDirs)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# HIER: 'SHARED' explizit gesetzt. Es entsteht zwingend eine .so Datei.
add_library(libsival SHARED
  include/sival/sival.hpp
  include/sival/acousticsetup.hpp             src/acousticsetup.cpp
  include/sival/abstractions/driver.hpp       src/abstractions/driver.cpp
  include/sival/abstractions/enclosure.hpp    src/abstractions/enclosure.cpp
  include/sival/abstractions/response.hpp     src/abstractions/response.cpp

  # Utilities
  include/sival/SiVALUtils.hpp
  include/sival/utils/siconverter.hpp         src/utils/siconverter.cpp

  # Driver
  include/sival/components/driver/factory.hpp src/components/driver/factory.cpp
  include/sival/components/driver/lowdriver.hpp src/components/driver/lowdriver.cpp

  # Enclosure
  include/sival/components/enclosure/factory.hpp src/components/enclosure/factory.cpp
  include/sival/components/enclosure/sealed.hpp  src/components/enclosure/sealed.cpp
  include/sival/components/enclosure/vented.hpp  src/components/enclosure/vented.cpp

  include/sival/core/exceptions.hpp
  include/sival/core/roleconfig.hpp
  README.md
)

target_compile_definitions(libsival PRIVATE LIBSIVAL_LIBRARY)

# --- Installations-Anweisungen ---

# 1. Die Bibliothek (.so) in den Systemordner (meist /usr/lib) kopieren
install(TARGETS libsival
    EXPORT libsivalTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # Nötig für das Linken unter Linux
)

# 2. Die Header-Dateien kopieren, damit andere Programme die Lib nutzen können
install(DIRECTORY include/sival
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
