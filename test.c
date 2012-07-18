#include "uCini/uCini.h"
#include <stdio.h>
#include <string.h>

// Internal data
char foo = -1;
short bar = -2;
long baz = -3;
unsigned char ufoo = 1;
unsigned short ubar = 2;
unsigned long ubaz = 3;
char spam[80] = "Master Foo";
char eggs = 0xFF;
#define EGG0 0
#define EGG1 1
#define EGG2 2
struct {
  int foo: 1;
  int bar: 2;
  int baz: 6;
} foobar;

static void rw_egg2(char* str, int write);
static void rw_foobar_foo(char* str, int write);

#include "ini_map.h"

static void rw_egg2(char* str, int write)
{
  if (write) {
    strcat(str, GET(eggs, EGG2) ? "yes" : "no");
  }
  else {
    if      (!strcmp(str, "yes")) SET(eggs, EGG2);
    else if (!strcmp(str, "no" )) CLR(eggs, EGG2);
  }
}

static void rw_foobar_foo(char* str, int write)
{
  if (write) {
    scatd(str, foobar.foo);
  }
  else {
    long num;
    if (sscand(str, &num)) foobar.foo = num;
  }
}

int main(void)
{
  printf("\nOriginal data\n-------------\n");
  uCiniDump(&ini, NULL);
  printf("\nEnter inifile\n-------------\n");
  uCiniParse(&ini, NULL);
  printf("\nModified data\n-------------\n");
  uCiniDump(&ini, NULL);
  return 0;
}
