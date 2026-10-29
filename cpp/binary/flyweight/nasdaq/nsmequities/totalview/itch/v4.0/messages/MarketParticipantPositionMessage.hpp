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
#include "../enums/PrimaryMarketMaker.hpp"
#include "../enums/MarketMakerMode.hpp"
#include "../enums/MarketParticipantState.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// At the start of each trading day, NASDAQ disseminates a spin of market participant position
// messages. Throughout the day, NASDAQ will send out this message only if NASDAQ Operations
// changes the status of a market participant firm in an issue.
class MarketParticipantPositionMessage {
  public:
    static constexpr const char* name = "MarketParticipantPositionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MarketParticipantPositionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MarketParticipantPositionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::string_view mpid() const { return view::text(at(4), 4, ' '); }

    std::string_view stock() const { return view::text(at(8), 6, ' '); }

    PrimaryMarketMaker primary_market_maker() const { return static_cast<PrimaryMarketMaker>(wire::read_char(at(14))); }

    MarketMakerMode market_maker_mode() const { return static_cast<MarketMakerMode>(wire::read_char(at(15))); }

    MarketParticipantState market_participant_state() const { return static_cast<MarketParticipantState>(wire::read_char(at(16))); }

    void print(std::ostream& out) const {
        out << "MarketParticipantPositionMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", mpid=";
        print::text(out, mpid());
        out << ", stock=";
        print::text(out, stock());
        out << ", primary_market_maker=";
        out << primary_market_maker();
        out << ", market_maker_mode=";
        out << market_maker_mode();
        out << ", market_participant_state=";
        out << market_participant_state();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MarketParticipantPositionMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
