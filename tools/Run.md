# Probar `buttons` en Termux

Demo de botones en C + ncurses (arm64). Hay dos opciones: compilar desde el
código fuente, o descargar el binario ya compilado.

## Requisitos

- Termux con arquitectura arm64/aarch64 (verificar con `uname -m`)
- Los archivos deben estar subidos al repo (`git push`) antes de poder descargarlos

## Opción A: compilar desde el código fuente

1. Instalar el compilador y ncurses:

   ```sh
   pkg update && pkg install -y clang ncurses
   ```

2. Descargar el código fuente:

   ```sh
   curl -fL -o buttons.c https://raw.githubusercontent.com/tequitl/wp-net-base/main/tools/buttons.c
   ```

3. Compilar:

   ```sh
   clang -O2 -o buttons buttons.c -lncursesw
   ```

4. Ejecutar:

   ```sh
   ./buttons
   ```

## Opción B: descargar el binario listo

1. Instalar dependencias (ncurses provee `libncursesw.so.6`):

   ```sh
   pkg update && pkg install -y ncurses curl
   ```

2. Descargar el binario:

   ```sh
   curl -fL -o buttons https://raw.githubusercontent.com/tequitl/wp-net-base/main/tools/buttons
   ```

3. Darle permisos de ejecución:

   ```sh
   chmod +x buttons
   ```

4. Ejecutarlo:

   ```sh
   ./buttons
   ```

## Uso

- Navega con las flechas o Tab y confirma con Enter
- También puedes tocar un botón directamente (soporte de mouse/touch)
- `q` o ESC para salir
- Botones: **Saludar**, **Hora**, **Salir**
