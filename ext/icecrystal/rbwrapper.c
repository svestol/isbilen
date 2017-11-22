#include <ruby.h>
#include "isbilen.h"

VALUE Icecrystal = Qnil;

static VALUE get_snowflake(VALUE self, VALUE instance_id) {
  char c_buffer[33];
  sves_isbilen_t c_snowflake;
  uint32_t c_instance_id = NUM2UINT(instance_id);

  sves_isbilen_init(c_instance_id, &c_snowflake);
  sves_isbilen_get_hex(&c_snowflake, c_buffer, 33);

  return rb_str_new_cstr(c_buffer);
}

static VALUE is_valid(VALUE self, VALUE string) {
  const char *c_hex = StringValueCStr(string);
  sves_isbilen_t c_snowflake;

  if (!sves_isbilen_from_hex(&c_snowflake, c_hex, strlen(c_hex) ) ) {
    return Qfalse;
  }

  return sves_isbilen_valid(&c_snowflake) ? Qtrue : Qfalse;
}

void Init_icecrystal() {
    Icecrystal = rb_define_module("Icecrystal");
    rb_define_method(Icecrystal, "snowflake", get_snowflake, 1);
    rb_define_method(Icecrystal, "valid?", is_valid, 1);
}
