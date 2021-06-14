#define soc_cv_av

#define DEBUG

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "hwlib.h"
#include "soc_cv_av/socal/socal.h"
#include "soc_cv_av/socal/hps.h"
#include "soc_cv_av/socal/alt_gpio.h"
#include "hps_0.h"



#include <time.h>
void delay(int milliseconds);



#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 ) //64 MB with 32 bit adress space this is 256 MB
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

//setting for the HPS2FPGA AXI Bridge
#define ALT_AXI_FPGASLVS_OFST (0xC0000000) // axi_master
#define HW_FPGA_AXI_SPAN (0x40000000) // Bridge span 1GB
#define HW_FPGA_AXI_MASK ( HW_FPGA_AXI_SPAN - 1 )





int main() {

	//pointer to the different address spaces

	void *virtual_base;
	void *axi_virtual_base;
	int fd;

	void *h2p_lw_StepEnable;
	void *h2p_lw_Direction;
	void *h2p_lw_Reset;
	//void *h2p_lw_myBus_addr;

	//void *h2p_led_addr; //led via AXI master


	// map the address space for the LED registers into user space so we can interact with them.
	// we'll actually map in the entire CSR span of the HPS since we want to access various registers within that span

	if ((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1) {
		printf("ERROR: could not open \"/dev/mem\"...\n");
		return(1);
	}

	//lightweight HPS-to-FPGA bridge
	virtual_base = mmap(NULL, HW_REGS_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, HW_REGS_BASE);

	if (virtual_base == MAP_FAILED) {
		printf("ERROR: mmap() failed...\n");
		close(fd);
		return(1);
	}

	//HPS-to-FPGA bridge
	axi_virtual_base = mmap(NULL, HW_FPGA_AXI_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, ALT_AXI_FPGASLVS_OFST);

	if (axi_virtual_base == MAP_FAILED) {
		printf("ERROR: axi mmap() failed...\n");
		close(fd);
		return(1);
	}


	//-----------------------------------------------------------
	//configure the LEDs of the Golden Reference design
	//printf( "\n\n\n-----------Set the LEDs on-------------\n\n" );

	//LED connected to the HPS-to-FPGA bridge
	//h2p_led_addr=axi_virtual_base + ( ( unsigned long  )( 0x0 + PIO_LED_BASE ) & ( unsigned long)( HW_FPGA_AXI_MASK ) );

	//*(uint32_t *)h2p_led_addr = 0b10111100;


	//-----------------------------------------------------------
	//Partie utilisation

	printf("\n\n\n-----------Set Thils et VDB on-------------\n\n");

	//the address of the two input (reg1 and reg2) registers and the output register (reg3)
	h2p_lw_StepEnable = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + STEPENABLE_BASE) & (unsigned long)(HW_REGS_MASK));
	h2p_lw_Direction = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + DIRECTION_BASE) & (unsigned long)(HW_REGS_MASK));
	h2p_lw_Reset = virtual_base + ((unsigned long)(ALT_LWFPGASLVS_OFST + RESET_BASE) & (unsigned long)(HW_REGS_MASK));

	printf("\nInitialisation des pointeurs - OK\n");

	//write into register to test the adder
	*(uint32_t *)h2p_lw_StepEnable = 1;
	*(uint32_t *)h2p_lw_Direction = 1;
	*(uint32_t *)h2p_lw_Reset = 1;

	printf("\nInitialisation des inputs - OK\n");

	delay(3000);
	int compteur = 1;

	int Duree1tour = 800;

	printf("\nFin d'initialisation\n");

	while (compteur < 5) {

		if (compteur == 1)
		{
			printf("\nRotation de +90 degres\n");

			*(uint32_t *)h2p_lw_StepEnable = 1;
			*(uint32_t *)h2p_lw_Reset = 0;

			delay(Duree1tour / 4);
			*(uint32_t *)h2p_lw_StepEnable = 0;

			delay(3000);

			printf("\nRotation de +180 degres\n");

			*(uint32_t *)h2p_lw_StepEnable = 1;

			delay(Duree1tour / 2);
			*(uint32_t *)h2p_lw_StepEnable = 0;

			delay(3000);

			printf("\nRotation de +270 degres\n");

			*(uint32_t *)h2p_lw_StepEnable = 1;

			delay(Duree1tour * 0.75);
			*(uint32_t *)h2p_lw_StepEnable = 0;

			delay(3000);

			printf("\nRotation de -180 degres\n");

			*(uint32_t *)h2p_lw_StepEnable = 1;
			*(uint32_t *)h2p_lw_Direction = 0;

			delay(Duree1tour / 2);
			*(uint32_t *)h2p_lw_StepEnable = 0;

			delay(5000);
		}

		compteur = compteur + 1;

	}

	printf("\nJ'ai fini !\n");
	*(uint32_t *)h2p_lw_StepEnable = 0;


	if (munmap(virtual_base, HW_REGS_SPAN) != 0) {
		printf("ERROR: munmap() failed...\n");
		close(fd);
		return(1);
	}

	if (munmap(axi_virtual_base, HW_FPGA_AXI_SPAN) != 0) {
		printf("ERROR: axi munmap() failed...\n");
		close(fd);
		return(1);
	}

	close(fd);

	return(0);
}



void delay(int miliseconds)
{
	long pause;
	clock_t now, then;

	pause = miliseconds*(CLOCKS_PER_SEC / 1000);
	now = then = clock();
	while ((now - then) < pause)
		now = clock();
}
