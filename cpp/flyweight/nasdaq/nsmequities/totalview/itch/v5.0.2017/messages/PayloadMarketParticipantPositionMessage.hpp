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

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

// Throughout the day, NASDAQ will send out this message only if NASDAQ Operations changes the
// status of a market participant firm in an issue.
class PayloadMarketParticipantPositionMessage {
  public:
    static constexpr const char* name = "PayloadMarketParticipantPositionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PayloadMarketParticipantPositionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PayloadMarketParticipantPositionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 25;
    static constexpr std::size_t fixed_size = 25;
    std::size_t encoded_size() const { return 25; }

    std::uint16_t stock_locate() const { return wire::read_u16_be(at(0)); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(2)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(4)))); }

    std::string_view mpid() const { return view::text(at(10), 4, ' '); }

    std::string_view stock() const { return view::text(at(14), 8, ' '); }

    PrimaryMarketMaker primary_market_maker() const { return static_cast<PrimaryMarketMaker>(wire::read_char(at(22))); }

    MarketMakerMode market_maker_mode() const { return static_cast<MarketMakerMode>(wire::read_char(at(23))); }

    MarketParticipantState market_participant_state() const { return static_cast<MarketParticipantState>(wire::read_char(at(24))); }

    void print(std::ostream& out) const {
        out << "PayloadMarketParticipantPositionMessage{";
        out << "stock_locate=";
        out << stock_locate();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        out << timestamp().count();
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

inline std::ostream& operator<<(std::ostream& out, const PayloadMarketParticipantPositionMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
