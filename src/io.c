#include "io.h"

size_t get_file_size(FILE *stream)
{
    fseek(stream, 0, SEEK_END);
    size_t file_size = ftell(stream);
    rewind(stream);

    return file_size;
}

File *read_file(const char *path)
{
    FILE *stream = fopen(path, "r");
    if (!stream)
    {
        panic("Failed to open file '%s'", path);
    }

    File *file = (File *)malloc(sizeof(File));
    if (!file)
    {
        fclose(stream);
        panic("Allocation for 'struct File' failed");
    }

    file->size = get_file_size(stream);
    file->content = (char *)malloc(file->size + 1);

    if (!file->content)
    {
        fclose(stream);
        panic("Allocation for 'file content' failed");
    }

    size_t bytes_read = fread(file->content, 1, file->size, stream);
    file->content[bytes_read] = '\0';

    fclose(stream);
    return file;
}