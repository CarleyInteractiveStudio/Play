import struct
import sys
import os

def pack_pg(title, developer, bin_path, icon_path, output_path):
    # Leer el binario del juego
    with open(bin_path, 'rb') as f:
        code = f.read()

    # Leer el icono (si existe)
    icon = b''
    if icon_path and os.path.exists(icon_path):
        with open(icon_path, 'rb') as f:
            icon = f.read()

    # Preparar cabecera (pg_header_t)
    # char signature[2], uint8_t version, uint8_t padding, char title[64], char developer[64],
    # uint32_t code_size, uint32_t compressed_size, uint32_t icon_offset, uint32_t icon_size, uint32_t entry_point, uint32_t checksum

    fmt = "2s B B 64s 64s I I I I I I"
    sig = b'PG'
    ver = 1
    pad = 0
    title_b = title.encode('utf-8').ljust(64, b'\0')
    dev_b = developer.encode('utf-8').ljust(64, b'\0')
    code_size = len(code)
    compressed_size = 0 # Implementar compresión LZ4 en Python aquí
    icon_offset = struct.calcsize(fmt) + code_size
    icon_size = len(icon)
    entry_point = 0x02000000 # Dirección de carga por defecto
    checksum = 0 # TODO: Calcular checksum real

    header = struct.pack(fmt, sig, ver, pad, title_b, dev_b, code_size, compressed_size, icon_offset, icon_size, entry_point, checksum)

    # Escribir archivo .pg final
    with open(output_path, 'wb') as f:
        f.write(header)
        f.write(code)
        f.write(icon)

    print(f"Éxito: Juego empaquetado en {output_path}")

if __name__ == "__main__":
    if len(sys.argv) < 5:
        print("Uso: python pg-pack.py <titulo> <desarrollador> <binario> <icono> <salida.pg>")
    else:
        pack_pg(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5])
