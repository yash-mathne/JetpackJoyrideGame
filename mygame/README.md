Jetpack Joyride Game
=========================

Instructions:
mkdir build
cd build
cmake ..
make all 

Note - In case of Experimental Error for GLM.
add "#define GLM_ENABLE_EXPERIMENTAL" in the files main.h nonedit.cpp other_handlers.cpp and input.cpp, before you include glm.
