
if (WIN32)
  link_libraries(Delayimp)
endif()

add_library(args_check SHARED args_check.cpp ${CMAKE_JS_SRC})
set_target_properties(args_check PROPERTIES PREFIX "" SUFFIX ".node")

add_library(type_converter SHARED type_converter.cpp ${CMAKE_JS_SRC})
set_target_properties(type_converter PROPERTIES PREFIX "" SUFFIX ".node")

add_library(apply SHARED apply.cpp ${CMAKE_JS_SRC})
set_target_properties(apply PROPERTIES PREFIX "" SUFFIX ".node")

add_library(fetch_info_item SHARED fetch_info_item.cpp ${CMAKE_JS_SRC})
set_target_properties(fetch_info_item PROPERTIES PREFIX "" SUFFIX ".node")


add_library(create_async_worker SHARED create_async_worker.cpp ${CMAKE_JS_SRC})
set_target_properties(create_async_worker PROPERTIES PREFIX "" SUFFIX ".node")

add_library(native_event_emitter SHARED native_event_emitter.cpp ${CMAKE_JS_SRC})
set_target_properties(native_event_emitter PROPERTIES PREFIX "" SUFFIX ".node")

add_library(create_sync_method SHARED create_sync_method.cpp ${CMAKE_JS_SRC})
set_target_properties(create_sync_method PROPERTIES PREFIX "" SUFFIX ".node")
