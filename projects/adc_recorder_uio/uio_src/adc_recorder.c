#include "zynq_io.h"

int main(int argc, char *argv[])
{
	//int fd;
	//unsigned int size;
	uint32_t i,val=0;
	uint32_t wo;
	int16_t ch[2];

	//printf("ADC RECORDER test\n");

	//initialize devices. TODO: add error checking 
	//intc_init();
	cfg_init();    
	cma_init();
	//sts_init();
	//xadc_init();

	// set writer address
	//   *(uint32_t *)(cfg + 4) = size;
	//
	//printf("Set writer address...\n");
	val=rd_reg_value(1, CFG_WR_ADDR_OFFSET,0);
	//printf("dev_size es: %d ...\n",dev_size);
	wr_reg_value(1, CFG_WR_ADDR_OFFSET, dev_size,0);

	 // set number of samples
	 //   *(uint32_t *)(cfg + 8) = 1024 * 1024 - 1;
	 //
	//printf("Set number of samples...\n");
	val=rd_reg_value(1, CFG_NSAMPLES_OFFSET,0);
	wr_reg_value(1, CFG_NSAMPLES_OFFSET, 1024 * 1024 - 1,0);

	// reset writer
	//*((uint32_t *)(cfg + 0)) &= ~4;
	//printf("Reseting writer...\n");
	val=rd_reg_value(1, CFG_RESET_GRAL_OFFSET,0);
	wr_reg_value(1, CFG_RESET_GRAL_OFFSET, val &= ~4,0);
	//*((uint32_t *)(cfg + 0)) |= 4;
	val=rd_reg_value(1, CFG_RESET_GRAL_OFFSET,0);
	wr_reg_value(1, CFG_RESET_GRAL_OFFSET, val |= 4,0);
//	printf("Reseting writer %d ...\n",val);
	//printf("Reseting fifo and filters...\n");
//	// reset fifo and filters
	//*((uint32_t *)(cfg + 0)) &= ~1;
	val=rd_reg_value(1, CFG_RESET_GRAL_OFFSET,0);
	wr_reg_value(1, CFG_RESET_GRAL_OFFSET, val &=~1,0);
//	//*((uint32_t *)(cfg + 0)) |= 1;
	val=rd_reg_value(1, CFG_RESET_GRAL_OFFSET,0);
	wr_reg_value(1, CFG_RESET_GRAL_OFFSET, val |=1,0);
//	printf("Reseting fifo and filters %d ...\n",val);
//
//	// wait 1 second
	sleep(1);
//
	//printf("Reseting packetizer...\n");
	// enter reset mode for packetizer
	//*((uint32_t *)(cfg + 0)) &= ~2; 
	val=rd_reg_value(1, CFG_RESET_GRAL_OFFSET,0);
	wr_reg_value(1, CFG_RESET_GRAL_OFFSET, val &=~2,0);

	// set number of samples
	//*((uint32_t *)(cfg + 4)) = 1024 * 1024 - 1;
//	wr_reg_value(1, CFG_NSAMPLES_OFFSET, 1024 * 1024 - 1);

	// enter normal mode
//	//*((uint32_t *)(cfg + 0)) |= 2;
	val=rd_reg_value(1, CFG_RESET_GRAL_OFFSET,0);
	wr_reg_value(1, CFG_RESET_GRAL_OFFSET, val |=2,0);
//	printf("Reseting packetizer %d ...\n",val);
//
//	// wait 1 second
	sleep(1);

	// print IN1 and IN2 samples
	for(i = 0; i < 1024 * 1024; ++i){
		ch[0] = cma_ptr[2*i + 0];
		ch[1] = cma_ptr[2*i + 1];
		//ch[0] = *((int16_t *)(cma_ptr + 2*i + 0));
		//ch[1] = *((int16_t *)(cma_ptr + 2*i + 1));
		wo = *((uint32_t *)(cma_ptr + 2*i));
		printf("%5d %5d %10d\n", ch[0], ch[1], wo);
//		ch[0] = cma_ptr[2 * i + 0];
//		ch[1] = cma_ptr[2 * i + 1];
//		//wo    = cma_ptr[i] 
//		printf("%5d %5d\n", ch[0], ch[1]);
	}

	// unmap and close the devices 
	//munmap(intc_ptr, sysconf(_SC_PAGESIZE));
//	munmap(cfg_ptr, sysconf(_SC_PAGESIZE));
//	//munmap(sts_ptr, sysconf(_SC_PAGESIZE));
//	//munmap(xadc_ptr, sysconf(_SC_PAGESIZE));
//	munmap(cma_ptr, sysconf(_SC_PAGESIZE));

	//close(intc_fd);
	close(cfg_fd);
	//close(sts_fd);
	//close(xadc_fd);
	//printf("Saliendo ...\n");

	return 0;

}
