set ( SOURCES
    "src/interface.cpp"
    "src/image_loader.cpp"
)

set (HEADERS
    "include/image_loader.h"
	${HEADERS_SHARED}
)

include_directories("include")

add_library ( image_loader MODULE ${SOURCES} ${HEADERS})
target_link_libraries(image_loader PRIVATE lmscore imaging)
