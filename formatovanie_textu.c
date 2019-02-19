#ifndef __PROGTEST__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#endif /* __PROGTEST__ */
 // This function  if  finds  two newlines then it  does nothing else if there are more  than two newlines  they are simply skipped
char *double_liner(char *str2) {
    int size = strlen(str2) + 3;
    int newlines = 0;
    int i = 0;
    char *pt_srt = NULL;
    char *str_output = (char *) calloc(size, sizeof(char));
    pt_srt = str_output;
    while (*str2) {
        str_output[i++] = *str2;
        ++str2;
        if (*str2 != '\n')newlines = 0;
        if (*str2 == '\n') {
            ++newlines;
        }
        if (newlines > 2)
            while (*str2 == '\n') {
                ++str2;
                if (*str2 != '\n')newlines = 0;
            }
    }
    return pt_srt;
}
 // All spaces are removed 
void squeeze_spaces(char *str) {
    char *dst, *dst2;
    int space = 1;
    dst = str;
    dst2 = str;
    while (*dst2) {
        if (space) {
            if (*dst2 != ' ') {
                *dst++ = *dst2;
                space = 0;
            }
        } else {
            *dst++ = *dst2;
            if (*dst2 == ' ')
                space = 1;
        }
        dst2++;
    }
    if (space && dst > str)
        dst--;
    *dst = 0;
}
 //If there  is  only one  newline  it  is replaced by space
void replace_one_newlines(char *str) {
    char *replacer = str;
    while (*replacer) {
        if (*replacer == '\n' && *++replacer != '\n') {
            *--replacer = ' ';
        }
        ++replacer;
    }
}
 // Tabs are replaced by space
void replace_whitespace(char *str) {
    char *replacer2 = str;
    while (*replacer2) {
        if (*replacer2 == '\t' )
            *replacer2 = ' ';
        ++replacer2;
    }
}

int formatter(char *str, int width) {
    char *er_str = str;
    int newline = 0;
    int oversize = 0;
    int counter = 0;
    while (*er_str) {
   // Dividing the  text to lines
        if (counter == width && (*er_str == ' ' || *er_str=='\n')) {
            *er_str = '\n';
            counter = 0;
        }
        if (counter == width && *er_str != ' ') {

//if there is a word  that exceeds the  width then the  pointer goes backwards  while  it  doesn't  find a white space 
            while (*er_str != ' ') {
                --er_str;
            // count  the number of characters till it gets a white space
                oversize++;
                if (oversize > width) return -1;
                if (*er_str == ' ')oversize = 0;
                if (*er_str == ' ' || *er_str == '\t' || *er_str == '\r' || *er_str == '\n' || *er_str == '\v') {
                    *er_str = '\n';
                    ++er_str;
                    counter = 0;
                    break;
                }
            }
        }
        if (*er_str == '\n') {
            ++er_str;
            ++newline;
            if (*er_str == '\n') {
                counter = 0;
                ++er_str;
            } else if (*er_str != '\n') {
                ++counter;
                ++er_str;
                newline = 0;
            }
            continue;
        }
        ++counter;
        ++er_str;
    }
    *er_str = '\n';
    ++er_str;
    *er_str = '\0';
    return 0;
}

char *wordWrap(int width, const char *src) {
    long long int size = 0;
    int input = 0;
    char *pt = NULL;
    size = strlen(src) + 3;
    char *str = (char *) calloc(size, sizeof(char));
    strcpy(str, src);
    if (size - 3 == 0) {
        *str = '\0';
        return str;
    }
    replace_whitespace(str);
    replace_one_newlines(str);
    squeeze_spaces(str);
    input = formatter(str, width);
    if (input == -1) {
        free(str);
        return NULL;
    }
    pt = double_liner(str);
    free(str);
    int l = strlen(pt);
    if (l > 0 && pt[l - 1] == '\n' && pt[l - 2] == '\n')
        pt[l - 1] = 0;
    char*pt_src=pt;
    while (*pt_src){
        printf("%c",*pt_src);
        ++pt_src;
    }
    return pt;
}

#ifndef __PROGTEST__

int main(void) {
    char *res;
    const char *s0 =
            "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus\n"
            "pede, pretium vitae, rhoncus et, auctor sit amet, ligula. Integer volutpat\n"
            "orci et elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus\n"
            "lectus, vitae feugiat purus orci ultricies turpis. Pellentesque habitant\n"
            "morbi tristique senectus et netus et malesuada fames ac turpis egestas. Nam\n"
            "in pede. Etiam eu sem id urna ultricies congue. Vestibulum porttitor\n"
            "ultrices neque. Mauris semper, mauris ut feugiat ultricies, augue purus\n"
            "tincidunt  elit, eu interdum ante nisl ac ante. Pellentesque dui. Vestibulum\n"
            "pretium, augue non cursus pretium, nibh dolor laoreet leo, sed pharetra pede\n"
            "libero non diam.";
    const char *s1 =
            "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus\n"
            "pede, pretium vitae, rhoncus et, auctor sit amet, ligula. Integer volutpat\n"
            "orci et elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus\n"
            "lectus, vitae feugiat purus orci ultricies turpis. Pellentesque habitant\n"
            "morbi tristique senectus et netus et malesuada fames ac turpis egestas. Nam\n"
            "in pede. Etiam eu sem id urna ultricies congue. Vestibulum porttitor\n"
            "ultrices neque. Mauris semper, mauris ut feugiat ultricies, augue purus\n"
            "tincidunt  elit, eu interdum ante nisl ac ante. Pellentesque dui. Vestibulum\n"
            "pretium, augue non cursus pretium, nibh\tdolor laoreet leo, sed pharetra pede\n"
            "libero non diam.\n"
            "\n"
            "Proin est nisi,                     gravida ac, vulputate id, fringilla sit\n"
            "amet, magna. Nam congue cursus magna. In malesuada, velit a gravida sodales,\n"
            "dolor nisl vestibulum orci, sit amet sagittis mauris tellus nec purus. Nulla\n"
            "eget risus. Quisque nec sapien blandit odio convallis ullamcorper. Lorem\n"
            "ipsum dolor sit amet, consectetuer adipiscing elit. Pellentesque cursus.\n"
            "Aliquam tempus neque vitae libero molestie ut auctor.\n"
            "\n"
            "\n"
            "\n"
            "In nec massa eu tortor vulputate suscipit.\tNam tristique magna nec pede. Sed\n"
            "a nisi. Nulla sed augue ut risus placerat porttitor. Ut aliquam. Nulla\n"
            "facilisi. Nulla vehicula nibh ac sapien. Nunc facilisis dapibus ipsum. Donec\n"
            "sed mauris. Nulla quam nisi, laoreet non, dignissim posuere, lacinia nec,\n"
            "turpis. Mauris malesuada nisi sed enim. In hac habitasse platea dictumst.\n"
            "Fusce    faucibus, turpis nec auctor posuere, nulla tellus scelerisque metus,\n"
            "quis molestie mi dui id quam. Mauris vestibulum. Nam ullamcorper.\n"
            "\n";
    

    res = wordWrap(40, s0);
    assert (!strcmp(res,
                    "Lorem ipsum dolor sit amet, consectetuer\n"
                    "adipiscing elit. Integer metus pede,\n"
                    "pretium vitae, rhoncus et, auctor sit\n"
                    "amet, ligula. Integer volutpat orci et\n"
                    "elit. Nunc tempus, urna at sollicitudin\n"
                    "rutrum, arcu libero rhoncus lectus,\n"
                    "vitae feugiat purus orci ultricies\n"
                    "turpis. Pellentesque habitant morbi\n"
                    "tristique senectus et netus et malesuada\n"
                    "fames ac turpis egestas. Nam in pede.\n"
                    "Etiam eu sem id urna ultricies congue.\n"
                    "Vestibulum porttitor ultrices neque.\n"
                    "Mauris semper, mauris ut feugiat\n"
                    "ultricies, augue purus tincidunt elit,\n"
                    "eu interdum ante nisl ac ante.\n"
                    "Pellentesque dui. Vestibulum pretium,\n"
                    "augue non cursus pretium, nibh dolor\n"
                    "laoreet leo, sed pharetra pede libero\n"
                    "non diam.\n"));
    free(res);

    res = wordWrap(120, s0);
    assert (!strcmp(res,
                    "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus pede, pretium vitae, rhoncus et, auctor sit\n"
                    "amet, ligula. Integer volutpat orci et elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus lectus, vitae\n"
                    "feugiat purus orci ultricies turpis. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac\n"
                    "turpis egestas. Nam in pede. Etiam eu sem id urna ultricies congue. Vestibulum porttitor ultrices neque. Mauris semper,\n"
                    "mauris ut feugiat ultricies, augue purus tincidunt elit, eu interdum ante nisl ac ante. Pellentesque dui. Vestibulum\n"
                    "pretium, augue non cursus pretium, nibh dolor laoreet leo, sed pharetra pede libero non diam.\n"));
    free(res);

    res = wordWrap(10, s1);
    assert (res == NULL);

    res = wordWrap(40, s1);
    assert (!strcmp(res,
                    "Lorem ipsum dolor sit amet, consectetuer\n"
                    "adipiscing elit. Integer metus pede,\n"
                    "pretium vitae, rhoncus et, auctor sit\n"
                    "amet, ligula. Integer volutpat orci et\n"
                    "elit. Nunc tempus, urna at sollicitudin\n"
                    "rutrum, arcu libero rhoncus lectus,\n"
                    "vitae feugiat purus orci ultricies\n"
                    "turpis. Pellentesque habitant morbi\n"
                    "tristique senectus et netus et malesuada\n"
                    "fames ac turpis egestas. Nam in pede.\n"
                    "Etiam eu sem id urna ultricies congue.\n"
                    "Vestibulum porttitor ultrices neque.\n"
                    "Mauris semper, mauris ut feugiat\n"
                    "ultricies, augue purus tincidunt elit,\n"
                    "eu interdum ante nisl ac ante.\n"
                    "Pellentesque dui. Vestibulum pretium,\n"
                    "augue non cursus pretium, nibh dolor\n"
                    "laoreet leo, sed pharetra pede libero\n"
                    "non diam.\n"
                    "\n"
                    "Proin est nisi, gravida ac, vulputate\n"
                    "id, fringilla sit amet, magna. Nam\n"
                    "congue cursus magna. In malesuada, velit\n"
                    "a gravida sodales, dolor nisl vestibulum\n"
                    "orci, sit amet sagittis mauris tellus\n"
                    "nec purus. Nulla eget risus. Quisque nec\n"
                    "sapien blandit odio convallis\n"
                    "ullamcorper. Lorem ipsum dolor sit amet,\n"
                    "consectetuer adipiscing elit.\n"
                    "Pellentesque cursus. Aliquam tempus\n"
                    "neque vitae libero molestie ut auctor.\n"
                    "\n"
                    "In nec massa eu tortor vulputate\n"
                    "suscipit. Nam tristique magna nec pede.\n"
                    "Sed a nisi. Nulla sed augue ut risus\n"
                    "placerat porttitor. Ut aliquam. Nulla\n"
                    "facilisi. Nulla vehicula nibh ac sapien.\n"
                    "Nunc facilisis dapibus ipsum. Donec sed\n"
                    "mauris. Nulla quam nisi, laoreet non,\n"
                    "dignissim posuere, lacinia nec, turpis.\n"
                    "Mauris malesuada nisi sed enim. In hac\n"
                    "habitasse platea dictumst. Fusce\n"
                    "faucibus, turpis nec auctor posuere,\n"
                    "nulla tellus scelerisque metus, quis\n"
                    "molestie mi dui id quam. Mauris\n"
                    "vestibulum. Nam ullamcorper.\n"));
    free(res);

    res = wordWrap(80, s1);
    assert (!strcmp(res,
                    "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus pede,\n"
                    "pretium vitae, rhoncus et, auctor sit amet, ligula. Integer volutpat orci et\n"
                    "elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus lectus,\n"
                    "vitae feugiat purus orci ultricies turpis. Pellentesque habitant morbi tristique\n"
                    "senectus et netus et malesuada fames ac turpis egestas. Nam in pede. Etiam eu\n"
                    "sem id urna ultricies congue. Vestibulum porttitor ultrices neque. Mauris\n"
                    "semper, mauris ut feugiat ultricies, augue purus tincidunt elit, eu interdum\n"
                    "ante nisl ac ante. Pellentesque dui. Vestibulum pretium, augue non cursus\n"
                    "pretium, nibh dolor laoreet leo, sed pharetra pede libero non diam.\n"
                    "\n"
                    "Proin est nisi, gravida ac, vulputate id, fringilla sit amet, magna. Nam congue\n"
                    "cursus magna. In malesuada, velit a gravida sodales, dolor nisl vestibulum orci,\n"
                    "sit amet sagittis mauris tellus nec purus. Nulla eget risus. Quisque nec sapien\n"
                    "blandit odio convallis ullamcorper. Lorem ipsum dolor sit amet, consectetuer\n"
                    "adipiscing elit. Pellentesque cursus. Aliquam tempus neque vitae libero molestie\n"
                    "ut auctor.\n"
                    "\n"
                    "In nec massa eu tortor vulputate suscipit. Nam tristique magna nec pede. Sed a\n"
                    "nisi. Nulla sed augue ut risus placerat porttitor. Ut aliquam. Nulla facilisi.\n"
                    "Nulla vehicula nibh ac sapien. Nunc facilisis dapibus ipsum. Donec sed mauris.\n"
                    "Nulla quam nisi, laoreet non, dignissim posuere, lacinia nec, turpis. Mauris\n"
                    "malesuada nisi sed enim. In hac habitasse platea dictumst. Fusce faucibus,\n"
                    "turpis nec auctor posuere, nulla tellus scelerisque metus, quis molestie mi dui\n"
                    "id quam. Mauris vestibulum. Nam ullamcorper.\n"));
    free(res);



    return 0;
}

#endif /* __PROGTEST__ */
