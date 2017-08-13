#include "DelimiterFramer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ErrorHelper.h"

static const char DELIMITER = '\n';

int getNextMesage(FILE *in, uint8_t *buffer, size_t bufferSize)
{
	int count = 0;
	int nextChar;
	while ((unsigned long)count < bufferSize)
   	{
		nextChar = getc(in);
		if (nextChar == EOF) {
			if (count > 0)
				dieWithUserMessage("GetNextMsg()", "Stream ended prematurely");
			else
				return -1;
		}
		if (nextChar == DELIMITER)
			break;
		buffer[count++] = nextChar;
	}
	if (nextChar != DELIMITER) { // Out of space: count==bufSize
		return -count;
	} else { // Found delimiter
		return count;
	}
}

/* Write the given message to the output stream, followed by
 * the delimiter. Return number of bytes written, or -1 on failure.
 */
int putMessage(uint8_t buffer[], size_t messageSize, FILE *out)
{
	// Check for delimiter in message
	unsigned long i;
	for (i = 0; i < messageSize; i++)
		if (buffer[i] == DELIMITER)
			return -1;
	if (fwrite(buffer, 1, messageSize, out) != messageSize)
		return -1;
	fputc(DELIMITER, out);
	fflush(out);
	return messageSize;
}
