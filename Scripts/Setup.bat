@echo off

pushd %~dp0

set TOOLCHAIN_FILE=%CD%/../vcpkg/scripts/buildsystems/vcpkg.cmake

if "%1%" == "" (
	set BUILD_TYPE=Release
) else (
	set BUILD_TYPE=%1
)

cd ..
if not exist Binaries\%BUILD_TYPE%\ (
	mkdir Binaries\%BUILD_TYPE%
)
cd Binaries\%BUILD_TYPE%

cmake ../.. -DCMAKE_TOOLCHAIN_FILE=%TOOLCHAIN_FILE% -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DVCPKG_FEATURE_FLAGS=manifests,registries
popd