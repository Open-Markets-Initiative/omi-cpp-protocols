// Nyse.ArcaOptions.TopFeed.Pillar.v1.2.c canonical values, through the Tmp header: every value the Tmp reading hands
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
#include "cpp/binary/tmp/nyse/arcaoptions/topfeed/pillar/v1.2.c/nyse_arcaoptions_topfeed_pillar_v1_2_c.hpp"

// Nyse ArcaOptions TopFeed Pillar 1.2.c: the reading of its packets, through its Template Meta Programming header
namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

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

// Refresh Header Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_refresh_header_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& refresh_header_message_section_1_ = tmp::read<refresh_header_message_section_1>(data + offset, bound - offset, handler); offset += refresh_header_message_section_1::size;
    if (static_cast<bool>(tmp::rule(refresh_header_message_section_1_.template get<current_refresh_pkt>()) == 1)) {
        offset += tmp::take<full_refresh_header>(data + offset, bound - offset, handler);
    }
    return offset;
}

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
    if (static_cast<bool>(tmp::rule(message_type_) == 1)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& sequence_number_reset_message_ = tmp::read<sequence_number_reset_message>(data + offset, bound - offset, handler); offset += sequence_number_reset_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 2)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& time_reference_message_ = tmp::read<time_reference_message>(data + offset, bound - offset, handler); offset += time_reference_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 3)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& symbol_index_mapping_message_ = tmp::read<symbol_index_mapping_message>(data + offset, bound - offset, handler); offset += symbol_index_mapping_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 10)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& retransmission_request_message_ = tmp::read<retransmission_request_message>(data + offset, bound - offset, handler); offset += retransmission_request_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 11)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& request_response_message_ = tmp::read<request_response_message>(data + offset, bound - offset, handler); offset += request_response_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 12)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& heartbeat_response_message_ = tmp::read<heartbeat_response_message>(data + offset, bound - offset, handler); offset += heartbeat_response_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 13)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& symbol_index_mapping_request_message_ = tmp::read<symbol_index_mapping_request_message>(data + offset, bound - offset, handler); offset += symbol_index_mapping_request_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 15)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& refresh_request_message_ = tmp::read<refresh_request_message>(data + offset, bound - offset, handler); offset += refresh_request_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 31)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& message_unavailable_message_ = tmp::read<message_unavailable_message>(data + offset, bound - offset, handler); offset += message_unavailable_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 32)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& symbol_clear_message_ = tmp::read<symbol_clear_message>(data + offset, bound - offset, handler); offset += symbol_clear_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 34)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& security_status_message_ = tmp::read<security_status_message>(data + offset, bound - offset, handler); offset += security_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 35)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_refresh_header_message(data + offset, bound - offset, handler);
        tmp::call(handler, refresh_header_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 50)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& outright_series_index_mapping_message_ = tmp::read<outright_series_index_mapping_message>(data + offset, bound - offset, handler); offset += outright_series_index_mapping_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 51)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& options_status_message_ = tmp::read<options_status_message>(data + offset, bound - offset, handler); offset += options_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 340)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& options_quote_message_ = tmp::read<options_quote_message>(data + offset, bound - offset, handler); offset += options_quote_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 320)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& options_trade_message_ = tmp::read<options_trade_message>(data + offset, bound - offset, handler); offset += options_trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 321)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& options_trade_cancel_message_ = tmp::read<options_trade_cancel_message>(data + offset, bound - offset, handler); offset += options_trade_cancel_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 322)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& options_trade_correction_message_ = tmp::read<options_trade_correction_message>(data + offset, bound - offset, handler); offset += options_trade_correction_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 305)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& options_imbalance_message_ = tmp::read<options_imbalance_message>(data + offset, bound - offset, handler); offset += options_imbalance_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 307)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& series_rfq_message_ = tmp::read<series_rfq_message>(data + offset, bound - offset, handler); offset += series_rfq_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 323)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& outright_series_summary_message_ = tmp::read<outright_series_summary_message>(data + offset, bound - offset, handler); offset += outright_series_summary_message::size;
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
    [[maybe_unused]] const auto& message_header_ = tmp::read<message_header>(data + offset, bound - offset, handler); offset += message_header::size;
    bound = static_cast<std::size_t>(tmp::rule(message_header_.template get<message_size>()));
    tmp::require(bound, length);
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(message_header_.template get<message_size>()))) - 4);
        tmp::require(offset + size, bound);
        parse_payload(data + offset, size, handler, message_header_.template get<message_type>());
        offset += size;
    }
    return bound;
}

// Messages: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_messages([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const delivery_flag& delivery_flag_) {
    if (static_cast<bool>(tmp::rule(delivery_flag_) == 1)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, heartbeat{});
        return offset;
    }
    {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
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
}

// Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& packet_header_ = tmp::read<packet_header>(data + offset, bound - offset, handler); offset += packet_header::size;
    offset += parse_messages(data + offset, bound - offset, handler, packet_header_.template get<delivery_flag>());
    return offset;
}


} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c

namespace protocol = ::nyse::arcaoptions::topfeed::pillar::v1_2_c;

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
        if constexpr (requires { header.template get<protocol::pkt_size>(); }) { values["packet.packetheader.pktsize"] = canonical::number(header.template get<protocol::pkt_size>().value()); }
        if constexpr (requires { header.template get<protocol::delivery_flag>(); }) { values["packet.packetheader.deliveryflag"] = canonical::number(header.template get<protocol::delivery_flag>().value()); }
        if constexpr (requires { header.template get<protocol::number_msgs>(); }) { values["packet.packetheader.numbermsgs"] = canonical::number(header.template get<protocol::number_msgs>().value()); }
        if constexpr (requires { header.template get<protocol::seq_num>(); }) { values["packet.packetheader.seqnum"] = canonical::number(header.template get<protocol::seq_num>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        entry = "packet.messages.message[" + std::to_string(index++) + "]";
        if constexpr (requires { header.template get<protocol::message_size>(); }) { values[entry + ".messageheader.messagesize"] = canonical::number(header.template get<protocol::message_size>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { values[entry + ".messageheader.messagetype"] = canonical::number(header.template get<protocol::message_type>().value()); }
    }

    void operator()(const protocol::sequence_number_reset_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.sequencenumberresetmessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.sequencenumberresetmessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.sequencenumberresetmessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::product_id>(); }) { values[entry + ".payload.sequencenumberresetmessage.productid"] = canonical::number(message.template get<protocol::product_id>().value()); }
        if constexpr (requires { message.template get<protocol::channel_id>(); }) { values[entry + ".payload.sequencenumberresetmessage.channelid"] = canonical::number(message.template get<protocol::channel_id>().value()); }
    }

    void operator()(const protocol::time_reference_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.timereferencemessage";
        if constexpr (requires { message.template get<protocol::id>(); }) { values[entry + ".payload.timereferencemessage.id"] = canonical::number(message.template get<protocol::id>().value()); }
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.timereferencemessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
    }

    void operator()(const protocol::symbol_index_mapping_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.symbolindexmappingmessage";
        if constexpr (requires { message.template get<protocol::symbol_index>(); }) { values[entry + ".payload.symbolindexmappingmessage.symbolindex"] = canonical::number(message.template get<protocol::symbol_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".payload.symbolindexmappingmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::market_id>(); }) { values[entry + ".payload.symbolindexmappingmessage.marketid"] = canonical::number(message.template get<protocol::market_id>().value()); }
        if constexpr (requires { message.template get<protocol::system_id>(); }) { values[entry + ".payload.symbolindexmappingmessage.systemid"] = canonical::number(message.template get<protocol::system_id>().value()); }
        if constexpr (requires { message.template get<protocol::exchange_code>(); }) { values[entry + ".payload.symbolindexmappingmessage.exchangecode"] = canonical::text(canonical::character(message.template get<protocol::exchange_code>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::price_scale_code>(); }) { values[entry + ".payload.symbolindexmappingmessage.pricescalecode"] = canonical::number(message.template get<protocol::price_scale_code>().value()); }
        if constexpr (requires { message.template get<protocol::security_type>(); }) { values[entry + ".payload.symbolindexmappingmessage.securitytype"] = canonical::text(canonical::character(message.template get<protocol::security_type>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::lot_size>(); }) { values[entry + ".payload.symbolindexmappingmessage.lotsize"] = canonical::number(message.template get<protocol::lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::prev_close_price>(); }) { values[entry + ".payload.symbolindexmappingmessage.prevcloseprice"] = canonical::number(message.template get<protocol::prev_close_price>().value()); }
        if constexpr (requires { message.template get<protocol::prev_close_volume>(); }) { values[entry + ".payload.symbolindexmappingmessage.prevclosevolume"] = canonical::number(message.template get<protocol::prev_close_volume>().value()); }
        if constexpr (requires { message.template get<protocol::price_resolution>(); }) { values[entry + ".payload.symbolindexmappingmessage.priceresolution"] = canonical::number(message.template get<protocol::price_resolution>().value()); }
        if constexpr (requires { message.template get<protocol::round_lot>(); }) { values[entry + ".payload.symbolindexmappingmessage.roundlot"] = canonical::text(canonical::character(message.template get<protocol::round_lot>().value()), '\0', false); }
    }

    void operator()(const protocol::retransmission_request_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.retransmissionrequestmessage";
        if constexpr (requires { message.template get<protocol::begin_seq_num>(); }) { values[entry + ".payload.retransmissionrequestmessage.beginseqnum"] = canonical::number(message.template get<protocol::begin_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::end_seq_num>(); }) { values[entry + ".payload.retransmissionrequestmessage.endseqnum"] = canonical::number(message.template get<protocol::end_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::source_id>(); }) { values[entry + ".payload.retransmissionrequestmessage.sourceid"] = canonical::text(std::string(message.template get<protocol::source_id>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::product_id>(); }) { values[entry + ".payload.retransmissionrequestmessage.productid"] = canonical::number(message.template get<protocol::product_id>().value()); }
        if constexpr (requires { message.template get<protocol::channel_id>(); }) { values[entry + ".payload.retransmissionrequestmessage.channelid"] = canonical::number(message.template get<protocol::channel_id>().value()); }
    }

    void operator()(const protocol::request_response_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.requestresponsemessage";
        if constexpr (requires { message.template get<protocol::request_seq_num>(); }) { values[entry + ".payload.requestresponsemessage.requestseqnum"] = canonical::number(message.template get<protocol::request_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::begin_seq_num>(); }) { values[entry + ".payload.requestresponsemessage.beginseqnum"] = canonical::number(message.template get<protocol::begin_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::end_seq_num>(); }) { values[entry + ".payload.requestresponsemessage.endseqnum"] = canonical::number(message.template get<protocol::end_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::source_id>(); }) { values[entry + ".payload.requestresponsemessage.sourceid"] = canonical::text(std::string(message.template get<protocol::source_id>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::product_id>(); }) { values[entry + ".payload.requestresponsemessage.productid"] = canonical::number(message.template get<protocol::product_id>().value()); }
        if constexpr (requires { message.template get<protocol::channel_id>(); }) { values[entry + ".payload.requestresponsemessage.channelid"] = canonical::number(message.template get<protocol::channel_id>().value()); }
        if constexpr (requires { message.template get<protocol::status>(); }) { values[entry + ".payload.requestresponsemessage.status"] = canonical::text(canonical::character(message.template get<protocol::status>().value()), '\0', false); }
    }

    void operator()(const protocol::heartbeat_response_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.heartbeatresponsemessage";
        if constexpr (requires { message.template get<protocol::source_id>(); }) { values[entry + ".payload.heartbeatresponsemessage.sourceid"] = canonical::text(std::string(message.template get<protocol::source_id>().value()), '\0', false); }
    }

    void operator()(const protocol::symbol_index_mapping_request_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.symbolindexmappingrequestmessage";
        if constexpr (requires { message.template get<protocol::symbol_index>(); }) { values[entry + ".payload.symbolindexmappingrequestmessage.symbolindex"] = canonical::number(message.template get<protocol::symbol_index>().value()); }
        if constexpr (requires { message.template get<protocol::source_id>(); }) { values[entry + ".payload.symbolindexmappingrequestmessage.sourceid"] = canonical::text(std::string(message.template get<protocol::source_id>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::product_id>(); }) { values[entry + ".payload.symbolindexmappingrequestmessage.productid"] = canonical::number(message.template get<protocol::product_id>().value()); }
        if constexpr (requires { message.template get<protocol::channel_id>(); }) { values[entry + ".payload.symbolindexmappingrequestmessage.channelid"] = canonical::number(message.template get<protocol::channel_id>().value()); }
        if constexpr (requires { message.template get<protocol::retransmit_method>(); }) { values[entry + ".payload.symbolindexmappingrequestmessage.retransmitmethod"] = canonical::number(message.template get<protocol::retransmit_method>().value()); }
    }

    void operator()(const protocol::refresh_request_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.refreshrequestmessage";
        if constexpr (requires { message.template get<protocol::symbol_index>(); }) { values[entry + ".payload.refreshrequestmessage.symbolindex"] = canonical::number(message.template get<protocol::symbol_index>().value()); }
        if constexpr (requires { message.template get<protocol::source_id>(); }) { values[entry + ".payload.refreshrequestmessage.sourceid"] = canonical::text(std::string(message.template get<protocol::source_id>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::product_id>(); }) { values[entry + ".payload.refreshrequestmessage.productid"] = canonical::number(message.template get<protocol::product_id>().value()); }
        if constexpr (requires { message.template get<protocol::channel_id>(); }) { values[entry + ".payload.refreshrequestmessage.channelid"] = canonical::number(message.template get<protocol::channel_id>().value()); }
    }

    void operator()(const protocol::message_unavailable_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.messageunavailablemessage";
        if constexpr (requires { message.template get<protocol::begin_seq_num>(); }) { values[entry + ".payload.messageunavailablemessage.beginseqnum"] = canonical::number(message.template get<protocol::begin_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::end_seq_num>(); }) { values[entry + ".payload.messageunavailablemessage.endseqnum"] = canonical::number(message.template get<protocol::end_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::product_id>(); }) { values[entry + ".payload.messageunavailablemessage.productid"] = canonical::number(message.template get<protocol::product_id>().value()); }
        if constexpr (requires { message.template get<protocol::channel_id>(); }) { values[entry + ".payload.messageunavailablemessage.channelid"] = canonical::number(message.template get<protocol::channel_id>().value()); }
    }

    void operator()(const protocol::symbol_clear_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.symbolclearmessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.symbolclearmessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.symbolclearmessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_index>(); }) { values[entry + ".payload.symbolclearmessage.symbolindex"] = canonical::number(message.template get<protocol::symbol_index>().value()); }
        if constexpr (requires { message.template get<protocol::next_source_seq_num>(); }) { values[entry + ".payload.symbolclearmessage.nextsourceseqnum"] = canonical::number(message.template get<protocol::next_source_seq_num>().value()); }
    }

    void operator()(const protocol::security_status_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.securitystatusmessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.securitystatusmessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.securitystatusmessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_index>(); }) { values[entry + ".payload.securitystatusmessage.symbolindex"] = canonical::number(message.template get<protocol::symbol_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { values[entry + ".payload.securitystatusmessage.symbolseqnum"] = canonical::number(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::security_status>(); }) { values[entry + ".payload.securitystatusmessage.securitystatus"] = canonical::text(canonical::character(message.template get<protocol::security_status>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::halt_condition>(); }) { values[entry + ".payload.securitystatusmessage.haltcondition"] = canonical::text(canonical::character(message.template get<protocol::halt_condition>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::price_1>(); }) { values[entry + ".payload.securitystatusmessage.price1"] = canonical::number(message.template get<protocol::price_1>().value()); }
        if constexpr (requires { message.template get<protocol::price_2>(); }) { values[entry + ".payload.securitystatusmessage.price2"] = canonical::number(message.template get<protocol::price_2>().value()); }
        if constexpr (requires { message.template get<protocol::ssr_triggering_exchange_id>(); }) { values[entry + ".payload.securitystatusmessage.ssrtriggeringexchangeid"] = canonical::text(canonical::character(message.template get<protocol::ssr_triggering_exchange_id>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::ssr_triggering_volume>(); }) { values[entry + ".payload.securitystatusmessage.ssrtriggeringvolume"] = canonical::number(message.template get<protocol::ssr_triggering_volume>().value()); }
        if constexpr (requires { message.template get<protocol::time>(); }) { values[entry + ".payload.securitystatusmessage.time"] = (static_cast<std::uint32_t>(message.template get<protocol::time>().value()) != 0x0U ? canonical::number(message.template get<protocol::time>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::ssr_state>(); }) { values[entry + ".payload.securitystatusmessage.ssrstate"] = canonical::text(canonical::character(message.template get<protocol::ssr_state>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::market_state>(); }) { values[entry + ".payload.securitystatusmessage.marketstate"] = canonical::text(canonical::character(message.template get<protocol::market_state>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::session_state>(); }) { values[entry + ".payload.securitystatusmessage.sessionstate"] = canonical::number(message.template get<protocol::session_state>().value()); }
    }

    void operator()(const protocol::refresh_header_message&) {
        values[entry + ".payload"] = "packet.messages.message.payload.refreshheadermessage";
    }

    void operator()(const protocol::outright_series_index_mapping_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.outrightseriesindexmappingmessage";
        if constexpr (requires { message.template get<protocol::series_index>(); }) { values[entry + ".payload.outrightseriesindexmappingmessage.seriesindex"] = canonical::number(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::series_type>(); }) { values[entry + ".payload.outrightseriesindexmappingmessage.seriestype"] = canonical::number(message.template get<protocol::series_type>().value()); }
        if constexpr (requires { message.template get<protocol::market_id>(); }) { values[entry + ".payload.outrightseriesindexmappingmessage.marketid"] = canonical::number(message.template get<protocol::market_id>().value()); }
        if constexpr (requires { message.template get<protocol::system_id>(); }) { values[entry + ".payload.outrightseriesindexmappingmessage.systemid"] = canonical::number(message.template get<protocol::system_id>().value()); }
        if constexpr (requires { message.template get<protocol::option_symbol_root>(); }) { values[entry + ".payload.outrightseriesindexmappingmessage.optionsymbolroot"] = canonical::text(std::string(message.template get<protocol::option_symbol_root>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::underlying_symbol>(); }) { values[entry + ".payload.outrightseriesindexmappingmessage.underlyingsymbol"] = canonical::text(std::string(message.template get<protocol::underlying_symbol>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::underlying_index>(); }) { values[entry + ".payload.outrightseriesindexmappingmessage.underlyingindex"] = canonical::number(message.template get<protocol::underlying_index>().value()); }
        if constexpr (requires { message.template get<protocol::price_scale_code>(); }) { values[entry + ".payload.outrightseriesindexmappingmessage.pricescalecode"] = canonical::number(message.template get<protocol::price_scale_code>().value()); }
        if constexpr (requires { message.template get<protocol::contract_multiplier>(); }) { values[entry + ".payload.outrightseriesindexmappingmessage.contractmultiplier"] = canonical::number(message.template get<protocol::contract_multiplier>().value()); }
        if constexpr (requires { message.template get<protocol::maturity_date>(); }) { values[entry + ".payload.outrightseriesindexmappingmessage.maturitydate"] = canonical::text(std::string(message.template get<protocol::maturity_date>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::put_or_call>(); }) { values[entry + ".payload.outrightseriesindexmappingmessage.putorcall"] = canonical::number(message.template get<protocol::put_or_call>().value()); }
        if constexpr (requires { message.template get<protocol::strike_price>(); }) { values[entry + ".payload.outrightseriesindexmappingmessage.strikeprice"] = canonical::text(std::string(message.template get<protocol::strike_price>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::closing_only_indicator>(); }) { values[entry + ".payload.outrightseriesindexmappingmessage.closingonlyindicator"] = canonical::text(canonical::character(message.template get<protocol::closing_only_indicator>().value()), '\0', false); }
    }

    void operator()(const protocol::options_status_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.optionsstatusmessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.optionsstatusmessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.optionsstatusmessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::series_index>(); }) { values[entry + ".payload.optionsstatusmessage.seriesindex"] = canonical::number(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::series_seq_num>(); }) { values[entry + ".payload.optionsstatusmessage.seriesseqnum"] = canonical::number(message.template get<protocol::series_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::series_status>(); }) { values[entry + ".payload.optionsstatusmessage.seriesstatus"] = canonical::text(canonical::character(message.template get<protocol::series_status>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::market_state>(); }) { values[entry + ".payload.optionsstatusmessage.marketstate"] = canonical::text(canonical::character(message.template get<protocol::market_state>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::halt_condition>(); }) { values[entry + ".payload.optionsstatusmessage.haltcondition"] = canonical::text(canonical::character(message.template get<protocol::halt_condition>().value()), '\0', false); }
    }

    void operator()(const protocol::options_quote_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.optionsquotemessage";
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.optionsquotemessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::series_index>(); }) { values[entry + ".payload.optionsquotemessage.seriesindex"] = canonical::number(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::series_seq_num>(); }) { values[entry + ".payload.optionsquotemessage.seriesseqnum"] = canonical::number(message.template get<protocol::series_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::ask_price>(); }) { values[entry + ".payload.optionsquotemessage.askprice"] = canonical::number(message.template get<protocol::ask_price>().value()); }
        if constexpr (requires { message.template get<protocol::ask_volume>(); }) { values[entry + ".payload.optionsquotemessage.askvolume"] = canonical::number(message.template get<protocol::ask_volume>().value()); }
        if constexpr (requires { message.template get<protocol::bid_price>(); }) { values[entry + ".payload.optionsquotemessage.bidprice"] = canonical::number(message.template get<protocol::bid_price>().value()); }
        if constexpr (requires { message.template get<protocol::bid_volume>(); }) { values[entry + ".payload.optionsquotemessage.bidvolume"] = canonical::number(message.template get<protocol::bid_volume>().value()); }
        if constexpr (requires { message.template get<protocol::quote_condition>(); }) { values[entry + ".payload.optionsquotemessage.quotecondition"] = canonical::text(canonical::character(message.template get<protocol::quote_condition>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::ask_customer_volume>(); }) { values[entry + ".payload.optionsquotemessage.askcustomervolume"] = canonical::number(message.template get<protocol::ask_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::bid_customer_volume>(); }) { values[entry + ".payload.optionsquotemessage.bidcustomervolume"] = canonical::number(message.template get<protocol::bid_customer_volume>().value()); }
    }

    void operator()(const protocol::options_trade_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.optionstrademessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.optionstrademessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.optionstrademessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::series_index>(); }) { values[entry + ".payload.optionstrademessage.seriesindex"] = canonical::number(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::series_seq_num>(); }) { values[entry + ".payload.optionstrademessage.seriesseqnum"] = canonical::number(message.template get<protocol::series_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".payload.optionstrademessage.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.optionstrademessage.price"] = canonical::number(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { values[entry + ".payload.optionstrademessage.volume"] = canonical::number(message.template get<protocol::volume>().value()); }
    }

    void operator()(const protocol::options_trade_cancel_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.optionstradecancelmessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.optionstradecancelmessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.optionstradecancelmessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::series_index>(); }) { values[entry + ".payload.optionstradecancelmessage.seriesindex"] = canonical::number(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::series_seq_num>(); }) { values[entry + ".payload.optionstradecancelmessage.seriesseqnum"] = canonical::number(message.template get<protocol::series_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::original_trade_id>(); }) { values[entry + ".payload.optionstradecancelmessage.originaltradeid"] = canonical::number(message.template get<protocol::original_trade_id>().value()); }
    }

    void operator()(const protocol::options_trade_correction_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.optionstradecorrectionmessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.optionstradecorrectionmessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.optionstradecorrectionmessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::series_index>(); }) { values[entry + ".payload.optionstradecorrectionmessage.seriesindex"] = canonical::number(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::series_seq_num>(); }) { values[entry + ".payload.optionstradecorrectionmessage.seriesseqnum"] = canonical::number(message.template get<protocol::series_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::original_trade_id>(); }) { values[entry + ".payload.optionstradecorrectionmessage.originaltradeid"] = canonical::number(message.template get<protocol::original_trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".payload.optionstradecorrectionmessage.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.optionstradecorrectionmessage.price"] = canonical::number(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { values[entry + ".payload.optionstradecorrectionmessage.volume"] = canonical::number(message.template get<protocol::volume>().value()); }
    }

    void operator()(const protocol::options_imbalance_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.optionsimbalancemessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.optionsimbalancemessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.optionsimbalancemessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::series_index>(); }) { values[entry + ".payload.optionsimbalancemessage.seriesindex"] = canonical::number(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::series_seq_num>(); }) { values[entry + ".payload.optionsimbalancemessage.seriesseqnum"] = canonical::number(message.template get<protocol::series_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::paired_qty>(); }) { values[entry + ".payload.optionsimbalancemessage.pairedqty"] = canonical::number(message.template get<protocol::paired_qty>().value()); }
        if constexpr (requires { message.template get<protocol::total_imbalance_qty>(); }) { values[entry + ".payload.optionsimbalancemessage.totalimbalanceqty"] = canonical::number(message.template get<protocol::total_imbalance_qty>().value()); }
        if constexpr (requires { message.template get<protocol::market_imbalance_qty>(); }) { values[entry + ".payload.optionsimbalancemessage.marketimbalanceqty"] = canonical::number(message.template get<protocol::market_imbalance_qty>().value()); }
        if constexpr (requires { message.template get<protocol::auction_type>(); }) { values[entry + ".payload.optionsimbalancemessage.auctiontype"] = canonical::text(canonical::character(message.template get<protocol::auction_type>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::imbalance_side>(); }) { values[entry + ".payload.optionsimbalancemessage.imbalanceside"] = canonical::text(canonical::character(message.template get<protocol::imbalance_side>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::continuous_book_clearing_price>(); }) { values[entry + ".payload.optionsimbalancemessage.continuousbookclearingprice"] = canonical::number(message.template get<protocol::continuous_book_clearing_price>().value()); }
        if constexpr (requires { message.template get<protocol::auction_interest_clearing_price>(); }) { values[entry + ".payload.optionsimbalancemessage.auctioninterestclearingprice"] = canonical::number(message.template get<protocol::auction_interest_clearing_price>().value()); }
        if constexpr (requires { message.template get<protocol::indicative_match_price>(); }) { values[entry + ".payload.optionsimbalancemessage.indicativematchprice"] = canonical::number(message.template get<protocol::indicative_match_price>().value()); }
        if constexpr (requires { message.template get<protocol::upper_collar>(); }) { values[entry + ".payload.optionsimbalancemessage.uppercollar"] = canonical::number(message.template get<protocol::upper_collar>().value()); }
        if constexpr (requires { message.template get<protocol::lower_collar>(); }) { values[entry + ".payload.optionsimbalancemessage.lowercollar"] = canonical::number(message.template get<protocol::lower_collar>().value()); }
        if constexpr (requires { message.template get<protocol::auction_status>(); }) { values[entry + ".payload.optionsimbalancemessage.auctionstatus"] = canonical::number(message.template get<protocol::auction_status>().value()); }
    }

    void operator()(const protocol::series_rfq_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.seriesrfqmessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.seriesrfqmessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.seriesrfqmessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::series_index>(); }) { values[entry + ".payload.seriesrfqmessage.seriesindex"] = canonical::number(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::series_seq_num>(); }) { values[entry + ".payload.seriesrfqmessage.seriesseqnum"] = canonical::number(message.template get<protocol::series_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.seriesrfqmessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::type_type>(); }) { values[entry + ".payload.seriesrfqmessage.type"] = canonical::text(canonical::character(message.template get<protocol::type_type>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::capacity>(); }) { values[entry + ".payload.seriesrfqmessage.capacity"] = canonical::text(canonical::character(message.template get<protocol::capacity>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::total_quantity>(); }) { values[entry + ".payload.seriesrfqmessage.totalquantity"] = canonical::number(message.template get<protocol::total_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::working_price>(); }) { values[entry + ".payload.seriesrfqmessage.workingprice"] = canonical::number(message.template get<protocol::working_price>().value()); }
        if constexpr (requires { message.template get<protocol::participant>(); }) { values[entry + ".payload.seriesrfqmessage.participant"] = canonical::number(message.template get<protocol::participant>().value()); }
        if constexpr (requires { message.template get<protocol::auction_id>(); }) { values[entry + ".payload.seriesrfqmessage.auctionid"] = canonical::number(message.template get<protocol::auction_id>().value()); }
        if constexpr (requires { message.template get<protocol::rfq_status>(); }) { values[entry + ".payload.seriesrfqmessage.rfqstatus"] = canonical::text(canonical::character(message.template get<protocol::rfq_status>().value()), '\0', false); }
    }

    void operator()(const protocol::outright_series_summary_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.outrightseriessummarymessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.outrightseriessummarymessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.outrightseriessummarymessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::series_index>(); }) { values[entry + ".payload.outrightseriessummarymessage.seriesindex"] = canonical::number(message.template get<protocol::series_index>().value()); }
        if constexpr (requires { message.template get<protocol::high_price>(); }) { values[entry + ".payload.outrightseriessummarymessage.highprice"] = canonical::number(message.template get<protocol::high_price>().value()); }
        if constexpr (requires { message.template get<protocol::low_price>(); }) { values[entry + ".payload.outrightseriessummarymessage.lowprice"] = canonical::number(message.template get<protocol::low_price>().value()); }
        if constexpr (requires { message.template get<protocol::open>(); }) { values[entry + ".payload.outrightseriessummarymessage.open"] = canonical::number(message.template get<protocol::open>().value()); }
        if constexpr (requires { message.template get<protocol::close>(); }) { values[entry + ".payload.outrightseriessummarymessage.close"] = canonical::number(message.template get<protocol::close>().value()); }
        if constexpr (requires { message.template get<protocol::total_volume>(); }) { values[entry + ".payload.outrightseriessummarymessage.totalvolume"] = canonical::number(message.template get<protocol::total_volume>().value()); }
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
    std::printf("== Nyse.ArcaOptions.TopFeed.Pillar.v1.2.c (tmp values)\n");
    int failures = 0;
    failures += check("HeartBeat", "Nyse/ArcaOptions.TopFeed.Pillar.v1.2.c/HeartBeat.pcap", "nyse/arcaoptions/topfeed/pillar/v1.2.c/HeartBeat.values");
    failures += check("OptionsQuoteMessage", "Nyse/ArcaOptions.TopFeed.Pillar.v1.2.c/OptionsQuoteMessage.pcap", "nyse/arcaoptions/topfeed/pillar/v1.2.c/OptionsQuoteMessage.values");
    failures += check("SequenceNumberResetMessage", "Nyse/ArcaOptions.TopFeed.Pillar.v1.2.c/SequenceNumberResetMessage.pcap", "nyse/arcaoptions/topfeed/pillar/v1.2.c/SequenceNumberResetMessage.values");
    return failures == 0 ? 0 : 1;
}
