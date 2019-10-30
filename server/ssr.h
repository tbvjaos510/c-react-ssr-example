#include <stdio.h>
#include <errno.h>

char *read_file(char *path)
{
  FILE *infile;
  char *buffer;
  long numbytes;

  infile = fopen(path, "r");

  if (infile == NULL)
  {
    fprintf(stderr, "file open error: %d\n", errno);
    return "";
  }

  fseek(infile, 0L, SEEK_END);
  numbytes = ftell(infile);
  fseek(infile, 0L, SEEK_SET);
  buffer = (char *)calloc(numbytes + 1, sizeof(char));
  if (buffer == NULL)
    return "";

  fread(buffer, sizeof(char), numbytes, infile);
  fclose(infile);
  printf("max: %d, bufflen: %d\n", numbytes, strlen(buffer));
  return buffer;
}

void fileio_push_file_buffer(duk_context *ctx, const char *filename)
{
  FILE *f = NULL;
  long len;
  void *buf;
  size_t got;

  if (!filename)
  {
    goto error;
  }

  f = fopen(filename, "rb");
  if (!f)
  {
    goto error;
  }

  if (fseek(f, 0, SEEK_END) != 0)
  {
    goto error;
  }

  len = ftell(f);

  if (fseek(f, 0, SEEK_SET) != 0)
  {
    goto error;
  }

  buf = duk_push_fixed_buffer(ctx, (size_t)len);

  got = fread(buf, 1, len, f);
  if (got != (size_t)len)
  {
    duk_pop(ctx);
    goto error;
  }

  fclose(f);
  return;

error:
  if (f)
  {
    fclose(f);
  }
  fprintf(stderr, "file open error\n");
  duk_push_undefined(ctx);
}
void duk_push_file(duk_context *ctx, const char *filename)
{
  fileio_push_file_buffer(ctx, filename);
  if (duk_is_buffer_data(ctx, -1))
  {
    duk_buffer_to_string(ctx, -1);
  }
}

char *replaceString(char *strInput, const char *strTarget, const char *strChange)
{
  char *strResult;
  char *strTemp;
  int i = 0;
  int nCount = 0;
  int nTargetLength = strlen(strTarget);

  if (nTargetLength < 1)
    return strInput;

  int nChangeLength = strlen(strChange);

  if (nChangeLength != nTargetLength)
  {
    for (i = 0; strInput[i] != '\0';)
    {
      if (memcmp(&strInput[i], strTarget, nTargetLength) == 0)
      {
        nCount++;
        i += nTargetLength;
      }
      else
        i++;
    }
  }
  else
  {
    i = strlen(strInput);
  }

  strResult = (char *)malloc(i + 1 + nCount * (nChangeLength - nTargetLength));
  if (strResult == NULL)
    return NULL;

  strTemp = strResult;
  while (*strInput)
  {
    if (memcmp(strInput, strTarget, nTargetLength) == 0)
    {
      memcpy(strTemp, strChange, nChangeLength);
      strTemp += nChangeLength;
      strInput += nTargetLength;
    }
    else
    {
      *strTemp++ = *strInput++;
    }
  }

  *strTemp = '\0';

  return strResult;
}

static void my_fatal(void *udata, const char *msg)
{
  /* Note that 'msg' may be NULL. */
  fprintf(stderr, "*** FATAL ERROR: %s\n", (msg ? msg : "no message"));
  fflush(stderr);
  exit(1);
}
static duk_ret_t native_print(duk_context *ctx)
{
  printf("print called\n");
  size_t s = 0;
  const char *str = duk_get_lstring(ctx, 0, &s);
  if (str[0] == '!')
  {
    printf("log %s\n", str);
    return 0;
  }
  duk_push_lstring(ctx, str, s);
  duk_put_global_string(ctx, "result");
  return 0;
}