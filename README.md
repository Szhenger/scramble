# Scramble
#### Video Demo:  [Scramble](https://youtu.be/KNZfhI4DNzo)
#### Description:
Hello, World! In the modern era, computers are foundational to how society operates at large; however, these electronics are only so pervasive because what of infomation is stored and operated on device. This presents risks and costs to individuals, but benefits and rewards to adversaries by enabling the theft of infomation at global distances. Today, we have protocols in place to better secure our infomation whether in hopes of preventing theft or making the theft moot by encrpting the infomation. A common method is scrambling the infomation stored within memory or drive, so that opening the file requires decrypting the infomation with a key stored securely by the individual. This command-line program using C scrambles the contents of the input file by inverting the bytes or reversing the order of bytes or hashing the bytes or splice bytes within the input file. Note that the input file will be modified with the command-line program; however, by running any even parity sequence of runs on the input file will return the file to the original state of the file for the first two encryption algorithms.
#### Specification:
scramble.c (in src folder) is the source code file written in C that algorithmically encrypts source files by running a main procedure on the source file that calls an encryption subprocedure to read and write the encrypted contents of the original source file into an empty cipher file:

main is the procedure written that scrambles the contents of a source file. In particular, the procedure opens the source file and the empty cipher file and encrypts the contents of the source file by calling an encryption algorithm to read and write the encrypted contents to the cipher file, removes the original source file, and renames the cipher file to the pathname of the original source file. With respect to design for space and time complexity, the procedure was designed prior to algorthmically change the source file in-place; however, that design presented a program that depended on the operating system for which the program ran for intended performance, so this implementation was constructed for portability sake.

invert is an algorithm that inverts each byte in the source file. In the context of the C implentation, the algorithm takes an input file and output file to read and write to respectively by loading the contents of the input file into a buffer and operating on the buffer allocation and taking the one's complement of each byte iteratively, and writing the results to the output file. With respect to the design of the algorithm, the code is written so that proving the correctness is clear by induction i.e. iteratively inverts each bit in every byte of the file. Considering this is how the algorithm is implemented for the sake of clear logic, the time complexity is linear e.g. the running time of each instance is proportional to the size of the input; however, this is to be expect since a file in typical operating systems are represented as static arrays of bytes and so to iteratively output the file requires worst-case linear time.

reverse is an algorithm that reverses the ordering of bytes in the source file. In particular, the algorithm takes an input file and output file to read and write to respectively by reading hte input file bytewise into the buffer and writing directly into the output file. In other words, the algorithm iteratively reads each byte starting from the end of the input file into memory to append to the beginning of the output file; hence, we can easily argue correctness by induction for each iteration reverses the input by a constant size and obtain that it runs in linear-time. It is worthnoting that the initial design of the reverse algorithm was written in-place so that we could obtain a sub-linear running time; however, universality to all operating systems becomes an issue as some operating systems do not implement every C function the same via systems call meaning this destructive write i.e. overwriting the file with iterating through the file could lead to segmentation faults. Another way would be to make a copy of the input file and overwrite the copy while preserving that original source file; however, this would incurr at least linear-time because we need to make and fill the new copy of the file.

hash is an algorithm that hashes bytes to integers in the source file. In the lieu of the program, the algorithm takes the same arguments as listing in the encryption algorithms above; however, hashes bytes to other bytes using a random integer. This technique adds a randomization element to the encoding; hence, making the encryption stronger for the output will provide the integer key to decrypt the text only at the terminal. Similarly, we have written the algorithm iteratively to argue correctness at the expense of efficency; however, that this to be expected since every byte in the input file must be read for hashing to be done, so the bigger issue is choice of hash function. Since bytes are sequences of 8 bits (typicaaly, except for some bizzare instructions) i.e. only 256 distinct permuatations, the output space cannot be reduced; otherwise, at the risk of security. For the sake of correctness, I have elected to use a random division method hash; however, this function can be changed at any point within the source code for any partciular encoding.

splice is an algorithm that splices random bytes into the source file to obsecure the contents of the source file. This technique ensures that decrypting is easy for the intended users, but difficult for other users. From the source code, we can see that the splicing occurs at every odd index in the file array i.e. tho sufficient obsecure the contents a sequence of splices is preferred. Similarly, the algorithm is written iterative for the ease of proving correctness; however, we note that any other design of this algorithm still incurs worst-case linear time for the simple reason that each insertion is done per byte in the input file.

errors handling is emphasized in the design of the program, so the messages printed to the terminal are detailed with explainations as which procedure the program encounter an exception if at all. 
