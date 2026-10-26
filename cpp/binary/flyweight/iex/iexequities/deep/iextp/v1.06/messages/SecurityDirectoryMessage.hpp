#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../bitfields/SecurityDirectoryFlags.hpp"
#include "../common/Decimal.hpp"
#include "../enums/LuldTier.hpp"

namespace iex::iexequities::deep::iextp::v1_06 {

// The System Event Message is used to indicate events that apply to the market or the data
// feed.
class SecurityDirectoryMessage {
  public:
    static constexpr const char* name = "SecurityDirectoryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityDirectoryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecurityDirectoryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 30;
    static constexpr std::size_t fixed_size = 30;
    std::size_t encoded_size() const { return 30; }

    SecurityDirectoryFlags security_directory_flags() const { return SecurityDirectoryFlags{ bytes_.subspan(0) }; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(at(1)))); }

    std::string_view symbol() const { return view::text(at(9), 8, ' '); }

    std::uint32_t round_lot_size() const { return wire::read_u32_le(at(17)); }

    Decimal adjusted_poc_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(21))), -4); }

    LuldTier luld_tier() const { return static_cast<LuldTier>(wire::read_u8(at(29))); }

    void print(std::ostream& out) const {
        out << "SecurityDirectoryMessage{";
        out << "security_directory_flags=";
        security_directory_flags().print(out);
        out << ", timestamp=";
        out << timestamp().count();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", round_lot_size=";
        out << round_lot_size();
        out << ", adjusted_poc_price=";
        out << adjusted_poc_price();
        out << ", luld_tier=";
        out << luld_tier();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityDirectoryMessage& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::deep::iextp::v1_06
