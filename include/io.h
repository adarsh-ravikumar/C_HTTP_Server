#pragma once
#include "common.h"

size_t get_file_size(FILE *stream);
File *read_file(const char *path, MimeType mime_type);
File *read_from_disk(const char *path, bool is_text);
