#include "in_out.h"

int clock(enum content type){
  switch (type) {
    case seconds:
      _out(70h, 0x00);
      break;
    case minutes:
      _out(70h, 0x02);
      break;
    case hours:
      _out(70h, 0x04);
  }
}
