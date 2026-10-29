#include "UnderlyingSymbol.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

UnderlyingSymbol::UnderlyingSymbol(std::uint8_t underlying_symbol_length, const std::string& underlying_symbol_text)
  : underlying_symbol_length_(underlying_symbol_length), underlying_symbol_text_(underlying_symbol_text) {}

std::uint8_t UnderlyingSymbol::underlying_symbol_length() const { return underlying_symbol_length_; }
void UnderlyingSymbol::set_underlying_symbol_length(std::uint8_t value) { underlying_symbol_length_ = value; }

const std::string& UnderlyingSymbol::underlying_symbol_text() const { return underlying_symbol_text_; }
std::string& UnderlyingSymbol::underlying_symbol_text() { return underlying_symbol_text_; }
void UnderlyingSymbol::set_underlying_symbol_text(const std::string& value) { underlying_symbol_text_ = value; }

std::size_t UnderlyingSymbol::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("UnderlyingSymbol", offset + 1, length);
    underlying_symbol_length_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(underlying_symbol_length_);
        wire::require("UnderlyingSymbol", offset + count, length);
        underlying_symbol_text_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t UnderlyingSymbol::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UnderlyingSymbol", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto underlying_symbol_length = underlying_symbol_length_;
    underlying_symbol_length = static_cast<std::uint8_t>(underlying_symbol_text_.size());

    wire::write_u8(data + offset, static_cast<std::uint8_t>(underlying_symbol_length));
    offset += 1;

    wire::require_capacity("encode", offset + underlying_symbol_text_.size(), capacity);
    wire::write_text(data + offset, underlying_symbol_text_.size(), ' ', underlying_symbol_text_);
    offset += underlying_symbol_text_.size();

    return offset;
}

std::size_t UnderlyingSymbol::encoded_size() const {
    return 1 + underlying_symbol_text_.size();
}

void UnderlyingSymbol::print(std::ostream& out) const {
    out << "UnderlyingSymbol{";
    out << "underlying_symbol_length=";
    out << static_cast<int>(underlying_symbol_length_);
    out << ", underlying_symbol_text=";
    print::text(out, underlying_symbol_text_);
    out << '}';
}

bool UnderlyingSymbol::operator==(const UnderlyingSymbol& other) const {
    return underlying_symbol_length_ == other.underlying_symbol_length_
        && underlying_symbol_text_ == other.underlying_symbol_text_;
}

bool UnderlyingSymbol::operator!=(const UnderlyingSymbol& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const UnderlyingSymbol& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
