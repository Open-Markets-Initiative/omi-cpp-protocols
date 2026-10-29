#include "CorrectionCondition.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

CorrectionCondition::CorrectionCondition(Transaction transaction, const std::array<std::byte, 3>& reserved_3)
  : transaction_(transaction), reserved_3_(reserved_3) {}

Transaction CorrectionCondition::transaction() const { return transaction_; }
void CorrectionCondition::set_transaction(Transaction value) { transaction_ = value; }

const std::array<std::byte, 3>& CorrectionCondition::reserved_3() const { return reserved_3_; }
std::array<std::byte, 3>& CorrectionCondition::reserved_3() { return reserved_3_; }
void CorrectionCondition::set_reserved_3(const std::array<std::byte, 3>& value) { reserved_3_ = value; }

std::size_t CorrectionCondition::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CorrectionCondition", wire_size, length);

    transaction_ = static_cast<Transaction>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_3_.data(), 3);
    offset += 3;

    return offset;
}

std::size_t CorrectionCondition::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CorrectionCondition", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(transaction_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_3_.data(), 3);
    offset += 3;

    return offset;
}

std::size_t CorrectionCondition::encoded_size() const {
    return wire_size;
}

void CorrectionCondition::print(std::ostream& out) const {
    out << "CorrectionCondition{";
    out << "transaction=";
    out << transaction_;
    out << ", reserved_3=";
    print::hex(out, reserved_3_.data(), reserved_3_.size());
    out << '}';
}

bool CorrectionCondition::operator==(const CorrectionCondition& other) const {
    return transaction_ == other.transaction_
        && reserved_3_ == other.reserved_3_;
}

bool CorrectionCondition::operator!=(const CorrectionCondition& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const CorrectionCondition& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
