set(srcs "pic.c")

if(IDF_TARGET STREQUAL "esp32s3")
    list(APPEND srcs "esp32s3/main.c")
    list(APPEND includes "esp32s3/include")
endif()


idf_component_register(SRCS "${srcs}"
                    INCLUDE_DIRS ${includes}
                    ) #cannot totally hide soc headers, since there are a lot arguments in the driver are chip-dependent
