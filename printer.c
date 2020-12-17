#include "lexer.h"
#include "color.h"
#include <stdio.h>
#include <stdlib.h>

struct reader
{
  struct lexer *lexer;
  struct token current_token;
  struct token next_token;
};

void
next_token (struct reader *r)
{
  r->current_token = r->next_token;
  gettoken (r->lexer, &r->next_token);
}

void render_comments(struct reader *r) {
  while (r->current_token.type != TOKEN_EOF && r->current_token.type != TOKEN_NEWLINE) {
        LOG_GRAY(r->current_token.literal);
  	next_token(r);
  }
  printf("%s", r->current_token.literal);
}

struct reader
new_reader (struct lexer *l)
{
  struct reader r = {
    .lexer = l,
  };

  gettoken (r.lexer, &r.current_token);
  gettoken (r.lexer, &r.next_token);

  return r;
}
const char* quo = "\""; 
void
print_tokens (struct reader *r)
{

  while (r->current_token.type != TOKEN_EOF)
    {
      switch (r->current_token.type)
	{
	case TOKEN_INT:
	  LOG_YELLOW (r->current_token.literal);
	  break;
	case TOKEN_STRING:
	  LOG_GREEN(quo);
	  LOG_GREEN (r->current_token.literal);
	  LOG_GREEN(quo);
	 break;
	case TOKEN_IDENT:
	  LOG_RED (r->current_token.literal);
	  break;
	case TOKEN_SLASH:
	  if(r->next_token.type == TOKEN_SLASH) {
	    render_comments(r);
	    break;
	  }
	default:
	  printf ("%s", r->current_token.literal);
	  break;
	}
      next_token (r);
    }
}

char *
ReadFile (char *filename)
{
  char *buffer = NULL;
  int string_size, read_size;
  FILE *handler = fopen (filename, "r");

  if (handler)
    {
      // Seek the last byte of the file
      fseek (handler, 0, SEEK_END);
      // Offset from the first to the last byte, or in other words, filesize
      string_size = ftell (handler);
      // go back to the start of the file
      rewind (handler);

      // Allocate a string that can hold it all
      buffer = (char *) malloc (sizeof (char) * (string_size + 1));

      // Read it all in one operation
      read_size = fread (buffer, sizeof (char), string_size, handler);

      // fread doesn't set it so put a \0 in the last position
      // and buffer is now officially a string
      buffer[string_size] = '\0';

      if (string_size != read_size)
	{
	  // Something went wrong, throw away the memory and set
	  // the buffer to NULL
	  free (buffer);
	  buffer = NULL;
	}

      // Always remember to close the file.
      fclose (handler);
    }

  return buffer;
}

int
main ()
{
  char *string = ReadFile ("example.go");
  if (string)
    {
      struct lexer l = new_lexer (string);
      struct reader r = new_reader (&l);
      print_tokens (&r);
      free (string);
    }

}
