cmake_minimum_required (VERSION 3.8)

project (animalGuessingGame)

set(SOURCE_FILES
	main.cpp
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable (${PROJECT_NAME} ${SOURCE_FILES})



cmake_minimum_required (VERSION 3.8)
project (libraryManagementSystem)