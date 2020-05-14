
if (WIN32)
  link_libraries(Delayimp)
endif()

add_library(args_check SHARED args_check.cpp ${CMAKE_JS_SRC})
set_target_properties(args_check PROPERTIES PREFIX "" SUFFIX ".node")

add_library(type_converter SHARED type_converter.cpp ${CMAKE_JS_SRC})
set_target_properties(type_converter PROPERTIES PREFIX "" SUFFIX ".node")
