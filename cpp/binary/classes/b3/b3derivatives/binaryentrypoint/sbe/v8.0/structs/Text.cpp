#include "Text.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

Text::Text(std::uint8_t text_length, const std::string& text_data)
  : text_length_(text_length), text_data_(text_data) {}

std::uint8_t Text::text_length() const { return text_length_; }
void Text::set_text_length(std::uint8_t value) { text_length_ = value; }

const std::string& Text::text_data() const { return text_data_; }
std::string& Text::text_data() { return text_data_; }
void Text::set_text_data(const std::string& value) { text_data_ = value; }

std::size_t Text::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("Text", offset + 1, length);
    text_length_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(text_length_);
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
    text_length = static_cast<std::uint8_t>(text_data_.size());

    wire::write_u8(data + offset, static_cast<std::uint8_t>(text_length));
    offset += 1;

    wire::require_capacity("encode", offset + text_data_.size(), capacity);
    wire::write_text(data + offset, text_data_.size(), ' ', text_data_);
    offset += text_data_.size();

    return offset;
}

std::size_t Text::encoded_size() const {
    return 1 + text_data_.size();
}

void Text::print(std::ostream& out) const {
    out << "Text{";
    out << "text_length=";
    out << static_cast<int>(text_length_);
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

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
