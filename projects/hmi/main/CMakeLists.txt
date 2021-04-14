set(src_dirs "")
set(includes "")

list(APPEND src_dirs "gui"
                     "gui/generated"
                     "gui/generated/guider_fonts"
                     "gui/generated/images")

list(APPEND includes "gui"
                     "gui/generated"
                     "gui/generated/guider_fonts"
                     "gui/generated/guider_customer_fonts")

if(IDF_TARGET STREQUAL "esp32")
    list(APPEND src_dirs "esp32")
    list(APPEND includes "esp32/include")
endif()

if(IDF_TARGET STREQUAL "esp32s2")
    list(APPEND src_dirs "esp32s2")
    list(APPEND includes "esp32s2/include")
endif()

if(IDF_TARGET STREQUAL "esp32s3")
    list(APPEND src_dirs "esp32s3")
    list(APPEND includes "esp32s3/include")
endif()

if(IDF_TARGET STREQUAL "esp32c3")
    list(APPEND src_dirs "esp32c3")
    list(APPEND includes "esp32c3/include")
endif()


idf_component_register(SRC_DIRS "${src_dirs}"
                       INCLUDE_DIRS ${includes}
                       ) #cannot totally hide soc headers, since there are a lot arguments in the driver are chip-dependent
