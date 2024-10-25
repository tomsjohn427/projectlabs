#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char opcode[10], operand[10], label[10], ch;
    char mnemonic[10][10] = {"START", "LDA", "STA", "LDCH", "STCH", "END"};
    int locctr = 0, start = 0, len = 0, i = 0;
    FILE *fp1, *fp2, *fp3, *fp4;

    // Open files with error checking
    fp1 = fopen("INPUT.DAT", "r");
    if (fp1 == NULL) {
        printf("Error opening INPUT.DAT\n");
        return 1;
    }
    fp2 = fopen("SYMTAB.DAT", "w");
    if (fp2 == NULL) {
        printf("Error opening SYMTAB.DAT\n");
        fclose(fp1);
        return 1;
    }
    fp3 = fopen("OUT.DAT", "w");
    if (fp3 == NULL) {
        printf("Error opening OUT.DAT\n");
        fclose(fp1);
        fclose(fp2);
        return 1;
    }

    // Read first line of the input file
    if (fscanf(fp1, "%s%s%s", label, opcode, operand) != 3) {
        printf("Error reading from INPUT.DAT\n");
        fclose(fp1);
        fclose(fp2);
        fclose(fp3);
        return 1;
    }

    // Handle START opcode
    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);  // Convert operand to integer (starting address)
        locctr = start;
        fprintf(fp3, "%s\t%s\t%s\n", label, opcode, operand);  // Write the first line to output file
        if (fscanf(fp1, "%s%s%s", label, opcode, operand) != 3) {
            printf("Error reading from INPUT.DAT\n");
            fclose(fp1);
            fclose(fp2);
            fclose(fp3);
            return 1;
        }
    } else {
        locctr = 0;  // Default start location
    }

    // Process each line until END opcode is encountered
    while (strcmp(opcode, "END") != 0) {
        fprintf(fp3, "%d\t", locctr);  // Print the current location counter to the output file

        if (strcmp(label, "**") != 0) {
            fprintf(fp2, "%s\t%d\n", label, locctr);  // Write label and locctr to SYMTAB if label is not "**"
        }

        // Check if opcode matches any mnemonic and update locctr accordingly
        int found = 0;
        for (i = 0; i < 5; i++) {  // Check against the 5 mnemonics
            if (strcmp(opcode, mnemonic[i]) == 0) {
                locctr += 3;  // All these opcodes are assumed to be of length 3
                found = 1;
                break;
            }
        }

        if (!found) {
            // Handle other directives: WORD, RESW, RESB, BYTE
            if (strcmp(opcode, "WORD") == 0) {
                locctr += 3;
            } else if (strcmp(opcode, "RESW") == 0) {
                locctr += 3 * atoi(operand);  // Reserve words (3 bytes each)
            } else if (strcmp(opcode, "RESB") == 0) {
                locctr += atoi(operand);  // Reserve bytes
            } else if (strcmp(opcode, "BYTE") == 0) {
                locctr += 1;  // Byte uses 1 byte
            }
        }

        // Write the current line to the output file
        fprintf(fp3, "%s\t%s\t%s\n", label, opcode, operand);

        // Read the next line
        if (fscanf(fp1, "%s%s%s", label, opcode, operand) != 3) {
            printf("Error reading from INPUT.DAT\n");
            fclose(fp1);
            fclose(fp2);
            fclose(fp3);
            return 1;
        }
    }

    // Write the END line to the output file
    fprintf(fp3, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    // Close the files
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    // Print the contents of the input, output, and symbol table files

    // Print INPUT.DAT
    printf("\n\nThe contents of Input Table:\n\n");
    fp1 = fopen("INPUT.DAT", "r");
    if (fp1 != NULL) {
        while ((ch = fgetc(fp1)) != EOF) {
            putchar(ch);
        }
        fclose(fp1);
    }
    
    // Print OPTAB.DAT
    printf("\n\nThe contents of Opcode Table:\n\n");
    fp4 = fopen("OPTAB.DAT", "r");
    if (fp4 != NULL) {
        while ((ch = fgetc(fp4)) != EOF) {
            putchar(ch);
        }
        fclose(fp4);
    }

    // Print OUT.DAT
    printf("\n\nThe contents of Output Table:\n\n");
    fp3 = fopen("OUT.DAT", "r");
    if (fp3 != NULL) {
        while ((ch = fgetc(fp3)) != EOF) {
            putchar(ch);
        }
        fclose(fp3);
    }

    // Print SYMTAB.DAT
    printf("\n\nThe contents of Symbol Table:\n\n");
    fp2 = fopen("SYMTAB.DAT", "r");
    if (fp2 != NULL) {
        while ((ch = fgetc(fp2)) != EOF) {
            putchar(ch);
        }
        fclose(fp2);
    }

    // Calculate and print the length of the program
    len = locctr - start;
    printf("\nThe length of the program is %d.\n\n", len);

    return 0;
}

