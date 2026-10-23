#include "NationalBestBidShortAppendage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cqs::output::cta::v2_10_a {

NationalBestBidShortAppendage::NationalBestBidShortAppendage(char best_bid_participant_id, Decimal best_bid_price_short, std::uint16_t best_bid_size_short)
  : best_bid_participant_id_(best_bid_participant_id), best_bid_price_short_(best_bid_price_short), best_bid_size_short_(best_bid_size_short) {}

char NationalBestBidShortAppendage::best_bid_participant_id() const { return best_bid_participant_id_; }
void NationalBestBidShortAppendage::set_best_bid_participant_id(char value) { best_bid_participant_id_ = value; }

Decimal NationalBestBidShortAppendage::best_bid_price_short() const { return best_bid_price_short_; }
void NationalBestBidShortAppendage::set_best_bid_price_short(Decimal value) { best_bid_price_short_ = value; }

std::uint16_t NationalBestBidShortAppendage::best_bid_size_short() const { return best_bid_size_short_; }
void NationalBestBidShortAppendage::set_best_bid_size_short(std::uint16_t value) { best_bid_size_short_ = value; }

std::size_t NationalBestBidShortAppendage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("NationalBestBidShortAppendage", wire_size, length);

    best_bid_participant_id_ = wire::read_char(data + offset);
    offset += 1;

    best_bid_price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -2);
    offset += 2;

    best_bid_size_short_ = wire::read_u16_be(data + offset);
    offset += 2;

    return offset;
}

std::size_t NationalBestBidShortAppendage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("NationalBestBidShortAppendage", wire_size, capacity);

    wire::write_char(data + offset, best_bid_participant_id_);
    offset += 1;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(best_bid_price_short_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(best_bid_size_short_));
    offset += 2;

    return offset;
}

std::size_t NationalBestBidShortAppendage::encoded_size() const {
    return wire_size;
}

void NationalBestBidShortAppendage::print(std::ostream& out) const {
    out << "NationalBestBidShortAppendage{";
    out << "best_bid_participant_id=";
    print::character(out, best_bid_participant_id_);
    out << ", best_bid_price_short=";
    out << best_bid_price_short_;
    out << ", best_bid_size_short=";
    out << best_bid_size_short_;
    out << '}';
}

bool NationalBestBidShortAppendage::operator==(const NationalBestBidShortAppendage& other) const {
    return best_bid_participant_id_ == other.best_bid_participant_id_
        && best_bid_price_short_ == other.best_bid_price_short_
        && best_bid_size_short_ == other.best_bid_size_short_;
}

bool NationalBestBidShortAppendage::operator!=(const NationalBestBidShortAppendage& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const NationalBestBidShortAppendage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cqs::output::cta::v2_10_a
