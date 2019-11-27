@echo off
echo Borrando ficheros temporales
del *.asm
del *.ihx
del *.lst
del *.sym
echo Borrando rom
del *.sms
echo Compilar Juego
sdcc -c -mz80 --peep-file peep-rules.txt game.c
if %errorlevel% neq 0 exit
echo Linkar Juego
sdcc -o shooter.ihx -mz80 --no-std-crt0 --data-loc 0xC000 crt0_sms.rel game.rel SMSlib.lib
if %errorlevel% neq 0 exit
echo Convertir de binario a rom
ihx2sms shooter.ihx shooter.sms
if %errorlevel% neq 0 exit
echo Ejecutar emulador
java -jar c:\Users\JordiM\Desktop\emuladores\mastersystem\Emulicious\Emulicious.jar shooter.sms