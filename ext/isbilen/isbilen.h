#ifndef SVES_ISBILEN_H
#define SVES_ISBILEN_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct sves_isbilen sves_isbilen_t;
struct sves_isbilen {
  unsigned seconds     : 32;
  unsigned microsec    : 20;
  unsigned instance_id : 32;
  unsigned pid         : 16;
  unsigned counter     : 12;
  unsigned version     :  8;
  unsigned checksum    :  8;
} __attribute__((packed));

const sves_isbilen_t *sves_isbilen_init(const uint32_t instance_id,
                                        sves_isbilen_t * const out)
                                        ;

bool sves_isbilen_valid(const sves_isbilen_t * const snowflake);

const sves_isbilen_t *sves_isbilen_from_hex(sves_isbilen_t * const restrict out,
                                            const char * const restrict hex,
                                            size_t len);

const char *sves_isbilen_get_hex(const sves_isbilen_t * const restrict snowflake,
                                 char * const restrict buffer,
                                 const size_t len);

uint32_t sves_isbilen_get_seconds(const sves_isbilen_t * const snowflake);

uint32_t sves_isbilen_get_microsec(const sves_isbilen_t * const snowflake);

uint32_t sves_isbilen_get_instance_id(const sves_isbilen_t * const snowflake);

uint8_t sves_isbilen_get_version(const sves_isbilen_t * const snowflake);


#endif
