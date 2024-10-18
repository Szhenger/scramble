#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Prototypes of the encryption algorithms
int invert(FILE *input, FILE *output);
int reverse(FILE *input, FILE *output);
int hash(FILE *input, FILE *output);
int splice(FILE *input, FILE *output);

int main(int argc, char *argv[])
{
    // Ensure proper usage of the program
    if (argc != 3)
    {
        printf("Usage: ./scramble source.txt method\n");
        return 1;
    }

    // Open source file for reading
    char *src_name = argv[1];
    FILE *src = fopen(src_name, "r");
    if (src == NULL)
    {
        printf("Main Error: Failed to open %s\n", src_name);
        return 2;
    }

    // Open cipher file for writing
    char *cip_name = "encrypt";
    FILE *cip = fopen(cip_name, "w");
    if (cip == NULL)
    {
        printf("Main Error: Failed to open %s\n", cip_name);
        fclose(src);
        src = NULL;
        return 3;
    }

    // Declare encryption flag
    int is_encrypted;

    // Scramble the contents of source file by writing to cipher file
    char *mth_name = argv[2];
    if (strcasecmp(mth_name, "invert") == 0)
    {
        // Inverts each byte in source file
        is_encrypted = (invert(src, cip)) ? 0 : 1;
    }
    else if (strcasecmp(mth_name, "reverse") == 0)
    {
        // Reverses the order of bytes in source file
        is_encrypted = (reverse(src, cip)) ? 0 : 1;
    }
    else if (strcasecmp(mth_name, "hash") == 0)
    {
        // Hashes each bytes in source file
        is_encrypted = (hash(src, cip)) ? 0 : 1;
    }
    else if (strcasecmp(mth_name, "splice") == 0)
    {
        // Splices bytes into source file
        is_encrypted = (splice(src, cip)) ? 0 : 1;
    }
    else
    {
        printf("Main Error: Invalid encryption method %s\n", mth_name);
        return 4;
    }

    // Closes source and cipher files
    fclose(src);
    fclose(cip);
    src = cip = NULL;

    // Replace source file with encrypted copy file
    if (is_encrypted == 1)
    {
        if (remove(src_name))
        {
            printf("Main Error: Failed to delete %s\n", src_name);
            return 5;
        }
        if (rename(cip_name, src_name))
        {
            printf("Main Error: Failed to rename %s to %s\n", cip_name, src_name);
            return 6;
        }
        return 0;
    }
    else
    {
        printf("Main Error: Failed to encrypt %s\n", src_name);
        remove(cip_name);
        return 7;
    }
}

// Encrypts the contents of files by inverting representation bytewise
int invert(FILE *input, FILE *output)
{
    // Ensures that files exists
    assert(input != NULL);
    assert(output != NULL);

    // Get size of input file in bytes
    if (fseek(input, 0, SEEK_END))
    {
        printf("Invert Error: Cannot get size of file in bytes\n");
        return 8;
    }
    long size = ftell(input) + 1;

    // Move pointer of input file stream to start
    if (fseek(input, 0, SEEK_SET))
    {
        printf("Invert Error: Cannot move pointer to start of file\n");
        return 9;
    }

    // Allocate buffer array
    char *buffer = malloc(size);
    if (buffer == NULL)
    {
        printf("Invert Error: Cannot allocate buffer\n");
        return 10;
    }

    // Read input file into buffer
    fread(buffer, sizeof(char), size, input);
    if (ferror(input))
    {
        printf("Invert Error: Cannot read file into buffer\n");
        free(buffer);
        buffer = NULL;
        return 11;
    }

    // Invert each bit in every byte within buffer
    for (int i = 0; i < size; i++)
        buffer[i] = ~buffer[i];

    // Writes buffer to output file
    fwrite(buffer, sizeof(char), size, output);
    if (ferror(output))
    {
        printf("Invert Error: Failed to properly invert file\n");
        free(buffer);
        buffer = NULL;
        return 12;
    }

    // Free buffer
    free(buffer);
    buffer = NULL;
    return 0;
}

// Encrypts the contents of files by reversing representation sequence bytewise
int reverse(FILE *input, FILE *output)
{
    // Assume that files exists
    assert(input != NULL);
    assert(output != NULL);

    // Get size of input file in bytes
    if (fseek(input, 0, SEEK_END))
    {
        printf("Reverse Error: Cannot get size of file in bytes\n");
        return 8;
    }
    int size = ftell(input) + 1;

    // Declare a char buffer
    char buffer;

    // Reverse the file sequence bytewise
    for (int i = 0; i < size; i++)
    {
        // Move the pointer of stream to the btye to be reversed
        if (fseek(input, size - i, SEEK_SET))
        {
            printf("Reverse Error: Cannot move the pointer of file stream to left\n");
            return 14;
        }

        // Read byte to be reversed into buffer from input file
        fread(&buffer, sizeof(char), 1, input);
        if (ferror(input))
        {
            printf("Reverse Error: Cannot read file into buffer\n");
            return 15;
        }

        // Write buffer to output file
        fwrite(&buffer, sizeof(char), 1, output);
        if (ferror(output))
        {
            printf("Reverse Error: Cannot write buffer to file\n");
            return 16;
        }
    }
    return 0;
}

// Encrypts the contents of files by hashing representation bytewise
int hash(FILE *input, FILE *output)
{
    // Ensure that files exists
    assert(input != NULL);
    assert(output != NULL);

    // Get size of input file in bytes
    if (fseek(input, 0, SEEK_END))
    {
        printf("Hash Error: Cannot get size of file in bytes\n");
        return 8;
    }
    int size = ftell(input) + 1;

    // Move the pointer of stream to start
    if (fseek(input, 0, SEEK_SET))
    {
        printf("Hash Error: Cannot move to start of file\n");
        return 9;
    }

    // Allocate buffer array
    char *buffer = malloc(size);
    if (buffer == NULL)
    {
        printf("Hash Error: Cannot allocate buffer\n");
        free(buffer);
        buffer = NULL;
        return 10;
    }

    // Read file into buffer
    fread(buffer, sizeof(char), size, input);
    if (ferror(input))
    {
        printf("Hash Error: Cannot read file into buffer\n");
        free(buffer);
        buffer = NULL;
        return 11;
    }

    // Randomly hash each byte in buffer
    char c = rand() % 128;
    for (int i = 0; i < size; i++)
    {
        buffer[i] %= c;
    }

    // Write buffer to output file
    fwrite(buffer, sizeof(char), size, output);
    if (ferror(output))
    {
        printf("Hash Error: Failed to properly hash file\n");
        free(buffer);
        buffer = NULL;
        return 17;
    }

    // Free buffer
    free(buffer);
    buffer = NULL;
    
    // Print key to decrypt hashed file
    printf("%i\n", c);
    return 0;
}

// Encrypts the contents of files by splicing random bytes in representation
int splice(FILE *input, FILE *output)
{
    // Assume that file exists
    assert(input != NULL);
    assert(output != NULL);

    // Get size of file in bytes
    if (fseek(input, 0, SEEK_END))
    {
        printf("Splice Error: Cannot get size of file in bytes\n");
        return 8;
    }
    int size = ftell(input);

    // Move the pointer of stream to start
    if (fseek(input, 0, SEEK_SET))
    {
        printf("Splice Error: Cannot move to start of file\n");
        return 9;
    }

    // Allocate buffer array
    char *buffer = malloc(2 * size);
    if (buffer == NULL)
    {
        printf("Splice Error: Cannot allocate buffer\n");
        return 11;
    }

    // Read byte and append random byte per iteration from input
    char byte;
    for (int i = 0; i < size; i++)
    {
        // Read byte to odd index of buffer
        fread(&byte, sizeof(char), 1, input);
        if (ferror(input))
        {
            printf("Splice Error: Cannot read file into buffer\n");
            free(buffer);
            buffer = NULL;
            return 18;
        }
        buffer[2 * i] = byte;

        // Append random byte to even index of buffer
        buffer[2 * i + 1] = rand() % 128;
    }

    // Write the contents of buffer to output
    fwrite(buffer, sizeof(char), 2 * size, output);
    if (ferror(output))
    {
        printf("Splice Error: Failed to properly splice file\n");
        free(buffer);
        buffer = NULL;
        return 19;
    }

    // Free buffer
    free(buffer);
    buffer = NULL;
    return 0;
}
