#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/BestBidParticipantId.hpp"
#include "../enums/BestBidDenominatorCode.hpp"
#include "../common/Decimal.hpp"
#include "../enums/BestOfferParticipantId.hpp"
#include "../enums/BestOfferDenominatorCode.hpp"

namespace siac::opra::output::obi::v6_2 {

// Best Bid and Offer Appendage
class BestBidAndOfferAppendage {
  public:
    static constexpr const char* name = "BestBidAndOfferAppendage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit BestBidAndOfferAppendage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every BestBidAndOfferAppendage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 20;
    static constexpr std::size_t fixed_size = 20;
    std::size_t encoded_size() const { return 20; }

    BestBidParticipantId best_bid_participant_id() const { return static_cast<BestBidParticipantId>(wire::read_char(at(0))); }

    BestBidDenominatorCode best_bid_denominator_code() const { return static_cast<BestBidDenominatorCode>(wire::read_char(at(1))); }

    // the exponent best_bid_denominator_code states, or 0 for a code it does not state
    static constexpr int best_bid_price_exponent(char code) {
        switch (code) {
            case 'A': return -1;
            case 'B': return -2;
            case 'C': return -3;
            case 'D': return -4;
            case 'E': return -5;
            case 'F': return -6;
            case 'G': return -7;
            case 'H': return -8;
            case 'I': return 0;
            default: return 0;
        }
    }
    Decimal best_bid_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i32_be(at(2))), best_bid_price_exponent(static_cast<char>(best_bid_denominator_code()))); }

    std::uint32_t best_bid_size() const { return wire::read_u32_be(at(6)); }

    BestOfferParticipantId best_offer_participant_id() const { return static_cast<BestOfferParticipantId>(wire::read_char(at(10))); }

    BestOfferDenominatorCode best_offer_denominator_code() const { return static_cast<BestOfferDenominatorCode>(wire::read_char(at(11))); }

    // the exponent best_offer_denominator_code states, or 0 for a code it does not state
    static constexpr int best_offer_price_exponent(char code) {
        switch (code) {
            case 'A': return -1;
            case 'B': return -2;
            case 'C': return -3;
            case 'D': return -4;
            case 'E': return -5;
            case 'F': return -6;
            case 'G': return -7;
            case 'H': return -8;
            case 'I': return 0;
            default: return 0;
        }
    }
    Decimal best_offer_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i32_be(at(12))), best_offer_price_exponent(static_cast<char>(best_offer_denominator_code()))); }

    std::uint32_t best_offer_size() const { return wire::read_u32_be(at(16)); }

    void print(std::ostream& out) const {
        out << "BestBidAndOfferAppendage{";
        out << "best_bid_participant_id=";
        out << best_bid_participant_id();
        out << ", best_bid_denominator_code=";
        out << best_bid_denominator_code();
        out << ", best_bid_price=";
        out << best_bid_price();
        out << ", best_bid_size=";
        out << best_bid_size();
        out << ", best_offer_participant_id=";
        out << best_offer_participant_id();
        out << ", best_offer_denominator_code=";
        out << best_offer_denominator_code();
        out << ", best_offer_price=";
        out << best_offer_price();
        out << ", best_offer_size=";
        out << best_offer_size();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const BestBidAndOfferAppendage& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
