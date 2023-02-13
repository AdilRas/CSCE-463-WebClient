default: build run

build:
	/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake --build /Users/adil/CLionProjects/Dragonov/cmake-build-debug --target Dragonov -j 8
	/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake --build /Users/adil/CLionProjects/Dragonov/cmake-build-debug --target test_suite -j 8

run:
	./cmake-build-debug/Dragonov $(args)
