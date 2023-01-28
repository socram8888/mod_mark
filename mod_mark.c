
#include <stdint.h>

#include "apr_portable.h"
#include "httpd.h"
#include "http_core.h"
#include "http_request.h"

static int translate_handle(request_rec * req) {
	apr_socket_t * apache_socket = ap_get_conn_socket(req->connection);

	int connfd;
        apr_os_sock_get(&connfd, apache_socket);

	uint32_t mark;
	socklen_t mark_len = sizeof(mark);
	if (getsockopt(connfd, SOL_SOCKET, SO_MARK, &mark, &mark_len)) {
		return DECLINED;
	}

	char mark_dec[12];
	sprintf(mark_dec, "%d", mark);
	apr_table_set(req->subprocess_env, "SOCKET_MARK", mark_dec);

	return DECLINED;
}

static void register_hooks(apr_pool_t * pool) {
	ap_hook_translate_name(translate_handle, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA mark_module = {
	STANDARD20_MODULE_STUFF,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	register_hooks
};
