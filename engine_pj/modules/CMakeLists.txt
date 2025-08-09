if(ENABLE_EMBEDDED)
    add_subdirectory(embedded)
endif()

if(ENABLE_GRAPHICS)
    add_subdirectory(graphics)
endif()

if(ENABLE_AI)
    add_subdirectory(ai_ext)
endif()

add_subdirectory(camera)
add_subdirectory(game)
