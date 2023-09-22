import os
import sys
import numpy as np

if __name__ == "__main__":
    # Get commandline arguments
    TRACE_FILE = sys.argv[1]

    # Extract timestamps from trace file
    binfile = open(TRACE_FILE, 'rb')
    length = int(os.path.getsize(TRACE_FILE)/6)
    timestamps = np.ndarray((length), dtype=np.uint32)
    for i in range(length):
        # Skip 16-bit ID
        id = binfile.read(2)
        if len(id) < 2:
            break

        # Get 32-bit timestamp
        timestamp = binfile.read(4)
        if len(timestamp) < 4:
            break
        timestamps[i] = int.from_bytes(timestamp, 'big')
    binfile.close()

    # Calculate mean overhead and percentiles
    overhead = np.diff(timestamps)
    print(f"Average: {np.mean(overhead)}")
    print(f"Percentiles: {np.percentile(overhead, [p for p in range(0, 100+10, 10)])}")
    print(f"Minimum: {np.min(overhead}")




