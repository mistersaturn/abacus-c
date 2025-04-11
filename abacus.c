#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 256
#define INSTRUCTION_SIZE 4

int memory[MEMORY_SIZE] = {0}; // Memory array initialized to zero
int accumulator = 0; // Accumulator for arithmetic operations
int program_counter = 0; // Tracks the current instruction

// Function to load the program into memory
void load_program() {
    printf("\n\033[96;1;4m-- ABACUS C MACHINE --\n\033[0m");
    printf("\nENTER THE PROGRAM \033[93m[END WITH -1] ->\n\n\033[0m");
    int instruction;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (scanf("%d", &instruction) != 1) { // Check for valid input
            fprintf(stderr, "!!! -- INVALID INPUT. ENTER AN INTEGER.\n");
            exit(EXIT_FAILURE);
        }
        if (instruction == -1) break; // End input on -1
        if (i >= MEMORY_SIZE) {
            fprintf(stderr, "!!! -- MEMORY OVERFLOW. MAXIMUM INSTRUCTIONS REACHED.\n");
            exit(EXIT_FAILURE);
        }
        memory[i] = instruction; // Store instruction in memory
    }
}

// Function to execute a single instruction
void execute_instruction(int instruction) {
    int opcode = instruction / 100; // Extract opcode (first two digits)
    int operand = instruction % 100; // Extract operand (last two digits)

    if (operand < 0 || operand >= MEMORY_SIZE) { // Validate operand
        fprintf(stderr, "!!! -- INVALID OPERAND -> %d\n", operand);
        exit(EXIT_FAILURE);
    }

    switch (opcode) {
        case 1: // ADD
            accumulator += memory[operand]; // Add value from memory to accumulator
            break;
        case 2: // SUB
            accumulator -= memory[operand]; // Subtract value from memory from accumulator
            break;
        case 3: // STORE
            memory[operand] = accumulator; // Store accumulator value in memory
            break;
        case 4: // LOAD
            accumulator = memory[operand]; // Load value from memory into accumulator
            break;
        case 5: // JUMP
            program_counter = operand; // Set program counter to operand
            return;
        case 6: // JUMP IF ZERO
            if (accumulator == 0) program_counter = operand; // Jump if accumulator is zero
            return;
        case 7: // JUMP IF POSITIVE
            if (accumulator > 0) program_counter = operand; // Jump if accumulator is positive
            return;
        case 8: // INPUT
            printf("ENTER A NUMBER -> ");
            if (scanf("%d", &memory[operand]) != 1) { // Check for valid input
                fprintf(stderr, "!!! -- INVALID INPUT. ENTER AN INTEGER.\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 9: // OUTPUT
            printf("\n\033[92mOUTPUT -> %d\n\n\033[0m", memory[operand]); // Print value from memory
            break;
        case 0: // HALT
            exit(EXIT_SUCCESS); // Terminate the program gracefully
        default:
            fprintf(stderr, "!!! -- INVALID INSTRUCTION -> %d\n", instruction); // Error handling
            exit(EXIT_FAILURE);
    }
}

// Function to run the loaded program
void run() {
    while (1) {
        if (program_counter < 0 || program_counter >= MEMORY_SIZE) { // Validate program counter
            fprintf(stderr, "!!! -- PROGRAM COUNTER OUT OF BOUNDS -> %d\n", program_counter);
            exit(EXIT_FAILURE);
        }
        int instruction = memory[program_counter]; // Fetch instruction from memory
        execute_instruction(instruction); // Execute the fetched instruction
        program_counter++; // Move to the next instruction
    }
}

int main() {
    load_program(); // Load instructions into memory
    run(); // Start executing the loaded program
    return EXIT_SUCCESS; // Exit the program gracefully
}
