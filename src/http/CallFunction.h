//
// Created by ddd on 3/10/23.
//

#ifndef LIBDD_CALLFUNCTION_H
#define LIBDD_CALLFUNCTION_H

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include <fstream>

#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpServer.h"
#include "Logging.h"
#include "Timestamp.h"

char* openAndMmap(const std::string& path) {
  auto fd = open(path.c_str(), O_RDONLY);
  if (fd < 0) {
    LOG_WARN << "未找到文件：" << path;
    return (char*)"Error! Can't find the file";
  }
  auto size = lseek(fd, 0, SEEK_END);
  return (char*)mmap(nullptr, size, PROT_READ, MAP_PRIVATE, fd, 0);
}

void defaultFunction(const HttpRequest& req, HttpResponse* resp) {
  resp->setStatusCode(HttpResponse::k200Ok);
  resp->setStatusMessage("OK");
  resp->setContentType("text/html");
  resp->addHeader("Server", "Muduo");
  std::string now = Timestamp::now().toFormattedString();
  resp->setBody(
      "<html><head><title>This is title</title></head>"
      "<body><h1>Hello</h1>Now is " +
      now + "</body></html>");
}

void htmlFunction(const HttpRequest& req, HttpResponse* resp) {
  auto path = req.path().substr(1, req.path().size() - 1);
  //  path.append(".html");
  auto data = openAndMmap(path);
  resp->setStatusCode(HttpResponse::k200Ok);
  resp->setStatusMessage("OK");
  resp->setContentType("text/html");
  resp->addHeader("Server", "Muduo");
  resp->setBody(data);
}

void pictureFunction(const HttpRequest& req, HttpResponse* resp) {
  auto path = req.path().substr(1, req.path().size() - 1);
  //  path.append(".jpg");
  struct stat statbuf {};
  stat(path.data(), &statbuf);
  auto filesize = statbuf.st_size;
  auto data = openAndMmap(path);
  //  auto in = open(path.c_str(), O_LARGEFILE);
  //  char* buffer = new char[filesize];
  //  read(in, buffer, filesize);
  resp->setStatusCode(HttpResponse::k200Ok);
  resp->setStatusMessage("OK");
  resp->setContentType("image/jpeg");
  resp->addHeader("Server", "Muduo");
  resp->setBody(std::string(data, filesize));
}

void textFunction(const HttpRequest& req, HttpResponse* resp) {
  resp->setStatusCode(HttpResponse::k200Ok);
  resp->setStatusMessage("OK");
  resp->setContentType("text/html");
  resp->addHeader("Server", "Muduo");
  std::string now = Timestamp::now().toFormattedString();
  resp->setBody("textFunction");
}

void largeFileFunction(const HttpRequest& req, HttpResponse* resp) {
  resp->setStatusCode(HttpResponse::k200Ok);
  resp->setStatusMessage("OK");
  resp->setContentType("text/html");
  resp->addHeader("Server", "Muduo");
  std::string now = Timestamp::now().toFormattedString();
  resp->setBody("textFunction");
}

void exceptionFunction(const HttpRequest& req, HttpResponse* resp) {
  resp->setStatusCode(HttpResponse::k404NotFound);
  resp->setStatusMessage("Not Found");
  resp->setBody("404 ERROR");
  resp->setCloseConnection(true);
}

#endif  // LIBDD_CALLFUNCTION_H
