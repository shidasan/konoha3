cmake_minimum_required(VERSION 2.6)
if(USE_DSE_PLATFORM)
	find_library(HAVE_LIBEVENT NAMES event)
	find_library(HAVE_LIBLOGPOOL  NAMES logpool)
	add_executable(dse dse.c)
	set(DSE_PLATFORM_SCRIPT_CODE script/dse.k)
	set(_DSE_SCRIPT_DIR minikonoha/dse)
	set(DSE_PLATFORM_EXTRA_LIBRARY minikonoha)
	if(HAVE_LIBEVENT)
		set(DSE_PLATFORM_EXTRA_LIBRARY ${DSE_PLATFORM_EXTRA_LIBRARY} event)
	endif(HAVE_LIBEVENT)
	if(HAVE_LIBLOGPOOL)
		set(DSE_PLATFORM_EXTRA_LIBRARY ${DSE_PLATFORM_EXTRA_LIBRARY} logpool)
	endif(HAVE_LIBLOGPOOL)
	target_link_libraries(dse ${DSE_PLATFORM_EXTRA_LIBRARY})
	install(TARGETS dse DESTINATION bin)
	install(FILES ${DSE_PLATFORM_SCRIPT_CODE} DESTINATION ${_DSE_SCRIPT_DIR})
endif(USE_DSE_PLATFORM)
