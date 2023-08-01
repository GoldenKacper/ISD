//
// Created by kacpe on 31.07.2023.
//
#include "py/dynruntime.h"

STATIC mp_obj_t NN_process_output_TEST(
        mp_obj_t inputs_neurons_obj,
mp_obj_t hidden_neurons_obj,
        mp_obj_t outputs_neurons_obj) {
mp_obj_t *inputs_neurons = NULL;
size_t inputs_neurons_len = 0;
mp_obj_get_array(inputs_neurons_obj, &inputs_neurons_len, &inputs_neurons);
mp_int_t inputs_neurons_item_1 = mp_obj_get_int(inputs_neurons[0]);
mp_float_t inputs_neurons_item_2 = mp_obj_get_float(inputs_neurons[1]);
const char* inputs_neurons_item_3 = mp_obj_str_get_str(inputs_neurons[2]);

mp_obj_t *hidden_neurons = NULL;
size_t hidden_neurons_len = 0;
mp_obj_get_array(hidden_neurons_obj, &hidden_neurons_len, &hidden_neurons);
mp_int_t inputs_neurons_item_1 = mp_obj_get_int(hidden_neurons[0]);
mp_float_t hidden_neurons_item_2 = mp_obj_get_float(hidden_neurons[1]);
const char* hidden_neurons_item_3 = mp_obj_str_get_str(hidden_neurons[2]);

mp_obj_t *outputs_neurons = NULL;
size_t outputs_neurons_len = 0;
mp_obj_get_array(utputs_neurons_item_1 = mp_obj_get_int(outputs_neurons[0]);
mp_float_toutputs_neurons_obj, &outputs_neurons_len, &outputs_neurons);
mp_int_t o outputs_neurons_item_2 = mp_obj_get_float(outputs_neurons[1]);
const char* outputs_neurons_item_3 = mp_obj_str_get_str(outputs_neurons[2]);

// Your code here!
mp_int_t result = inputs_neurons_item_1 + inputs_neurons_item_1 + outputs_neurons_item_1



// signature: mp_obj_t mp_obj_new_str(const char* data, size_t len);
if(result < 1)
    return mp_obj_new_str("t", 1);
else return mp_obj_new_str("n", 1);
}
MP_DEFINE_CONST_FUN_OBJ_3(NN_process_output_TEST_obj, NN_process_output_TEST);

// Copy the uncommented line into your map table
// STATIC const mp_rom_map_elem_t my_module_globals_table[] = {
// { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_builtins) },
{ MP_ROM_QSTR(MP_QSTR_NN_process_output_TEST), MP_ROM_PTR(&NN_process_output_TEST_obj) },
// };