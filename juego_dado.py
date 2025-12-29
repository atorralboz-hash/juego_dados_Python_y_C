import ctypes
import os

# 1. Buscamos el archivo DLL
# Asegúrate de que este nombre coincide con el archivo que pegaste en la carpeta
nombre_dll = "libuntitledddd.dll"
ruta_dll = os.path.abspath(nombre_dll)

print(f"--- Cargando juego desde: {ruta_dll} ---")

try:
    # 2. Cargamos el "cerebro" en C
    juego_c = ctypes.CDLL(ruta_dll)

    print("✅ ¡Conectado correctamente!")
    print("🎲 Lanzando el juego...")
    print("⚠️ IMPORTANTE: Haz clic en la pantalla negra de abajo antes de escribir.")
    print("----------------------------------------------------\n")

    # 3. Arrancamos el juego
    juego_c.jugar_partida()

except Exception as e:
    print(f"❌ Error: {e}")