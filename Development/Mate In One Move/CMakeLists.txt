cmake_minimum_required( VERSION 3.26 )

project( Mate_In_One_Move )

set( MAIN_PROGRAM MIOM )

# Set compiler flags
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_EXTENSIONS OFF )

# use mold linker
set(CMAKE_EXE_LINKER_FLAGS_INIT    "-fuse-ld=mold")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "-fuse-ld=mold")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "-fuse-ld=mold")

set(SOURCE
	src/Solver.cpp
	main.cpp
	)


add_executable( ${MAIN_PROGRAM} ${SOURCE} )

target_compile_options( ${MAIN_PROGRAM} 
	PRIVATE
		-Wall 
		-Werror 
		-Wextra 
		-pedantic 
		-pedantic-errors
)

target_include_directories( ${MAIN_PROGRAM} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
target_include_directories( ${MAIN_PROGRAM} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src" )


set( TEST_SUITE MIOM_Tests_Suite )

include(CTest)
enable_testing()

find_package( GTest REQUIRED )

set( TEST_SOURCE 
	src/Solver.cpp
   tests/mate_in_one_move.t.cpp
)

add_executable( ${TEST_SUITE} ${TEST_SOURCE} )

target_compile_options( ${TEST_SUITE} 
	PRIVATE
		-Wall 
		-Wextra 
		-pedantic 
		-pedantic-errors
		-pg
		-ftest-coverage
		-fsanitize=address
		-fsanitize=undefined
			-fsanitize=shift
			-fsanitize=shift-exponent
			-fsanitize=shift-base
			-fsanitize=integer-divide-by-zero
			-fsanitize=vla-bound
			-fsanitize=null
			-fsanitize=return
			-fsanitize=signed-integer-overflow
			-fsanitize=bounds
			-fsanitize=bounds-strict
			-fsanitize=alignment 
			-fsanitize=object-size
			-fsanitize=float-divide-by-zero 
			-fsanitize=float-cast-overflow 
			-fsanitize=enum
			-fsanitize=pointer-overflow
		-fsanitize-address-use-after-scope
		-fstack-protector-all
)

target_link_options(${TEST_SUITE}  
	PRIVATE 
		-fsanitize=undefined
		-fsanitize=address
)

target_link_libraries( ${TEST_SUITE} GTest::gtest_main )
target_link_libraries( ${TEST_SUITE} GTest::gmock_main)

target_include_directories( ${TEST_SUITE} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
target_include_directories( ${TEST_SUITE} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src" )

include( GoogleTest )
gtest_discover_tests( ${TEST_SUITE} )