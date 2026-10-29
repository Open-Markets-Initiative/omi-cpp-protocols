#include "Symbol.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

Symbol::Symbol(std::uint8_t symbol_length, const std::string& symbol_text)
  : symbol_length_(symbol_length), symbol_text_(symbol_text) {}

std::uint8_t Symbol::symbol_length() const { return symbol_length_; }
void Symbol::set_symbol_length(std::uint8_t value) { symbol_length_ = value; }

const std::string& Symbol::symbol_text() const { return symbol_text_; }
std::string& Symbol::symbol_text() { return symbol_text_; }
void Symbol::set_symbol_text(const std::string& value) { symbol_text_ = value; }

std::size_t Symbol::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("Symbol", offset + 1, length);
    symbol_length_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(symbol_length_);
        wire::require("Symbol", offset + count, length);
        symbol_text_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t Symbol::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Symbol", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto symbol_length = symbol_length_;
    symbol_length = static_cast<std::uint8_t>(symbol_text_.size());

    wire::write_u8(data + offset, static_cast<std::uint8_t>(symbol_length));
    offset += 1;

    wire::require_capacity("encode", offset + symbol_text_.size(), capacity);
    wire::write_text(data + offset, symbol_text_.size(), ' ', symbol_text_);
    offset += symbol_text_.size();

    return offset;
}

std::size_t Symbol::encoded_size() const {
    return 1 + symbol_text_.size();
}

void Symbol::print(std::ostream& out) const {
    out << "Symbol{";
    out << "symbol_length=";
    out << static_cast<int>(symbol_length_);
    out << ", symbol_text=";
    print::text(out, symbol_text_);
    out << '}';
}

bool Symbol::operator==(const Symbol& other) const {
    return symbol_length_ == other.symbol_length_
        && symbol_text_ == other.symbol_text_;
}

bool Symbol::operator!=(const Symbol& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Symbol& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
