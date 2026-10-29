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
#include "../enums/Event.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Transitions in the overall session state
class MarketEventMessage {
  public:
    static constexpr const char* name = "MarketEventMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MarketEventMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MarketEventMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 11;
    static constexpr std::size_t fixed_size = 11;
    std::size_t encoded_size() const { return 11; }

    std::string_view reserved_2() const { return view::text(at(0), 2, ' '); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(2)))); }

    Event event() const { return static_cast<Event>(wire::read_char(at(10))); }

    void print(std::ostream& out) const {
        out << "MarketEventMessage{";
        out << "reserved_2=";
        print::text(out, reserved_2());
        out << ", timestamp=";
        out << timestamp().count();
        out << ", event=";
        out << event();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MarketEventMessage& value) {
    value.print(out);
    return out;
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
