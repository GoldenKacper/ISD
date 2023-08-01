//
// Created by kacpe on 01.08.2023.
//
#include "py/dynruntime.h"

STATIC mp_obj_t NN_process_output(mp_obj_t outputsNeurons_obj) {

mp_obj_t *outputsNeurons = NULL;
size_t outputsNeurons_len = 5; // default value 5 because outputsNeurons are 5

mp_obj_get_array(outputsNeurons_obj, &outputsNeurons_len, &outputsNeurons);

mp_float_t outputsNeurons_item[5]; // !!! it may cause error !!!
for (mp_int_t i = 0; i < outputsNeurons_len; i+=1) {
    outputsNeurons_item[i] = mp_obj_get_int(outputsNeurons[i]);
}

mp_float_t tolerance_degree = 0.90f;
mp_int_t flag = 0;
mp_int_t index = 0;

for (mp_int_t i = 0; i < outputsNeurons_len; i+=1) {
    if (outputsNeurons_item[i] >= tolerance_degree) {
        flag += 1;
        index = i;
    }
}

// signature: mp_obj_t mp_obj_new_str(const char* data, size_t len);
if (flag == 1) {
    switch (index) {
        case 0:
            return mp_obj_new_str("n", 1);
        case 1:
            return mp_obj_new_str("l", 1);
        case 2:
            return mp_obj_new_str("s", 1);
        case 3:
            return mp_obj_new_str("w", 1);
        case 4:
            return mp_obj_new_str("r", 1);
    }
} else if (flag < 1) {
    return mp_obj_new_str("d", 1);
} else if (flag > 1) {
    return mp_obj_new_str("u", 1);
}
}
MP_DEFINE_CONST_FUN_OBJ_2(NN_process_output_obj, NN_process_output);

// Copy the uncommented line into your map table
// STATIC const mp_rom_map_elem_t my_module_globals_table[] = {
// { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_builtins) },
//{ MP_ROM_QSTR(MP_QSTR_NN_process_output), MP_ROM_PTR(&NN_process_output_obj) },
// };

// This is the entry point and is called when the module is imported
mp_obj_t mpy_init(mp_obj_fun_bc_t *self, size_t n_args, size_t n_kw, mp_obj_t *args) {
    // This must be first, it sets up the globals dict and other things
    MP_DYNRUNTIME_INIT_ENTRY

    // Make the function available in the module's namespace
    mp_store_global(MP_QSTR_NN_process_output, MP_OBJ_FROM_PTR(&NN_process_output_obj));

    // This must be last, it restores the globals dict
    MP_DYNRUNTIME_INIT_EXIT
}