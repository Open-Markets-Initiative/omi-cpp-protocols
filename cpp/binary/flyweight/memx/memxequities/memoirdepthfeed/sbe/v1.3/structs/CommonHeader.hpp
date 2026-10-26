#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MessageType.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// Common Header
class CommonHeader {
  public:
    static constexpr const char* name = "CommonHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CommonHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CommonHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 18;
    static constexpr std::size_t fixed_size = 18;
    std::size_t encoded_size() const { return 18; }

    MessageType message_type() const { return static_cast<MessageType>(wire::read_u8(at(0))); }

    std::uint8_t header_length() const { return wire::read_u8(at(1)); }

    std::uint64_t session_id() const { return wire::read_u64_be(at(2)); }

    std::uint64_t sequence_number() const { return wire::read_u64_be(at(10)); }

    void print(std::ostream& out) const {
        out << "CommonHeader{";
        out << "message_type=";
        out << message_type();
        out << ", header_length=";
        out << static_cast<int>(header_length());
        out << ", session_id=";
        out << session_id();
        out << ", sequence_number=";
        out << sequence_number();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CommonHeader& value) {
    value.print(out);
    return out;
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
