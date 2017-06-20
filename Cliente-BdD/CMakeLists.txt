cmake_minimum_required(VERSION 3.6)
project(Cliente_BdD)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/Main.cpp include/ipc/Cola.h include/Persona.h src/ipc/Semaforo.cpp include/ipc/Semaforo.h include/ipc/MemoriaCompartida.h src/BdD.cpp include/BdD.h src/Conector.cpp include/Conector.h src/ipc/ExclusiveLockFile.cpp include/ipc/ExclusiveLockFile.h src/Logger.cpp include/Logger.h src/ipc/SharedLockFile.cpp include/ipc/SharedLockFile.h include/ipc/signal/EventHandler.h include/ipc/signal/impl/SIGINT_Handler.h src/ipc/signal/SignalHandler.cpp include/ipc/signal/SignalHandler.h)
add_executable(Cliente_BdD ${SOURCE_FILES})