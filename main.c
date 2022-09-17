#define DELAY_ANIMATION 7000

static inline
void lidt( void * base, unsigned short size )
{
    struct
    {
        unsigned short length;
        unsigned long base;
    } __attribute__((__packed__)) IDTR;
 
    IDTR.length = size;
    IDTR.base = (unsigned long)base;
    asm( "lidt (%0)"
         : : "p"(&IDTR) );
}

int main( void )
{ 
  int i;
  
  setColor(0x0f,0x0c);
  clearscreen();

  for(;;){ /* Keep the OS running */
    setXY(1,1);
    setColor(0x0F,0x00);
    puts("Kernel Running ");
    
    for(i = 0;i < DELAY_ANIMATION;i++ )
      putcXY('\\',16,1);
    for(i = 0;i < DELAY_ANIMATION;i++ )
      putcXY('|',16,1);
    for(i = 0;i < DELAY_ANIMATION;i++ )
      putcXY('/',16,1);
    for(i = 0;i < DELAY_ANIMATION;i++ )
      putcXY('-',16,1);
  }
}
