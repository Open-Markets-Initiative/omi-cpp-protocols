#include "BestBidAppendage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::opra::output::obi::v6_2 {

BestBidAppendage::BestBidAppendage(BestBidParticipantId best_bid_participant_id, BestBidDenominatorCode best_bid_denominator_code, Decimal best_bid_price, std::uint32_t best_bid_size)
  : best_bid_participant_id_(best_bid_participant_id), best_bid_denominator_code_(best_bid_denominator_code), best_bid_price_(best_bid_price), best_bid_size_(best_bid_size) {}

BestBidParticipantId BestBidAppendage::best_bid_participant_id() const { return best_bid_participant_id_; }
void BestBidAppendage::set_best_bid_participant_id(BestBidParticipantId value) { best_bid_participant_id_ = value; }

BestBidDenominatorCode BestBidAppendage::best_bid_denominator_code() const { return best_bid_denominator_code_; }
void BestBidAppendage::set_best_bid_denominator_code(BestBidDenominatorCode value) { best_bid_denominator_code_ = value; }

Decimal BestBidAppendage::best_bid_price() const { return best_bid_price_; }
void BestBidAppendage::set_best_bid_price(Decimal value) { best_bid_price_ = value; }
int BestBidAppendage::best_bid_price_exponent(char code) {
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

std::uint32_t BestBidAppendage::best_bid_size() const { return best_bid_size_; }
void BestBidAppendage::set_best_bid_size(std::uint32_t value) { best_bid_size_ = value; }

std::size_t BestBidAppendage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("BestBidAppendage", wire_size, length);

    best_bid_participant_id_ = static_cast<BestBidParticipantId>(wire::read_char(data + offset));
    offset += 1;

    best_bid_denominator_code_ = static_cast<BestBidDenominatorCode>(wire::read_char(data + offset));
    offset += 1;

    best_bid_price_ = Decimal(static_cast<std::int64_t>(wire::read_i32_be(data + offset)), best_bid_price_exponent(static_cast<char>(best_bid_denominator_code_)));
    offset += 4;

    best_bid_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t BestBidAppendage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BestBidAppendage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(best_bid_participant_id_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(best_bid_denominator_code_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(best_bid_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(best_bid_size_));
    offset += 4;

    return offset;
}

std::size_t BestBidAppendage::encoded_size() const {
    return wire_size;
}

void BestBidAppendage::print(std::ostream& out) const {
    out << "BestBidAppendage{";
    out << "best_bid_participant_id=";
    out << best_bid_participant_id_;
    out << ", best_bid_denominator_code=";
    out << best_bid_denominator_code_;
    out << ", best_bid_price=";
    out << best_bid_price_;
    out << ", best_bid_size=";
    out << best_bid_size_;
    out << '}';
}

bool BestBidAppendage::operator==(const BestBidAppendage& other) const {
    return best_bid_participant_id_ == other.best_bid_participant_id_
        && best_bid_denominator_code_ == other.best_bid_denominator_code_
        && best_bid_price_ == other.best_bid_price_
        && best_bid_size_ == other.best_bid_size_;
}

bool BestBidAppendage::operator!=(const BestBidAppendage& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const BestBidAppendage& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
