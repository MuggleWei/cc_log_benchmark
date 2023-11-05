cmake_minimum_required (VERSION 3.18.6)
project(log_benchmark)

################################
# general config
################################

message("-- use c compiler ${CMAKE_C_COMPILER}")
message("-- use c++ compiler ${CMAKE_CXX_COMPILER}")

# set compile parameter
if (${CMAKE_C_COMPILER_ID} STREQUAL GNU)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
elseif (${CMAKE_C_COMPILER_ID} MATCHES Clang)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-missing-field-initializers")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-missing-field-initializers")
elseif (${CMAKE_C_COMPILER_ID} STREQUAL MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS=1 -D_UNICODE -DUNICODE)
	add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
	add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
	add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>")
	add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/std:c++20>")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("-- c compiler support features: ")
foreach(feature ${CMAKE_C_COMPILE_FEATURES})
	message("support c feature: ${feature}")
endforeach()

message("-- c++ compiler support features: ")
foreach(feature ${CMAKE_CXX_COMPILE_FEATURES})
	message("support c++ feature: ${feature}")
endforeach()

# set output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# for vim plugin
if (NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# set use folder in vs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# fetch functions
include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/_deps)

################################
# options
################################

set(benchmark_easyloggingpp OFF CACHE BOOL "generate benchmark: easyloggingpp")

if (APPLE)
	set(benchmark_fmtlog OFF CACHE BOOL "generate benchmark: fmtlog")
else()
	set(benchmark_fmtlog ON CACHE BOOL "generate benchmark: fmtlog")
endif()

set(benchmark_glog ON CACHE BOOL "generate benchmark: glog")

set(benchmark_haclog ON CACHE BOOL "generate benchmark: haclog")

set(benchmark_loguru ON CACHE BOOL "generate benchmark: loguru")

if (UNIX)
	if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
		set(benchmark_nanolog OFF CACHE BOOL "generate benchmark: nanolog")
	else()
		set(benchmark_nanolog ON CACHE BOOL "generate benchmark: nanolog")
	endif()
else()
	set(benchmark_nanolog OFF CACHE BOOL "generate benchmark: nanolog")
endif()

set(benchmark_quill ON CACHE BOOL "generate benchmark: quill")

if (APPLE OR WIN32)
	set(benchmark_reckless OFF CACHE BOOL "generate benchmark: reckless")
else()
	set(benchmark_reckless ON CACHE BOOL "generate benchmark: reckless")
endif()

set(benchmark_spdlog ON CACHE BOOL "generate benchmark: spdlog")


################################
# log message
################################

FILE(GLOB_RECURSE log_msg_h "${CMAKE_CURRENT_LIST_DIR}/log_msg/*.h")
FILE(GLOB_RECURSE log_msg_cpp "${CMAKE_CURRENT_LIST_DIR}/log_msg/*.cpp")
add_library(log_msg STATIC
	${log_msg_h}
	${log_msg_cpp})
set_target_properties(log_msg PROPERTIES LINKER_LANGUAGE CXX)

FILE(GLOB_RECURSE gen_data_h "${CMAKE_CURRENT_LIST_DIR}/gen_random_data/*.h")
FILE(GLOB_RECURSE gen_data_cpp "${CMAKE_CURRENT_LIST_DIR}/gen_random_data/*.cpp")
add_executable(gen_random_data
	${gen_data_h}
	${gen_data_cpp})
add_dependencies(gen_random_data log_msg)
target_include_directories(gen_random_data PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/log_msg)
target_link_libraries(gen_random_data log_msg)

################################
# google benchmark
################################

message("# fetch google benchmark")
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "")
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "")
FetchContent_Declare(
	benchmark
	GIT_REPOSITORY https://github.com/google/benchmark.git
	GIT_TAG v1.8.3
	GIT_SHALLOW TRUE
	GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(benchmark)

#message("# fetch mugglec")
#SET(MUGGLE_BUILD_BENCHMARK_UTILS ON CACHE BOOL "")
#FetchContent_Declare(
#    mugglec
#    GIT_REPOSITORY https://github.com/MuggleWei/mugglec.git
#    GIT_TAG v1.3.4
#    GIT_SHALLOW TRUE
#    GIT_PROGRESS TRUE)
#FetchContent_MakeAvailable(mugglec)

find_package(Threads)

function(add_gbench name folder)
	message("add gbenchmark ${name} ${folder}")
	set(name gbenchmark_${name})

	file(GLOB_RECURSE tmp_h ${folder}/*.h)
	file(GLOB_RECURSE tmp_c ${folder}/*.c)
	file(GLOB_RECURSE tmp_cpp ${folder}/*.cpp)
	file(GLOB_RECURSE tmp_cc ${folder}/*.cc)

	if (MSVC OR MINGW)
		add_executable(${name} ${tmp_h} ${tmp_c} ${tmp_cpp} ${tmp_cc})
		set_target_properties(${name}
			PROPERTIES
			FOLDER "example"
			VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)"
		)
	else()
		add_executable(${name} ${tmp_c} ${tmp_cpp} ${tmp_cc})
		if (APPLE)
			set_target_properties(${name}
				PROPERTIES
				INSTALL_RPATH "@executable_path/../lib"
			)
		elseif (UNIX)
			set_target_properties(${name}
				PROPERTIES
				INSTALL_RPATH "\$ORIGIN/../lib"
			)
		endif()
	endif(MSVC OR MINGW)

	add_dependencies(${name} benchmark log_msg)
	target_include_directories(${name} PRIVATE
		${folder}
		${FETCHCONTENT_BASE_DIR}/benchmark-src
		${CMAKE_CURRENT_LIST_DIR})
	target_link_libraries(${name} benchmark log_msg)

	# save temp object file, such as: asm code
	if ((${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU") OR
		(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"))
		target_compile_options(${name} PUBLIC -save-temps=obj)
	endif()
endfunction()

################################
# logging libraries
################################

if (benchmark_easyloggingpp)
	message("# fetch easyloggingpp")
	set(build_static_lib ON)
	FetchContent_Declare(
		easyloggingpp
		GIT_REPOSITORY https://github.com/abumq/easyloggingpp.git
		GIT_TAG v9.97.1
		GIT_SHALLOW TRUE
		GIT_PROGRESS TRUE
		)
	FetchContent_MakeAvailable(easyloggingpp)
	target_compile_definitions(easyloggingpp PUBLIC ELPP_THREAD_SAFE)
endif()

if (benchmark_fmtlog)
	message("# fetch fmtlog")
	FetchContent_Declare(
		fmtlog
		GIT_REPOSITORY https://github.com/MengRao/fmtlog.git
		GIT_TAG v2.2.1
		GIT_SHALLOW TRUE
		GIT_PROGRESS TRUE
		)
	FetchContent_MakeAvailable(fmtlog)
endif()

if (benchmark_haclog)
	message("# fetch haclog")
	FetchContent_Declare(
		haclog
		GIT_REPOSITORY https://github.com/MuggleWei/haclog.git
		GIT_TAG "v0.0.4"
		GIT_SHALLOW TRUE
		GIT_PROGRESS TRUE
		)
	FetchContent_MakeAvailable(haclog)
endif()

if (benchmark_loguru)
	message("# fetch loguru")
	FetchContent_Declare(
		loguru
		GIT_REPOSITORY https://github.com/emilk/loguru.git
		GIT_TAG "v2.1.0"
		GIT_SHALLOW TRUE
		GIT_PROGRESS TRUE
		)
	FetchContent_Populate(loguru)
endif()

if (benchmark_glog)
	message("# fetch glog")
	set(WITH_GFLAGS OFF)
	FetchContent_Declare(
		glog
		GIT_REPOSITORY https://github.com/google/glog.git
		GIT_TAG v0.6.0
		GIT_SHALLOW TRUE
		GIT_PROGRESS TRUE
		)
	FetchContent_MakeAvailable(glog)
endif()

if (benchmark_nanolog)
	message("# fetch nanolog")
	FetchContent_Declare(
		nanolog
		GIT_REPOSITORY https://github.com/PlatformLab/NanoLog.git
		GIT_TAG "2a94d70f9d1db4da416053b1b926387fa068a59b"
		GIT_SHALLOW TRUE
		GIT_PROGRESS TRUE
		)
	FetchContent_Populate(nanolog)

	include(ExternalProject)
	ExternalProject_Add(nanolog
		SOURCE_DIR "${FETCHCONTENT_BASE_DIR}/nanolog-src/runtime"
		#BINARY_DIR "${FETCHCONTENT_BASE_DIR}/nanolog-build"
		DOWNLOAD_COMMAND ""
		CONFIGURE_COMMAND ""
		BUILD_COMMAND "make"
		BUILD_IN_SOURCE TRUE
		INSTALL_COMMAND ""
		BUILD_BYPRODUCTS "${FETCHCONTENT_BASE_DIR}/nanolog-src/runtime/libnano.a"
		)

	add_library(nanolog_lib STATIC IMPORTED GLOBAL)
	set_property(TARGET nanolog_lib
		PROPERTY IMPORTED_LOCATION 
		${FETCHCONTENT_BASE_DIR}/nanolog-src/runtime/libNanoLog.a
		)
endif()

if (benchmark_quill)
	message("# fetch quill")
	FetchContent_Declare(
		quill
		GIT_REPOSITORY https://github.com/odygrd/quill.git
		GIT_TAG v3.3.1
		GIT_SHALLOW TRUE
		GIT_PROGRESS TRUE
		)
	FetchContent_MakeAvailable(quill)
endif()

if (benchmark_reckless)
	message("# fetch reckless")
	FetchContent_Declare(
		reckless
		GIT_REPOSITORY https://github.com/mattiasflodin/reckless.git
		GIT_TAG v3.0.3
		GIT_SHALLOW TRUE
		GIT_PROGRESS TRUE
		)
	FetchContent_MakeAvailable(reckless)
endif()

if (benchmark_spdlog)
	message("# fetch spdlog")
	FetchContent_Declare(
		spdlog
		GIT_REPOSITORY https://github.com/gabime/spdlog.git
		GIT_TAG v1.12.0
		GIT_SHALLOW TRUE
		GIT_PROGRESS TRUE
		)
	FetchContent_MakeAvailable(spdlog)
endif()

################################
# gbenchmark
################################

set(gbenchmark_dir ${CMAKE_CURRENT_LIST_DIR}/gbenchmark)

if (benchmark_easyloggingpp)
	add_gbench(easyloggingpp ${gbenchmark_dir}/cpp/easyloggingpp)
	add_dependencies(gbenchmark_easyloggingpp easyloggingpp)
	target_link_libraries(gbenchmark_easyloggingpp easyloggingpp)
	target_include_directories(gbenchmark_easyloggingpp PUBLIC ${FETCHCONTENT_BASE_DIR}/easyloggingpp-src/src)
endif()

if (benchmark_fmtlog)
	add_gbench(fmtlog ${gbenchmark_dir}/cpp/fmtlog)
	add_dependencies(gbenchmark_fmtlog fmtlog-static fmt)
	target_link_libraries(gbenchmark_fmtlog fmtlog-static fmt)
	target_include_directories(gbenchmark_fmtlog PUBLIC
		${FETCHCONTENT_BASE_DIR}/fmtlog-src/
		${FETCHCONTENT_BASE_DIR}/fmtlog-src/fmt/include
		)

	add_gbench(fmtlog_block ${gbenchmark_dir}/cpp/fmtlog_block)
	add_dependencies(gbenchmark_fmtlog_block fmtlog-static fmt)
	target_link_libraries(gbenchmark_fmtlog_block fmtlog-static fmt)
	target_include_directories(gbenchmark_fmtlog_block PUBLIC
		${FETCHCONTENT_BASE_DIR}/fmtlog-src/
		${FETCHCONTENT_BASE_DIR}/fmtlog-src/fmt/include
		)
endif()

if (benchmark_glog)
	add_gbench(glog ${gbenchmark_dir}/cpp/glog)
	add_dependencies(gbenchmark_glog glog)
	target_link_libraries(gbenchmark_glog glog)
endif()

if (benchmark_haclog)
	add_gbench(haclog ${gbenchmark_dir}/c/haclog)
	add_dependencies(gbenchmark_haclog haclog)
	target_link_libraries(gbenchmark_haclog haclog)
endif()

if (benchmark_loguru)
	add_gbench(loguru ${gbenchmark_dir}/cpp/loguru)
	target_include_directories(gbenchmark_loguru PUBLIC ${FETCHCONTENT_BASE_DIR}/loguru-src)
endif()

if (benchmark_nanolog)
	add_gbench(nanolog ${gbenchmark_dir}/cpp/nanolog)
	add_dependencies(gbenchmark_nanolog nanolog_lib)
	target_link_libraries(gbenchmark_nanolog nanolog_lib)
	target_include_directories(gbenchmark_nanolog PUBLIC ${FETCHCONTENT_BASE_DIR}/nanolog-src/runtime)
endif()

if (benchmark_quill)
	add_gbench(quill_unbounded ${gbenchmark_dir}/cpp/quill_unbounded)
	add_dependencies(gbenchmark_quill_unbounded quill)
	target_link_libraries(gbenchmark_quill_unbounded quill)

	add_gbench(quill_bounded ${gbenchmark_dir}/cpp/quill_bounded)
	add_dependencies(gbenchmark_quill_bounded quill)
	target_link_libraries(gbenchmark_quill_bounded quill)
	target_compile_definitions(gbenchmark_quill_bounded PUBLIC QUILL_USE_BOUNDED_QUEUE)
endif()

if (benchmark_reckless)
	add_gbench(reckless ${gbenchmark_dir}/cpp/reckless)
	add_dependencies(gbenchmark_reckless reckless)
	target_link_libraries(gbenchmark_reckless reckless)
	if (Threads_FOUND)
		target_link_libraries(gbenchmark_reckless reckless ${CMAKE_THREAD_LIBS_INIT})
	endif()
	target_include_directories(gbenchmark_reckless PUBLIC ${FETCHCONTENT_BASE_DIR}/reckless-src/reckless/include)
endif()

if (benchmark_spdlog)
	add_gbench(spdlog_sync ${gbenchmark_dir}/cpp/spdlog_sync)
	add_dependencies(gbenchmark_spdlog_sync spdlog)
	target_link_libraries(gbenchmark_spdlog_sync spdlog)

	add_gbench(spdlog_async ${gbenchmark_dir}/cpp/spdlog_async)
	add_dependencies(gbenchmark_spdlog_async spdlog)
	target_link_libraries(gbenchmark_spdlog_async spdlog)
endif()

message("# --------------------------------")
message("# benchmark easyloggingpp: ${benchmark_easyloggingpp}")
message("# benchmark fmtlog: ${benchmark_fmtlog}")
message("# benchmark glog: ${benchmark_glog}")
message("# benchmark haclog: ${benchmark_haclog}")
message("# benchmark loguru: ${benchmark_loguru}")
message("# benchmark nanolog: ${benchmark_nanolog}")
message("# benchmark reckless: ${benchmark_reckless}")
message("# benchmark spdlog: ${benchmark_spdlog}")
message("# --------------------------------")
