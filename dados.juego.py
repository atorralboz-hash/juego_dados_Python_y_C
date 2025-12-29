import ctypes
import os

# 1. Configuración del nombre del archivo
nombre_dll = "libuntitled.dll"

# Obtenemos la ruta absoluta para que Python encuentre el archivo sí o sí
ruta_dll = os.path.abspath(nombre_dll)

print(f"--- Buscando la librería en: {ruta_dll} ---")

try:
    # 2. Cargamos la librería (el cerebro en C)
    juego_c = ctypes.CDLL(ruta_dll)

    print("✅ ¡Librería cargada con éxito!")
    print("🎲 Iniciando el juego de C dentro de Python...")
    print("⚠️ IMPORTANTE: Haz clic en esta consola negra antes de escribir 's' o 'n'")
    print("----------------------------------------------------\n")

    # 3. Llamamos a la función principal del juego
    juego_c.jugar_partida()

except OSError as e:
    print(f"\n❌ ERROR: No encuentro el archivo '{nombre_dll}'.")
    print("Asegúrate de copiar el archivo .dll de la carpeta de CLion a esta carpeta de PyCharm.")
    print(f"Detalle: {e}")
