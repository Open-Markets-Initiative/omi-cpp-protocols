#include "CurrencyCode.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

CurrencyCode::CurrencyCode(std::uint8_t currency_code_length, const std::string& currency_code_text)
  : currency_code_length_(currency_code_length), currency_code_text_(currency_code_text) {}

std::uint8_t CurrencyCode::currency_code_length() const { return currency_code_length_; }
void CurrencyCode::set_currency_code_length(std::uint8_t value) { currency_code_length_ = value; }

const std::string& CurrencyCode::currency_code_text() const { return currency_code_text_; }
std::string& CurrencyCode::currency_code_text() { return currency_code_text_; }
void CurrencyCode::set_currency_code_text(const std::string& value) { currency_code_text_ = value; }

std::size_t CurrencyCode::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("CurrencyCode", offset + 1, length);
    currency_code_length_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(currency_code_length_);
        wire::require("CurrencyCode", offset + count, length);
        currency_code_text_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t CurrencyCode::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CurrencyCode", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto currency_code_length = currency_code_length_;
    currency_code_length = static_cast<std::uint8_t>(currency_code_text_.size());

    wire::write_u8(data + offset, static_cast<std::uint8_t>(currency_code_length));
    offset += 1;

    wire::require_capacity("encode", offset + currency_code_text_.size(), capacity);
    wire::write_text(data + offset, currency_code_text_.size(), ' ', currency_code_text_);
    offset += currency_code_text_.size();

    return offset;
}

std::size_t CurrencyCode::encoded_size() const {
    return 1 + currency_code_text_.size();
}

void CurrencyCode::print(std::ostream& out) const {
    out << "CurrencyCode{";
    out << "currency_code_length=";
    out << static_cast<int>(currency_code_length_);
    out << ", currency_code_text=";
    print::text(out, currency_code_text_);
    out << '}';
}

bool CurrencyCode::operator==(const CurrencyCode& other) const {
    return currency_code_length_ == other.currency_code_length_
        && currency_code_text_ == other.currency_code_text_;
}

bool CurrencyCode::operator!=(const CurrencyCode& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const CurrencyCode& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
