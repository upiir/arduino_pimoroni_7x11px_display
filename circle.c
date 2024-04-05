#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_CIRCLE
#define LV_ATTRIBUTE_IMG_CIRCLE
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_CIRCLE uint8_t circle_map[] = {
  0x02, 0x0d, 0x17, 0x1b, 0x17, 0x0d, 0x02, 
  0x1b, 0x30, 0x41, 0x47, 0x41, 0x30, 0x1b, 
  0x3b, 0x5b, 0x74, 0x7d, 0x74, 0x5b, 0x3b, 
  0x5b, 0x86, 0xa7, 0xb3, 0xa7, 0x86, 0x5b, 
  0x74, 0xa7, 0xcf, 0xe0, 0xcf, 0xa7, 0x74, 
  0x7d, 0xb3, 0xe0, 0xff, 0xe0, 0xb3, 0x7d, 
  0x74, 0xa7, 0xcf, 0xe0, 0xcf, 0xa7, 0x74, 
  0x5b, 0x86, 0xa7, 0xb3, 0xa7, 0x86, 0x5b, 
  0x3b, 0x5b, 0x74, 0x7d, 0x74, 0x5b, 0x3b, 
  0x1b, 0x30, 0x41, 0x47, 0x41, 0x30, 0x1b, 
  0x02, 0x0d, 0x17, 0x1b, 0x17, 0x0d, 0x02, 
};

const lv_img_dsc_t circle = {
  .header.cf = LV_IMG_CF_ALPHA_8BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 7,
  .header.h = 11,
  .data_size = 77,
  .data = circle_map,
};