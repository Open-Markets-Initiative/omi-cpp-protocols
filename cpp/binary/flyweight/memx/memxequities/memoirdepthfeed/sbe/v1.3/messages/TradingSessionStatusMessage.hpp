#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/TradingSession.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// TradingSessionStatusMessage
class TradingSessionStatusMessage {
  public:
    static constexpr const char* name = "TradingSessionStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradingSessionStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradingSessionStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 9;
    static constexpr std::size_t fixed_size = 9;
    std::size_t encoded_size() const { return 9; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }

    TradingSession trading_session() const { return static_cast<TradingSession>(wire::read_char(at(8))); }

    void print(std::ostream& out) const {
        out << "TradingSessionStatusMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", trading_session=";
        out << trading_session();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradingSessionStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
