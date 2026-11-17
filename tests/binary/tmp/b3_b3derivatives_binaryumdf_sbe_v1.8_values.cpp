// B3.B3Derivatives.BinaryUmdf.Sbe.v1.8 canonical values, through the Tmp header: every value the Tmp reading hands
// over from each sample, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/tmp/b3/b3derivatives/binaryumdf/sbe/v1.8/b3_b3derivatives_binaryumdf_sbe_v1_8.hpp"

// B3 B3Derivatives BinaryUmdf Sbe 1.8: the reading of its packets, through its Template Meta Programming header
namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

/////////////////////////////////////////////////////////////////////
// Reading
/////////////////////////////////////////////////////////////////////

namespace tmp {
    // Thrown when the bytes end before what they must hold
    struct short_read : std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    inline void require(std::size_t needed, std::size_t available) {
        if (needed > available) {
            throw short_read(std::to_string(needed) + " bytes needed, " + std::to_string(available) + " available");
        }
    }

    // The bytes left for a member when the members after it take some: refused when fewer remain
    inline std::size_t leaving(std::size_t available, std::size_t taken) {
        require(taken, available);
        return available - taken;
    }

    // Hand the handler a value, when it takes one
    template <typename Handler, typename T>
    constexpr void call(Handler& handler, const T& value) {
        if constexpr (requires { handler(value); }) { handler(value); }
    }

    // A type laid over its bytes, handed to the handler
    template <typename T, typename Handler>
    const T& read(const std::byte* data, std::size_t length, Handler& handler) {
        require(T::size, length);
        const auto& value = *reinterpret_cast<const T*>(data);
        call(handler, value);
        return value;
    }

    // A field as a rule reads it: an enum by the code the wire holds, a field by its value, and a
    // bit - which its bitfield answers as a value - as it is
    template <typename T>
    constexpr auto rule(const T& field) noexcept {
        if constexpr (requires { field.raw(); }) { return field.raw(); }
        else if constexpr (requires { field.value(); }) { return field.value(); }
        else { return field; }
    }

    // A field an optional member may hold, read as its type's zero when the member is absent
    template <typename T>
    struct maybe {
        const T* field;

        constexpr auto value() const noexcept {
            using type = decltype(field->value());
            return field != nullptr ? field->value() : type{};
        }

        constexpr auto raw() const noexcept requires requires(const T& held) { held.raw(); } {
            using type = decltype(field->raw());
            return field != nullptr ? field->raw() : type{};
        }

        // a bit of an optional bitfield, nothing when the bitfield is absent
        template <typename Bit>
        constexpr auto get() const noexcept requires requires(const T& held) { held.template get<Bit>(); } {
            using type = std::remove_cvref_t<decltype(field->template get<Bit>())>;
            return field != nullptr ? type{ field->template get<Bit>() } : type{};
        }
    };

    // A type laid over its bytes without handing it on: a frame's length, read before the frame is
    template <typename T>
    const T& at(const std::byte* data) noexcept {
        return *reinterpret_cast<const T*>(data);
    }

    // A type laid over bytes ahead of the walk, at a place every byte before it fixes, which a rule
    // reads before the walk reaches it: a branch's code in the header its messages begin with
    template <typename T>
    const T& ahead(const std::byte* data, std::size_t length, std::size_t at) {
        require(at + T::size, length);
        return *reinterpret_cast<const T*>(data + at);
    }

    // A type laid over its bytes and handed to the handler; what it returns is the bytes it took
    template <typename T, typename Handler>
    std::size_t take(const std::byte* data, std::size_t length, Handler& handler) {
        read<T>(data, length, handler);
        return T::size;
    }

    // The characters before a terminating zero, which the bytes must hold
    inline std::size_t terminated(const std::byte* data, std::size_t length) {
        for (std::size_t index = 0; index < length; ++index) {
            if (data[index] == std::byte{ 0 }) { return index; }
        }
        throw short_read("no terminator in " + std::to_string(length) + " bytes");
    }

    // The bytes before the first of a field's delimiters, which it leaves for what follows it; at
    // most its maximum, and the bytes must hold a delimiter when they are shorter than that
    template <std::size_t Count>
    std::size_t delimited(const std::byte* data, std::size_t length, std::size_t maximum, const std::array<std::byte, Count>& delimiters) {
        const std::size_t limit = std::min(maximum, length);
        for (std::size_t index = 0; index < limit; ++index) {
            for (const std::byte delimiter : delimiters) {
                if (data[index] == delimiter) { return index; }
            }
        }
        if (limit < length) { return limit; }
        throw short_read("no delimiter in " + std::to_string(length) + " bytes");
    }

    // The bytes of a frame ending on a terminator, the terminator included; none while the bytes
    // do not hold it yet
    inline std::size_t through(const std::byte* data, std::size_t length, std::byte terminator) noexcept {
        for (std::size_t index = 0; index < length; ++index) {
            if (data[index] == terminator) { return index + 1; }
        }
        return 0;
    }

    // Bytes a branch's code selects no message for, handed to the handler when it takes them
    template <typename Handler>
    void unknown(Handler& handler, const std::byte* data, std::size_t length) {
        if constexpr (requires { handler.unknown(data, length); }) { handler.unknown(data, length); }
    }

    // How many a count or a length states: a number, or digits of text
    template <typename T>
        requires std::is_integral_v<T>
    constexpr std::size_t count(T value) noexcept { return static_cast<std::size_t>(value); }

    inline std::size_t count(char digit) {
        if (digit < '0' || digit > '9') { throw short_read(std::string("'") + digit + "' is not a digit"); }
        return static_cast<std::size_t>(digit - '0');
    }

    inline std::size_t count(std::string_view digits) {
        std::size_t value = 0;
        for (const char digit : digits) {
            if (digit == ' ') { continue; }
            if (digit < '0' || digit > '9') { throw short_read("\"" + std::string(digits) + "\" is not a number"); }
            value = value * 10 + static_cast<std::size_t>(digit - '0');
        }
        return value;
    }
} // namespace tmp

/////////////////////////////////////////////////////////////////////
// Parsing
/////////////////////////////////////////////////////////////////////

// Snapshot Full Refresh Orders Mb O 71 Message No M D Entries Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_encoding_ = tmp::read<group_size_encoding>(data + offset, bound - offset, handler); offset += group_size_encoding::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Snapshot Full Refresh Orders Mb O 71 Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_snapshot_full_refresh_orders_mb_o_71_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& snapshot_full_refresh_orders_mb_o_71_message_section_1_ = tmp::read<snapshot_full_refresh_orders_mb_o_71_message_section_1>(data + offset, bound - offset, handler); offset += snapshot_full_refresh_orders_mb_o_71_message_section_1::size;
    offset += parse_snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups(data + offset, bound - offset, handler);
    return offset;
}

// Url Link: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_url_link([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& url_link_section_1_ = tmp::read<url_link_section_1>(data + offset, bound - offset, handler); offset += url_link_section_1::size;
    if (static_cast<bool>(tmp::rule(url_link_section_1_.template get<url_link_length>()) > 0)) {
        {
            const std::size_t size = static_cast<std::size_t>(tmp::rule(url_link_section_1_.template get<url_link_length>()));
            tmp::require(offset + size, bound);
            tmp::call(handler, url_link_data{ data + offset, size });
            offset += size;
        }
    }
    return offset;
}

// Text: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_text([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& text_section_1_ = tmp::read<text_section_1>(data + offset, bound - offset, handler); offset += text_section_1::size;
    if (static_cast<bool>(tmp::rule(text_section_1_.template get<text_length>()) > 0)) {
        {
            const std::size_t size = static_cast<std::size_t>(tmp::rule(text_section_1_.template get<text_length>()));
            tmp::require(offset + size, bound);
            tmp::call(handler, text_data{ data + offset, size });
            offset += size;
        }
    }
    return offset;
}

// Headline: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_headline([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& headline_section_1_ = tmp::read<headline_section_1>(data + offset, bound - offset, handler); offset += headline_section_1::size;
    if (static_cast<bool>(tmp::rule(headline_section_1_.template get<headline_length>()) > 0)) {
        {
            const std::size_t size = static_cast<std::size_t>(tmp::rule(headline_section_1_.template get<headline_length>()));
            tmp::require(offset + size, bound);
            tmp::call(handler, headline_data{ data + offset, size });
            offset += size;
        }
    }
    return offset;
}

// News 5 Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_news_5_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& news_5_message_section_1_ = tmp::read<news_5_message_section_1>(data + offset, bound - offset, handler); offset += news_5_message_section_1::size;
    offset += parse_headline(data + offset, bound - offset, handler);
    offset += parse_text(data + offset, bound - offset, handler);
    offset += parse_url_link(data + offset, bound - offset, handler);
    return offset;
}

// Security Desc: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_security_desc([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& security_desc_section_1_ = tmp::read<security_desc_section_1>(data + offset, bound - offset, handler); offset += security_desc_section_1::size;
    if (static_cast<bool>(tmp::rule(security_desc_section_1_.template get<security_desc_length>()) > 0)) {
        {
            const std::size_t size = static_cast<std::size_t>(tmp::rule(security_desc_section_1_.template get<security_desc_length>()));
            tmp::require(offset + size, bound);
            tmp::call(handler, security_desc_data{ data + offset, size });
            offset += size;
        }
    }
    return offset;
}

// Instr Attribs Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_instr_attribs_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_encoding_ = tmp::read<group_size_encoding>(data + offset, bound - offset, handler); offset += group_size_encoding::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<instr_attribs_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Legs Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_legs_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_encoding_ = tmp::read<group_size_encoding>(data + offset, bound - offset, handler); offset += group_size_encoding::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<legs_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Underlyings Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_underlyings_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_encoding_ = tmp::read<group_size_encoding>(data + offset, bound - offset, handler); offset += group_size_encoding::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<underlyings_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Security Definition Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_security_definition_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& security_definition_message_section_1_ = tmp::read<security_definition_message_section_1>(data + offset, bound - offset, handler); offset += security_definition_message_section_1::size;
    offset += parse_underlyings_groups(data + offset, bound - offset, handler);
    offset += parse_legs_groups(data + offset, bound - offset, handler);
    offset += parse_instr_attribs_groups(data + offset, bound - offset, handler);
    offset += parse_security_desc(data + offset, bound - offset, handler);
    return offset;
}

// Deprecated Instr Attribs Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_deprecated_instr_attribs_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_encoding_ = tmp::read<group_size_encoding>(data + offset, bound - offset, handler); offset += group_size_encoding::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<deprecated_instr_attribs_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Deprecated Legs Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_deprecated_legs_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_encoding_ = tmp::read<group_size_encoding>(data + offset, bound - offset, handler); offset += group_size_encoding::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<deprecated_legs_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Deprecated Underlyings Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_deprecated_underlyings_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_encoding_ = tmp::read<group_size_encoding>(data + offset, bound - offset, handler); offset += group_size_encoding::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<deprecated_underlyings_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Deprecated Security Definition Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_deprecated_security_definition_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& deprecated_security_definition_message_section_1_ = tmp::read<deprecated_security_definition_message_section_1>(data + offset, bound - offset, handler); offset += deprecated_security_definition_message_section_1::size;
    offset += parse_deprecated_underlyings_groups(data + offset, bound - offset, handler);
    offset += parse_deprecated_legs_groups(data + offset, bound - offset, handler);
    offset += parse_deprecated_instr_attribs_groups(data + offset, bound - offset, handler);
    offset += parse_security_desc(data + offset, bound - offset, handler);
    return offset;
}

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const template_id& template_id_, const block_length& block_length_) {
    if (static_cast<bool>(tmp::rule(template_id_) == 1)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, sequence_reset_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 2)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<sequence_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 9)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<empty_book_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 11)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<channel_reset_11_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 3)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<security_status_3_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 10)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<security_group_phase_10_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 4)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_deprecated_security_definition_message(data + offset, bound - offset, handler);
            tmp::call(handler, deprecated_security_definition_message{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 12)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_security_definition_message(data + offset, bound - offset, handler);
            tmp::call(handler, security_definition_message{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 5)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_news_5_message(data + offset, bound - offset, handler);
            tmp::call(handler, news_5_message{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 15)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<opening_price_15_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 16)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<theoretical_opening_price_16_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 17)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<closing_price_17_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 19)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<auction_imbalance_19_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 20)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<price_band_20_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 21)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<quantity_band_21_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 22)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<price_band_22_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 24)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<high_price_24_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 25)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<low_price_25_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 27)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<last_trade_price_27_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 28)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<settlement_price_28_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 29)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<open_interest_29_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 30)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<snapshot_full_refresh_header_30_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 50)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<order_mb_o_50_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 51)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<delete_order_mb_o_51_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 52)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<mass_delete_orders_mb_o_52_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 53)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<trade_53_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 54)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<forward_trade_54_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 55)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<execution_summary_55_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 56)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<execution_statistics_56_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 57)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<trade_bust_57_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 71)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_snapshot_full_refresh_orders_mb_o_71_message(data + offset, bound - offset, handler);
            tmp::call(handler, snapshot_full_refresh_orders_mb_o_71_message{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& message_section_1_ = tmp::read<message_section_1>(data + offset, bound - offset, handler); offset += message_section_1::size;
    bound = static_cast<std::size_t>(tmp::rule(message_section_1_.template get<framing_header>().template get<message_length>()));
    tmp::require(bound, length);
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(message_section_1_.template get<framing_header>().template get<message_length>()))) - 12);
        tmp::require(offset + size, bound);
        parse_payload(data + offset, size, handler, message_section_1_.template get<message_header>().template get<template_id>(), message_section_1_.template get<message_header>().template get<block_length>());
        offset += size;
    }
    return bound;
}

// Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& packet_header_ = tmp::read<packet_header>(data + offset, bound - offset, handler); offset += packet_header::size;
    {
        const std::size_t end = static_cast<std::size_t>(static_cast<std::int64_t>(bound));
        tmp::require(end, bound);
        while (offset < end) {
            [[maybe_unused]] const std::size_t bound = end;
            offset += parse_message(data + offset, bound - offset, handler);
        }
    }
    return offset;
}


} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8

namespace protocol = ::b3::b3derivatives::binaryumdf::sbe::v1_8;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;
    std::string entry;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::packet_header& header) {
        if constexpr (requires { header.template get<protocol::channel_id>(); }) { values["packet.packetheader.channelid"] = canonical::number(header.template get<protocol::channel_id>().value()); }
        if constexpr (requires { header.template get<protocol::packet_reserved>(); }) { values["packet.packetheader.packetreserved"] = canonical::number(header.template get<protocol::packet_reserved>().value()); }
        if constexpr (requires { header.template get<protocol::sequence_version>(); }) { values["packet.packetheader.sequenceversion"] = canonical::number(header.template get<protocol::sequence_version>().value()); }
        if constexpr (requires { header.template get<protocol::sequence_number>(); }) { values["packet.packetheader.sequencenumber"] = canonical::number(header.template get<protocol::sequence_number>().value()); }
        if constexpr (requires { header.template get<protocol::sending_time>(); }) { values["packet.packetheader.sendingtime"] = canonical::number(header.template get<protocol::sending_time>().value()); }
    }

    void operator()(const protocol::framing_header& header) {
        entry = "packet.message[" + std::to_string(index++) + "]";
        if constexpr (requires { header.template get<protocol::message_length>(); }) { values[entry + ".framingheader.messagelength"] = canonical::number(header.template get<protocol::message_length>().value()); }
        if constexpr (requires { header.template get<protocol::encoding_type>(); }) { values[entry + ".framingheader.encodingtype"] = canonical::number(header.template get<protocol::encoding_type>().value()); }
    }

    void operator()(const protocol::sequence_message& message) {
        values[entry + ".payload"] = "packet.message.payload.sequencemessage";
        if constexpr (requires { message.template get<protocol::next_seq_no>(); }) { values[entry + ".payload.sequencemessage.nextseqno"] = canonical::number(message.template get<protocol::next_seq_no>().value()); }
    }

    void operator()(const protocol::empty_book_message& message) {
        values[entry + ".payload"] = "packet.message.payload.emptybookmessage";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.emptybookmessage.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.emptybookmessage.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::channel_reset_11_message& message) {
        values[entry + ".payload"] = "packet.message.payload.channelreset11message";
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.channelreset11message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::security_status_3_message& message) {
        values[entry + ".payload"] = "packet.message.payload.securitystatus3message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.securitystatus3message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { values[entry + ".payload.securitystatus3message.tradingsessionid"] = canonical::number(message.template get<protocol::trading_session_id>().value()); }
        if constexpr (requires { message.template get<protocol::security_trading_status>(); }) { values[entry + ".payload.securitystatus3message.securitytradingstatus"] = canonical::number(message.template get<protocol::security_trading_status>().value()); }
        if constexpr (requires { message.template get<protocol::security_trading_event>(); }) { values[entry + ".payload.securitystatus3message.securitytradingevent"] = (static_cast<std::uint8_t>(message.template get<protocol::security_trading_event>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::security_trading_event>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.securitystatus3message.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::trad_ses_open_time>(); }) { values[entry + ".payload.securitystatus3message.tradsesopentime"] = (static_cast<std::uint64_t>(message.template get<protocol::trad_ses_open_time>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trad_ses_open_time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.securitystatus3message.transacttime"] = (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::transact_time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.securitystatus3message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::security_group_phase_10_message& message) {
        values[entry + ".payload"] = "packet.message.payload.securitygroupphase10message";
        if constexpr (requires { message.template get<protocol::security_group>(); }) { values[entry + ".payload.securitygroupphase10message.securitygroup"] = canonical::text(std::string(message.template get<protocol::security_group>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { values[entry + ".payload.securitygroupphase10message.tradingsessionid"] = canonical::number(message.template get<protocol::trading_session_id>().value()); }
        if constexpr (requires { message.template get<protocol::trading_session_sub_id>(); }) { values[entry + ".payload.securitygroupphase10message.tradingsessionsubid"] = canonical::number(message.template get<protocol::trading_session_sub_id>().value()); }
        if constexpr (requires { message.template get<protocol::security_trading_event>(); }) { values[entry + ".payload.securitygroupphase10message.securitytradingevent"] = (static_cast<std::uint8_t>(message.template get<protocol::security_trading_event>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::security_trading_event>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.securitygroupphase10message.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::trad_ses_open_time>(); }) { values[entry + ".payload.securitygroupphase10message.tradsesopentime"] = (static_cast<std::uint64_t>(message.template get<protocol::trad_ses_open_time>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trad_ses_open_time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { values[entry + ".payload.securitygroupphase10message.transacttime"] = (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::transact_time>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::deprecated_security_definition_message&) {
        values[entry + ".payload"] = "packet.message.payload.deprecatedsecuritydefinitionmessage";
    }

    void operator()(const protocol::security_definition_message&) {
        values[entry + ".payload"] = "packet.message.payload.securitydefinitionmessage";
    }

    void operator()(const protocol::news_5_message&) {
        values[entry + ".payload"] = "packet.message.payload.news5message";
    }

    void operator()(const protocol::opening_price_15_message& message) {
        values[entry + ".payload"] = "packet.message.payload.openingprice15message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.openingprice15message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_update_action>(); }) { values[entry + ".payload.openingprice15message.mdupdateaction"] = canonical::number(message.template get<protocol::md_update_action>().value()); }
        if constexpr (requires { message.template get<protocol::open_close_settl_flag>(); }) { values[entry + ".payload.openingprice15message.openclosesettlflag"] = canonical::number(message.template get<protocol::open_close_settl_flag>().value()); }
        if constexpr (requires { message.template get<protocol::md_future_price>(); }) { values[entry + ".payload.openingprice15message.mdfutureprice"] = canonical::scaled(message.template get<protocol::md_future_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::net_chg_prev_day>(); }) { values[entry + ".payload.openingprice15message.netchgprevday"] = (static_cast<std::uint64_t>(message.template get<protocol::net_chg_prev_day>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::net_chg_prev_day>().value(), -8) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.openingprice15message.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.openingprice15message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.openingprice15message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::theoretical_opening_price_16_message& message) {
        values[entry + ".payload"] = "packet.message.payload.theoreticalopeningprice16message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.theoreticalopeningprice16message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_update_action>(); }) { values[entry + ".payload.theoreticalopeningprice16message.mdupdateaction"] = canonical::number(message.template get<protocol::md_update_action>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.theoreticalopeningprice16message.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::md_corporate_offset_price_optional>(); }) { values[entry + ".payload.theoreticalopeningprice16message.mdcorporateoffsetpriceoptional"] = (static_cast<std::uint64_t>(message.template get<protocol::md_corporate_offset_price_optional>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::md_corporate_offset_price_optional>().value(), -4) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::md_entry_size_optional>(); }) { values[entry + ".payload.theoreticalopeningprice16message.mdentrysizeoptional"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_size_optional>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::md_entry_size_optional>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.theoreticalopeningprice16message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.theoreticalopeningprice16message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::closing_price_17_message& message) {
        values[entry + ".payload"] = "packet.message.payload.closingprice17message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.closingprice17message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::open_close_settl_flag>(); }) { values[entry + ".payload.closingprice17message.openclosesettlflag"] = canonical::number(message.template get<protocol::open_close_settl_flag>().value()); }
        if constexpr (requires { message.template get<protocol::md_corporate_price>(); }) { values[entry + ".payload.closingprice17message.mdcorporateprice"] = canonical::scaled(message.template get<protocol::md_corporate_price>().value(), -8); }
        if constexpr (requires { message.template get<protocol::last_trade_date>(); }) { values[entry + ".payload.closingprice17message.lasttradedate"] = (static_cast<std::uint16_t>(message.template get<protocol::last_trade_date>().value()) != 0x0U ? canonical::number(message.template get<protocol::last_trade_date>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.closingprice17message.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.closingprice17message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.closingprice17message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::auction_imbalance_19_message& message) {
        values[entry + ".payload"] = "packet.message.payload.auctionimbalance19message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.auctionimbalance19message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_update_action>(); }) { values[entry + ".payload.auctionimbalance19message.mdupdateaction"] = canonical::number(message.template get<protocol::md_update_action>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_size_optional>(); }) { values[entry + ".payload.auctionimbalance19message.mdentrysizeoptional"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_size_optional>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::md_entry_size_optional>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.auctionimbalance19message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.auctionimbalance19message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::price_band_20_message& message) {
        values[entry + ".payload"] = "packet.message.payload.priceband20message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.priceband20message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::price_band_type>(); }) { values[entry + ".payload.priceband20message.pricebandtype"] = (static_cast<std::uint8_t>(message.template get<protocol::price_band_type>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::price_band_type>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::price_limit_type>(); }) { values[entry + ".payload.priceband20message.pricelimittype"] = (static_cast<std::uint8_t>(message.template get<protocol::price_limit_type>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::price_limit_type>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::price_band_midpoint_price_type>(); }) { values[entry + ".payload.priceband20message.pricebandmidpointpricetype"] = (static_cast<std::uint8_t>(message.template get<protocol::price_band_midpoint_price_type>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::price_band_midpoint_price_type>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::low_limit_price>(); }) { values[entry + ".payload.priceband20message.lowlimitprice"] = (static_cast<std::uint64_t>(message.template get<protocol::low_limit_price>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::low_limit_price>().value(), -4) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::high_limit_price>(); }) { values[entry + ".payload.priceband20message.highlimitprice"] = (static_cast<std::uint64_t>(message.template get<protocol::high_limit_price>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::high_limit_price>().value(), -4) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trading_reference_price_legacy>(); }) { values[entry + ".payload.priceband20message.tradingreferencepricelegacy"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_reference_price_legacy>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::trading_reference_price_legacy>().value(), -4) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.priceband20message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.priceband20message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::quantity_band_21_message& message) {
        values[entry + ".payload"] = "packet.message.payload.quantityband21message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.quantityband21message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::avg_daily_traded_qty>(); }) { values[entry + ".payload.quantityband21message.avgdailytradedqty"] = (static_cast<std::uint64_t>(message.template get<protocol::avg_daily_traded_qty>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::avg_daily_traded_qty>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::max_trade_vol>(); }) { values[entry + ".payload.quantityband21message.maxtradevol"] = (static_cast<std::uint64_t>(message.template get<protocol::max_trade_vol>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::max_trade_vol>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.quantityband21message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.quantityband21message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::price_band_22_message& message) {
        values[entry + ".payload"] = "packet.message.payload.priceband22message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.priceband22message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::price_band_type>(); }) { values[entry + ".payload.priceband22message.pricebandtype"] = (static_cast<std::uint8_t>(message.template get<protocol::price_band_type>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::price_band_type>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::price_limit_type>(); }) { values[entry + ".payload.priceband22message.pricelimittype"] = (static_cast<std::uint8_t>(message.template get<protocol::price_limit_type>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::price_limit_type>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::price_band_midpoint_price_type>(); }) { values[entry + ".payload.priceband22message.pricebandmidpointpricetype"] = (static_cast<std::uint8_t>(message.template get<protocol::price_band_midpoint_price_type>().value()) != 0x0FFU ? canonical::number(message.template get<protocol::price_band_midpoint_price_type>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::low_limit_price>(); }) { values[entry + ".payload.priceband22message.lowlimitprice"] = (static_cast<std::uint64_t>(message.template get<protocol::low_limit_price>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::low_limit_price>().value(), -4) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::high_limit_price>(); }) { values[entry + ".payload.priceband22message.highlimitprice"] = (static_cast<std::uint64_t>(message.template get<protocol::high_limit_price>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::high_limit_price>().value(), -4) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trading_reference_price_optional>(); }) { values[entry + ".payload.priceband22message.tradingreferencepriceoptional"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_reference_price_optional>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::trading_reference_price_optional>().value(), -8) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.priceband22message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.priceband22message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::high_price_24_message& message) {
        values[entry + ".payload"] = "packet.message.payload.highprice24message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.highprice24message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_update_action>(); }) { values[entry + ".payload.highprice24message.mdupdateaction"] = canonical::number(message.template get<protocol::md_update_action>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.highprice24message.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::md_future_price>(); }) { values[entry + ".payload.highprice24message.mdfutureprice"] = canonical::scaled(message.template get<protocol::md_future_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.highprice24message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.highprice24message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::low_price_25_message& message) {
        values[entry + ".payload"] = "packet.message.payload.lowprice25message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.lowprice25message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_update_action>(); }) { values[entry + ".payload.lowprice25message.mdupdateaction"] = canonical::number(message.template get<protocol::md_update_action>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.lowprice25message.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::md_future_price>(); }) { values[entry + ".payload.lowprice25message.mdfutureprice"] = canonical::scaled(message.template get<protocol::md_future_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.lowprice25message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.lowprice25message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::last_trade_price_27_message& message) {
        values[entry + ".payload"] = "packet.message.payload.lasttradeprice27message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.lasttradeprice27message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { values[entry + ".payload.lasttradeprice27message.tradingsessionid"] = canonical::number(message.template get<protocol::trading_session_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_future_price>(); }) { values[entry + ".payload.lasttradeprice27message.mdfutureprice"] = canonical::scaled(message.template get<protocol::md_future_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::md_entry_size>(); }) { values[entry + ".payload.lasttradeprice27message.mdentrysize"] = canonical::number(message.template get<protocol::md_entry_size>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".payload.lasttradeprice27message.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_buyer>(); }) { values[entry + ".payload.lasttradeprice27message.mdentrybuyer"] = (static_cast<std::uint32_t>(message.template get<protocol::md_entry_buyer>().value()) != 0x0U ? canonical::number(message.template get<protocol::md_entry_buyer>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::md_entry_seller>(); }) { values[entry + ".payload.lasttradeprice27message.mdentryseller"] = (static_cast<std::uint32_t>(message.template get<protocol::md_entry_seller>().value()) != 0x0U ? canonical::number(message.template get<protocol::md_entry_seller>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.lasttradeprice27message.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.lasttradeprice27message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.lasttradeprice27message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::seller_days>(); }) { values[entry + ".payload.lasttradeprice27message.sellerdays"] = (static_cast<std::uint16_t>(message.template get<protocol::seller_days>().value()) != 0x0U ? canonical::number(message.template get<protocol::seller_days>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::md_entry_interest_rate>(); }) { values[entry + ".payload.lasttradeprice27message.mdentryinterestrate"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_interest_rate>().value()) != 0x0ULL ? canonical::scaled(message.template get<protocol::md_entry_interest_rate>().value(), -4) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trd_sub_type>(); }) { values[entry + ".payload.lasttradeprice27message.trdsubtype"] = (static_cast<std::uint8_t>(message.template get<protocol::trd_sub_type>().value()) != 0x0U ? canonical::number(message.template get<protocol::trd_sub_type>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::settlement_price_28_message& message) {
        values[entry + ".payload"] = "packet.message.payload.settlementprice28message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.settlementprice28message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.settlementprice28message.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::md_future_price>(); }) { values[entry + ".payload.settlementprice28message.mdfutureprice"] = canonical::scaled(message.template get<protocol::md_future_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.settlementprice28message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::open_close_settl_flag>(); }) { values[entry + ".payload.settlementprice28message.openclosesettlflag"] = canonical::number(message.template get<protocol::open_close_settl_flag>().value()); }
        if constexpr (requires { message.template get<protocol::price_type>(); }) { values[entry + ".payload.settlementprice28message.pricetype"] = canonical::number(message.template get<protocol::price_type>().value()); }
        if constexpr (requires { message.template get<protocol::settl_price_type>(); }) { values[entry + ".payload.settlementprice28message.settlpricetype"] = canonical::number(message.template get<protocol::settl_price_type>().value()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.settlementprice28message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::open_interest_29_message& message) {
        values[entry + ".payload"] = "packet.message.payload.openinterest29message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.openinterest29message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.openinterest29message.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_size>(); }) { values[entry + ".payload.openinterest29message.mdentrysize"] = canonical::number(message.template get<protocol::md_entry_size>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.openinterest29message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.openinterest29message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::snapshot_full_refresh_header_30_message& message) {
        values[entry + ".payload"] = "packet.message.payload.snapshotfullrefreshheader30message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.snapshotfullrefreshheader30message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::last_msg_seq_num_processed>(); }) { values[entry + ".payload.snapshotfullrefreshheader30message.lastmsgseqnumprocessed"] = canonical::number(message.template get<protocol::last_msg_seq_num_processed>().value()); }
        if constexpr (requires { message.template get<protocol::tot_num_reports>(); }) { values[entry + ".payload.snapshotfullrefreshheader30message.totnumreports"] = canonical::number(message.template get<protocol::tot_num_reports>().value()); }
        if constexpr (requires { message.template get<protocol::tot_num_bids>(); }) { values[entry + ".payload.snapshotfullrefreshheader30message.totnumbids"] = canonical::number(message.template get<protocol::tot_num_bids>().value()); }
        if constexpr (requires { message.template get<protocol::tot_num_offers>(); }) { values[entry + ".payload.snapshotfullrefreshheader30message.totnumoffers"] = canonical::number(message.template get<protocol::tot_num_offers>().value()); }
        if constexpr (requires { message.template get<protocol::tot_num_stats>(); }) { values[entry + ".payload.snapshotfullrefreshheader30message.totnumstats"] = canonical::number(message.template get<protocol::tot_num_stats>().value()); }
        if constexpr (requires { message.template get<protocol::last_rpt_seq>(); }) { values[entry + ".payload.snapshotfullrefreshheader30message.lastrptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::last_rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::last_rpt_seq>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::order_mb_o_50_message& message) {
        values[entry + ".payload"] = "packet.message.payload.ordermbo50message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.ordermbo50message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_update_action>(); }) { values[entry + ".payload.ordermbo50message.mdupdateaction"] = canonical::number(message.template get<protocol::md_update_action>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_type>(); }) { values[entry + ".payload.ordermbo50message.mdentrytype"] = canonical::text(canonical::character(message.template get<protocol::md_entry_type>().value())); }
        if constexpr (requires { message.template get<protocol::md_corporate_offset_price_optional>(); }) { values[entry + ".payload.ordermbo50message.mdcorporateoffsetpriceoptional"] = (static_cast<std::uint64_t>(message.template get<protocol::md_corporate_offset_price_optional>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::md_corporate_offset_price_optional>().value(), -4) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::md_entry_size>(); }) { values[entry + ".payload.ordermbo50message.mdentrysize"] = canonical::number(message.template get<protocol::md_entry_size>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_position_no>(); }) { values[entry + ".payload.ordermbo50message.mdentrypositionno"] = canonical::number(message.template get<protocol::md_entry_position_no>().value()); }
        if constexpr (requires { message.template get<protocol::entering_firm>(); }) { values[entry + ".payload.ordermbo50message.enteringfirm"] = (static_cast<std::uint32_t>(message.template get<protocol::entering_firm>().value()) != 0x0U ? canonical::number(message.template get<protocol::entering_firm>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::md_insert_timestamp>(); }) { values[entry + ".payload.ordermbo50message.mdinserttimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_insert_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_insert_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::secondary_order_id>(); }) { values[entry + ".payload.ordermbo50message.secondaryorderid"] = canonical::number(message.template get<protocol::secondary_order_id>().value()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.ordermbo50message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.ordermbo50message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::delete_order_mb_o_51_message& message) {
        values[entry + ".payload"] = "packet.message.payload.deleteordermbo51message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.deleteordermbo51message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_type>(); }) { values[entry + ".payload.deleteordermbo51message.mdentrytype"] = canonical::text(canonical::character(message.template get<protocol::md_entry_type>().value())); }
        if constexpr (requires { message.template get<protocol::md_entry_position_no>(); }) { values[entry + ".payload.deleteordermbo51message.mdentrypositionno"] = canonical::number(message.template get<protocol::md_entry_position_no>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_size_optional>(); }) { values[entry + ".payload.deleteordermbo51message.mdentrysizeoptional"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_size_optional>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::md_entry_size_optional>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::secondary_order_id>(); }) { values[entry + ".payload.deleteordermbo51message.secondaryorderid"] = canonical::number(message.template get<protocol::secondary_order_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.deleteordermbo51message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.deleteordermbo51message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::mass_delete_orders_mb_o_52_message& message) {
        values[entry + ".payload"] = "packet.message.payload.massdeleteordersmbo52message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.massdeleteordersmbo52message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_update_action>(); }) { values[entry + ".payload.massdeleteordersmbo52message.mdupdateaction"] = canonical::number(message.template get<protocol::md_update_action>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_type>(); }) { values[entry + ".payload.massdeleteordersmbo52message.mdentrytype"] = canonical::text(canonical::character(message.template get<protocol::md_entry_type>().value())); }
        if constexpr (requires { message.template get<protocol::md_entry_position_no>(); }) { values[entry + ".payload.massdeleteordersmbo52message.mdentrypositionno"] = canonical::number(message.template get<protocol::md_entry_position_no>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.massdeleteordersmbo52message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.massdeleteordersmbo52message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::trade_53_message& message) {
        values[entry + ".payload"] = "packet.message.payload.trade53message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.trade53message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { values[entry + ".payload.trade53message.tradingsessionid"] = canonical::number(message.template get<protocol::trading_session_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_future_price>(); }) { values[entry + ".payload.trade53message.mdfutureprice"] = canonical::scaled(message.template get<protocol::md_future_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::md_entry_size>(); }) { values[entry + ".payload.trade53message.mdentrysize"] = canonical::number(message.template get<protocol::md_entry_size>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".payload.trade53message.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_buyer>(); }) { values[entry + ".payload.trade53message.mdentrybuyer"] = (static_cast<std::uint32_t>(message.template get<protocol::md_entry_buyer>().value()) != 0x0U ? canonical::number(message.template get<protocol::md_entry_buyer>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::md_entry_seller>(); }) { values[entry + ".payload.trade53message.mdentryseller"] = (static_cast<std::uint32_t>(message.template get<protocol::md_entry_seller>().value()) != 0x0U ? canonical::number(message.template get<protocol::md_entry_seller>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.trade53message.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::trd_sub_type>(); }) { values[entry + ".payload.trade53message.trdsubtype"] = (static_cast<std::uint8_t>(message.template get<protocol::trd_sub_type>().value()) != 0x0U ? canonical::number(message.template get<protocol::trd_sub_type>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.trade53message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.trade53message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::forward_trade_54_message& message) {
        values[entry + ".payload"] = "packet.message.payload.forwardtrade54message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.forwardtrade54message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { values[entry + ".payload.forwardtrade54message.tradingsessionid"] = canonical::number(message.template get<protocol::trading_session_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_future_price>(); }) { values[entry + ".payload.forwardtrade54message.mdfutureprice"] = canonical::scaled(message.template get<protocol::md_future_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::md_entry_size>(); }) { values[entry + ".payload.forwardtrade54message.mdentrysize"] = canonical::number(message.template get<protocol::md_entry_size>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".payload.forwardtrade54message.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_buyer>(); }) { values[entry + ".payload.forwardtrade54message.mdentrybuyer"] = (static_cast<std::uint32_t>(message.template get<protocol::md_entry_buyer>().value()) != 0x0U ? canonical::number(message.template get<protocol::md_entry_buyer>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::md_entry_seller>(); }) { values[entry + ".payload.forwardtrade54message.mdentryseller"] = (static_cast<std::uint32_t>(message.template get<protocol::md_entry_seller>().value()) != 0x0U ? canonical::number(message.template get<protocol::md_entry_seller>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.forwardtrade54message.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.forwardtrade54message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.forwardtrade54message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::seller_days>(); }) { values[entry + ".payload.forwardtrade54message.sellerdays"] = (static_cast<std::uint16_t>(message.template get<protocol::seller_days>().value()) != 0x0U ? canonical::number(message.template get<protocol::seller_days>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::md_entry_interest_rate>(); }) { values[entry + ".payload.forwardtrade54message.mdentryinterestrate"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_interest_rate>().value()) != 0x0ULL ? canonical::scaled(message.template get<protocol::md_entry_interest_rate>().value(), -4) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trd_sub_type>(); }) { values[entry + ".payload.forwardtrade54message.trdsubtype"] = (static_cast<std::uint8_t>(message.template get<protocol::trd_sub_type>().value()) != 0x0U ? canonical::number(message.template get<protocol::trd_sub_type>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::execution_summary_55_message& message) {
        values[entry + ".payload"] = "packet.message.payload.executionsummary55message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.executionsummary55message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::aggressor_side>(); }) { values[entry + ".payload.executionsummary55message.aggressorside"] = canonical::number(message.template get<protocol::aggressor_side>().value()); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { values[entry + ".payload.executionsummary55message.lastpx"] = canonical::scaled(message.template get<protocol::last_px>().value(), -4); }
        if constexpr (requires { message.template get<protocol::fill_qty>(); }) { values[entry + ".payload.executionsummary55message.fillqty"] = canonical::number(message.template get<protocol::fill_qty>().value()); }
        if constexpr (requires { message.template get<protocol::traded_hidden_qty>(); }) { values[entry + ".payload.executionsummary55message.tradedhiddenqty"] = (static_cast<std::uint64_t>(message.template get<protocol::traded_hidden_qty>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::traded_hidden_qty>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::cxl_qty>(); }) { values[entry + ".payload.executionsummary55message.cxlqty"] = (static_cast<std::uint64_t>(message.template get<protocol::cxl_qty>().value()) != 0x08000000000000000ULL ? canonical::number(message.template get<protocol::cxl_qty>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::aggressor_time>(); }) { values[entry + ".payload.executionsummary55message.aggressortime"] = (static_cast<std::uint64_t>(message.template get<protocol::aggressor_time>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::aggressor_time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.executionsummary55message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.executionsummary55message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::execution_statistics_56_message& message) {
        values[entry + ".payload"] = "packet.message.payload.executionstatistics56message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.executionstatistics56message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { values[entry + ".payload.executionstatistics56message.tradingsessionid"] = canonical::number(message.template get<protocol::trading_session_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.executionstatistics56message.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::trade_volume>(); }) { values[entry + ".payload.executionstatistics56message.tradevolume"] = canonical::number(message.template get<protocol::trade_volume>().value()); }
        if constexpr (requires { message.template get<protocol::vwap_px>(); }) { values[entry + ".payload.executionstatistics56message.vwappx"] = (static_cast<std::uint64_t>(message.template get<protocol::vwap_px>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::vwap_px>().value(), -4) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::net_chg_prev_day>(); }) { values[entry + ".payload.executionstatistics56message.netchgprevday"] = (static_cast<std::uint64_t>(message.template get<protocol::net_chg_prev_day>().value()) != 0x08000000000000000ULL ? canonical::scaled(message.template get<protocol::net_chg_prev_day>().value(), -8) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::number_of_trades>(); }) { values[entry + ".payload.executionstatistics56message.numberoftrades"] = canonical::number(message.template get<protocol::number_of_trades>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.executionstatistics56message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.executionstatistics56message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::trade_bust_57_message& message) {
        values[entry + ".payload"] = "packet.message.payload.tradebust57message";
        if constexpr (requires { message.template get<protocol::security_id>(); }) { values[entry + ".payload.tradebust57message.securityid"] = canonical::number(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { values[entry + ".payload.tradebust57message.tradingsessionid"] = canonical::number(message.template get<protocol::trading_session_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_future_price>(); }) { values[entry + ".payload.tradebust57message.mdfutureprice"] = canonical::scaled(message.template get<protocol::md_future_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::md_entry_size>(); }) { values[entry + ".payload.tradebust57message.mdentrysize"] = canonical::number(message.template get<protocol::md_entry_size>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".payload.tradebust57message.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { values[entry + ".payload.tradebust57message.tradedate"] = canonical::number(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { values[entry + ".payload.tradebust57message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::md_entry_timestamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { values[entry + ".payload.tradebust57message.rptseq"] = (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? canonical::number(message.template get<protocol::rpt_seq>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::snapshot_full_refresh_orders_mb_o_71_message&) {
        values[entry + ".payload"] = "packet.message.payload.snapshotfullrefreshordersmbo71message";
    }
};

// The values the Tmp reading reads from one datagram, by indexed address. A datagram it cannot read
// is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::parse_packet(frame.payload, frame.payload_len, reader);
    } catch (const std::exception& error) {
        reader.values["(does not decode)"] = error.what();
    }

    return reader.values;
}

// Read each datagram of a sample with Tmp and hold it to the model's values
int check(const char* name, const char* capture, const char* expected) {
    const char* packets = std::getenv("OMI_PACKETS_DIR");

    if (packets == nullptr) {
        std::printf("FAIL: OMI_PACKETS_DIR is not set\n");
        return 1;
    }

    const auto model = canonical::load(canonical::root() + "/" + expected);
    std::vector<std::pair<std::string, std::int64_t>> sources;
    sources.emplace_back(std::string{packets} + "/" + capture, 0);

    packet::PcapIterator captures(sources);
    std::size_t datagram = 0;
    int differences = 0;

    while (captures.advance()) {
        const packet::Frame frame(captures.data(), captures.length());

        if (!frame.valid() || !frame.is_udp()) { continue; }

        if (datagram >= model.size()) {
            std::printf("FAIL %s: more datagrams than the model read\n", name);
            return 1;
        }

        differences += canonical::compare(name, datagram, model[datagram], read(frame));
        ++datagram;
    }

    if (datagram != model.size()) {
        std::printf("FAIL %s: %zu datagrams, the model read %zu\n", name, datagram, model.size());
        return 1;
    }

    if (differences == 0) {
        std::printf("ok   %s: %zu datagrams\n", name, datagram);
    }

    return differences == 0 ? 0 : 1;
}

}

int main() {
    std::printf("== B3.B3Derivatives.BinaryUmdf.Sbe.v1.8 (tmp values)\n");
    int failures = 0;
    failures += check("SecurityDefinitionMessage", "B3/B3Derivatives.BinaryUmdf.Sbe.v1.8/SecurityDefinitionMessage.pcap", "b3/b3derivatives/binaryumdf/sbe/v1.8/SecurityDefinitionMessage.values");
    failures += check("SequenceMessage", "B3/B3Derivatives.BinaryUmdf.Sbe.v1.8/SequenceMessage.pcap", "b3/b3derivatives/binaryumdf/sbe/v1.8/SequenceMessage.values");
    return failures == 0 ? 0 : 1;
}
