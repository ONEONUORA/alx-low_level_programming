#include "main.h"

/**
 * create_file - Creates a file and writes text content to it.
 * @filename: The name of the file to create.
 * @text_content: The text content to write to the file.
 *
 * Return: 1 on success, -1 on failure.
 */
int create_file(const char *filename, char *text_content)
{
    int file_d, lenw;
    
    if (filename == NULL)
        return (-1);

    file_d = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    
    if (file_d == -1)
        return (-1);

    if (text_content != NULL)
    {
        lenw = write(file_d, text_content, _strlen(text_content));

        if (lenw == -1 || (size_t)lenw != (size_t)_strlen(text_content))
        {
            close(file_d);
            return (-1);
        }
    }

    close(file_d);
    return (1);
}

