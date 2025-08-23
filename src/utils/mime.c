#include "utils.h"

const char *mime_to_str(MimeType type)
{
    switch (type)
    {
    case TEXT_HTML:
        return "text/html";
    case TEXT_CSS:
        return "text/css";
    case TEXT_PLAIN:
        return "text/plain";
    case APP_JSON:
        return "application/json";
    case APP_JS:
        return "application/javascript";
    case IMG_PNG:
        return "image/png";
    case IMG_JPEG:
        return "image/jpeg";
    case IMG_GIF:
        return "image/gif";
    case IMG_SVG:
        return "image/svg+xml";
    case AUDIO_MPEG:
        return "audio/mpeg";
    case VIDEO_MP4:
        return "video/mp4";
    default:
        return "application/octet-stream"; // fallback
    }
}

MimeType mime_from_string(char *mime_str)
{
    if (!mime_str)
        return UNKNOWN_MIME;

    if (strcasecmp(mime_str, "text/html") == 0)
        return TEXT_HTML;
    if (strcasecmp(mime_str, "text/css") == 0)
        return TEXT_CSS;
    if (strcasecmp(mime_str, "text/plain") == 0)
        return TEXT_PLAIN;
    if (strcasecmp(mime_str, "application/json") == 0)
        return APP_JSON;
    if (strcasecmp(mime_str, "application/javascript") == 0 ||
        strcasecmp(mime_str, "text/javascript") == 0)
        return APP_JS; // handle old MIME type
    if (strcasecmp(mime_str, "image/png") == 0)
        return IMG_PNG;
    if (strcasecmp(mime_str, "image/jpeg") == 0 ||
        strcasecmp(mime_str, "image/jpg") == 0)
        return IMG_JPEG;
    if (strcasecmp(mime_str, "image/gif") == 0)
        return IMG_GIF;
    if (strcasecmp(mime_str, "image/svg+xml") == 0)
        return IMG_SVG;
    if (strcasecmp(mime_str, "audio/mpeg") == 0)
        return AUDIO_MPEG;
    if (strcasecmp(mime_str, "video/mp4") == 0)
        return VIDEO_MP4;

    return UNKNOWN_MIME;
}

char *get_file_extension(char *filename)
{
    if (!filename)
        return NULL;

    char *dot = strrchr(filename, '.');
    if (!dot || dot == filename)
        return NULL;

    return dot + 1;
}

MimeType get_mime_type(char *filename)
{
    char *ext = get_file_extension(filename);

    if (!ext)
        return UNKNOWN_MIME;

    if (ext[0] == '.')
        ext++;

    if (strcasecmp(ext, "html") == 0 || strcasecmp(ext, "htm") == 0)
        return TEXT_HTML;
    if (strcasecmp(ext, "css") == 0)
        return TEXT_CSS;
    if (strcasecmp(ext, "txt") == 0)
        return TEXT_PLAIN;
    if (strcasecmp(ext, "json") == 0)
        return APP_JSON;
    if (strcasecmp(ext, "js") == 0 || strcasecmp(ext, "mjs") == 0)
        return APP_JS;
    if (strcasecmp(ext, "png") == 0)
        return IMG_PNG;
    if (strcasecmp(ext, "jpg") == 0 || strcasecmp(ext, "jpeg") == 0)
        return IMG_JPEG;
    if (strcasecmp(ext, "gif") == 0)
        return IMG_GIF;
    if (strcasecmp(ext, "svg") == 0)
        return IMG_SVG;
    if (strcasecmp(ext, "mp3") == 0)
        return AUDIO_MPEG;
    if (strcasecmp(ext, "mp4") == 0)
        return VIDEO_MP4;

    return UNKNOWN_MIME;
}


bool is_text_file(MimeType mime_type)
{
    return mime_type <= APP_JS;
}