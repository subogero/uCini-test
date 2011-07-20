#include "uCini/uCini.h"
#include <stdio.h>
#include <string.h>

// Internal data
char foo = -1;
unsigned char ufoo = -2;
short bar = -3;
unsigned short ubar = 1;
long baz = 2;
unsigned long ubaz = 3;
char spam[80] = "Master Foo";
char eggs = 0xFF;
#define EGG0 0
#define EGG1 1
#define EGG2 2
static void rw_egg2(char* str, int write);

static const struct tEntry si[] = {
  { "foo", &foo, 1 + eType_INT + eType_SGND },
  { "bar", &bar, 2 + eType_INT + eType_SGND },
  { "baz", &baz, 4 + eType_INT + eType_SGND },
};
static const struct tEntry ui[] = {
  { "ufoo", &ufoo, 1 + eType_INT },
  { "ubar", &ubar, 2 + eType_INT },
  { "ubaz", &ubaz, 4 + eType_INT },
};
static const struct tEntry ex[] = {
  { "spam", spam, eType_SZ },
  { "egg0", &eggs, 0 + eType_FLAG },
  { "egg1", &eggs, 1 + eType_FLAG },
  { "egg2", rw_egg2, eType_FUNC },
};

static const struct tSection sect[] = {
  { "signed"  , si, sizeof(si) / sizeof(struct tEntry) },
  { "unsigned", ui, sizeof(ui) / sizeof(struct tEntry) },
  { "exotic"  , ex, sizeof(ex) / sizeof(struct tEntry) },
};

static const struct tIni ini = {
  sect, sizeof(sect) / sizeof(struct tSection) 
};

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

int main(void)
{
  printf("Original data\n-------------\n");
  uCiniDump(&ini, NULL);
  printf("Enter inifile\n-------------\n");
  uCiniParse(&ini, NULL);
  printf("Modified data\n-------------\n");
  uCiniDump(&ini, NULL);
}


