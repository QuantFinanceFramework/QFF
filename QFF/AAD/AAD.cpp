#include "aad_all.h"

//  Statics
using namespace aad;
size_t node::num_adj_ = 1;
bool tape::is_multi_ = false;

tape global_tape;
thread_local tape* aad_double::tape = &global_tape;
