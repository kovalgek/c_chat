#include <stdio.h>
#include "inttypes.h"

int getNextMesage(FILE *in, uint8_t *buffer, size_t bufferSize);
int putMessage(uint8_t buffer[], size_t messageSize, FILE *out);
