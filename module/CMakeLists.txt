cmake_minimum_required(VERSION 2.6)

macro(GET_MODULE_NAME _STR _RESULT)
	string(REPLACE "/" ";" _tmp ${_STR})
	list(REVERSE _tmp)
	list(GET _tmp 0 ${_RESULT})
endmacro()

set(KONOHA_MODULE_DIR
	"lib/minikonoha/${SO_VERSION}/module/${KONOHA_VERSION}/${ModuleName}")

macro(add_konoha_module ModuleName)
	MESSAGE(STATUS "Compiling ${ModuleName} Module")
	add_library(${ModuleName} SHARED ${MODULE_SOURCE_CODE})
	target_link_libraries(${ModuleName} ${MODULE_EXTRA_LIBRARY})
	set_target_properties(${ModuleName} PROPERTIES PREFIX "")
	install(TARGETS ${ModuleName} DESTINATION ${KONOHA_MODULE_DIR})
endmacro(add_konoha_module ModuleName)

file(GLOB dirs ${CMAKE_CURRENT_SOURCE_DIR}/*)
foreach(dir ${dirs})
	set(ModuleName)
	GET_MODULE_NAME(${dir} ModuleName)
	if(IS_DIRECTORY ${dir} AND EXISTS ${dir}/${ModuleName}.c)
		add_subdirectory(${dir})
	endif()
endforeach()