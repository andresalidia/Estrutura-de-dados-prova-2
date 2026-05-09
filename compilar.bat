@echo off
echo Compilando o Navegador...
gcc -I./include src/main.c src/lista.c src/storage.c src/ui.c src/logica.c -o navegador.exe
if %errorlevel% equ 0 (
    echo Compilado com sucesso! Rode .\navegador.exe
) else (
    echo Erro na compilacao.
)
pause