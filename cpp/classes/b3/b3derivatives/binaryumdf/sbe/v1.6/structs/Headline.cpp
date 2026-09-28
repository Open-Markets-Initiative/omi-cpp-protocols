#include "Headline.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

Headline::Headline(std::uint16_t headline_length, const std::string& headline_data)
  : headline_length_(headline_length), headline_data_(headline_data) {}

std::uint16_t Headline::headline_length() const { return headline_length_; }
void Headline::set_headline_length(std::uint16_t value) { headline_length_ = value; }

const std::string& Headline::headline_data() const { return headline_data_; }
std::string& Headline::headline_data() { return headline_data_; }
void Headline::set_headline_data(const std::string& value) { headline_data_ = value; }

std::size_t Headline::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("Headline", offset + 2, length);
    headline_length_ = wire::read_u16_le(data + offset);
    offset += 2;

    {
        const std::size_t count = static_cast<std::size_t>(headline_length_);
        wire::require("Headline", offset + count, length);
        headline_data_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t Headline::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Headline", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto headline_length = headline_length_;
    headline_length = static_cast<std::uint16_t>(headline_data_.size());

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(headline_length));
    offset += 2;

    wire::require_capacity("encode", offset + headline_data_.size(), capacity);
    wire::write_text(data + offset, headline_data_.size(), ' ', headline_data_);
    offset += headline_data_.size();

    return offset;
}

std::size_t Headline::encoded_size() const {
    return 2 + headline_data_.size();
}

void Headline::print(std::ostream& out) const {
    out << "Headline{";
    out << "headline_length=";
    out << headline_length_;
    out << ", headline_data=";
    print::text(out, headline_data_);
    out << '}';
}

bool Headline::operator==(const Headline& other) const {
    return headline_length_ == other.headline_length_
        && headline_data_ == other.headline_data_;
}

bool Headline::operator!=(const Headline& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Headline& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
