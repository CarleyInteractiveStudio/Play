import sys

def compile_shader(input_path, output_path):
    print(f"Compilando sombreador: {input_path}")

    with open(input_path, 'r') as f:
        code = f.read()

    # Simulación de compilación para Mali-400 (Fixed pipeline emulation)
    # En un entorno real, aquí se llamaría al binario 'malic' de ARM.
    binary_code = code.encode('utf-8')

    with open(output_path, 'wb') as f:
        f.write(binary_code)

    print(f"Éxito: Sombreador guardado en {output_path}")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Uso: python cp-shc.py <input.glsl> <output.spv>")
    else:
        compile_shader(sys.argv[1], sys.argv[2])
