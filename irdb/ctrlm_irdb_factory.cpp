#include "ctrlm_irdb_factory.h"
#include "ctrlm_irdb_stub.h"

ctrlm_irdb_t *ctrlm_irdb_create() {
    ctrlm_irdb_t *ret = NULL;

    if(ret == NULL) {
        ret = new ctrlm_irdb_stub_t(CTRLM_IRDB_MODE_OFFLINE);
    }

    return(ret);
}
