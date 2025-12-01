cmake_minimum_required(VERSION 3.16)

project(libSiVAL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Lädt die Standard-Pfade für Linux (z.B. /usr/lib)
include(GNUInstallDirs)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# -------------------------------------------------------------------------
# 1. Bibliothek definieren (Deine Original-Dateiliste)
# -------------------------------------------------------------------------
add_library(libSiVAL SHARED
  include/sival/libsival.hpp
  include/sival/acousticsetup.hpp             src/acousticsetup.cpp
  include/sival/abstractions/driver.hpp       src/abstractions/driver.cpp
  include/sival/abstractions/enclosure.hpp    src/abstractions/enclosure.cpp
  include/sival/abstractions/response.hpp     src/abstractions/response.cpp

  # Utilities
  include/sival/SiVALUtils.hpp
  include/sival/utils/siconverter.hpp         src/utils/siconverter.cpp

  # Driver
  include/sival/components/driver/factory.hpp   src/components/driver/factory.cpp
  include/sival/components/driver/lowdriver.hpp src/components/driver/lowdriver.cpp

  # Enclosure
  include/sival/components/enclosure/factory.hpp src/components/enclosure/factory.cpp
  include/sival/components/enclosure/sealed.hpp  src/components/enclosure/sealed.cpp
  include/sival/components/enclosure/vented.hpp  src/components/enclosure/vented.cpp

  include/sival/core/exceptions.hpp
  include/sival/core/roleconfig.hpp
  README.md
)

# -------------------------------------------------------------------------
# 2. Export-Header generieren (MUSS vor der Nutzung passieren!)
# -------------------------------------------------------------------------
include(GenerateExportHeader)

# Erstellt die Datei im Build-Ordner
generate_export_header(libSiVAL
    EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/include/sival/libsival_export.hpp"
    EXPORT_MACRO_NAME SIVAL_API
)

# -------------------------------------------------------------------------
# 3. Include-Pfade setzen (Kritischer Schritt)
# -------------------------------------------------------------------------
# Damit der Compiler die gerade generierte Datei auch findet.
target_include_directories(libSiVAL PUBLIC
    # Dein normaler Source-Code
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    # WICHTIG: Der Ordner im Build-Verzeichnis für die generierten Dateien
    "${CMAKE_CURRENT_BINARY_DIR}/include"
)

# -------------------------------------------------------------------------
# 4. PCH setzen (Nach Generierung und Include-Pfad-Setzung)
# -------------------------------------------------------------------------
target_precompile_headers(libSiVAL PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}/include/sival/libsival_export.hpp"
)

set_target_properties(libSiVAL PROPERTIES OUTPUT_NAME "SiVAL")

target_compile_definitions(libSiVAL PRIVATE LIBSIVAL_LIBRARY)

# --- Installations-Anweisungen ---

install(TARGETS libSiVAL
    EXPORT libsivalTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/sival
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
