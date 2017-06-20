cmake_minimum_required(VERSION 3.6)
project(Gestor_BdD)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/Main.cpp include/ipc/Cola.h include/Persona.h src/ipc/Semaforo.cpp include/ipc/Semaforo.h src/Logger.cpp include/Logger.h src/ipc/ExclusiveLockFile.cpp include/ipc/ExclusiveLockFile.h src/DespachanteConsultas.cpp include/DespachanteConsultas.h src/Buscador.cpp include/Buscador.h src/ipc/SharedLockFile.cpp include/ipc/SharedLockFile.h src/Insertor.cpp include/Insertor.h include/ipc/signal/EventHandler.h include/ipc/signal/impl/SIGINT_Handler.h src/ipc/signal/SignalHandler.cpp include/ipc/signal/SignalHandler.h)
add_executable(Gestor_BdD ${SOURCE_FILES})