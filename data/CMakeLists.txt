# -- CMake build rules

set(SRC_LIST
  # We credit Ryan Holmes for the original .off files
  # (retrieved on March 25, 2019, from http://www.holmes3d.net/graphics/offfiles/)
  boxcube-ASCII.off
  dodecahedron-ASCII.off
  icosahedron-ASCII.off
)

install(FILES ${SRC_LIST}
  DESTINATION bin
)
