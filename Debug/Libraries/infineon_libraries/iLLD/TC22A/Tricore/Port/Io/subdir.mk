################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/infineon_libraries/iLLD/TC22A/Tricore/Port/Io/IfxPort_Io.c 

OBJS += \
./Libraries/infineon_libraries/iLLD/TC22A/Tricore/Port/Io/IfxPort_Io.o 

COMPILED_SRCS += \
./Libraries/infineon_libraries/iLLD/TC22A/Tricore/Port/Io/IfxPort_Io.src 

C_DEPS += \
./Libraries/infineon_libraries/iLLD/TC22A/Tricore/Port/Io/IfxPort_Io.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/infineon_libraries/iLLD/TC22A/Tricore/Port/Io/%.src: ../Libraries/infineon_libraries/iLLD/TC22A/Tricore/Port/Io/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc21x -I"E:\MT9V03x_PC_OTSU_Demo\CODE" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Gpt12" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Gpt12\IncrEnc" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Gpt12\Std" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\doc" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Configurations" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\_Build" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\_Impl" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\_Lib" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\_Lib\DataHandling" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\_Lib\InternalMux" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\_PinMap" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Asclin" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Asclin\Asc" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Asclin\Lin" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Asclin\Spi" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Asclin\Std" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Ccu6" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Ccu6\Icu" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Ccu6\PwmBc" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Ccu6\PwmHl" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Ccu6\Std" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Ccu6\Timer" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Ccu6\TimerWithTrigger" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Ccu6\TPwm" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Cpu" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Cpu\CStart" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Cpu\Irq" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Cpu\Std" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Cpu\Trap" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Dma" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Dma\Dma" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Dma\Std" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Dts" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Dts\Dts" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Dts\Std" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Flash" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Flash\Std" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Gtm" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Gtm\Std" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Gtm\Tim" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Gtm\Tim\In" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Gtm\Tom" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Gtm\Tom\Pwm" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Gtm\Tom\PwmHl" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Gtm\Tom\Timer" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Gtm\Trig" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Iom" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Iom\Driver" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Iom\Std" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Mtu" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Mtu\Std" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Multican" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Multican\Can" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Multican\Std" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Port" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Port\Io" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Port\Std" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Qspi" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Qspi\SpiMaster" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Qspi\SpiSlave" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Qspi\Std" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Scu" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Scu\Std" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Sent" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Sent\Sent" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Sent\Std" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Smu" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Smu\Std" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Src" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Src\Std" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Stm" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Stm\Std" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Stm\Timer" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Vadc" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Vadc\Adc" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\iLLD\TC22A\Tricore\Vadc\Std" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Infra" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Infra\Platform" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Infra\Platform\Tricore" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Infra\Platform\Tricore\Compilers" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Infra\Sfr" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Infra\Sfr\TC22A" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Infra\Sfr\TC22A\_Reg" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Service" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Service\CpuGeneric" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Service\CpuGeneric\_Utilities" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Service\CpuGeneric\If" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Service\CpuGeneric\If\Ccu6If" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Service\CpuGeneric\StdIf" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Service\CpuGeneric\SysSe" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Service\CpuGeneric\SysSe\Bsp" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Service\CpuGeneric\SysSe\Comm" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Service\CpuGeneric\SysSe\General" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Service\CpuGeneric\SysSe\Math" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\infineon_libraries\Service\CpuGeneric\SysSe\Time" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\seekfree_libraries" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\seekfree_libraries\common" -I"E:\MT9V03x_PC_OTSU_Demo\Libraries\seekfree_peripheral" -I"E:\MT9V03x_PC_OTSU_Demo\USER" --iso=99 --c++14 --language=+volatile --anachronisms --fp-model=3 --fp-model=c --fp-model=f --fp-model=l --fp-model=n --fp-model=r --fp-model=z -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc21x -o "$@"  "$<"  -cs --dep-file=$(@:.src=.d) --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/infineon_libraries/iLLD/TC22A/Tricore/Port/Io/%.o: ./Libraries/infineon_libraries/iLLD/TC22A/Tricore/Port/Io/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


