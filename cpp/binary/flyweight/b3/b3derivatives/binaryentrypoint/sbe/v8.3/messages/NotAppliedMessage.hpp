#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// NotAppliedMessage
class NotAppliedMessage {
  public:
    static constexpr const char* name = "NotAppliedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NotAppliedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every NotAppliedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::uint32_t from_seq_no() const { return wire::read_u32_le(at(0)); }

    std::uint32_t count() const { return wire::read_u32_le(at(4)); }

    void print(std::ostream& out) const {
        out << "NotAppliedMessage{";
        out << "from_seq_no=";
        out << from_seq_no();
        out << ", count=";
        out << count();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const NotAppliedMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
