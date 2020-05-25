
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <unistd.h>
#include "duktape.h"
#include "civetweb.h"
#include "ssr.h"
#define PORT "3030"

char *html = 0;

static int mainHandler(struct mg_connection *conn, void *ctx)
{
  const struct mg_request_info *info = mg_get_request_info(conn);
  duk_get_global_string(ctx, "make");
  duk_push_string(ctx, info->request_uri);
  duk_call(ctx, 1);
  mg_printf(conn, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
  const char *build = duk_get_string(ctx, -1);
  char *page = replaceString(html, "<div id=\"root\"></div>", build);
  mg_printf(conn, page);
  free(page);
  return 1;
}

static int authHandler() {
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
      0};
  duk_context *ctx;
  struct mg_callbacks callbacks;
  struct mg_context *mg;

  html = read_file("dist/index.html");

  ctx = duk_create_heap(NULL, NULL, NULL, NULL, my_fatal);
  if (!ctx)
  {
    exit(1);
  }

  duk_push_file(ctx, "dist/server.js");
  duk_eval(ctx);
  printf("load success\n");
  memset(&callbacks, 0, sizeof(callbacks));
  mg = mg_start(&callbacks, 0, options);
  mg_set_auth_handler(mg, "/", authHandler, 0);
  mg_set_request_handler(mg, "/$", mainHandler, ctx);
  mg_set_request_handler(mg, "/test", mainHandler, ctx);
  printf("Server Start in port %s\n", PORT);

  while (1)
  {
    sleep(1);
  }

  mg_stop(mg);
  free(html);

  return 0;
}