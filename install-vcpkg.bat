@echo off

set GIT_REPO="https://github.com/microsoft/vcpkg"
set GIT_TAG="2022.05.10"

git clone --depth 1 --branch %GIT_TAG% %GIT_REPO%

vcpkg/bootstrap-vcpkg.bat

@echo on