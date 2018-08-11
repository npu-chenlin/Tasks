include_directories(${PROJECT_SOURCE_DIR}/libfloyd)
AUX_SOURCE_DIRECTORY(. APP_SRC)
add_executable(floyd ${APP_SRC})
target_link_libraries(floyd libfloyd)