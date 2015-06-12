/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
//#include "usbdisk.h"	/* Example: Header file of existing USB MSD control module */
//#include "atadrive.h"	/* Example: Header file of existing ATA harddisk control module */
//#include "sdcard.h"		/* Example: Header file of existing MMC/SDC contorl module */

/* Definitions of physical drive number for each drive */
//#define ATA		0	/* Example: Map ATA harddisk to physical drive 0 */
//#define MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
//#define USB		2	/* Example: Map USB MSD to physical drive 2 */
//#include "../../../application/sd_card/sd_card.hpp"
/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status(BYTE pdrv /* Physical drive nmuber to identify the drive */)
{
	return 0;

//	DSTATUS stat;
//	int result;
//
//	switch (pdrv) {
//	case ATA :
//		result = ATA_disk_status();
//
//		// translate the reslut code here
//
//		return stat;
//
//	case MMC :
//		result = MMC_disk_status();
//
//		// translate the reslut code here
//
//		return stat;
//
//	case USB :
//		result = USB_disk_status();
//
//		// translate the reslut code here
//
//		return stat;
//	}
//	return STA_NOINIT;
}

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize(BYTE pdrv /* Physical drive nmuber to identify the drive */)
{
	if (SDCard_initialize())
	{
		return 0;
	}
	else
	{
		return STA_NOINIT;
	}
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read(BYTE pdrv, /* Physical drive nmuber to identify the drive */
					BYTE *buff, /* Data buffer to store read data */
					DWORD sector, /* Sector address in LBA */
					UINT count /* Number of sectors to read */
					)
{
	unsigned char result;
	unsigned char buf[2];

	// check if parameters are in valid range
	if (count > 128)
	{
		return RES_PARERR;
	}

	sector *= 512;    // convert LBA to physical address
//	sdc_assert();    // assert SDC

	// if multiple sectors are to be read
	if (count > 1)
	{
		return RES_PARERR;
//		// start multiple sector read
//		sdc_sendCommand(SDC_READ_MULTIPLE_BLOCK, ((sector >> 24) & 0xFF), ((sector >> 16) & 0xFF),
//						((sector >> 8) & 0xFF), (sector & 0xFF));
//
//		while (sdc_getResponse(0x00))
//			;    // wait for command acknowledgement
//
//		while (count)
//		{
//			while (sdc_getResponse(0xFE))
//				;    // wait for data token 0xFE
//			SPI_receive(SPI1, buff, 512);    // read 512 bytes
//			SPI_receive(SPI1, buf, 2);    // receive two byte CRC
//			count--;
//			buff += 512;
//		}
//		// stop multiple sector read
//		sdc_sendCommand(SDC_STOP_TRANSMISSION, 0, 0, 0, 0);
//		while (sdc_getResponse(0x00))
//			;    // wait for R1 response
	}
	else    // if single sector is to be read
	{

		SDCard_read_Single_Block(sector, buff, 512);

//		sdc_sendCommand(SDC_READ_SINGLE_BLOCK, ((sector >> 24) & 0xFF), ((sector >> 16) & 0xFF),
//						((sector >> 8) & 0xFF), (sector & 0xFF));
//		while (sdc_getResponse(0x00))
//			;    // wait for command acknowledgement
//		while (sdc_getResponse(0xFE))
//			;    // wait for data token 0xFE
//		SPI_receive(SPI1, buff, 512);    // receive data
//		SPI_receive(SPI1, buf, 2);    // receive two byte CRC
	}

//	while (!SPI_receive_single(SPI1))
//		;    // wait until card is not busy anymore

//	sdc_deassert();    // deassert SDC

	return RES_OK;

//	DRESULT res;
//	int result;
//
//	switch (pdrv) {
//	case ATA :
//		// translate the arguments here
//
//		result = ATA_disk_read(buff, sector, count);
//
//		// translate the reslut code here
//
//		return res;
//
//	case MMC :
//		// translate the arguments here
//
//		result = MMC_disk_read(buff, sector, count);
//
//		// translate the reslut code here
//
//		return res;
//
//	case USB :
//		// translate the arguments here
//
//		result = USB_disk_read(buff, sector, count);
//
//		// translate the reslut code here
//
//		return res;
//	}
//
//	return RES_PARERR;
}

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write(BYTE pdrv, /* Physical drive nmuber to identify the drive */
					const BYTE *buff, /* Data to be written */
					DWORD sector, /* Sector address in LBA */
					UINT count /* Number of sectors to write */
					)
{
	// check if parameters are in valid range
	if (count > 128)
	{
		return RES_PARERR;
	}

	sector *= 512;    // convert LBA to physical address

	if (count > 1)
	{
		return RES_PARERR;
	}
	else
	{
		SDCard_write_Block(sector, buff, 512);
	}

	return RES_OK;

	/*
	 unsigned char result;
	 unsigned char buf[2];
	 buf[0] = 0xFF;
	 buf[1] = 0xFF;

	 // check if parameters are in valid range
	 if (count > 128)
	 {
	 return RES_PARERR;
	 }

	 sector *= 512;    // convert LBA to physical address
	 sdc_assert();    // assert SDC

	 // if multiple sectors are to be written
	 if (count > 1)
	 {
	 // start multiple sector write
	 sdc_sendCommand(SDC_WRITE_MULTIPLE_BLOCK, ((sector >> 24) & 0xFF), ((sector >> 16) & 0xFF),
	 ((sector >> 8) & 0xFF), (sector & 0xFF));
	 while (sdc_getResponse(0x00))
	 ;    // wait for R1 response
	 SPI_send_single(SPI1, 0xFF);    // send one byte gap

	 while (count)
	 {
	 SPI_send_single(SPI1, 0xFC);    // send multi byte data token 0xFC
	 SPI_send(SPI1, (unsigned char*) buff, 512);    // send 512 bytes
	 SPI_send(SPI1, buf, 2);    // send two byte CRC

	 // check if card has accepted data
	 result = SPI_receive_single(SPI1);
	 if ((result & 0x1F) != 0x05)
	 {
	 return RES_ERROR;
	 }
	 count--;
	 buff += 512;
	 while (!SPI_receive_single(SPI1))
	 ;    // wait until SD card is ready
	 }

	 SPI_send_single(SPI1, 0xFD);    // send stop transmission data token 0xFD
	 SPI_send_single(SPI1, 0xFF);    // send one byte gap
	 }
	 else    // if single sector is to be written
	 {
	 sdc_sendCommand(SDC_WRITE_BLOCK, ((sector >> 24) & 0xFF), ((sector >> 16) & 0xFF),
	 ((sector >> 8) & 0xFF), (sector & 0xFF));
	 while (sdc_getResponse(0x00))
	 ;    // wait for R1 response
	 SPI_send_single(SPI1, 0xFF);    // send one byte gap
	 SPI_send_single(SPI1, 0xFE);    // send data token 0xFE
	 SPI_send(SPI1, (unsigned char*) buff, 512);    // send data
	 SPI_send(SPI1, buf, 2);    // send two byte CRC
	 // check if card has accepted data
	 result = SPI_receive_single(SPI1);
	 if ((result & 0x1F) != 0x05)
	 {
	 return RES_ERROR;
	 }
	 }

	 while (!SPI_receive_single(SPI1))
	 ;    // wait until card is not busy anymore

	 sdc_deassert();    // deassert SDC

	 return RES_OK;
	 */

//	return 0;
//	DRESULT res;
//	int result;
//
//	switch (pdrv) {
//	case ATA :
//		// translate the arguments here
//
//		result = ATA_disk_write(buff, sector, count);
//
//		// translate the reslut code here
//
//		return res;
//
//	case MMC :
//		// translate the arguments here
//
//		result = MMC_disk_write(buff, sector, count);
//
//		// translate the reslut code here
//
//		return res;
//
//	case USB :
//		// translate the arguments here
//
//		result = USB_disk_write(buff, sector, count);
//
//		// translate the reslut code here
//
//		return res;
//	}
//
//	return RES_PARERR;
}
#endif

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl(BYTE pdrv, /* Physical drive nmuber (0..) */
					BYTE cmd, /* Control code */
					void *buff /* Buffer to send/receive control data */
					)
{
	return 0;

//	DRESULT res;
//	int result;
//
//	switch (pdrv) {
//	case ATA :
//
//		// Process of the command for the ATA drive
//
//		return res;
//
//	case MMC :
//
//		// Process of the command for the MMC/SD card
//
//		return res;
//
//	case USB :
//
//		// Process of the command the USB drive
//
//		return res;
//	}
//
//	return RES_PARERR;
}
#endif
