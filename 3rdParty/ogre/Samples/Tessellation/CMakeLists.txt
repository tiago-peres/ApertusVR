# Configure Tessellation demo build

set(HEADER_FILES include/Tessellation.h)
set(SOURCE_FILES src/Tessellation.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
ogre_add_library_to_folder(Samples Sample_Tessellation ${OGRE_LIB_TYPE} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(Sample_Tessellation ${OGRE_LIBRARIES} ${OIS_LIBRARIES})
ogre_config_sample_lib(Sample_Tessellation)

if (APPLE AND NOT OGRE_BUILD_PLATFORM_APPLE_IOS)
    # Set the INSTALL_PATH so that Samples can be installed in the application package
    set_target_properties(Sample_Tessellation
       PROPERTIES BUILD_WITH_INSTALL_RPATH 1
       INSTALL_NAME_DIR "@executable_path/../Plugins"
    )
endif()

