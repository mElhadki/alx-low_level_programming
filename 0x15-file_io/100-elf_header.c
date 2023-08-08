#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct {
    uint8_t magic[4];
    uint8_t class;
    uint8_t data;
    uint8_t version;
    uint8_t abi;
    uint8_t abi_version;
    uint8_t padding[7];
    uint16_t type;
    uint16_t machine;
    uint32_t version2;
    uint64_t entry;
} ElfHeader;

void print_error(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(98);
}

void print_elf_header(const ElfHeader *header) {
    printf("ELF Header:\n");
    printf("  Magic:   %02x %02x %02x %02x\n",
           header->magic[0], header->magic[1],
           header->magic[2], header->magic[3]);
    printf("  Class:                             %s\n",
           header->class == 1 ? "ELF32" : (header->class == 2 ? "ELF64" : "Unknown"));
    printf("  Data:                              %s\n",
           header->data == 1 ? "2's complement, little endian" : "Unknown");
    printf("  Version:                           %d (current)\n", header->version);
    printf("  OS/ABI:                            ");
    switch (header->abi) {
        case 0: printf("UNIX - System V\n"); break;
        case 3: printf("UNIX - NetBSD\n"); break;
        case 6: printf("UNIX - Solaris\n"); break;
        default: printf("<unknown: %d>\n", header->abi); break;
    }
    printf("  ABI Version:                       %d\n", header->abi_version);
    printf("  Type:                              ");
    switch (header->type) {
        case 1: printf("REL (Relocatable file)\n"); break;
        case 2: printf("EXEC (Executable file)\n"); break;
        case 3: printf("DYN (Shared object file)\n"); break;
        default: printf("Unknown\n"); break;
    }
    printf("  Entry point address:               0x%lx\n", header->entry);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_error("Usage: elf_header elf_filename");
    }

    const char *filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        print_error("Failed to open file");
    }

    ElfHeader header;
    if (read(fd, &header, sizeof(header)) != sizeof(header)) {
        close(fd);
        print_error("Failed to read ELF header");
    }

    if (header.magic[0] != 0x7f || header.magic[1] != 'E' || header.magic[2] != 'L' || header.magic[3] != 'F') {
        close(fd);
        print_error("Not an ELF file");
    }

    print_elf_header(&header);

    close(fd);
    return 0;
}

