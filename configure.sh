cmake -S . \
	-B build \
	-DCMAKE_C_COMPILER=gcc-10 \
	-DCMAKE_CXX_COMPILER=g++-10 \
	-DUSE_VCPKG=TRUE\
	-DVCPKG_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake