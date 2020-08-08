#define MOVE 0
#define ADD  1
#define SUB  2
#define BRA  3
#define CMP  4
#define BEQ  5
#define BNE  6
#define EXG  7
#define MULT 8
#define STOP 15
void main(void)
{

    unsigned short int PC = 0;
    unsigned short int DO = 0;
    unsigned short int A0 = 0 ;
    unsigned short int CCR = 0 ;
    unsigned short int MAR;
    unsigned short int MBR;
    unsigned short int IR;
    unsigned short int operand;
    unsigned short int source;

    unsigned short int destination;
    unsigned short int opcode;
    unsigned short int amode;
    unsigned short int direction;
    unsigned short int memory[256];
    unsigned short int run = 1;
    ex(memory);
    int i;
    for( i=0; i<7; i++)
    {

        printf("memory at %d =%d\n",i,memory[i]);
    }
    printf("------------------\n");
    while (run)
    {
        MAR = PC;
        PC = PC + 1 ;
        MBR = memory [MAR];
        IR = MBR;
        opcode = IR;

        MAR = PC;
        PC = PC + 1 ;
        MBR = memory [MAR];
        IR = MBR;
        operand = IR ;
        amode = opcode & 0x03;
        direction = (opcode & 0x04) >> 2;
        opcode = opcode >> 4 ;

        switch (amode)
        {
        case 0:
        {
            source = memory[operand];
            break;
        }
        case 1:
        {
            source = operand;
            break;
        }
        case 2:
        {
            source = memory[A0 + operand];
            break;
        }
        case 3:
        {
            source = memory[PC + operand];
            break;
        }

        }
        printf("****** source=%d *******\n",source) ;
        switch (opcode)
        {
        case MOVE:
        {
            printf("Move\n") ;
            if (direction == 0) destination = DO;
            else DO = source;
            if (DO == 0) CCR = 1;
            else CCR = 0; /* update CCR */
             p(PC,  DO,A0,CCR, MAR, MBR, IR, operand,source, destination, opcode, amode,direction  );
            break;
        }
         case MULT:
        {
            printf("MULT\n") ;
            if (direction == 0) destination = DO*source;
            else DO = DO*source;
            if (DO == 0) CCR = 1;
            else CCR = 0; /* update CCR */
             p(PC,  DO,A0,CCR, MAR, MBR, IR, operand,source, destination, opcode, amode,direction  );
            break;
        }
        case ADD:
        {
            printf("ADD\n") ;
            if (direction == 0)

            {
                destination = DO + source;
                if (destination == 0) CCR = 1;
                else CCR = 0;
            }
            else
            {
                DO = DO + source;
                if (DO == 0 ) CCR = 1;
                else CCR = 0;
            }
             p(PC,  DO,A0,CCR, MAR, MBR, IR, operand,source, destination, opcode, amode,direction  );
            break;
        }
        case SUB:
        {
            printf("SUB\n") ;
            if (direction == 0)

            {
                destination = DO - source;
                if (destination == 0) CCR = 1;
                else CCR = 0;
            }
            else
            {
                DO = DO - source;
                if (DO == 0 ) CCR = 1;
                else CCR = 0;
            }
             p(PC,  DO,A0,CCR, MAR, MBR, IR, operand,source, destination, opcode, amode,direction  );
            break;
        }

        case BRA:
        {
            printf("BRA\n") ;
            if (amode ==0 ) PC = operand;

            if (amode ==1 ) PC = PC + operand;
             p(PC,  DO,A0,CCR, MAR, MBR, IR, operand,source, destination, opcode, amode,direction  );
            break;
        }
        case CMP:
        {
            printf("CMP\n") ;
            MBR = DO - source;
            if (MBR == 0) CCR = 1;
            else CCR = 0;
             p(PC,  DO,A0,CCR, MAR, MBR, IR, operand,source, destination, opcode, amode,direction  );
            break;
        }
        case BEQ:
        {
            printf("BEQ\n") ;
            if (CCR == 1)

            {
                if (amode ==0 ) PC = operand;
                if (amode ==1 ) PC = PC + operand;
            }
             p(PC,  DO,A0,CCR, MAR, MBR, IR, operand,source, destination, opcode, amode,direction  );
            break;
        }
        case BNE:
        {
            printf("BNE\n") ;
            if (CCR != 1)

            {
                if (amode ==0 ) PC = operand;
                if (amode == 1) PC = PC + operand;
            }
             p(PC,  DO,A0,CCR, MAR, MBR, IR, operand,source, destination, opcode, amode,direction  );
            break;
        }
        case EXG:
        {
            MBR = DO;
            DO = A0;
            A0 = MBR;
            printf("EXG\n") ;
             p(PC,  DO,A0,CCR, MAR, MBR, IR, operand,source, destination, opcode, amode,direction  );
            break;

        }
        case STOP:
        {
            direction=5;
            printf("Stop\n") ;
            run = 0;
             p(PC,  DO,A0,CCR, MAR, MBR, IR, operand,source, destination, opcode, amode,direction  );
            break;

        }
        p(PC,  DO,A0,CCR, MAR, MBR, IR, operand,source, destination, opcode, amode,direction  );
        }
        if(direction==0)
        {
            switch (amode)
            {
            case 0:
            {
                printf("in\n");
                memory[operand]=destination;
                break; /* absolute*/
            }
            case 1:
            {
                break; /* literal */
            }
            case 2:
            {
                memory[A0 + operand]= destination;
                break; /* indexed */
            }
            case 3:
            {
                memory[PC + operand]=destination;
                break; /* PC relative */
            }

            }

        }
    }
 for( i=0; i<7; i++)
    {

        printf("memory at %d =%d\n",i,memory[i]);
    }
}
void p(unsigned short int PC, unsigned short int DO,  unsigned short int A0,unsigned short int CCR,unsigned short int MAR,unsigned short int MBR,unsigned short int IR,unsigned short int operand,unsigned short int source,unsigned short int destination,unsigned short int opcode,unsigned short int amode,unsigned short int direction   )
{
    printf("PC=%d\n",PC   );
    printf("DO=%d\n",DO );
    printf("A0=%d\n",A0 );
    printf("CCR=%d\n",CCR  );
    printf("MAR=%d\n",MAR ) ;
    printf("MBR=%d\n",MBR)   ;
    printf("IR=%d\n",IR)     ;
    printf("operand=%d\n",operand) ;
    printf("source=%d\n",source) ;
    printf("destination=%d\n",destination);
    printf("opcode=%d\n",opcode)      ;
    printf("amode=%d\n",amode)      ;
    printf("direction=%d\n",direction) ;

}

void list_of_instruction()
{
    printf("List of opcodes:\n 1-MOVE\n 2-ADD\n 3-SUB\n 4-BRA\n 5-CMP\n 6-BEQ\n 7-BNE\n 8-EXG 9-MULT\n 15-STOP\n ------------\n");
}
int inst (int choose)
{
    if(choose==1)
        return 0;
    else if(choose==2)
        return 16;
    else if(choose==3)
        return 32;
    else if(choose==4)
        return 48;
    else if(choose==5)
        return 64;
    else if(choose==6)
        return 80;
    else if(choose==7)
        return 96;
    else if(choose==8)
        return 112;
    else if(choose==9)
        return 128;
    else if(choose==15)
        return 240;
    else ;
}
void list_of_modes()
{
    printf("List of modes:\n 1-absolute\n 2-literal\n 3-indexed\n 4-relative\n------------\n");
}
int mode (int choose)
{
    if(choose==1)
        return 0;
    else if(choose==2)
        return 1;
    else if(choose==3)
        return 2;
    else if(choose==4)
        return 3;
    else ;

}
void show_direction()
{
    printf("direction:\n 1-register to memory\n 2-memory to register\n------------\n");
}
int di (int choose)
{
    if(choose==1)
        return 0;
    else if(choose==2)
        return 4;
    else ;


}
int scan()
{
    int choose;
    printf("enter your number\n");
    scanf("%d",&choose);
    return choose;
}
int checkloop()
{
    int choose;
    printf("put 1 to enter another instruction or enter 0 to go out\n");
    scanf("%d",&choose);
    return choose;
}
void ex(unsigned short int memory[256])
{
    int in=-1;
    int loop=1;
    while(loop==1&&in<256)
    {
        unsigned short int part1=0;
        in++;
        list_of_instruction();
        part1=inst(scan());
        list_of_modes();
        part1=part1+mode(scan());
        show_direction();
        part1=part1+di(scan());
        memory[in]=part1;
        in++;
        memory[in]=scan();
        loop=checkloop();

    }



}
/* Instruction format:   */
/* 7 6 5 4 3 2 1 0      */
/* Bit 1 and 0 2-bit address mode */
/* 00 address mode = absolute */
/* 01 address mode = literal */
/* 10 address mode = indexed */
/* 11 address mode = relative */
/* Bit 2   1-bit direction (source/operand) */
/* Bit 3   not used */
/* Bit 7 to 4  4-bit instruction code */

/* main loop */

