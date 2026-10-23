#include "BestOfferAppendage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::opra::output::obi::v6_2 {

BestOfferAppendage::BestOfferAppendage(BestOfferParticipantId best_offer_participant_id, BestOfferDenominatorCode best_offer_denominator_code, Decimal best_offer_price, std::uint32_t best_offer_size)
  : best_offer_participant_id_(best_offer_participant_id), best_offer_denominator_code_(best_offer_denominator_code), best_offer_price_(best_offer_price), best_offer_size_(best_offer_size) {}

BestOfferParticipantId BestOfferAppendage::best_offer_participant_id() const { return best_offer_participant_id_; }
void BestOfferAppendage::set_best_offer_participant_id(BestOfferParticipantId value) { best_offer_participant_id_ = value; }

BestOfferDenominatorCode BestOfferAppendage::best_offer_denominator_code() const { return best_offer_denominator_code_; }
void BestOfferAppendage::set_best_offer_denominator_code(BestOfferDenominatorCode value) { best_offer_denominator_code_ = value; }

Decimal BestOfferAppendage::best_offer_price() const { return best_offer_price_; }
void BestOfferAppendage::set_best_offer_price(Decimal value) { best_offer_price_ = value; }
int BestOfferAppendage::best_offer_price_exponent(char code) {
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

std::uint32_t BestOfferAppendage::best_offer_size() const { return best_offer_size_; }
void BestOfferAppendage::set_best_offer_size(std::uint32_t value) { best_offer_size_ = value; }

std::size_t BestOfferAppendage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("BestOfferAppendage", wire_size, length);

    best_offer_participant_id_ = static_cast<BestOfferParticipantId>(wire::read_char(data + offset));
    offset += 1;

    best_offer_denominator_code_ = static_cast<BestOfferDenominatorCode>(wire::read_char(data + offset));
    offset += 1;

    best_offer_price_ = Decimal(static_cast<std::int64_t>(wire::read_i32_be(data + offset)), best_offer_price_exponent(static_cast<char>(best_offer_denominator_code_)));
    offset += 4;

    best_offer_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t BestOfferAppendage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BestOfferAppendage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(best_offer_participant_id_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(best_offer_denominator_code_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(best_offer_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(best_offer_size_));
    offset += 4;

    return offset;
}

std::size_t BestOfferAppendage::encoded_size() const {
    return wire_size;
}

void BestOfferAppendage::print(std::ostream& out) const {
    out << "BestOfferAppendage{";
    out << "best_offer_participant_id=";
    out << best_offer_participant_id_;
    out << ", best_offer_denominator_code=";
    out << best_offer_denominator_code_;
    out << ", best_offer_price=";
    out << best_offer_price_;
    out << ", best_offer_size=";
    out << best_offer_size_;
    out << '}';
}

bool BestOfferAppendage::operator==(const BestOfferAppendage& other) const {
    return best_offer_participant_id_ == other.best_offer_participant_id_
        && best_offer_denominator_code_ == other.best_offer_denominator_code_
        && best_offer_price_ == other.best_offer_price_
        && best_offer_size_ == other.best_offer_size_;
}

bool BestOfferAppendage::operator!=(const BestOfferAppendage& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const BestOfferAppendage& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
