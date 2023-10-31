#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <string.h>

void print_elf_header_info(Elf64_Ehdr *header);

int main(int argc, char *argv[]) {
    int fd;
    Elf64_Ehdr header;

    if (argc != 2) {
        dprintf(2, "Usage: elf_header elf_filename\n");
        return 98;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        dprintf(2, "Error: Can't open file %s\n", argv[1]);
        return 98;
    }

    if (read(fd, &header, sizeof(header)) != sizeof(header)) {
        dprintf(2, "Error: Can't read from file %s\n", argv[1]);
        return 98;
    }

    if (memcmp(header.e_ident, ELFMAG, SELFMAG) != 0) {
        dprintf(2, "Error: Not an ELF file\n");
        return 98;
    }

    print_elf_header_info(&header);

    close(fd);
    return 0;
}

void print_elf_header_info(Elf64_Ehdr *header) {
    printf("Magic: ");
    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x ", header->e_ident[i]);
    }
    printf("\n");
    
    printf("Class: %d-bit\n", (header->e_ident[EI_CLASS] == ELFCLASS64) ? 64 : 32);
    printf("Data: 2's complement, %s\n", (header->e_ident[EI_DATA] == ELFDATA2LSB) ? "little endian" : "big endian");
    printf("Version: %d (current)\n", header->e_ident[EI_VERSION]);
    printf("OS/ABI: %d\n", header->e_ident[EI_OSABI]);
    printf("ABI Version: %d\n", header->e_ident[EI_ABIVERSION]);
    printf("Type: 0x%x\n", header->e_type);
    printf("Entry point address: 0x%lx\n", (unsigned long)header->e_entry);
}
