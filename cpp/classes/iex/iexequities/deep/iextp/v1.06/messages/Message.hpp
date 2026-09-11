#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/MessageType.hpp"

namespace iex::iexequities::deep::iextp::v1_06 {

class Visitor;

// The code that selects a message: the frame's Message Type
using MessageCode = MessageType;

// One decoded message. A message owns its fields: it is decoded once from the wire, and
// from then on it is an ordinary object that can be copied, stored, compared, printed and
// encoded back, whether or not the buffer it came from still exists.
class Message {
  public:
    virtual ~Message() = default;

    // The code that selects this message
    virtual MessageCode type() const = 0;
    // The message's name as the specification gives it
    virtual std::string_view name() const = 0;

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    virtual std::size_t decode(const std::byte* data, std::size_t length) = 0;
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    virtual std::size_t encode(std::byte* data, std::size_t capacity) const = 0;
    // How many bytes encode would write
    virtual std::size_t encoded_size() const = 0;

    // Call the visitor's overload for this message's class
    virtual void accept(Visitor& visitor) const = 0;
    // A copy of this message behind the base class
    virtual std::unique_ptr<Message> clone() const = 0;
    virtual void print(std::ostream& out) const = 0;
    // Same class and same fields
    virtual bool equals(const Message& other) const = 0;

  protected:
    Message() = default;
    Message(const Message&) = default;
    Message& operator=(const Message&) = default;
};

inline std::ostream& operator<<(std::ostream& out, const Message& message) {
    message.print(out);
    return out;
}

inline bool operator==(const Message& left, const Message& right) {
    return left.equals(right);
}

inline bool operator!=(const Message& left, const Message& right) {
    return !left.equals(right);
}

} // namespace iex::iexequities::deep::iextp::v1_06
