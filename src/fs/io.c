#include "io.h"

size_t get_file_size(FILE *stream)
{
    fseek(stream, 0, SEEK_END);
    size_t file_size = ftell(stream);
    rewind(stream);

    return file_size;
}

File *read_file(const char *path, MimeType mime_type)
{
    File *file = read_from_disk(path, is_text_file(mime_type));
    
    if (is_text_file(mime_type))
    {
        file->content[file->size] = '\0';
    }

    file->mime_type = mime_type;
    return file;
}

File *read_from_disk(const char *path, bool is_text)
{
    FILE *stream = fopen(path, is_text ? "r" : "rb");
    if (!stream)
    {
        panic("Failed to open file '%s'", path);
    }

    size_t file_size = get_file_size(stream);
    char *content = malloc(file_size + (is_text ? 1 : 0));

    if (!content)
    {
        fclose(stream);
        panic("Allocation for content failed");
    }

    fseek(stream, 0, SEEK_SET);
    size_t bytes_read = fread(content, 1, file_size, stream);

    if (bytes_read != file_size)
    {
        free(content);
        fclose(stream);
        panic("Failed to read full file '%s'", path);
    }

    fclose(stream);

    
    File *file = malloc(sizeof(File));
    file->content = content;
    file->size = file_size;
    
    char *base = strrchr(path, '/');
    file->name = strdup(base ? base + 1 : path);
    
    
    return file;
}