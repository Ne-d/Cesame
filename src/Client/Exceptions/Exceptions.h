#ifndef NOTIMPLEMENTEDEXCEPTION_H
#define NOTIMPLEMENTEDEXCEPTION_H
#include <exception>

namespace Cesame {
class NotImplementedException final : public std::exception {};

class FileOpenException final : public std::exception {};

class ValueNotFoundException final : public std::exception {};
}

#endif //NOTIMPLEMENTEDEXCEPTION_H
