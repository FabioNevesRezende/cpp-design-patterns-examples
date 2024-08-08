cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)

if(ADAPTER)
    add_executable(adapter adapter.cpp)
endif()

if(BRIDGE)
    add_executable(bridge bridge.cpp)
endif()

if(COMPOSITE)
    add_executable(composite composite.cpp)
endif()

if(DECORATOR)
    add_executable(decorator decorator.cpp)
endif()

if(FACADE)
    add_executable(facade facade.cpp)
endif()

if(FLYWEIGHT)
    add_executable(flyweight flyweight.cpp)
endif()

if(PROXY)
    add_executable(proxy proxy.cpp)
endif()

if(FACTORY)
    add_executable(factory factory.cpp)
endif()

if(ABSTRACTFACTORY)
    add_executable(abstractFactory abstractFactory.cpp)
endif()

if(BUILDER)
    add_executable(builder builder.cpp)
endif()

if(PROTOTYPE)
    add_executable(prototype prototype.cpp)
endif()

if(SINGLETON)
    add_executable(singleton singleton.cpp)
endif()

if(CHAIN)
    add_executable(chain-of-responsibility chain-of-responsibility.cpp)
endif()

if(COMMANDPTN)
    add_executable(command command.cpp)
endif()

if(TESTPTR)
    add_executable(testptr testptr.cpp)
endif()

if(MEDIATOR)
    add_executable(mediator mediator.cpp)
endif()

if(OBSERVER)
    add_executable(observer observer.cpp)
endif()