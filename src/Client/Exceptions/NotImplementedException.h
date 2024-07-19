#ifndef NOTIMPLEMENTEDEXCEPTION_H
#define NOTIMPLEMENTEDEXCEPTION_H
#include <exception>

namespace Cesame {
class NotImplementedException final : public std::exception {};
}

#endif //NOTIMPLEMENTEDEXCEPTION_H
