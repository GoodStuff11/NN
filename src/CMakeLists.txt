file(GLOB files 
	main.cpp
	"data types/*.cpp"
	structure/*.cpp)

add_executable(Neural-Network ${files})