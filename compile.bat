@echo off
echo Borrando ficheros temporales
del *.asm
del *.ihx
del *.lst
del *.sym
echo Borrando rom
del *.sms
echo Reexportar graficos
.\tools\bmp2tile\bmp2tile.exe .\material\nave.png -nomirror  -savetiles .\assets\navetiles.bin -savepalette .\assets\navepalette.bin -exit
echo Reexportar fondos
java -jar .\tools\ugt.jar -tiledfile  .\material\level1.tmx -destination .\assets -name level1
echo Convertir ficheros de graficos a C y compilarlos
assets2banks assets --compile --singleheader
echo Compilar Librerias
sdcc -c -mz80 --peep-file peep-rules.txt libs/GSLib.c
echo Compilar Juego
sdcc -c -mz80 --peep-file peep-rules.txt game.c
if %errorlevel% neq 0 exit
echo Linkar Juego
sdcc -o shooter.ihx -mz80 --no-std-crt0 --data-loc 0xC000 -Wl-b_BANK2=0x8000 crt0_sms.rel game.rel SMSlib.lib GSLib.rel bank2.rel
if %errorlevel% neq 0 exit
echo Convertir de binario a rom
ihx2sms shooter.ihx shooter.sms
if %errorlevel% neq 0 exit
echo Ejecutar emulador
java -jar c:\Users\JordiM\Desktop\emuladores\mastersystem\Emulicious\Emulicious.jar shooter.sms