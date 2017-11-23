#include <ruby.h>
#include "isbilen.h"

VALUE Isbilen = Qnil;

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

static VALUE get_seconds(VALUE self, VALUE string) {
  const char *c_hex = StringValueCStr(string);
  sves_isbilen_t c_snowflake;

  if (!sves_isbilen_from_hex(&c_snowflake, c_hex, strlen(c_hex) ) ) {
    return Qfalse;
  }

  return UINT2NUM(sves_isbilen_get_seconds(&c_snowflake) );
}

static VALUE get_microsec(VALUE self, VALUE string) {
  const char *c_hex = StringValueCStr(string);
  sves_isbilen_t c_snowflake;

  if (!sves_isbilen_from_hex(&c_snowflake, c_hex, strlen(c_hex) ) ) {
    return Qfalse;
  }

  return UINT2NUM(sves_isbilen_get_microsec(&c_snowflake) );
}

static VALUE get_instance_id(VALUE self, VALUE string) {
  const char *c_hex = StringValueCStr(string);
  sves_isbilen_t c_snowflake;

  if (!sves_isbilen_from_hex(&c_snowflake, c_hex, strlen(c_hex) ) ) {
    return Qfalse;
  }

  return UINT2NUM(sves_isbilen_get_instance_id(&c_snowflake) );
}

static VALUE get_version(VALUE self, VALUE string) {
  const char *c_hex = StringValueCStr(string);
  sves_isbilen_t c_snowflake;

  if (!sves_isbilen_from_hex(&c_snowflake, c_hex, strlen(c_hex) ) ) {
    return Qfalse;
  }

  return UINT2NUM(sves_isbilen_get_version(&c_snowflake) );
}

void Init_isbilen() {
    Isbilen = rb_define_module("Isbilen");
    rb_define_singleton_method(Isbilen, "snowflake", get_snowflake, 1);
    rb_define_singleton_method(Isbilen, "valid?", is_valid, 1);
    rb_define_singleton_method(Isbilen, "seconds", get_seconds, 1);
    rb_define_singleton_method(Isbilen, "microsec", get_microsec, 1);
    rb_define_singleton_method(Isbilen, "instance_id", get_instance_id, 1);
    rb_define_singleton_method(Isbilen, "version", get_version, 1);
}
