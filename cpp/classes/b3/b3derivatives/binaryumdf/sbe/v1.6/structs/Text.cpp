#include "Text.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

Text::Text(std::uint16_t text_length, const std::string& text_data)
  : text_length_(text_length), text_data_(text_data) {}

std::uint16_t Text::text_length() const { return text_length_; }
void Text::set_text_length(std::uint16_t value) { text_length_ = value; }

const std::string& Text::text_data() const { return text_data_; }
std::string& Text::text_data() { return text_data_; }
void Text::set_text_data(const std::string& value) { text_data_ = value; }

std::size_t Text::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("Text", offset + 2, length);
    text_length_ = wire::read_u16_le(data + offset);
    offset += 2;

    {
        const std::size_t count = static_cast<std::size_t>(text_length_);
        wire::require("Text", offset + count, length);
        text_data_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t Text::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Text", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto text_length = text_length_;
    text_length = static_cast<std::uint16_t>(text_data_.size());

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(text_length));
    offset += 2;

    wire::require_capacity("encode", offset + text_data_.size(), capacity);
    wire::write_text(data + offset, text_data_.size(), ' ', text_data_);
    offset += text_data_.size();

    return offset;
}

std::size_t Text::encoded_size() const {
    return 2 + text_data_.size();
}

void Text::print(std::ostream& out) const {
    out << "Text{";
    out << "text_length=";
    out << text_length_;
    out << ", text_data=";
    print::text(out, text_data_);
    out << '}';
}

bool Text::operator==(const Text& other) const {
    return text_length_ == other.text_length_
        && text_data_ == other.text_data_;
}

bool Text::operator!=(const Text& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Text& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
