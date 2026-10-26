#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class SequencedMessageVisitor;

// The code that selects a message here: the Sequenced Message Type
using SequencedMessageCode = char;

// One message of the Sequenced Message dispatch — the messages a
// SequencedDataPacket carries, selected by its Sequenced Message Type.
// Its codes are its own, so it is a hierarchy of its own rather than a message of the
// outer dispatch, and it owns its fields the same way.
class SequencedMessage {
  public:
    virtual ~SequencedMessage() = default;

    // The code that selects this message
    virtual SequencedMessageCode type() const = 0;
    // The message's name as the specification gives it
    virtual std::string_view name() const = 0;

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    virtual std::size_t decode(const std::byte* data, std::size_t length) = 0;
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    virtual std::size_t encode(std::byte* data, std::size_t capacity) const = 0;
    // How many bytes encode would write
    virtual std::size_t encoded_size() const = 0;

    // Call the visitor's overload for this message's class
    virtual void accept(SequencedMessageVisitor& visitor) const = 0;
    // A copy of this message behind the base class
    virtual std::unique_ptr<SequencedMessage> clone() const = 0;
    virtual void print(std::ostream& out) const = 0;
    // Same class and same fields
    virtual bool equals(const SequencedMessage& other) const = 0;

  protected:
    SequencedMessage() = default;
    SequencedMessage(const SequencedMessage&) = default;
    SequencedMessage& operator=(const SequencedMessage&) = default;
};

inline std::ostream& operator<<(std::ostream& out, const SequencedMessage& message) {
    message.print(out);
    return out;
}

inline bool operator==(const SequencedMessage& left, const SequencedMessage& right) {
    return left.equals(right);
}

inline bool operator!=(const SequencedMessage& left, const SequencedMessage& right) {
    return !left.equals(right);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
