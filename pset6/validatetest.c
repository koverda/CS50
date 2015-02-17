#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LimitRequestLine 8190

char line[LimitRequestLine] = "GET /request.target?q=hello HTTP/1.1\r\n";
char root[10] = "/root";
int main(void)
{
    // output request line
    printf("%s", line);
    
    // count number of spaces in request
    int len = strlen(line);
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        if (line[i] == ' ') 
        {
            count++;
        }
    }
    if (count != 2)
    {
        printf("error 400: bad request\n");
        return(400);
    }
    
    //find CRLF
    int found = 0;
    for (int i = 0; i < len; i++)
    {
        if (line[i] == '\r')
        {
            if (line[i + 1] == '\n')
            {
                found = 1;
            }
        }
    }
    if (found == 0)
    {
        printf("error 400: bad request\n");
        return(400);
    }
    
    
    // find location of first and last space in request
    char *ptr1 = strchr(line, ' ');
    int spc1 = ptr1 - line;
    char *ptr2 = strrchr(line, ' ');
    int spc2 = ptr2 - line;    
    //printf("%i\n", spc2 - spc1 - 1);
    
    
    // output request like UP TO first space (should be req method)
    char requestMethod[10] = "";
    strncpy(requestMethod, line, spc1);
    requestMethod[spc1] = '\0';
    //printf("%s\n", requestMethod);
    
    if (strcmp(requestMethod, "GET") != 0)
    {
        printf("405 Method Not Allowed\n");
        return(405);
    }
 
 
    // the code below validates the request target
    // and checks if it contains a query   
    char requestTarget[LimitRequestLine] = "";
    
    //copy only request target
    strncpy(requestTarget, ptr1 + 1, spc2 - spc1 - 1);
    //printf("requestTarget: %s\n", requestTarget);
    
    // make sure it starts with a slash
    if (requestTarget[0] != '/')
    {
        printf("501 Not Implemented\n");
        return(501);        
    }
    
    // make sure it doesn't have a double quote
    if (strchr(requestTarget, '"') != NULL)
    {
        printf("error 400: bad request\n");
        return(400);        
    }
    
    //check for query: "?"
    char *queryLoc = strchr(requestTarget, '?');
    char absolutePath[LimitRequestLine] = "";
    char query[LimitRequestLine] = "";
    int qLoc = queryLoc - requestTarget;
    
    //debug
    //printf("%i\n",qLoc);
    
    if (queryLoc != NULL)
    {
        // query exists
        // take stuff from before ? and make it the absoultePath
        strncpy(absolutePath, requestTarget, qLoc);
        // take stuff from after the ? and make it the query
        int rtLen = strlen(requestTarget);
        strncpy(query, queryLoc + 1, rtLen - qLoc + 1);
        
    }
    else
    {
        // query doesn't exist
        strcpy(absolutePath, requestTarget);
    }
       
    //establish absolute path 
    
    //check for "." in path
    if (strchr(absolutePath, '.') == NULL)
    {
        printf("Error 501 Not Implemented.\n");
        return(501);        
    }    
    
    /*debug
    printf("All Good\n");
    printf("requestTarget:%s\n",requestTarget);
    printf("absolutePath:%s\n",absolutePath);
    printf("query:%s\n",query);     */   
    
    
    char path[(strlen(absolutePath) + strlen(root))];
    strcpy(path, "");
    strcat(path, root);
    strcat(path, absolutePath);
    
    /*
    printf("root:%s\n",root);    
    printf("absolutePath:%s\n",absolutePath);    
    printf("path:%s\n",path);
    */
    
    // extract path's extension
    char *ptrPeriod = strrchr(path, '.');
    int periodLoc = ptrPeriod - path;
    char extension[255] = "";
    strncpy(extension, ptrPeriod + 1, strlen(path) - periodLoc + 1);
    extension[strlen(path) - periodLoc + 2] = '\0';
    printf("%s\n",extension);
}
