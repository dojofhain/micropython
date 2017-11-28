/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2015-2017 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "microbit/microbitdal.h"

extern "C" {

#include "py/runtime.h"
#include "microbit/modmicrobit.h"

typedef struct _microbit_rgb_led_obj_t {
    mp_obj_base_t base;
    CalliopeRGB *rgb;
} microbit_rgb_led_obj_t;

STATIC mp_obj_t microbit_rgb_led_set(mp_uint_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_red,   MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_green, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_blue,  MP_ARG_INT, {.u_int = 0} }
    };

    // parse args
    microbit_rgb_led_obj_t *self = (microbit_rgb_led_obj_t*)pos_args[0];
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args - 1, pos_args + 1, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    self->rgb->setColour(args[0].u_int, args[1].u_int, args[2].u_int, 0);

    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(microbit_rgb_led_set_obj, 1, microbit_rgb_led_set);

STATIC mp_obj_t microbit_rgb_led_on(mp_obj_t obj) {
    microbit_rgb_led_obj_t *self = (microbit_rgb_led_obj_t*)obj;
    self->rgb->on();
    return mp_const_none;

}
MP_DEFINE_CONST_FUN_OBJ_1(microbit_rgb_led_on_obj, microbit_rgb_led_on);

STATIC mp_obj_t microbit_rgb_led_off(mp_obj_t obj) {
    microbit_rgb_led_obj_t *self = (microbit_rgb_led_obj_t*)obj;
    self->rgb->off();
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(microbit_rgb_led_off_obj, microbit_rgb_led_off);

STATIC const mp_map_elem_t microbit_rgb_led_locals_dict_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR_set), (mp_obj_t)&microbit_rgb_led_set_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_on),  (mp_obj_t)&microbit_rgb_led_on_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_off),  (mp_obj_t)&microbit_rgb_led_off_obj }
};

STATIC MP_DEFINE_CONST_DICT(microbit_rgb_led_locals_dict, microbit_rgb_led_locals_dict_table);

const mp_obj_type_t microbit_rgb_led_type = {
    { &mp_type_type },
    .name = MP_QSTR_CalliopeRGB,
    .print = NULL,
    .make_new = NULL,
    .call = NULL,
    .unary_op = NULL,
    .binary_op = NULL,
    .attr = NULL,
    .subscr = NULL,
    .getiter = NULL,
    .iternext = NULL,
    .buffer_p = {NULL},
    .protocol = NULL,
    .parent = NULL,
    .locals_dict = (mp_obj_dict_t*)&microbit_rgb_led_locals_dict,
};

const microbit_rgb_led_obj_t microbit_rgb_led_obj = {
    {&microbit_rgb_led_type},
    .rgb = &calliope_rgb
};

}
