add_library(LogicTerm_lib
            ${CMAKE_CURRENT_SOURCE_DIR}/LogicTerm/TermImpl.cpp
            ${${PROJECT_NAME}_SOURCE_DIR}/include/LogicTerm/TermImpl.hpp

            ${CMAKE_CURRENT_SOURCE_DIR}/LogicTerm/LogicTerm.cpp
            ${${PROJECT_NAME}_SOURCE_DIR}/include/LogicTerm/LogicTerm.hpp

            ${${PROJECT_NAME}_SOURCE_DIR}/include/LogicTerm/Logic.hpp
            ${${PROJECT_NAME}_SOURCE_DIR}/include/LogicBlock/Model.hpp

            ${${PROJECT_NAME}_SOURCE_DIR}/include/LogicUtil/util_logic.hpp
            ${${PROJECT_NAME}_SOURCE_DIR}/include/LogicUtil/util_logicterm.hpp
            ${${PROJECT_NAME}_SOURCE_DIR}/include/utils/logging.hpp
            ${${PROJECT_NAME}_SOURCE_DIR}/include/utils/csv_util.hpp
            ${${PROJECT_NAME}_SOURCE_DIR}/include/utils/json_util.hpp)
target_include_directories(LogicTerm_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(LogicTerm_lib PUBLIC plog)
# set required C++ standard and disable compiler specific extensions
target_compile_features(LogicTerm_lib PUBLIC cxx_std_17)
set_target_properties(LogicTerm_lib PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)

# set compiler flags depending on compiler
# since these are defined `PUBLIC` they are propagated to all linking targets
if(MSVC)
	target_compile_options(LogicTerm_lib PUBLIC /utf-8)
else()
	target_compile_options(LogicTerm_lib PUBLIC -Wall -Wextra $<$<CONFIG:DEBUG>:-Og>)
	if(NOT DEPLOY)
		# only include machine-specific optimizations when building for the host machine
		target_compile_options(LogicTerm_lib PUBLIC -mtune=native)
		include(CheckCXXCompilerFlag)
		check_cxx_compiler_flag(-march=native HAS_MARCH_NATIVE)
		if (HAS_MARCH_NATIVE)
			target_compile_options(LogicTerm_lib PUBLIC -march=native)
		endif ()
	endif ()
endif()


add_library(SMTLibLogic
            ${${PROJECT_NAME}_SOURCE_DIR}/include/LogicBlock/LogicBlock.hpp
            ${${PROJECT_NAME}_SOURCE_DIR}/include/LogicBlock/SMTLibLogicBlock.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/LogicBlock/SMTLibLogicBlock.cpp)
target_link_libraries(SMTLibLogic PUBLIC LogicTerm_lib)
add_library(logicblocks::SMTLibLogic ALIAS SMTLibLogic)

add_library(CNFLogic
		${${PROJECT_NAME}_SOURCE_DIR}/include/LogicBlock/LogicBlock.hpp
		${${PROJECT_NAME}_SOURCE_DIR}/include/LogicBlock/CNFLogicBlock.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/LogicBlock/CNFLogicBlock.cpp)
target_link_libraries(CNFLogic PUBLIC LogicTerm_lib)
add_library(logicblocks::CNFLogic ALIAS SMTLibLogic)

add_library(Z3Logic
            ${${PROJECT_NAME}_SOURCE_DIR}/include/LogicBlock/LogicBlock.hpp
            ${${PROJECT_NAME}_SOURCE_DIR}/include/LogicBlock/Z3Logic.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/LogicBlock/Z3Logic.cpp
            ${${PROJECT_NAME}_SOURCE_DIR}/include/LogicBlock/Z3Model.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/LogicBlock/Z3Model.cpp)
target_link_libraries(Z3Logic PUBLIC LogicTerm_lib z3::z3lib)
add_library(logicblocks::Z3Logic ALIAS Z3Logic)

add_library(Encodings
			${${PROJECT_NAME}_SOURCE_DIR}/include/LogicBlock/LogicBlock.hpp
			${${PROJECT_NAME}_SOURCE_DIR}/include/Encodings/Encodings.hpp
			${CMAKE_CURRENT_SOURCE_DIR}/Encodings/Encodings.cpp)
target_link_libraries(Encodings PUBLIC LogicTerm_lib )
add_library(logicblocks::Encodings ALIAS Encodings)

add_library(Logic INTERFACE)
target_link_libraries(Logic INTERFACE SMTLibLogic Z3Logic)
add_library(logicblocks::Logic ALIAS Logic)
