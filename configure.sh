cmake -S . \
	-B build \
	-DCMAKE_C_COMPILER=gcc-10 \
	-DCMAKE_CXX_COMPILER=g++-10 \
	--toolchain=vcpkg/scripts/buildsystems/vcpkg.cmake