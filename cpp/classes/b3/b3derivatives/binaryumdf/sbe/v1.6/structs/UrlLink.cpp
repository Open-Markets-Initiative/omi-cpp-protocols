#include "UrlLink.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

UrlLink::UrlLink(std::uint16_t url_link_length, const std::string& url_link_data)
  : url_link_length_(url_link_length), url_link_data_(url_link_data) {}

std::uint16_t UrlLink::url_link_length() const { return url_link_length_; }
void UrlLink::set_url_link_length(std::uint16_t value) { url_link_length_ = value; }

const std::string& UrlLink::url_link_data() const { return url_link_data_; }
std::string& UrlLink::url_link_data() { return url_link_data_; }
void UrlLink::set_url_link_data(const std::string& value) { url_link_data_ = value; }

std::size_t UrlLink::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("UrlLink", offset + 2, length);
    url_link_length_ = wire::read_u16_le(data + offset);
    offset += 2;

    {
        const std::size_t count = static_cast<std::size_t>(url_link_length_);
        wire::require("UrlLink", offset + count, length);
        url_link_data_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t UrlLink::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UrlLink", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto url_link_length = url_link_length_;
    url_link_length = static_cast<std::uint16_t>(url_link_data_.size());

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(url_link_length));
    offset += 2;

    wire::require_capacity("encode", offset + url_link_data_.size(), capacity);
    wire::write_text(data + offset, url_link_data_.size(), ' ', url_link_data_);
    offset += url_link_data_.size();

    return offset;
}

std::size_t UrlLink::encoded_size() const {
    return 2 + url_link_data_.size();
}

void UrlLink::print(std::ostream& out) const {
    out << "UrlLink{";
    out << "url_link_length=";
    out << url_link_length_;
    out << ", url_link_data=";
    print::text(out, url_link_data_);
    out << '}';
}

bool UrlLink::operator==(const UrlLink& other) const {
    return url_link_length_ == other.url_link_length_
        && url_link_data_ == other.url_link_data_;
}

bool UrlLink::operator!=(const UrlLink& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const UrlLink& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
