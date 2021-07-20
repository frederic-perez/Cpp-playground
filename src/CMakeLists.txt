# -- CMake build rules

# Boost stuff
set(Boost_USE_STATIC_LIBS ON CACHE BOOL "Use statically-linked boost libraries")
# '- Note: By default set Boost_USE_STATIC_LIBS to ON (to link them statically
#    to avoid possible problems during execution of the application (not finding
#    the .so files)), but let the user change it (useful for example to use
#    Fedora native boost libraries, or for OSX when using Boost's "locale" to
#    avoid weird "_iconv*" missing symbols when linking")
set(Boost_USE_MULTITHREADED ON)
find_package(Boost) # <-- Use this simple line when using only headers
# find_package(Boost
#   COMPONENTS
#     # lexicographically sorted
#     date_time
#     filesystem
#     locale
#     program_options
#     system
# )
if (Boost_FOUND)
  message(STATUS "Boost found:")
  include_directories(${Boost_INCLUDE_DIRS})
  message(STATUS "  Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
  message(STATUS "  Boost_LIBRARIES: ${Boost_LIBRARIES}
  Note: Boost_LIBRARIES can be empty if no COMPONENTS are used.") # Used below
else ()
  message(FATAL_ERROR "Boost not found - Hint(?): ENV{BOOST_ROOT} is $ENV{BOOST_ROOT}")
endif ()

set(SRC_LIST
  convert-ASCII-OFF-to-binary-OFF.cpp convert-ASCII-OFF-to-binary-OFF.h
  convert-ASCII-OFF-to-binary-PLY.cpp convert-ASCII-OFF-to-binary-PLY.h
  convert-ASCII-PLY-to-binary-PLY.cpp convert-ASCII-PLY-to-binary-PLY.h
  convert-binary-OFF-to-binary-PLY.cpp convert-binary-OFF-to-binary-PLY.h
  convert-binary-PLY-to-ASCII-OFF.cpp convert-binary-PLY-to-ASCII-OFF.h
  main.cpp
  spy.cpp spy.h
)

add_executable(${PROJECT_NAME} ${SRC_LIST})

# Link the executable to the required libraries

target_link_libraries(${PROJECT_NAME}
  ${Boost_LIBRARIES}
#  Other required 3rd party libraries would appear below (examples commented):
#  ${CMAKE_THREAD_LIBS_INIT}
#  ${OpenIGTLink_LIBRARIES}
#  ${ITK_LIBRARIES}
#  ${VTK_LIBRARIES}
)

set(TARGET_NAME ${PROJECT_NAME}Targets)
install(TARGETS ${PROJECT_NAME} # EXPORT ${TARGET_NAME}
#  LIBRARY DESTINATION lib
#  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
#  INCLUDES DESTINATION include
)
