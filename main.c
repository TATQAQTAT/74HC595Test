/*
ATMega328P
 */

#include <avr/io.h>
#include <avr/delay.h>

int main(void)
{   unsigned char num=0;
    unsigned char testplus;
    SPI_MasterInit();


    // Insert code

    //SPI595Out(0x02);
    NixieTube(8);

    while(1)
    {
        //SPI595Out();
        //PORTB=~PORTB;
        for(num=0;num<10;num++)
        {

            NixieTube(num);
            _delay_ms(1000);
        }
    }


    return 0;
}



void SPI_MasterInit(void)
{
	/*设置SS,MOSI和SCK为输出，其他为输入*/
	DDRB |= (1<<PB3)|(1<<PB5)|(1<<PB0)|(1<<PB2);;
	//PORTB &= ~(1<<PB2);
	/* SPI主机，fck/4 .模式0*/
	SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR0)|(0<<SPR1)|(0<<CPOL)|(0<<CPHA);
}

void SPI_MasterTransmit(char cData)
{
	/* 启动数据传输*/
	SPDR = cData;
	/* 等待传输结束*/
	while(!(SPSR & (1<<SPIF)))
        ;
}

void SPI595Out(uint8_t i)

{

    PORTB&=~(1<<PB0);             //等待数据传输，595存储寄存器数据不变

    SPI_MasterTransmit(i);        //传输数据

    PORTB|=(1<<PB0);              //595移位寄存器的数据进入数据存储寄存器，并在数码管上显示
    PORTB&=~(1<<PB0);
}

void NixieTube(unsigned char num)
{
    PORTB&=~(1<<PB0);             //等待数据传输，595存储寄存器数据不变
    if(num<8)
    {
        SPI_MasterTransmit(0);
        SPI_MasterTransmit(1<<num);
    }
    else
    {
        SPI_MasterTransmit(1<<(num-8));//传输数据
        SPI_MasterTransmit(0);
    }
    PORTB|=(1<<PB0);              //595移位寄存器的数据进入数据存储寄存器，并在数码管上显示
    PORTB&=~(1<<PB0);
}
