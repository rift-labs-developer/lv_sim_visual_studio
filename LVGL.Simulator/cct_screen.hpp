#pragma once
#include "lvgl/lvgl.h"
#define MASK_WIDTH 100
#define MASK_HEIGHT 100

#define HEX_MAIN_COLOR 0xE0DAD5
#define HEX_SECONDARY_COLOR 0X898481

#define HEX_BACKGROUND_COLOR 0x3d3b39


static const lv_font_t* font_large;
static const lv_font_t* font_normal;

extern "C" {
    // used in c code, avoid name mangling
    LV_IMG_DECLARE(cctarc);

}
void drawBrightnessSlider(lv_obj_t* sliderPointer) {
    lv_obj_remove_style_all(sliderPointer);
    const int16_t radius = 10;

    //lv_obj_remove_style(sliderPointer, NULL, LV_PART_KNOB);
    lv_obj_set_size(sliderPointer, 60, 360);
    //lv_obj_set_style_border_width(sliderPointer, 0, LV_PART_MAIN);
    //lv_obj_set_style_border_width(sliderPointer, 0, LV_PART_INDICATOR); 



    static lv_style_t styleMain;
    lv_style_init(&styleMain);
    lv_style_set_bg_opa(&styleMain, LV_OPA_COVER);
    lv_style_set_bg_color(&styleMain, lv_color_hex(HEX_SECONDARY_COLOR));
    //lv_style_set_border_width(&styleMain, 0);
    //lv_style_set_border_width(&styleMain, LV_PART_MAIN);
    lv_style_set_radius(&styleMain, radius);
    lv_obj_add_style(sliderPointer, &styleMain, LV_PART_MAIN);


    static lv_style_t styleIndicator;
    lv_style_init(&styleIndicator);
    lv_style_set_radius(&styleIndicator, radius);

    lv_style_set_bg_opa(&styleIndicator, LV_OPA_COVER);
    lv_style_set_bg_color(&styleIndicator, lv_color_hex(HEX_MAIN_COLOR));
    lv_obj_add_style(sliderPointer, &styleIndicator, LV_PART_INDICATOR);





    //lv_obj_set_style_outline_width(sliderPointer, 0, 0);
    //lv_obj_set_style_outline_color(sliderPointer, lv_color_hex(HEX_MAIN_COLOR), LV_PART_INDICATOR);
}


void cctScreen() {

    font_large = &lv_font_montserrat_24;
    font_normal = &lv_font_montserrat_16;
    // arc gradient
    //https://forum.lvgl.io/t/full-gradient-support-for-primitives/2223/2
    // using masks https://docs.lvgl.io/master/overview/drawing.html#using-masks
    // lvgl 8 replaced lv_objmask with https://docs.lvgl.io/master/overview/event.html makes no sense
    // add events https://docs.lvgl.io/master/overview/event.html#add-events-to-the-object
    //



    lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), 1, LV_FONT_DEFAULT);
    lv_obj_t* screen = lv_scr_act();
    lv_obj_set_scrollbar_mode(screen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(screen, lv_color_hex(HEX_BACKGROUND_COLOR), 0);
    //lv_obj_t* topBarPanel = lv_obj_create(screen);
//lv_obj_t* labelBarPanel = lv_obj_create(screen);
    lv_obj_t* modeAreaPanel = lv_obj_create(screen);

    lv_obj_t* encoderLabelAreaPanel = lv_obj_create(screen);


    lv_obj_set_style_bg_color(modeAreaPanel, lv_color_hex(HEX_BACKGROUND_COLOR), 0);
    lv_obj_set_style_border_width(modeAreaPanel, 0, 0); // actually removed the border

    lv_obj_set_style_bg_color(encoderLabelAreaPanel, lv_color_hex(HEX_BACKGROUND_COLOR), 0);
    lv_obj_set_style_border_width(encoderLabelAreaPanel, 0, 0); // actually removed the border

    lv_obj_set_layout(screen, LV_LAYOUT_GRID);
    lv_obj_set_layout(modeAreaPanel, LV_LAYOUT_GRID);
    lv_obj_set_layout(encoderLabelAreaPanel, LV_LAYOUT_GRID);



    //LV_IMG_DECLARE(cctarc);
    lv_obj_t* img1 = lv_img_create(modeAreaPanel);
    lv_img_set_src(img1, &cctarc);
    //lv_img_set_zoom(img1, 160);
    lv_img_set_size_mode(img1, LV_IMG_SIZE_MODE_REAL);
    //lv_img_set_auto_size(img1, true);
    //lv_obj_set_size(img1, 100, 100);
    //lv_obj_center(img1);

    //lv_obj_t* arc = lv_arc_create(modeAreaPanel);
    //static lv_style_t style;
    //lv_style_init(&style);
    //lv_style_set_arc_color(&style, lv_palette_main(LV_PALETTE_AMBER));
    //lv_obj_remove_style(arc, NULL, LV_PART_INDICATOR);
    //lv_style_set_arc_width(&style, 4);
    //lv_obj_set_size(arc, 250, 250);
    ////lv_obj_add_event_cb(arc,)
    //lv_arc_set_bg_angles(arc, 0, 360);
    ////lv_arc_set_angles(obj, 90, 90);
    //lv_obj_add_style(arc, &style, 0);
    ////lv_obj_center(arc);


    lv_obj_t* label = lv_label_create(modeAreaPanel);
    lv_label_set_text(label, "5600K");
    lv_obj_set_style_text_font(label, font_large, 0);

    // intensity slider
    lv_obj_t* intensitySlider = lv_slider_create(screen);
    drawBrightnessSlider(intensitySlider);

    lv_obj_t* intensitySliderLabel = lv_label_create(intensitySlider);
    lv_label_set_text(intensitySliderLabel, "60%");
    lv_obj_set_style_text_font(intensitySlider, font_large, 0);
    lv_obj_set_style_text_color(intensitySlider, lv_color_hex(HEX_BACKGROUND_COLOR), 0);
    //lv_obj_center
    lv_obj_align(intensitySliderLabel, LV_ALIGN_BOTTOM_MID, 0, 0);
    //lv_obj_align_to(intensitySliderLabel, NULL, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);


    // Top bar
    lv_obj_t* menuLabel = lv_label_create(screen);
    lv_label_set_text(menuLabel, "Menu");

    lv_obj_t* modeLabel = lv_label_create(screen);
    lv_label_set_text(modeLabel, "CCT");

    lv_obj_t* statusLabels = lv_label_create(screen);
    lv_label_set_text(statusLabels, "Statuses");

    lv_obj_t* presetLabels = lv_label_create(screen);
    lv_label_set_text(presetLabels, "Presets");

    //cct grid:
    // Row 1 top row
    // Row 2 content row
    // Row 3 label row

    // Encoder label row
    lv_obj_t* encoderIntensityLabel = lv_label_create(encoderLabelAreaPanel);
    lv_obj_t* encoderMiddleLabel = lv_label_create(encoderLabelAreaPanel);
    lv_obj_t* encoderRightLabel = lv_label_create(encoderLabelAreaPanel);

    lv_label_set_text(encoderIntensityLabel, "Intensity");
    lv_label_set_text(encoderMiddleLabel, "CCT");
    lv_label_set_text(encoderRightLabel, "+- Green");





    //Columns
    // Column 1 inteisty slider etc
    // Column 2 main content
    static lv_coord_t grid_main_col_dsc[] = { 75,175,350,200, LV_GRID_TEMPLATE_LAST };
    static lv_coord_t grid_main_row_dsc[] = { 60,360, 60, LV_GRID_TEMPLATE_LAST };

    lv_obj_set_grid_dsc_array(screen, grid_main_col_dsc, grid_main_row_dsc);
    lv_obj_set_grid_cell(modeAreaPanel, LV_GRID_ALIGN_STRETCH, 1, 3, LV_GRID_ALIGN_STRETCH, 1, 1);


    static lv_coord_t grid_mode_col_dsc[] = { LV_GRID_FR(7),LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST };
    static lv_coord_t grid_mode_row_dsc[] = { LV_GRID_CONTENT,LV_GRID_CONTENT, LV_GRID_TEMPLATE_LAST };
    lv_obj_set_grid_dsc_array(modeAreaPanel, grid_mode_col_dsc, grid_mode_row_dsc);

    lv_obj_set_grid_cell(img1, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);

    //lv_obj_set_grid_cell(arc, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
    lv_obj_set_grid_cell(label, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 1, 1);



    //TOP bar
    lv_obj_set_grid_cell(menuLabel, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_END, 0, 1);
    lv_obj_set_grid_cell(modeLabel, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_END, 0, 1);
    lv_obj_set_grid_cell(statusLabels, LV_GRID_ALIGN_START, 2, 1, LV_GRID_ALIGN_END, 0, 1);
    lv_obj_set_grid_cell(presetLabels, LV_GRID_ALIGN_START, 3, 1, LV_GRID_ALIGN_END, 0, 1);


    lv_obj_set_grid_cell(intensitySlider, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 1, 1);

    //Encoder label bar
    lv_obj_set_grid_cell(encoderLabelAreaPanel, LV_GRID_ALIGN_STRETCH, 0, 4, LV_GRID_ALIGN_STRETCH, 2, 1);

    static lv_coord_t grid_encoder_bar_col_dsc[] = { LV_GRID_FR(1),LV_GRID_FR(1),LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST };
    static lv_coord_t grid_encoder_bar_row_dsc[] = { LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST };
    lv_obj_set_grid_dsc_array(encoderLabelAreaPanel, grid_encoder_bar_col_dsc, grid_encoder_bar_row_dsc);


    lv_obj_set_grid_cell(encoderIntensityLabel, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(encoderMiddleLabel, LV_GRID_ALIGN_CENTER, 1, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(encoderRightLabel, LV_GRID_ALIGN_END, 2, 1, LV_GRID_ALIGN_CENTER, 0, 1);


}


///*

//
//   /* Create the mask of an arc by drawing it to a canvas*/
//static lv_opa_t mask_map[MASK_WIDTH * MASK_HEIGHT];

///*Create a "8 bit alpha" canvas and clear it*/
//lv_obj_t* canvas = lv_canvas_create(lv_scr_act());
//lv_canvas_set_buffer(canvas, mask_map, MASK_WIDTH, MASK_HEIGHT, LV_IMG_CF_ALPHA_8BIT);
//lv_canvas_fill_bg(canvas, lv_color_black(), LV_OPA_TRANSP);

///*Draw an arc to the canvas. The result "image" will be used as mask*/
//lv_draw_arc_dsc_t arc_dsc;
//lv_draw_arc_dsc_init(&arc_dsc);
//arc_dsc.color = lv_color_white();
//arc_dsc.width = 10;
//lv_canvas_draw_arc(canvas, MASK_WIDTH / 2, MASK_HEIGHT / 2, MASK_WIDTH / 2, 180, 360, &arc_dsc);

///*The mask is reads the canvas is not required anymore*/
//lv_obj_del(canvas);

///*Create an object mask which will use the created mask*/
//lv_draw_mask_add
//    lv_obj_t* om = lv_objmask_create(lv_scr_act(), NULL);
//lv_obj_set_size(om, MASK_WIDTH, MASK_HEIGHT);
//lv_obj_align(om, NULL, LV_ALIGN_CENTER, 0, 0);

///*Add the created mask map to the object mask*/
//lv_draw_mask_map_param_t m;
//lv_area_t a;
//a.x1 = 0;
//a.y1 = 0;
//a.x2 = MASK_WIDTH - 1;
//a.y2 = MASK_HEIGHT - 1;
//lv_draw_mask_map_init(&m, &a, mask_map);
//lv_objmask_add_mask(om, &m);

///*Create a style with gradient*/
//static lv_style_t style_bg;
//lv_style_init(&style_bg);
//lv_style_set_bg_opa(&style_bg, LV_STATE_DEFAULT, LV_OPA_COVER);
//lv_style_set_bg_color(&style_bg, LV_STATE_DEFAULT, LV_COLOR_RED);
//lv_style_set_bg_grad_color(&style_bg, LV_STATE_DEFAULT, LV_COLOR_BLUE);
//lv_style_set_bg_grad_dir(&style_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);

///* Create and object with the gradient style on the object mask.
// * The arc will be masked from the gradient*/
//lv_obj_t* bg = lv_obj_create(om, NULL);
//lv_obj_reset_style_list(bg, LV_OBJ_PART_MAIN);
//lv_obj_add_style(bg, LV_OBJ_PART_MAIN, &style_bg);
//lv_obj_set_size(bg, MASK_WIDTH, MASK_HEIGHT); */
