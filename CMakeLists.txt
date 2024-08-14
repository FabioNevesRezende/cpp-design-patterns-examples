cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)

if(ADAPTER OR ALL)
    add_executable(adapter structural/adapter.cpp)
endif()

if(BRIDGE OR ALL)
    add_executable(bridge structural/bridge.cpp)
endif()

if(COMPOSITE OR ALL)
    add_executable(composite structural/composite.cpp)
endif()

if(DECORATOR OR ALL)
    add_executable(decorator structural/decorator.cpp)
endif()

if(FACADE OR ALL)
    add_executable(facade structural/facade.cpp)
endif()

if(FLYWEIGHT OR ALL)
    add_executable(flyweight structural/flyweight.cpp)
endif()

if(PROXY OR ALL)
    add_executable(proxy structural/proxy.cpp)
endif()

if(FACTORY OR ALL)
    add_executable(factory creational/factory.cpp)
endif()

if(ABSTRACTFACTORY OR ALL)
    add_executable(abstractFactory creational/abstractFactory.cpp)
endif()

if(BUILDER OR ALL)
    add_executable(builder creational/builder.cpp)
endif()

if(PROTOTYPE OR ALL)
    add_executable(prototype creational/prototype.cpp)
endif()

if(SINGLETON OR ALL)
    add_executable(singleton creational/singleton.cpp)
endif()

if(CHAIN OR ALL)
    add_executable(chain-of-responsibility behavioral/chain-of-responsibility.cpp)
endif()

if(COMMANDPTN OR ALL)
    add_executable(command behavioral/command.cpp)
endif()

if(MEDIATOR OR ALL)
    add_executable(mediator behavioral/mediator.cpp)
endif()

if(OBSERVER OR ALL)
    add_executable(observer behavioral/observer.cpp)
endif()

if(INTERPRETER OR ALL)
    add_executable(interpreter behavioral/interpreter.cpp)
endif()

if(STATE OR ALL)
    add_executable(state behavioral/state.cpp)
endif()

if(STRATEGY OR ALL)
    add_executable(strategy behavioral/strategy.cpp)
endif()

if(TEMPLATE OR ALL)
    add_executable(template behavioral/template.cpp)
endif()

if(VISITOR OR ALL)
    add_executable(visitor behavioral/visitor.cpp)
endif()