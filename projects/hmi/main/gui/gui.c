#include "gui.h"
#include "gui_guider.h"
#include "events_init.h"

lv_ui guider_ui;

int gui_init(lv_disp_t **disp_array, lv_indev_t **indev_array, lv_theme_t * th)
{
    /*Set a cursor for the mouse*/
    LV_IMG_DECLARE(esp_icon);                          /*Declare the image file.*/
    lv_obj_t * cursor_obj =  lv_img_create(lv_scr_act(), NULL); /*Create an image object for the cursor */
    lv_img_set_src(cursor_obj, &esp_icon);             /*Set the image source*/
    lv_indev_set_cursor(indev_array[0], cursor_obj);               /*Connect the image  object to the driver*/

    // lv_demo_benchmark();

    // lv_demo_music();

    // lv_demo_widgets();

    // lv_demo_stress();

    /*Create a GUI-Guider app */
    setup_ui(&guider_ui);
    events_init(&guider_ui);

    return 0;
}