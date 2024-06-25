@echo off

cmake -DGLFW_BUILD_DOCS=OFF -DGLM_ENABLE_CXX_17=ON -G "MinGW Makefiles" -S . -B ./out/build/


