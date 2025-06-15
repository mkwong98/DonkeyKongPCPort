#include "binaryUtil.h"

void binaryUtil::inc(Uint8* v) {
	if ((*v) < 0xff) (*v)++;
	else (*v) = 0;
}

void binaryUtil::dec(Uint8* v) {
	if ((*v) > 0) (*v)--;
	else (*v) = 0xff;
}
