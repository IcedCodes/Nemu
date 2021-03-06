#include <am.h>
#include <x86.h>

#define RTC_PORT 0x48   // Note that this is not standard
static unsigned long boot_time;

void _ioe_init() {
  boot_time = inl(RTC_PORT);
}

unsigned long _uptime() {
  return inl(0x48) - boot_time;
}

uint32_t* const fb = (uint32_t *)0x40000;

_Screen _screen = {
  .width  = 400,
  .height = 300,
};

extern void* memcpy(void *, const void *, int);

void _draw_rect(const uint32_t *pixels, int x, int y, int w, int h) {
  int i, j, k;
  k = 0;
  for (i = y; i < y+h; i++) 
  {
    for (j = x; j < x+w; j++) 
    {
      fb[_screen.width*i+j] = pixels[k++];
    } 
  }
}

void _draw_sync() {
}

int _read_key() {
  if(inb(0x64))
  {
    return inl(0x60);
  }
  return _KEY_NONE;
}
