# -- CMake build rules

set(SRC_LIST
  # We credit Ryan Holmes for the original .off files
  # (retrieved on March 25, 2019, from http://www.holmes3d.net/graphics/offfiles/)
  boxcube.off
  dodecahedron.off
  icosahedron.off
)

install(FILES ${SRC_LIST}
	DESTINATION bin
)

# -- eof
