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
                                ../System/Source/Hal/Wifi                                \
                                ../System/Source/Middleware/Utils                        \
                                ../System/Source/Middleware/Configuration                \
                                ../System/Source/Middleware/Protocol                     \
                                ../System/Source/Application                             \
                                ../System/Libraries/freertos-addons/Source
COMPONENT_ADD_INCLUDEDIRS   +=  ${IDF_PATH}/components/                                  \
                                ../System/Include/Hal                                    \
                                ../System/Include/Hal/Camera                             \
                                ../System/Include/Hal/Wifi                               \
                                ../System/Include/Middleware/Utils                       \
                                ../System/Include/Middleware/Configuration               \
                                ../System/Include/Middleware/Common                      \
                                ../System/Include/Middleware/Protocol                    \
                                ../System/Include/Application                            \
                                ../System/Libraries/freertos-addons/Source/include