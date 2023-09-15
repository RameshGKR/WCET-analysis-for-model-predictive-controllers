import os
import sys
import tempfile
import numpy as np
from serial import Serial
from struct import unpack
from numba import njit

def receive(port, rxfile):
    # Initialize serial connection
    ser = Serial()
    ser.baudrate = 12_000_000
    ser.port = port
    ser.timeout = 2
    ser.open()
    print(f"Connected to instrumentation device through {ser.port}.")

    # Receive timestamps
    while True:
        if (ser.in_waiting >= 8):
            data = ser.read((ser.in_waiting // 8)*8)
            rxfile.write(data)

            # If an 8 byte word starts with 0b11 & 14 0's, done was asserted
            if data[-8:-6] == b'\xC0\x00':
                break

    print("Done receiving timestamps!")
    ser.close()

@njit
def crc_8_atm(bits):
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

def parse(rxfile, binfile):
    print(f"Parsing timestamps to {binfile.name}")

    # Start at beginning of file
    rxfile.seek(0)

    prev_seq = None
    while True:
        # Get 8-byte line
        line = rxfile.read(8)
        if line is None or len(line) < 8:
            raise Exception("Data loss has occurred!")

        # Check CRC
        bits = np.unpackbits(np.frombuffer(line, dtype='>u1'))
        full_crc = crc_8_atm(bits[0:-8]) # CRC of message including the CRC
        if np.any(full_crc):
            raise Exception("Invalid checksum detected!")

        # Check sequence number
        seq = unpack(">xxxxxxxB", line)
        if prev_seq != None and seq != prev_seq + 1:
            raise Exception("Invalid sequence number detected!")

        # If ID is start with 0b1100 0000 = 0x
        if line[0] == 0xC0:
            break

        binfile.write(line[0:6])

    print("Done parsing timestamps!")
    binfile.close()

if __name__ == "__main__":
    # Get commandline arguments
    COM_PORT = sys.argv[1]
    TRACE_FILE = sys.argv[2]

    rxfile = tempfile.TemporaryFile(buffering=0)
    receive(port=COM_PORT, rxfile=rxfile)

    binfile = open(TRACE_FILE, 'wb')
    parse(rxfile=rxfile, binfile=binfile)

    rxfile.close()
    binfile.close()
