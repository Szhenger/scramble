# Scramble

#### Video Demo:  [Scramble](https://youtu.be/KNZfhI4DNzo)

## Problem to Solve

Given the modern digital age in 2024, sensitive data stored on computers is vulnerable to breaches, theft, and unauthorized access. With growing cybersecurity threats and increasing regulatory requirements for data protection (e.g., GDPR, HIPAA), encrypting files at rest is crucial for safeguarding personal and corporate information. Files that remain unencrypted are easy targets for malicious actors, leading to identity theft, financial loss, and privacy violations.

While existing encryption tools are powerful, they can be overly complex for users who simply want a fast, effective solution to encrypt files. This is where `scramble` comes in—offering a lightweight, command-line encryption tool that enables users to protect their data with minimal effort.

`scramble` enables users to encrypt files by employing several encryption techniques, including bitwise inversion, byte reversal, and hashing. This flexibility ensures that files can be encrypted using an algorithm that best suits the user’s security requirements. The program is designed to be accessible and easy to integrate into automated workflows, making it an ideal solution for individuals and organizations alike.

## Background

Today, encryption is a paramount tool for securing information. By rewriting readable data into an unreadable format, encryption ensures that only authorized users can access the original content. In particular, file encryption is essential for protecting data at rest—files that are stored on a computer or device and not actively being used.

`scramble` was developed as a lightweight command-line tool to provide a quick and easy way to encrypt files. It uses a range of basic encryption techniques to modify the content of the file, including:
* Bitwise Inversion: Inverts each bit in the file’s data, turning `0`s into `1`s and vice versa.
* Byte Reversal: Reverses the sequence of bytes in the file, scrambling the order of the content.
* Hashing: Hashes each byte, transforming the file into a randomized format.
* Splicing: Randomly inserts new bytes between the file’s original data, further obscuring the content.

These methods were chosen for their simplicity and speed, making `scramble` an accessible tool for users who need basic file protection. On the other hand, it is important to note that these techniques do not offer the same level of security as advanced cryptographic algorithms like AES (Advanced Encryption Standard) or RSA (Rivest–Shamir–Adleman Public-Key Cryptosystem) and should not be used for securing highly sensitive information. Scramble is best suited for non-critical files where ease of use and fast encryption are key priorities.

By offering multiple methods for scrambling data, `scramble` provides flexibility for users to choose the approach that best meets their needs. Whether it's obfuscating temporary files or providing a basic level of file encryption, `scramble` is designed to be a user-friendly tool for everyday encryption tasks.

## Understanding

TODO

## Specification

TODO
