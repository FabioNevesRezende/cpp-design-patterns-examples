cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)

if(ADAPTER OR ALL)
    add_executable(adapter adapter.cpp)
endif()

if(BRIDGE OR ALL)
    add_executable(bridge bridge.cpp)
endif()

if(COMPOSITE OR ALL)
    add_executable(composite composite.cpp)
endif()

if(DECORATOR OR ALL)
    add_executable(decorator decorator.cpp)
endif()

if(FACADE OR ALL)
    add_executable(facade facade.cpp)
endif()

if(FLYWEIGHT OR ALL)
    add_executable(flyweight flyweight.cpp)
endif()

if(PROXY OR ALL)
    add_executable(proxy proxy.cpp)
endif()

if(FACTORY OR ALL)
    add_executable(factory factory.cpp)
endif()

if(ABSTRACTFACTORY OR ALL)
    add_executable(abstractFactory abstractFactory.cpp)
endif()

if(BUILDER OR ALL)
    add_executable(builder builder.cpp)
endif()

if(PROTOTYPE OR ALL)
    add_executable(prototype prototype.cpp)
endif()

if(SINGLETON OR ALL)
    add_executable(singleton singleton.cpp)
endif()

if(CHAIN OR ALL)
    add_executable(chain-of-responsibility chain-of-responsibility.cpp)
endif()

if(COMMANDPTN OR ALL)
    add_executable(command command.cpp)
endif()

if(TESTPTR OR ALL)
    add_executable(testptr testptr.cpp)
endif()

if(MEDIATOR OR ALL)
    add_executable(mediator mediator.cpp)
endif()

if(OBSERVER OR ALL)
    add_executable(observer observer.cpp)
endif()

if(INTERPRETER OR ALL)
    add_executable(interpreter interpreter.cpp)
endif()