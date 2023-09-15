import numpy as np

# Constants
INPUT_WORD_SIZE = 48

def crc_8_atm(bits: np.ndarray) -> np.ndarray:
    # CRC-8-ATM
    generator = np.array([1, 0, 0, 0, 0, 0, 1, 1, 1], dtype=np.uint0)
    degree = generator.shape[0] - 1

    # Multiply bit_array with x^(n-k)
    bits_shifted = np.concatenate((bits, np.zeros((degree), dtype=np.uint0)))
    
    # Calculate remainder after division by generator
    a, b = 0, generator.shape[0]
    while b <= bits_shifted.shape[0]:
        if bits_shifted[a:b][0] == 1:
            bits_shifted[a:b] = np.logical_xor(bits_shifted[a:b], generator)
        a, b = a+1, b+1
    remainder = bits_shifted[-degree:]

    return remainder

if __name__ == "__main__":
    generatorT = np.ndarray((INPUT_WORD_SIZE, 8), dtype=np.uint0)
    for i in range(INPUT_WORD_SIZE):
        input_word = np.zeros(INPUT_WORD_SIZE, dtype=np.uint0)
        input_word[i] = 1
        generatorT[i] = crc_8_atm(input_word)
    generator = generatorT.T
    
    print(f'-- CRC-8-ATM linear implementation for ({INPUT_WORD_SIZE+8}, {INPUT_WORD_SIZE}) code')
    print(f'type t_crc8 is array (0 to 7) of std_logic_vector({INPUT_WORD_SIZE-1} downto 0);')
    print('constant lut_crc8 : t_crc8 := (')
    for i in range(8):
        print(f'    "{"".join(str(x) for x in generator[i, :])}"{ {0: ",", 1: ""}[i == 7] }')
    print(');')
