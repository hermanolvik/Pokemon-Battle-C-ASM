
#define GPIO_D 0x40020C00
#define GPIO_MODER  ((volatile unsigned int *) (GPIO_D))  
#define GPIO_OTYPER  ((volatile unsigned short *) (GPIO_D+0x4))  
#define GPIO_PUPDR ((volatile unsigned int *) (GPIO_D+0xC))  
#define GPIO_IDR_LOW ((volatile unsigned char *) (GPIO_D+0x10))  

#define GPIO_IDR_HIGH  ((volatile unsigned char *) (GPIO_D+0x11))  
#define GPIO_ODR_LOW ((volatile unsigned char *) (GPIO_D+0x14))  
#define GPIO_ODR_HIGH ((volatile unsigned char *) (GPIO_D+0x15))



//klassiska keyb-funktionen. returnerar värdet för knapparna som trycks ner



char keyb(void){
	*( (unsigned long *) GPIO_PUPDR) = 0x00AA0000;
    *( (unsigned long *) GPIO_MODER) = 0x55005555;
        unsigned char key[] = {1,2,3,0xA, 4,5,6,0xB, 7,8,9,0xC, 0xE,0,0xF,0xD};
        int row, col;
       char s = 0;
        for(row = 1; row <= 4; row++){
            kbdActivate( row );
            if((col = kbdGetCol())){
                kbdActivate(0);
				s = key[4*(row-1) + col-1];
				if( (s <=4) && (s > 0) ){
					return s;
				}
				return 0;
            }
        }
    kbdActivate(0);
    return 0;
}
   

   
void kbdActivate(unsigned int row){
        switch(row){
            case 1: *GPIO_ODR_HIGH = 0x10; break;
            case 2: *GPIO_ODR_HIGH = 0x20; break;
            case 3: *GPIO_ODR_HIGH = 0x40; break;
            case 4: *GPIO_ODR_HIGH = 0x80; break;
            default: *GPIO_ODR_HIGH = 0;
        }
}

int kbdGetCol (void){
        unsigned char c;
        c = *GPIO_IDR_HIGH;
        if(c & 0x8) return 4;
        if(c & 0x4) return 3;
        if(c & 0x2) return 2;
        if(c & 0x1) return 1;
        return 0;
}