#include <metahook.h>
#include "client.h"
#include "proto_oob.h"

int CL_ConnectionlessPacket(const struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size)
{
	if (*args == A2S_INFO)
		return 1;

	return 0;
}