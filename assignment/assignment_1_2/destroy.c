#include "message_buffer_semaphore.h"

int main(void) {
    MessageBuffer *buffer;
    attach_buffer(&buffer);
    init_sem();
    destroy_sem();
    destroy_buffer();
    return 0;
}
