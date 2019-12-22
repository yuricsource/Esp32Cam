#
# Main component makefile.
#
# This Makefile can be left empty. By default, it will take the sources in the 
# src/ directory, compile them and link them into lib(subdirectory_name).a 
# in the build directory. This behaviour is entirely configurable,
# please read the ESP-IDF documents if you need to do this.
#
COMPONENT_SRCDIRS           +=  ../System/Source/Hal                                     \
                                ../System/Source/Hal/Camera                              \
                                ../System/Source/Middleware                              \
                                ../System/Libraries/freertos-addons/Source
COMPONENT_ADD_INCLUDEDIRS   +=  ${IDF_PATH}/components/                                  \
                                ../System/Include/Hal                                    \
                                ../System/Include/Hal/Camera                             \
                                ../System/Include/Middleware                             \
                                ../System/Libraries/freertos-addons/Source/include