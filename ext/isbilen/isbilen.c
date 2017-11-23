#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <unistd.h>
#include <sys/time.h>

#include "isbilen.h"

static inline uint8_t checksum_count(const sves_isbilen_t * const snowflake) {
  uint8_t cvalue = 0;

  for (int i = 0; i < 4; i++)
    cvalue += (snowflake->seconds >> (i * 8) ) & 0xFF;

  for (int i = 0; i < 3; i++)
    cvalue += (snowflake->microsec >> (i * 8) ) & 0xFF;

  for (int i = 0; i < 4; i++)
    cvalue += (snowflake->instance_id >> (i * 8) ) & 0xFF;

  for (int i = 0; i < 2; i++)
    cvalue += (snowflake->pid >> (i * 8) ) & 0xFF;

  for (int i = 0; i < 2; i++)
    cvalue += (snowflake->counter >> (i * 8) ) & 0xFF;

  return cvalue += snowflake->version;
}

const sves_isbilen_t *sves_isbilen_init(uint32_t instance_id, sves_isbilen_t * const out) {
  static _Atomic uint16_t counter = ATOMIC_VAR_INIT(0);
  struct timeval tv;

  if (gettimeofday(&tv, NULL) != 0) return NULL;

  *out = (sves_isbilen_t) {
    .seconds = (uint32_t) tv.tv_sec,
    .microsec = tv.tv_usec,
    .instance_id = instance_id,
    .pid = getpid(),
    .counter = __atomic_add_fetch(&counter,1, __ATOMIC_SEQ_CST),
    .version = 0x00,
  };

  out->checksum = (int)out->version - (int)checksum_count(out);

  return out;
}

bool sves_isbilen_valid(const sves_isbilen_t * const snowflake) {
  return (uint8_t) (checksum_count(snowflake) + snowflake->checksum) == snowflake->version;
}

const char *sves_isbilen_get_hex(const sves_isbilen_t * const restrict snowflake,
                                   char * const restrict buffer,
                                   const size_t len) {
  if (len < 33) return NULL;
  sprintf(buffer,
          "%0.2x%0.2x%0.2x%0.2x"
          "%x%0.2x%0.2x"
          "%0.2x%0.2x%0.2x%0.2x"
          "%0.2x%0.2x"
          "%x%0.2x"
          "%0.2x"
          "%0.2x",
          snowflake->seconds >> 24 & 0xFF,
          snowflake->seconds >> 16 & 0xFF,
          snowflake->seconds >>  8 & 0xFF,
          snowflake->seconds       & 0xFF,

          snowflake->microsec >> 16 & 0x0F,
          snowflake->microsec >>  8 & 0xFF,
          snowflake->microsec       & 0xFF,

          snowflake->instance_id >> 24 & 0xFF,
          snowflake->instance_id >> 16 & 0xFF,
          snowflake->instance_id >>  8 & 0xFF,
          snowflake->instance_id       & 0xFF,

          snowflake->pid >>  8 & 0xFF,
          snowflake->pid       & 0xFF,

          snowflake->counter >>  8 & 0x0F,
          snowflake->counter       & 0xFF,

          snowflake->version,
          snowflake->checksum
        );

  return buffer;
}

const sves_isbilen_t *sves_isbilen_from_hex(sves_isbilen_t * const restrict out,
                                                const char * const restrict hex,
                                                size_t len) {
  size_t i;
  uint8_t *ptr = (uint8_t *) hex;
  static uint8_t table[0x100] = {
    ['0'] = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    ['A'] = 10, 11, 12, 13, 14, 15,
    ['a'] = 10, 11, 12, 13, 14, 15,
  };

  if (len < 32) return NULL;

  memset(out, 0, sizeof *out);

  for (i = 0; i < 8; i++)
    out->seconds = out->seconds << 4 | table[ptr[i]];

  for (; i < 13; i++)
    out->microsec = out->microsec << 4 | table[ptr[i]];

  for (; i < 21; i++)
    out->instance_id = out->instance_id << 4 | table[ptr[i]];

  for (; i < 25; i++)
    out->pid = out->pid << 4 | table[ptr[i]];

  for (; i < 28; i++)
    out->counter = out->counter << 4 | table[ptr[i]];

  for (; i < 30; i++)
    out->version = out->version << 4 | table[ptr[i]];

  for (; i < 32; i++)
    out->checksum = out->checksum << 4 | table[ptr[i]];

  return out;
}

uint32_t sves_isbilen_get_seconds(const sves_isbilen_t * const snowflake) {
  return snowflake->seconds;
}

uint32_t sves_isbilen_get_microsec(const sves_isbilen_t * const snowflake) {
  return snowflake->microsec;
}

uint32_t sves_isbilen_get_instance_id(const sves_isbilen_t * const snowflake) {
  return snowflake->instance_id;
}

uint8_t sves_isbilen_get_version(const sves_isbilen_t * const snowflake) {
  return snowflake->version;
}
