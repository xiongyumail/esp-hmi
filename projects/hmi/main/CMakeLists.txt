set(srcs "pic.c" "gui/gui.c" "gui/esp_icon.c")

list(APPEND srcs "gui/generated/events_init.c"
                 "gui/generated/gui_guider.c"
                 "gui/generated/setup_scr_screen.c"
                 "gui/generated/guider_fonts/lv_font_simsun_12.c"
                 "gui/generated/guider_fonts/lv_font_simsun_20.c")

list(APPEND includes "gui"
                     "gui/generated"
                     "gui/generated/guider_fonts")

if(IDF_TARGET STREQUAL "esp32")
    list(APPEND srcs "esp32/main.c")
    list(APPEND includes "esp32/include")
endif()

if(IDF_TARGET STREQUAL "esp32s2")
    list(APPEND srcs "esp32s2/main.c")
    list(APPEND includes "esp32s2/include")
endif()

if(IDF_TARGET STREQUAL "esp32s3")
    list(APPEND srcs "esp32s3/main.c")
    list(APPEND includes "esp32s3/include")
endif()


idf_component_register(SRCS "${srcs}"
                    INCLUDE_DIRS ${includes}
                    ) #cannot totally hide soc headers, since there are a lot arguments in the driver are chip-dependent
