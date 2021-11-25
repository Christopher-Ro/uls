#include "uls.h"

bool mx_printfiles(t_list *dirs, char *flags)
{
    DIR *curr;
    char *buf_long;
    t_list *to_print = NULL;
    int block_counter = 0;
    bool has_files = false;
    while (dirs)
    {
        if (!dirs->data)
        {
            dirs = dirs->next;
            continue;
        }
        curr = opendir(dirs->data);
        if (curr == NULL && errno == ENOTDIR)
        {
            // TODO: define func for print colums
            has_files = true;
            errno = 0;
            if (!mx_strchr(flags, 'l'))
            {
                // mx_printstr(dirs->data);
                // if (dirs->next && is_terminal)
                //     mx_printchar('\t');
                // else if (dirs->next && !is_terminal)
                //     mx_printchar('\n');

                mx_push_back(&to_print, mx_strdup(dirs->data));
            }
            else
            {
                buf_long = mx_list_file_long(dirs->data, &block_counter);
                mx_printstr(buf_long);
                mx_printchar('\n');
                mx_strdel(&buf_long);
            }
            dirs->data = NULL;
        }
        dirs = dirs->next;
    }
    if (has_files)
    {
        mx_col_print(to_print);
        mx_del_list(&to_print);
    }
    return has_files;
}
