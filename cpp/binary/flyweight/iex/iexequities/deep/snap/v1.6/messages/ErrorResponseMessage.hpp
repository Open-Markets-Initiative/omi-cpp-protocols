#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/RejectReasonCode.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

// Sent by the Deep Snap server to the client when a Snapshot Request is rejected
class ErrorResponseMessage {
  public:
    static constexpr const char* name = "ErrorResponseMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ErrorResponseMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ErrorResponseMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    RejectReasonCode reject_reason_code() const { return static_cast<RejectReasonCode>(wire::read_char(at(0))); }

    void print(std::ostream& out) const {
        out << "ErrorResponseMessage{";
        out << "reject_reason_code=";
        out << reject_reason_code();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ErrorResponseMessage& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::deep::snap::v1_6
