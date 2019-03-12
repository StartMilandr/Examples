#include "mldr124.h"
#include "mldr124_CORDIC.h"
#include <stdlib.h>
#include <stdio.h> 
#include <math.h>
	
#if 1	
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

#if __ARMCC_VERSION<6000000	
struct __FILE { int handle; /* Add whatever is needed */ };
#endif
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
}	
#endif

volatile double ix,iy,ia;
volatile double ox,oy,oa;

volatile double   ix_dbl, iy_dbl, ia_dbl;
volatile float    ix_f32, iy_f32, ia_f32;
volatile int      ix_int, iy_int, ia_int;
volatile int      ox_int, oy_int, oa_int;
volatile float    ox_f32, oy_f32, oa_f32;
volatile double   ox_dbl, oy_dbl, oa_dbl;
volatile _Float16 ix_f16, iy_f16, ia_f16;
volatile _Float16 ox_f16, oy_f16, oa_f16;

#define M_PI        3.14159265358979323846264338327950288
#define SIGN_EXT(x, b) (((x)&(1UL<<(b)))?(x)|-(1UL<<(b)):(x)&((1UL<<(b))-1))
#define N 1000 // Количество итераций
int main(void)
{
	volatile int i;
	volatile double err, err_max;
	volatile double scale = 1./(0x00FFFFFF);

  CLK_CNTR->KEY = 0x8555AAA1;
  CLK_CNTR->PER0_CLK |= (0x7FF);
  
  CLK_CNTR->PER1_CLK |= (1U<<31);// Включить MDR_CORDIC_clk
  CLK_CNTR->CRDC_CLK = (1<<16);
    
	printf("Compiler version %d\n", __ARMCC_VERSION);

	//MDR_CRDC->CTRL   = (30u<<24)|(30<<16)|(1<<8)|(0x2<<4)|(0);
	CRD->CTRL_b.IN_LVL_VAL  = 30;
	CRD->CTRL_b.OUT_LVL_VAL = 30;
	CRD->CTRL_b.IN_MODE = 0; // Поворот входного вектора (xy) на угол a
	CRD->CTRL_b.CRD_EN = 1;

//#if (sizeof(float)!=4)
//	#error
//#endif

// Расчёт SIN,COS для разных форматов входных данных

	printf("Integer mode\n");
	CRD->CTRL_b.IN_FORMAT = 2; // Формат - целочисленный
	err_max = 0;	
	for(i=0;i<N;i++) {
		ia_dbl = 0.00001*i*i; // Радианы
		ia = (int)(ia_dbl*(0x01000000/2/M_PI))/(0x01000000/2/M_PI); 
// Ожидаемый результат
		ox = cos(ia);	
		oy = sin(ia);	
// Вычисление с помощью блока
		CRD->IN_X = ix_int = 0x00FFFFFF;
		CRD->IN_Y = iy_int = 0x00000000;	
		 CRD->IN_A = ia_int = fmod(ia, 2.*M_PI)*(0x01000000/2/M_PI);	//	CRD->IN_A = ia_int = SIGN_EXT((int32_t)(ia*(0x01000000/2/M_PI)), 24);
		while (CRD->STATUS_b.OUT_FIFO_EMPTY) ;		
		ox_int = CRD->OUT_X;
		oy_int = CRD->OUT_Y;
		oa_int = CRD->OUT_A;
		
		ox_dbl = ox_int *scale;
		oy_dbl = oy_int *scale;
		printf("sin(%12.9f) = %12.9f expected = %12.9f error = %12.9f  ", ia, oy_dbl, oy, oy_dbl-oy);
		printf("cos(%12.9f) = %12.9f expected = %12.9f error = %12.9f\n", ia, ox_dbl, ox, ox_dbl-ox);
		if (fabs(ox_dbl-ox) > err_max)
			err_max = fabs(ox_dbl-ox);
		if (fabs(oy_dbl-oy) > err_max)
			err_max = fabs(oy_dbl-oy);
	}
	printf("Max error = %12.9f, relative accuracy = %f%% = %.1f bit\n", err_max, 100*err_max/2., log(2./err_max)/log(2.));

	
	
	printf("Float32 mode\n");
	CRD->CTRL_b.IN_FORMAT = 0; // Формат - 32 бита плавающая точка
	err_max = 0;	
	for(i=0;i<N;i++) {
		ia_dbl = 0.00001*i*i; // Радианы
		ia = 2*M_PI*(double)(float)(ia_dbl*(1./2/M_PI)); 
		ox = cos(ia);	
		oy = sin(ia);	
		
		*(volatile float *)&(CRD->IN_X) = ix_f32 = 1.;
		*(volatile float *)&(CRD->IN_Y) = iy_f32 = 0.;
		*(volatile float *)&(CRD->IN_A) = ia_f32 = fmod(ia*(1./2/M_PI), 1.);
		while (CRD->STATUS_b.OUT_FIFO_EMPTY) ;		
		ox_f32 = *(volatile float *)&(CRD->OUT_X);
		oy_f32 = *(volatile float *)&(CRD->OUT_Y);
		oa_f32 = *(volatile float *)&(CRD->OUT_A);
		
		ox_dbl = ox_f32;
		oy_dbl = oy_f32;
		printf("sin(%12.9f rad) = %12.9f expected = %12.9f error = %12.9f  ", ia, oy_dbl, oy, oy_dbl-oy);
		printf("cos(%12.9f rad) = %12.9f expected = %12.9f error = %12.9f\n", ia, ox_dbl, ox, ox_dbl-ox);
		if (fabs(ox_dbl-ox) > err_max)
			err_max = fabs(ox_dbl-ox);
		if (fabs(oy_dbl-oy) > err_max)
			err_max = fabs(oy_dbl-oy);
	}
	printf("Max error = %12.9f, relative accuracy = %f%% = %.1f bit\n", err_max, 100*err_max/2., log(2./err_max)/log(2.));


	printf("Float16 mode %d\n", sizeof(_Float16)); // https://en.wikipedia.org/wiki/Half-precision_floating-point_format
	CRD->CTRL_b.IN_FORMAT = 1; // Формат - 16 бит плавающая точка
	err_max = 0;	
	for(i=0;i<N;i++) {
		//ix_dbl = 1.0 + pow(2,-i);
		//ix_f16 = ix_dbl;
		//ox_dbl = ix_f16;
		ia_dbl = 0.00001*i*i; // Радианы
		ia = 2*M_PI*(double)(_Float16)(ia_dbl*(1./2/M_PI)); 
		
		*(volatile _Float16 *)&(CRD->IN_X) = ix_f16 = 1.0f16;
		*(volatile _Float16 *)&(CRD->IN_Y) = iy_f16 = 0.0f16;
		*(volatile _Float16 *)&(CRD->IN_A) = ia_f16 = fmod(ia*(1./2/M_PI), 1.);
		while (CRD->STATUS_b.OUT_FIFO_EMPTY) ;		
		ox_f16 = *(volatile _Float16 *)&(CRD->OUT_X);
		oy_f16 = *(volatile _Float16 *)&(CRD->OUT_Y);
		oa_f16 = *(volatile _Float16 *)&(CRD->OUT_A);
		
		ox_dbl = ox_f16;
		oy_dbl = oy_f16;
		//ia_dbl = ia_f16*2*M_PI; 
		ox = cos(ia);	
		oy = sin(ia);	
		printf("sin(%12.9f) = %12.9f expected = %12.9f error = %12.9f  ", ia, oy_dbl, oy, oy_dbl-oy);
		printf("cos(%12.9f) = %12.9f expected = %12.9f error = %12.9f\n", ia, ox_dbl, ox, ox_dbl-ox);
		if (fabs(ox_dbl-ox) > err_max)
			err_max = fabs(ox_dbl-ox);
		if (fabs(oy_dbl-oy) > err_max)
			err_max = fabs(oy_dbl-oy);
	}
	printf("Max error = %12.9f, relative accuracy = %f%% = %.1f bit\n", err_max, 100*err_max/2., log(2./err_max)/log(2.));
	
// Расчёт ATAN	
	printf("Float32 ATAN\n");
	CRD->CTRL_b.IN_FORMAT = 0; // Формат - 32 бита плавающая точка
	CRD->CTRL_b.IN_MODE = 1; // Поворот входного вектора (xy) до оси OX
	err_max = 0;	
	for(i=0;i<N;i++) {
		ix = rand()*(2./RAND_MAX)-1.;
		iy = rand()*(2./RAND_MAX)-1.;
		
		*(volatile float *)&(CRD->IN_X) = ix_f32 = ix;
		*(volatile float *)&(CRD->IN_Y) = iy_f32 = iy;
		*(volatile float *)&(CRD->IN_A) = ia_f32 = 0.;
		while (CRD->STATUS_b.OUT_FIFO_EMPTY) ;		
		ox_f32 = *(volatile float *)&(CRD->OUT_X);
		oy_f32 = *(volatile float *)&(CRD->OUT_Y);
		oa_f32 = *(volatile float *)&(CRD->OUT_A);
		
		ox_dbl = ox_f32*0.607252935;
		oa_dbl = oa_f32*(2.*M_PI);
		ox = sqrt(ix*ix+iy*iy);
		oa = atan2(iy, ix); // *(1./2./M_PI)
		err = fmod(oa_dbl-oa+M_PI, 2.*M_PI)-M_PI;
		printf("atan2(%12.9f, %12.9f)   = %12.9f expected = %12.9f error = %12.9f  ", iy, ix, oa_dbl, oa, err);
		printf("sqrt(%12.9f^2+%12.9f^2) = %12.9f expected = %12.9f error = %12.9f\n", iy, ix, ox_dbl, ox, ox_dbl-ox);
		if (fabs(err) > err_max)
			err_max = fabs(err);
		//if (fabs(oy_dbl-oy) > err_max)
			//err_max = fabs(oy_dbl-oy);
	}
	printf("Max error = %12.9f, relative accuracy = %f%% = %.1f bit\n", err_max, 100*err_max/2., log(2./err_max)/log(2.));

}
