#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/OpenInterestMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

class OpenInterestMessagePayloadVisitor;

// The code that selects a message here: the Open Interest Message Type
using OpenInterestMessagePayloadCode = OpenInterestMessageType;

// One message of the Open Interest Message Payload dispatch — the messages a
// OpenInterestCategory carries, selected by its Open Interest Message Type.
// Its codes are its own, so it is a hierarchy of its own rather than a message of the
// outer dispatch, and it owns its fields the same way.
class OpenInterestMessagePayload {
  public:
    virtual ~OpenInterestMessagePayload() = default;

    // The code that selects this message
    virtual OpenInterestMessagePayloadCode type() const = 0;
    // The message's name as the specification gives it
    virtual std::string_view name() const = 0;

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    virtual std::size_t decode(const std::byte* data, std::size_t length) = 0;
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    virtual std::size_t encode(std::byte* data, std::size_t capacity) const = 0;
    // How many bytes encode would write
    virtual std::size_t encoded_size() const = 0;

    // Call the visitor's overload for this message's class
    virtual void accept(OpenInterestMessagePayloadVisitor& visitor) const = 0;
    // A copy of this message behind the base class
    virtual std::unique_ptr<OpenInterestMessagePayload> clone() const = 0;
    virtual void print(std::ostream& out) const = 0;
    // Same class and same fields
    virtual bool equals(const OpenInterestMessagePayload& other) const = 0;

  protected:
    OpenInterestMessagePayload() = default;
    OpenInterestMessagePayload(const OpenInterestMessagePayload&) = default;
    OpenInterestMessagePayload& operator=(const OpenInterestMessagePayload&) = default;
};

inline std::ostream& operator<<(std::ostream& out, const OpenInterestMessagePayload& message) {
    message.print(out);
    return out;
}

inline bool operator==(const OpenInterestMessagePayload& left, const OpenInterestMessagePayload& right) {
    return left.equals(right);
}

inline bool operator!=(const OpenInterestMessagePayload& left, const OpenInterestMessagePayload& right) {
    return !left.equals(right);
}

} // namespace siac::opra::output::obi::v6_2
