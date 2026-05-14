#ifndef EMBLIB_ERROR_H
#define EMBLIB_ERROR_H

typedef enum {
  EM_OK = 0,           /* success */
  EM_ERR_NO_MEM = -1,  /* request ran out of memory */
  EM_ERR_INVALID = -2, /* arguments/configuration was invalid */
  EM_ERR_UNIMP = -3,   /* unimplemented method */
  EM_ERR_OOB = -4,     /* out-of-bounds */
  EM_ERR_UNALIGN = -5, /* unaligned memory access */
} em_err_t;

#endif
