cmake_minimum_required(VERSION 2.6)
if(NOT LOGPOOL)
check_include_files(pthread.h      HAVE_PTHREAD_H)
check_include_files(event2/event.h HAVE_LIBEVENT_H)
check_include_files(libmemcached/memcached.h HAVE_MEMCACHED_H)
if(HAVE_PTHREAD_H AND HAVE_LIBEVENT_H AND HAVE_MEMCACHED_H)
add_subdirectory(ext/logpool)
set(LOGPOOL logpool)
endif()
endif(NOT LOGPOOL)

if(LOGPOOL)
set(PACKAGE_SOURCE_CODE logpool_glue.c)
set(PACKAGE_SCRIPT_CODE logpool_glue.k)
FIND_PACKAGE_EXTRA_LIBRARY(logpool memcached)
add_konoha_package(logpool)
else(LOGPOOL)
show_package_warning(logpool)
endif(LOGPOOL)
