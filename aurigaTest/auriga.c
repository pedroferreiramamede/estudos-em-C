#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define CRC_POLYNOME 0x04C11DB7
#define CRC_INITIAL  0xFFFFFFFF

unsigned long crc32(unsigned long crc, const unsigned char *data, size_t length) {
    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            crc = (crc >> 1) ^ ((crc & 1) ? CRC_POLYNOME : 0);
        }
    }
    return crc;
}

void apply_mask(uint8_t *payload, int length, uint32_t mask) {
    for (int i = 0; i < length; i++) {
        payload[i] ^= ((mask >> (8 * (i % 4))) & 0xFF);
    }
}

void write_hex(FILE *file, uint8_t *data, int length) {
    for (int i = 0; i < length; i++) {
        fprintf(file, "%02X", data[i]);
    }
}


int main() {
    FILE *input_file = fopen("data_in.txt", "r");
    FILE *output_file = fopen("data_out.txt", "a");

    if (input_file == NULL || output_file == NULL) {
        fprintf(output_file, "Error: Unable to open input/output file\n");
        return 1;
    }

    int type, size;
    char data[255]; // Assuming max size for data is 255 characters
    char new_data[255];
    uint32_t crc;
    uint32_t mask;

    char line[300]; // Assuming max line length is 300 characters

    while (fgets(line, sizeof(line), input_file)) {
        if (strncmp(line, "mask=", 5) == 0) {
            sscanf(line, "mask=%X", &mask);
        }    
        if (strncmp(line, "mess=", 5) == 0) {
            sscanf(line, "mess=%d|%d|%255[^|]|%X", &type, &size, data, &crc);

            // Apply mask to even tetrads in payload
            apply_mask((uint8_t *)new_data, size, mask);

            // Calculate CRC-32 for new data bytes
            uint32_t new_crc = crc32(CRC_INITIAL, (uint8_t *)data, size);

            // Write results to output file
            fprintf(output_file, "Type: %d\n", type);
            fprintf(output_file, "Initial Length: %d\n", size);
            fprintf(output_file, "Initial Data Bytes: %s\n", data);
            fprintf(output_file, "Initial CRC-32: %08X\n", crc);
            fprintf(output_file, "Modified Length: %d\n", size);
            fprintf(output_file, "Modified Data Bytes with Mask: ");
            write_hex(output_file, data, size / 2);
            fprintf(output_file, "\n");
            fprintf(output_file, "Modified CRC-32: %08X\n\n", new_crc);
        }
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}
