
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "duktape.h"
#include "civetweb.h"
#include "ssr.h"
#define PORT "3030"

duk_context *ctx;
int exitNow = 0;

static int mainHandler(struct mg_connection *conn, void *cbdata)
{
  duk_push_string(ctx, "/");
  duk_put_global_string(ctx, "location");
  duk_eval_string_noresult(ctx, "var context={}");
  duk_get_global_string(ctx, "make");
  duk_call(ctx, 0);
  char *html = read_file("dist/index.html");
  mg_printf(conn, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
  duk_get_global_string(ctx, "result");
  const char *build = duk_get_string(ctx, -1);
  char *page = replaceValue(html, "<div id=\"root\"></div>", build);
  mg_printf(conn, page);
  free(html);
  free(page);
  return 1;
}

int main(int argc, char **argv)
{
  const char *options[] = {
      "document_root",
      "dist",
      "listening_ports",
      PORT,
      "request_timeout_ms",
      "10000",
      "enable_auth_domain_check",
      "no",
      0};
  struct mg_callbacks callbacks;
  struct mg_context *mg;

  ctx = duk_create_heap(NULL, NULL, NULL, NULL, my_fatal);
  if (!ctx)
  {
    exit(1);
  }

  duk_push_c_function(ctx, native_print, 1);
  duk_put_global_string(ctx, "print");
  duk_push_thread(ctx);
  fileio_push_file_string(ctx, "dist/server.js");
  duk_eval(ctx);
  printf("load success\n");
  memset(&callbacks, 0, sizeof(callbacks));
  mg = mg_start(&callbacks, 0, options);
  mg_set_request_handler(mg, "/$", mainHandler, 0);
  mg_set_request_handler(mg, "/test", mainHandler, 0);
  printf("Server Start in port %s\n", PORT);

  while (!exitNow)
  {
    sleep(1);
  }

  mg_stop(mg);

  return 0;
}