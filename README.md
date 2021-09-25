# Huffman-Coding

Huffman coding implemented by Alice Sartori: https://github.com/sartorialice

The program creates the Huffman coding of a .txt input file.

# Execution:
To execute the program with any input .txt file you must change the file name in the function 'openinput' in main.cpp with the name of the file you want to use.
If you want to change the output file it's the same process but you should change the filename in the 'openoutput' function.

The output file is not actually compressed, since every 0 and 1 inserted are encoded with 8 bits. 
The program prints the coding for every character present in the .txt on standard output during its execution.
It also evaluetes the entropy of the file and the expected length of the Huffman coding.
