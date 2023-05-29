cmake_minimum_required(VERSION 3.10)

project( pf_v3 )
add_executable(${PROJECT_NAME} medicion.h medicion.cpp db_local.h db_local.cpp main.cpp 
			sensor.h sensor.cpp )
target_link_libraries (${PROJECT_NAME} sqlite3 )

