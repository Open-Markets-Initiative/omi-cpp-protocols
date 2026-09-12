#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/IexTpMessageType.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

class IexTpMessageDataVisitor;

// The code that selects a message here: the Iex Tp Message Type
using IexTpMessageDataCode = IexTpMessageType;

// One message of the Iex Tp Message Data dispatch — the messages a
// SnapshotDataMessage carries, selected by its Iex Tp Message Type.
// Its codes are its own, so it is a hierarchy of its own rather than a message of the
// outer dispatch, and it owns its fields the same way.
class IexTpMessageData {
  public:
    virtual ~IexTpMessageData() = default;

    // The code that selects this message
    virtual IexTpMessageDataCode type() const = 0;
    // The message's name as the specification gives it
    virtual std::string_view name() const = 0;

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    virtual std::size_t decode(const std::byte* data, std::size_t length) = 0;
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    virtual std::size_t encode(std::byte* data, std::size_t capacity) const = 0;
    // How many bytes encode would write
    virtual std::size_t encoded_size() const = 0;

    // Call the visitor's overload for this message's class
    virtual void accept(IexTpMessageDataVisitor& visitor) const = 0;
    // A copy of this message behind the base class
    virtual std::unique_ptr<IexTpMessageData> clone() const = 0;
    virtual void print(std::ostream& out) const = 0;
    // Same class and same fields
    virtual bool equals(const IexTpMessageData& other) const = 0;

  protected:
    IexTpMessageData() = default;
    IexTpMessageData(const IexTpMessageData&) = default;
    IexTpMessageData& operator=(const IexTpMessageData&) = default;
};

inline std::ostream& operator<<(std::ostream& out, const IexTpMessageData& message) {
    message.print(out);
    return out;
}

inline bool operator==(const IexTpMessageData& left, const IexTpMessageData& right) {
    return left.equals(right);
}

inline bool operator!=(const IexTpMessageData& left, const IexTpMessageData& right) {
    return !left.equals(right);
}

} // namespace iex::iexequities::deepplus::snap::v1_05
