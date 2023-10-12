@echo off

setlocal ENABLEDELAYEDEXPANSION

set origin_dir=%~dp0
set build_dir=%origin_dir%build

md %build_dir%

cmake ^
	-S %origin_dir% -B %build_dir% ^
    -G "Visual Studio 16 2019" -A x64 ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DBUILD_SHARED_LIBS=OFF

cd %build_dir%
cmake --build %build_dir% --config Release