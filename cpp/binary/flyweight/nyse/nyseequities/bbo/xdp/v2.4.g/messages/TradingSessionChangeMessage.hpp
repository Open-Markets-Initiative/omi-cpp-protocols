#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

// This message announces the start of a new trading session for a specified symbol.
class TradingSessionChangeMessage {
  public:
    static constexpr const char* name = "TradingSessionChangeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradingSessionChangeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradingSessionChangeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    std::uint32_t source_time() const { return wire::read_u32_le(at(0)); }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(4)); }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(8)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(12)); }

    std::uint8_t trading_session() const { return wire::read_u8(at(16)); }

    void print(std::ostream& out) const {
        out << "TradingSessionChangeMessage{";
        out << "source_time=";
        out << source_time();
        out << ", source_time_ns=";
        out << source_time_ns();
        out << ", symbol_index=";
        out << symbol_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", trading_session=";
        out << static_cast<int>(trading_session());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradingSessionChangeMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nyseequities::bbo::xdp::v2_4_g
