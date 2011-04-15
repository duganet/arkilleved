set(
	libio_SRCS
	file.cpp
	report.cpp
	io.cpp
)
add_library(arkilloid_io STATIC ${libio_SRCS})
