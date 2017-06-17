cmake_minimum_required(VERSION 3.6)
project(Cliente_BdD)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/Main.cpp include/ipc/Cola.h include/Persona.h src/ipc/Semaforo.cpp include/ipc/Semaforo.h include/ipc/MemoriaCompartida.h src/BdD.cpp include/BdD.h src/Conector.cpp include/Conector.h src/ipc/LockFIle.cpp include/ipc/LockFIle.h)
add_executable(Cliente_BdD ${SOURCE_FILES})