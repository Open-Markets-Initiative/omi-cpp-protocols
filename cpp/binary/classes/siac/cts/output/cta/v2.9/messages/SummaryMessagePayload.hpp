#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/SummaryMessageType.hpp"

namespace siac::cts::output::cta::v2_9 {

class SummaryMessagePayloadVisitor;

// The code that selects a message here: the Summary Message Type
using SummaryMessagePayloadCode = SummaryMessageType;

// One message of the Summary Message Payload dispatch — the messages a
// SummaryMessage carries, selected by its Summary Message Type.
// Its codes are its own, so it is a hierarchy of its own rather than a message of the
// outer dispatch, and it owns its fields the same way.
class SummaryMessagePayload {
  public:
    virtual ~SummaryMessagePayload() = default;

    // The code that selects this message
    virtual SummaryMessagePayloadCode type() const = 0;
    // The message's name as the specification gives it
    virtual std::string_view name() const = 0;

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    virtual std::size_t decode(const std::byte* data, std::size_t length) = 0;
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    virtual std::size_t encode(std::byte* data, std::size_t capacity) const = 0;
    // How many bytes encode would write
    virtual std::size_t encoded_size() const = 0;

    // Call the visitor's overload for this message's class
    virtual void accept(SummaryMessagePayloadVisitor& visitor) const = 0;
    // A copy of this message behind the base class
    virtual std::unique_ptr<SummaryMessagePayload> clone() const = 0;
    virtual void print(std::ostream& out) const = 0;
    // Same class and same fields
    virtual bool equals(const SummaryMessagePayload& other) const = 0;

  protected:
    SummaryMessagePayload() = default;
    SummaryMessagePayload(const SummaryMessagePayload&) = default;
    SummaryMessagePayload& operator=(const SummaryMessagePayload&) = default;
};

inline std::ostream& operator<<(std::ostream& out, const SummaryMessagePayload& message) {
    message.print(out);
    return out;
}

inline bool operator==(const SummaryMessagePayload& left, const SummaryMessagePayload& right) {
    return left.equals(right);
}

inline bool operator!=(const SummaryMessagePayload& left, const SummaryMessagePayload& right) {
    return !left.equals(right);
}

} // namespace siac::cts::output::cta::v2_9
