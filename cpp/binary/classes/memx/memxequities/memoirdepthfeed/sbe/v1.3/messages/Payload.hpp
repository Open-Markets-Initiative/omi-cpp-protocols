#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/TemplateId.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

class PayloadVisitor;

// The code that selects a message here: the Template Id
using PayloadCode = TemplateId;

// One message of the Payload dispatch — the messages a
// SbeMessage carries, selected by its Template Id.
// Its codes are its own, so it is a hierarchy of its own rather than a message of the
// outer dispatch, and it owns its fields the same way.
class Payload {
  public:
    virtual ~Payload() = default;

    // The code that selects this message
    virtual PayloadCode type() const = 0;
    // The message's name as the specification gives it
    virtual std::string_view name() const = 0;

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    virtual std::size_t decode(const std::byte* data, std::size_t length) = 0;
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    virtual std::size_t encode(std::byte* data, std::size_t capacity) const = 0;
    // How many bytes encode would write
    virtual std::size_t encoded_size() const = 0;

    // Call the visitor's overload for this message's class
    virtual void accept(PayloadVisitor& visitor) const = 0;
    // A copy of this message behind the base class
    virtual std::unique_ptr<Payload> clone() const = 0;
    virtual void print(std::ostream& out) const = 0;
    // Same class and same fields
    virtual bool equals(const Payload& other) const = 0;

  protected:
    Payload() = default;
    Payload(const Payload&) = default;
    Payload& operator=(const Payload&) = default;
};

inline std::ostream& operator<<(std::ostream& out, const Payload& message) {
    message.print(out);
    return out;
}

inline bool operator==(const Payload& left, const Payload& right) {
    return left.equals(right);
}

inline bool operator!=(const Payload& left, const Payload& right) {
    return !left.equals(right);
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
