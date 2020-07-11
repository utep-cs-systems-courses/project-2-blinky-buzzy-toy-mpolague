COMMON_OBJECTS  =
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: main.elf

#additional rules for files
main.elf: ${COMMON_OBJECTS} main.c stateMachines.o led.o wdInterruptHandler.o p2_interrupt_handler.o switches.o buzzer.o ../timerLib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: main.elf
	msp430loader.sh main.elf

clean:
	rm -f *.o *.elf *shell* *shell*~ *~

led.o: led.c led.h
stateMachines.o: stateMachines.c stateMachines.h
buzzer.o: buzzer.c buzzer.h
switches.o: switches.c switches.h
wdInterruptHandler.o: wdInterruptHandler.c
p2_interrupt_handler.o: p2_interrupt_handler.c
