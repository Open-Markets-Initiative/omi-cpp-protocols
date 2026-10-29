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
#include "../enums/Group.hpp"
#include "../enums/TradingState.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

// Trading State Message indicates the current trading state of an orderbook.
class TradingStateMessage {
  public:
    static constexpr const char* name = "TradingStateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradingStateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradingStateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 13;
    static constexpr std::size_t fixed_size = 13;
    std::size_t encoded_size() const { return 13; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t orderbook_id() const { return wire::read_u32_be(at(4)); }

    std::string_view group() const { return view::text(at(8), 4, ' '); }

    TradingState trading_state() const { return static_cast<TradingState>(wire::read_char(at(12))); }

    void print(std::ostream& out) const {
        out << "TradingStateMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", orderbook_id=";
        out << orderbook_id();
        out << ", group=";
        print::text(out, group());
        out << ", trading_state=";
        out << trading_state();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradingStateMessage& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::itch::v1_6
