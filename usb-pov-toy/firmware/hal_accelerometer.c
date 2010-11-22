#include "globals.h"



u8 hal_acl_read(u8 r)
{
u8 c;

ACL_CS=0;
hal_spi_rw((r<<1));
c=hal_spi_rw(0xff);
ACL_CS=1;
return c;
}

void hal_acl_write(u8 r, u8 v)//register and value
{
ACL_CS=0;
hal_spi_rw((r<<1)|0b10000000);
hal_spi_rw(v);
ACL_CS=1;
}

void hal_acl_enable(void){
ACL_CS=0;
hal_spi_rw((0x16<<1)|0b10000000);//write setup
hal_spi_rw(0b0001);//low g, measurement
ACL_CS=1;
}


void hal_acl_config(void)
{
	//setup change interrupt
//16 - mode control
//10 (4g) 10 (level detect)

hal_acl_write(MCTRL, 0b1010);

//18 int or absolute
//xPxxxxxx p=1 positive/negative
	//18Disable any unneeded axis
	//xxZYXxxx
//xxxxxIIx ii=00 level detection

hal_acl_write(CTL1, 0x00);

//enable interrupt (write 0x00 to 0x17)

hal_acl_write(INTRST, 0b11);
hal_acl_write(INTRST, 0x00);

//
//19 OR or AND
//xxxxxxxA 1=and 0x00 default...

//1a detection threshold

hal_acl_write(LVLTH, 0x0b11100000);

}


HAL_ACL_DIRECTION hal_acl_IsItReverseOrForward(void)
{
//TODO
return ACL_REVERSE;
//return ACL_FORWARD;
}

void hal_acl_adjustInterruptLvl(u8 value)
{
// TODO
}
