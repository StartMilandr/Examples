#include "5600VV3T.h"

uint8_t TXRX_Data(BRD_SPI_Obj* BRD_SPI, uint8_t addr, uint8_t rw, uint8_t data)
{
	uint16_t tmp;
	
	tmp = (addr<<10) | (rw<<9) | data;
	
	return BRD_SPI_Master_WRRD(BRD_SPI, tmp)&0xFF;
}

void Read_MAC_Table(BRD_SPI_Obj* BRD_SPI, MAC_StringTypeDef* MAC_String)
{
	uint32_t i, j;
	for(i=0;i<2048;i++)
	{
		TXRX_Data(BRD_SPI, RAM_CONTROL_1, WRITE, i&0xFF); 									 // ��������� ������� ����� ������
		TXRX_Data(BRD_SPI, RAM_CONTROL_0, WRITE, ((i>>8)&0x7)|0x80); 				 // ��������� ������� ����� ������ + ������ ���������� ������ �� ��� �������
		while((TXRX_Data(BRD_SPI, RAM_CONTROL_0, READ, NO_DATA)&0x80) == 1); // �������� ���������� ����������
		
	for(j = 0;j < 6;j++) 																							     // ������ MAC ������ � ���������
	{
		MAC_String[i].data |= (uint64_t) TXRX_Data(BRD_SPI, RAM_DATA6-j, READ, NO_DATA)<<8*j;
	}
	
		for(j = 6;j < 8;j++) 																							   // ������ ���������� ���� � ���������
	{
		MAC_String[i].data |= (uint64_t) TXRX_Data(BRD_SPI, RAM_DATA1+j, READ, NO_DATA)<<8*j;
	}
	}	
}

void Read_MAC_String(BRD_SPI_Obj* BRD_SPI, uint16_t addr, MAC_StringTypeDef* MAC_String)
{
	uint32_t j;
	TXRX_Data(BRD_SPI, RAM_CONTROL_1, WRITE, addr&0xFF); 								 // ��������� ������� ����� ������
	TXRX_Data(BRD_SPI, RAM_CONTROL_0, WRITE, ((addr>>8)&0x7)|0x80);      // ��������� ������� ����� ������ + ������ ���������� ������ �� ��� �������
	while((TXRX_Data(BRD_SPI, RAM_CONTROL_0, READ, NO_DATA)&0x80) == 1); // �������� ���������� ����������
	
	for(j = 0;j < 6;j++) 																							   // ������ MAC ������ � ���������
	{
		MAC_String->data |= (uint64_t) TXRX_Data(BRD_SPI, RAM_DATA6-j, READ, NO_DATA)<<8*j;
	}
	
		for(j = 6;j < 8;j++) 																							   // ������ ���������� ���� � ���������
	{
		MAC_String->data |= (uint64_t) TXRX_Data(BRD_SPI, RAM_DATA1+j, READ, NO_DATA)<<8*j;
	}
}

void Write_MAC_String(BRD_SPI_Obj* BRD_SPI, uint16_t addr, MAC_StringTypeDef* MAC_String)
{
	uint32_t j;

	for(j = 0;j < 6;j++)  																				       // ������ MAC ������ � �������� 5600��3�
	{
		TXRX_Data(BRD_SPI, RAM_DATA1+j, WRITE, MAC_String->data>>(40-8*j));
	}	
	
	for(j = 6;j < 8;j++)  																				       // ������ ���������� ���� � �������� 5600��3�
	{
		TXRX_Data(BRD_SPI, RAM_DATA1+j, WRITE, MAC_String->data>>8*j);
	}	
	
	TXRX_Data(BRD_SPI, RAM_CONTROL_1, WRITE, addr&0xFF); 								 // ��������� ������� ����� ������
	TXRX_Data(BRD_SPI, RAM_CONTROL_0, WRITE, ((addr>>8)&0x7)|0xC0);			 // ��������� ������� ����� ������ + ������ ���������� ������ ��� �������
	while((TXRX_Data(BRD_SPI, RAM_CONTROL_0, READ, NO_DATA)&0x80) == 1); // �������� ���������� ����������
}

uint16_t Get_Addr(MAC_StringTypeDef MAC_String, uint8_t NCell)
{
	uint16_t addr = 0, j;

	for(j = 0;j < 6;j++)
	{
		addr ^= (uint8_t) ((uint64_t) MAC_String.MAC>>8*j);
	}
	return addr = (addr<<3) | NCell&0x7;
}


// �������, �� ����������� ���������� ������������ MAC ������ ��� ���������

void Read_MAC_Table_1(BRD_SPI_Obj* BRD_SPI, MAC_StringTypeDef* MAC_String)
{
	uint32_t i, j;
	for(i=0;i<2048;i++)
	{
		TXRX_Data(BRD_SPI, RAM_CONTROL_1, WRITE, i&0xFF); 									 // ��������� ������� ����� ������
		TXRX_Data(BRD_SPI, RAM_CONTROL_0, WRITE, ((i>>8)&0x7)|0x80); 				 // ��������� ������� ����� ������ + ������ ���������� ������ �� ��� �������
		while((TXRX_Data(BRD_SPI, RAM_CONTROL_0, READ, NO_DATA)&0x80) == 1); // �������� ���������� ����������
		
		for(j = 0;j < 8;j++) 																							   // ������ ���� ���� � ���������
	{
		MAC_String[i].data |= (uint64_t) TXRX_Data(BRD_SPI, RAM_DATA1+j, READ, NO_DATA)<<8*j;
	}
	}	
}

void Read_MAC_String_1(BRD_SPI_Obj* BRD_SPI, uint16_t addr, MAC_StringTypeDef* MAC_String)
{
	uint32_t j;
	TXRX_Data(BRD_SPI, RAM_CONTROL_1, WRITE, addr&0xFF); 								 // ��������� ������� ����� ������
	TXRX_Data(BRD_SPI, RAM_CONTROL_0, WRITE, ((addr>>8)&0x7)|0x80);      // ��������� ������� ����� ������ + ������ ���������� ������ �� ��� �������
	while((TXRX_Data(BRD_SPI, RAM_CONTROL_0, READ, NO_DATA)&0x80) == 1); // �������� ���������� ����������
	
	for(j = 0;j < 8;j++) 																							   // ������ ���� ���� � ���������
	{
		MAC_String->data |= (uint64_t) TXRX_Data(BRD_SPI, RAM_DATA1+j, READ, NO_DATA)<<8*j;
	}
}

void Write_MAC_String_1(BRD_SPI_Obj* BRD_SPI, uint16_t addr, MAC_StringTypeDef* MAC_String)
{
	uint32_t j;

	for(j = 0;j < 8;j++)  																				       // ������ ���� ���� � �������� 5600��3�
	{
		TXRX_Data(BRD_SPI, RAM_DATA1+j, WRITE, MAC_String->data>>8*j);
	}	
	
	TXRX_Data(BRD_SPI, RAM_CONTROL_1, WRITE, addr&0xFF); 								 // ��������� ������� ����� ������
	TXRX_Data(BRD_SPI, RAM_CONTROL_0, WRITE, ((addr>>8)&0x7)|0xC0);			 // ��������� ������� ����� ������ + ������ ���������� ������ ��� �������
	while((TXRX_Data(BRD_SPI, RAM_CONTROL_0, READ, NO_DATA)&0x80) == 1); // �������� ���������� ����������
}


