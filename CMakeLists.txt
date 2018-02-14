cmake_minimum_required (VERSION 2.8) 

include_directories(SYSTEM 
./ 
) 

# enum your files 
add_executable(executable 
labNumberOne.cpp,
main.cpp,
string.h
) 

target_link_libraries(executable)
