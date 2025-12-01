cmake_minimum_required(VERSION 3.16)

project(libSiVAL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Lädt die Standard-Pfade für Linux (z.B. /usr/lib)
include(GNUInstallDirs)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# HIER: 'SHARED' explizit gesetzt. Es entsteht zwingend eine .so Datei.
add_library(libSiVAL SHARED
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

set_target_properties(libSiVAL PROPERTIES OUTPUT_NAME "SiVAL")

target_compile_definitions(libSiVAL PRIVATE LIBSIVAL_LIBRARY)

# --- Installations-Anweisungen ---

# 1. Die Bibliothek (.so) in den Systemordner (meist /usr/lib) kopieren
install(TARGETS libSiVAL
    EXPORT libsivalTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # Nötig für das Linken unter Linux
)

# 2. Die Header-Dateien kopieren, damit andere Programme die Lib nutzen können
install(DIRECTORY include/sival
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
