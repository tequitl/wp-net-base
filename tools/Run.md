# Descargar y ejecutar `buttons` en Termux

Demo de botones en C + ncurses (arm64).

## Requisitos

- Termux con arquitectura arm64/aarch64 (verificar con `uname -m`)
- El archivo debe estar subido al repo (`git push`) antes de poder descargarlo

## Pasos

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
- Botones: **Saludar**, **Hora**, **Salir**
