# Scramble

#### Video Demo:  [Scramble](https://youtu.be/KNZfhI4DNzo)

## Problem to Solve

Given the modern digital age in 2024, sensitive data stored on computers are vulnerable to breaches, theft, and unauthorized access. With growing cybersecurity threats and increasing regulatory requirements for data protection (e.g., GDPR and HIPAA), encrypting files at rest is crucial for safeguarding personal and corporate information. Files that remain unencrypted are easy targets for malicious actors, leading to identity theft, financial loss, and privacy violations.

While existing encryption tools are powerful, they can be overly complex for users who simply want a fast, effective solution to encrypt files. This is where `scramble` comes in—offering a lightweight, command-line encryption tool that enables users to protect their data with minimal effort.

`scramble` enables users to encrypt files by employing several encryption techniques, including bitwise inversion, byte reversal, and hashing. This flexibility ensures that files can be encrypted using an algorithm that best suits the user’s security requirements. The program is designed to be accessible and easy to integrate into automated workflows, making it an ideal solution for individuals and groups alike.

## Background

Today, encryption is a paramount tool for securing information. By rewriting readable data into an unreadable format, encryption ensures that only authorized users can access the original content. In particular, file encryption is essential for protecting data at rest — files that are stored on a computer or device and not actively being used.

`scramble` was developed as a lightweight command-line tool to provide a quick and easy way to encrypt files. It employs an array of basic encryption techniques to modify the content of the file, including:
* Bitwise Inversion: Inverts each bit in the file’s data, turning `0`s into `1`s and vice versa.
* Byte Reversal: Reverses the sequence of bytes in the file, scrambling the order of the content.
* Hashing: Hashes each byte, transforming the file into a randomized format.
* Splicing: Randomly inserts new bytes between the file’s original data, further obscuring the content.

These methods were chosen for their simplicity and speed, making `scramble` an accessible tool for users who need basic file protection. On the other hand, it is important to note that these techniques do not offer the same level of security as advanced cryptographic algorithms like AES (Advanced Encryption Standard) or RSA (Rivest–Shamir–Adleman Public-Key Cryptosystem) and should not be used for securing highly sensitive information. Scramble is best suited for non-critical files where ease of use and fast encryption are key priorities.

By offering multiple methods for scrambling data, `scramble` provides flexibility for users to choose the approach that best meets their needs. Whether it's obfuscating temporary files or providing a basic level of file encryption, `scramble` is designed to be a user-friendly tool for everyday encryption tasks.

## Understanding

`scramble` is a command-line tool that encrypts files using various techniques. It accepts two command-line arguments: the source file to be encrypted and the encryption method to apply. The selected encryption algorithm is executed on the file, and the resulting encrypted data is written to a temporary file. If the encryption process completes without errors, the original file is deleted, and the encrypted file is renamed to the original file's name.

### Key Components:
* Input/Output Handling: The program uses fopen to open the source file in read mode and a temporary output file in write mode. After processing, the temporary file is renamed to    replace the original file.
* Buffers: The program allocates a buffer in memory to store the file contents during encryption. The buffer is modified based on the selected encryption method before being         written back to disk.

### Main Procedures:
* `main()`: Takes as arguments source file and encryption method. Handles argument parsing, file opening, and selecting the appropriate encryption method. Manages file replacement   after successful encryption.
* `invert()`: Reads the file into a buffer, inverts the bits of each byte, and writes the result to the output file.
* `reverse()`: Reads the file in reverse order and writes the reversed byte sequence to the output file.
* `hash()`: Scrambles each byte using a basic hash function and writes the result to the output file.
* `splice()`: Reads each byte of the file and inserts a random byte between each one before writing to the output file.

### Error Handling:
* Invalid command-line arguments: If the user does not provide the correct number of arguments, then an error message is printed.
* File Access Errors: If the program cannot open the source or output files, then it returns an error.
* Invalid Encryption Method: If the provided encryption method is not supported, then the program prints an error message and exits.

### Limitations:
* Performance: The current implementation reads the entire file into memory, which causes issues with very large files. Future iterations could improve efficiency by processing the file in chunks.
* Security: The encryption techniques used are lightweight and should not be considered secure for highly sensitive data. They are best suited for basic file obfuscation rather than strong cryptographic encryption.

## Specification

### Input and Output:
* Input: The program takes two command-line arguments: the source file to be encrypted and the encryption method.
    * `<source-file>`: The path or name of the file to be encrypted (e.g., `source.txt`).
    * `<method>`: The encryption method to apply (`invert`, `reverse`, `hash`, `splice`).
* Output: The program produces an encrypted version of the input file. The original file is replaced by the encrypted version unless an error occurs during the process.

### Command-Line Usage:
* Syntax: `./scramble <source-file> <method>`.

### File Handling:
* If the encryption process is successful, then the original file is deleted and the encrypted file replaces it.
* If encryption fails, then the original file remains unchanged and the temporary encrypted file is removed.

### Edge Cases:
* Empty Files: The program handles empty files by producing an empty encrypted output file.
* File Permissions: If the program does not have permission to read or write the file, an error message is displayed, and no changes are   made to the file.

### Security Considerations:
* Basic Encryption: The methods implemented in `scramble` provide basic file obfuscation but are not intended for high-security encryption. For sensitive data, more robust cryptographic algorithms like AES should be applied.
