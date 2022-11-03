#include "WebUploadServlet.hpp"
#include <fstream>

void WebUploadServlet::doGet(int sock, ServletRequest request, ServletResponse response) {
    int rval;
    string resString = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-length: 513\r\n\r\n <!DOCTYPE html>\r\n<html>\n   <head>\n       <title>File Upload Form</title>\n   </head>\n   <body>\n       <h1>Upload file</h1>\n       <form method=\"POST\" action=\"upload\" enctype=\"multipart/form-data\">\n           <input type=\"file\" name=\"fileName\"/><br/><br/>\n           Caption: <input type=\"text\" name=\"caption\"<br/><br/><br/>\n           Date: <input type=\"date\" name=\"date\"<br/><br/><br/>\n           <input type=\"submit\" value=\"Submit\"/>\n       </form>\n   </body>\n</html>\r\n\r\n";
    char res[resString.length() + 1];
    strcpy(res, resString.c_str());

    if ((rval = write(sock, res, strlen(res))) < 0){
        perror("writing socket");
    }else  {
        printf("%s\n",res);
    }

    close (sock);
    return;
}

void WebUploadServlet::doPost(int sock, ServletRequest request, ServletResponse response) {
    int rval;
    string resString = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html>\r\n<html>\n   <head>\n       <title>File Upload Form</title>\n   </head>\n   <body>\n       <h3>File Uploaded: "
            + request.getFileName() + ", " + request.getCaption() + ", " + request.getDate() + "</h3>\n </body>\n</html>\r\n\r\n";

    ofstream fout;
    fout.open("images/" + request.getFileName(), ios::binary | ios::out);
    unsigned char *image = request.getFileByte();

    fout.write((char *)&image[0], request.getFileSize());
    fout.close();

    char res[resString.length() + 1];
    strcpy(res, resString.c_str());

    if ((rval = write(sock, res, strlen(res))) < 0){
        perror("writing socket");
    }else  {
        printf("%s\n",res);
    }

    close (sock);
    return;
}