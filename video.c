#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
#define SCREEN_MAX_CHAR 1920
#define SCREEN_MAX_MEM 3840

#define BLACK          0x00
#define BLUE           0x01
#define GREEN          0x02
#define CYAN           0x03
#define RED            0x04
#define MAGENTA        0x05
#define BROWN          0x06
#define LIGHT_GRAY     0x07
#define DARK_GRAY      0x08
#define BRIGHT_BLUE    0x09
#define BRIGHT_GREEN   0x0A
#define BRIGHT_CYAN    0x0B
#define BRIGHT_RED     0x0C
#define BRIGHT_MAGENTA 0x0D
#define BRIGHT_YELLOW  0x0E
#define BRIGHT_WHITE   0x0F

#define FOREGROUND BRIGHT_WHITE
#define BACKGROUND BRIGHT_RED
#define COLOR FOREGROUND | ( BACKGROUND << 4);

char color = COLOR; /* Our global color attribute */
int pos = 0;

void setColor(char foreground, char background)
{
  color = foreground | (background << 4);
}

void setXY(int xCord, int yCord)
{
  pos = ((SCREEN_WIDTH*(yCord%SCREEN_HEIGHT))+(xCord%SCREEN_WIDTH))*2;
}

void clearscreen(){
  setXY(0,0);
  int i;
  for(i = 0 ; i != SCREEN_MAX_CHAR;++i)
    putc(' ');
}

void putc( unsigned char c )
{
  char *vidmem = (char*)0xB8000; /* pointer to video memory */
  vidmem[pos%SCREEN_MAX_MEM]   = c; /* print the character */
  vidmem[pos + 1] = color; /* Set the color attribute */
  pos += 2;
  pos %= SCREEN_MAX_MEM;
}

int puts( char *message )
{
  int length;
  while(*message)
  {
    putc(*message++);
    length++;
  }
  return length;
}

void putcXY(unsigned char c, int xCord, int yCord)
{
  setXY(xCord,yCord);
  putc(c);
}

void putsXY(char *msg,int xCord, int yCord)
{
  setXY(xCord,yCord);
  puts(msg);
}
