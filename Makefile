CXX := g++
# Mac users: add -I/path/to/SFML/include to CXXFLAGS
CXXFLAGS := -Wall -Wextra -pedantic -std=c++17 -g

sfml_flags := -lsfml-graphics -lsfml-window -lsfml-system

all: asset_lib_tests.exe scene_tests.exe main.exe

test: asset_lib_tests.exe scene_tests.exe main.exe
	./asset_lib_tests.exe
	./scene_tests.exe
	./main.exe < main_public_test1.in > main_public_test1.out.txt
	diff main_public_test1.out.correct main_public_test1.out.txt
	./main.exe < main_public_test2.in > main_public_test2.out.txt
	diff main_public_test2.out.correct main_public_test2.out.txt
	./main.exe < main_public_test3.in > main_public_test3.out.txt
	diff main_public_test3.out.correct main_public_test3.out.txt

asset_lib_tests.exe: asset_lib.cpp asset_lib_tests.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

scene_tests.exe: scene.cpp asset_lib.cpp scene_tests.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(sfml_flags)

main.exe: asset_lib.cpp scene.cpp main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(sfml_flags)

.PHONY: clean all
clean:
	rm -vf *.exe *.out.txt
