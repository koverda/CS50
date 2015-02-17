#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char* lookup(const char* extension);

char extension[4] = "HTML";


int main(void)
{
    const char* type = lookup(extension);
    printf("%s\n", type);
    return 0;
}

const char* lookup(const char* extension)
{
    //make extension all lowercase
    char lowerCaseExtension[strlen(extension)];
    for(int i = 0; extension[i]; i++)
    {
        lowerCaseExtension[i] = tolower(extension[i]);
        lowerCaseExtension[i+1] = '\0';
    }
    
    //debug
    //printf("%s\n",lowerCaseExtension);
    
    // check if extension is any of the ones we care about
    if      (strcmp(lowerCaseExtension, "css" ) == 0) return "text/css";
    else if (strcmp(lowerCaseExtension, "html") == 0) return "text/html";
    else if (strcmp(lowerCaseExtension, "gif" ) == 0) return "image/gif";    
    else if (strcmp(lowerCaseExtension, "ico" ) == 0) return "image/x-icon";
    else if (strcmp(lowerCaseExtension, "jpg" ) == 0) return "image/jpeg";
    else if (strcmp(lowerCaseExtension, "js"  ) == 0) return "text/javascript";
    else if (strcmp(lowerCaseExtension, "png" ) == 0) return "image/png";
    
    // if not, return null
    else return NULL;
}
