#pragma once

#include "../definitions.hpp"

namespace siac::opra::output::obi::v6_2 {
// MessageIterator
struct MessageIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const BlockHeader* block_header = nullptr;
    const MessageHeader* message_header = nullptr;

    std::uint8_t messages_in_block = 0;
    std::uint8_t message_index = 0;
    char message_category = 0;
    const std::byte* message = nullptr;

    // initialize parser
    void initialize(const std::byte* data, std::size_t length) {

        end = data + length;

        if (length < sizeof(BlockHeader)) {
            current = end;
            message = nullptr;
            messages_in_block = 0;
            return;
        }

        block_header = BlockHeader::parse(data);
        current = data + sizeof(BlockHeader);
        message = nullptr;

        message_header = nullptr;
        message_index = 0;
        message_category = 0;
        messages_in_block = block_header->messages_in_block.get();
    }

    // size of the entry at entry, 0 where its codes are unknown or its bytes run out
    static std::size_t entry_size(const std::byte* entry, std::size_t available) {
        if (available < sizeof(MessageHeader)) {
            return 0;
        }
        // Administrative Category
        if (MessageHeader::parse(entry)->message_category.get() == 'C') {
            if (available < sizeof(MessageHeader) + sizeof(AdministrativeCategory)) {
                return 0;
            }
            // Administrative Message
            if (AdministrativeCategory::parse(entry + sizeof(MessageHeader))->administrative_message_type.get() == ' ') {
                if (available < sizeof(MessageHeader) + sizeof(AdministrativeCategory) + sizeof(AdministrativeMessage)) {
                    return 0;
                }
                return sizeof(MessageHeader) + sizeof(AdministrativeCategory) + (AdministrativeMessage::parse(entry + sizeof(MessageHeader) + sizeof(AdministrativeCategory))->message_data_length.get() + 11);
            }
            return 0;
        }
        // Control Category
        if (MessageHeader::parse(entry)->message_category.get() == 'H') {
            if (available < sizeof(MessageHeader) + sizeof(ControlCategory)) {
                return 0;
            }
            // Control Message
            if (ControlCategory::parse(entry + sizeof(MessageHeader))->control_message_type.get() == 'C' || ControlCategory::parse(entry + sizeof(MessageHeader))->control_message_type.get() == 'E' || ControlCategory::parse(entry + sizeof(MessageHeader))->control_message_type.get() == 'F' || ControlCategory::parse(entry + sizeof(MessageHeader))->control_message_type.get() == 'J' || ControlCategory::parse(entry + sizeof(MessageHeader))->control_message_type.get() == 'K' || ControlCategory::parse(entry + sizeof(MessageHeader))->control_message_type.get() == 'L' || ControlCategory::parse(entry + sizeof(MessageHeader))->control_message_type.get() == 'M' || ControlCategory::parse(entry + sizeof(MessageHeader))->control_message_type.get() == 'N' || ControlCategory::parse(entry + sizeof(MessageHeader))->control_message_type.get() == 'P') {
                return sizeof(MessageHeader) + sizeof(ControlCategory) + sizeof(ControlMessage);
            }
            return 0;
        }
        // Equity And Index Last Sale Category
        if (MessageHeader::parse(entry)->message_category.get() == 'a') {
            if (available < sizeof(MessageHeader) + sizeof(EquityAndIndexLastSaleCategory)) {
                return 0;
            }
            // Equity And Index Last Sale Message
            if (EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'A' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'B' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'C' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'D' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'E' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'F' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'G' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'H' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'I' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'J' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'K' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'L' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'M' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'N' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'O' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'P' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'Q' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'R' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'S' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'T' || EquityAndIndexLastSaleCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_last_sale_message_type.get() == 'X') {
                return sizeof(MessageHeader) + sizeof(EquityAndIndexLastSaleCategory) + sizeof(EquityAndIndexLastSaleMessage);
            }
            return 0;
        }
        // Open Interest Category
        if (MessageHeader::parse(entry)->message_category.get() == 'd') {
            if (available < sizeof(MessageHeader) + sizeof(OpenInterestCategory)) {
                return 0;
            }
            // Open Interest Message
            if (OpenInterestCategory::parse(entry + sizeof(MessageHeader))->open_interest_message_type.get() == ' ') {
                return sizeof(MessageHeader) + sizeof(OpenInterestCategory) + sizeof(OpenInterestMessage);
            }
            return 0;
        }
        // Equity And Index End Of Day Summary Category
        if (MessageHeader::parse(entry)->message_category.get() == 'f') {
            if (available < sizeof(MessageHeader) + sizeof(EquityAndIndexEndOfDaySummaryCategory)) {
                return 0;
            }
            // Equity And Index End Of Day Summary Message
            if (EquityAndIndexEndOfDaySummaryCategory::parse(entry + sizeof(MessageHeader))->equity_and_index_end_of_day_summary_message_type.get() == ' ') {
                return sizeof(MessageHeader) + sizeof(EquityAndIndexEndOfDaySummaryCategory) + sizeof(EquityAndIndexEndOfDaySummaryMessage);
            }
            return 0;
        }
        // Long Equity And Index Quote Category
        if (MessageHeader::parse(entry)->message_category.get() == 'k') {
            if (available < sizeof(MessageHeader) + sizeof(LongEquityAndIndexQuoteCategory)) {
                return 0;
            }
            // Long Equity And Index Quote Message
            if (LongEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->long_equity_and_index_quote_message_type.get() == ' ' || LongEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->long_equity_and_index_quote_message_type.get() == 'F' || LongEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->long_equity_and_index_quote_message_type.get() == 'I' || LongEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->long_equity_and_index_quote_message_type.get() == 'R' || LongEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->long_equity_and_index_quote_message_type.get() == 'T' || LongEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->long_equity_and_index_quote_message_type.get() == 'A' || LongEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->long_equity_and_index_quote_message_type.get() == 'B' || LongEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->long_equity_and_index_quote_message_type.get() == 'O' || LongEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->long_equity_and_index_quote_message_type.get() == 'C' || LongEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->long_equity_and_index_quote_message_type.get() == 'X' || LongEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->long_equity_and_index_quote_message_type.get() == 'Y') {
                if (available < sizeof(MessageHeader) + sizeof(LongEquityAndIndexQuoteCategory) + sizeof(LongEquityAndIndexQuoteMessage)) {
                    return 0;
                }
                return sizeof(MessageHeader) + sizeof(LongEquityAndIndexQuoteCategory) + sizeof(LongEquityAndIndexQuoteMessage) + (LongEquityAndIndexQuoteMessage::parse(entry + sizeof(MessageHeader) + sizeof(LongEquityAndIndexQuoteCategory))->bbo_indicator.get() == 'M' || LongEquityAndIndexQuoteMessage::parse(entry + sizeof(MessageHeader) + sizeof(LongEquityAndIndexQuoteCategory))->bbo_indicator.get() == 'N' || LongEquityAndIndexQuoteMessage::parse(entry + sizeof(MessageHeader) + sizeof(LongEquityAndIndexQuoteCategory))->bbo_indicator.get() == 'P' ? sizeof(BestBidAppendage) : 0) + (LongEquityAndIndexQuoteMessage::parse(entry + sizeof(MessageHeader) + sizeof(LongEquityAndIndexQuoteCategory))->bbo_indicator.get() == 'C' || LongEquityAndIndexQuoteMessage::parse(entry + sizeof(MessageHeader) + sizeof(LongEquityAndIndexQuoteCategory))->bbo_indicator.get() == 'G' || LongEquityAndIndexQuoteMessage::parse(entry + sizeof(MessageHeader) + sizeof(LongEquityAndIndexQuoteCategory))->bbo_indicator.get() == 'K' ? sizeof(BestOfferAppendage) : 0) + (LongEquityAndIndexQuoteMessage::parse(entry + sizeof(MessageHeader) + sizeof(LongEquityAndIndexQuoteCategory))->bbo_indicator.get() == 'O' ? sizeof(BestBidAndOfferAppendage) : 0);
            }
            return 0;
        }
        // Short Equity And Index Quote Category
        if (MessageHeader::parse(entry)->message_category.get() == 'q') {
            if (available < sizeof(MessageHeader) + sizeof(ShortEquityAndIndexQuoteCategory)) {
                return 0;
            }
            // Short Equity And Index Quote Message
            if (ShortEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->short_equity_and_index_quote_message_type.get() == ' ' || ShortEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->short_equity_and_index_quote_message_type.get() == 'F' || ShortEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->short_equity_and_index_quote_message_type.get() == 'I' || ShortEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->short_equity_and_index_quote_message_type.get() == 'R' || ShortEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->short_equity_and_index_quote_message_type.get() == 'T' || ShortEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->short_equity_and_index_quote_message_type.get() == 'A' || ShortEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->short_equity_and_index_quote_message_type.get() == 'B' || ShortEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->short_equity_and_index_quote_message_type.get() == 'O' || ShortEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->short_equity_and_index_quote_message_type.get() == 'C' || ShortEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->short_equity_and_index_quote_message_type.get() == 'X' || ShortEquityAndIndexQuoteCategory::parse(entry + sizeof(MessageHeader))->short_equity_and_index_quote_message_type.get() == 'Y') {
                if (available < sizeof(MessageHeader) + sizeof(ShortEquityAndIndexQuoteCategory) + sizeof(ShortEquityAndIndexQuoteMessage)) {
                    return 0;
                }
                return sizeof(MessageHeader) + sizeof(ShortEquityAndIndexQuoteCategory) + sizeof(ShortEquityAndIndexQuoteMessage) + (ShortEquityAndIndexQuoteMessage::parse(entry + sizeof(MessageHeader) + sizeof(ShortEquityAndIndexQuoteCategory))->bbo_indicator.get() == 'M' || ShortEquityAndIndexQuoteMessage::parse(entry + sizeof(MessageHeader) + sizeof(ShortEquityAndIndexQuoteCategory))->bbo_indicator.get() == 'N' || ShortEquityAndIndexQuoteMessage::parse(entry + sizeof(MessageHeader) + sizeof(ShortEquityAndIndexQuoteCategory))->bbo_indicator.get() == 'P' ? sizeof(BestBidAppendage) : 0) + (ShortEquityAndIndexQuoteMessage::parse(entry + sizeof(MessageHeader) + sizeof(ShortEquityAndIndexQuoteCategory))->bbo_indicator.get() == 'C' || ShortEquityAndIndexQuoteMessage::parse(entry + sizeof(MessageHeader) + sizeof(ShortEquityAndIndexQuoteCategory))->bbo_indicator.get() == 'G' || ShortEquityAndIndexQuoteMessage::parse(entry + sizeof(MessageHeader) + sizeof(ShortEquityAndIndexQuoteCategory))->bbo_indicator.get() == 'K' ? sizeof(BestOfferAppendage) : 0) + (ShortEquityAndIndexQuoteMessage::parse(entry + sizeof(MessageHeader) + sizeof(ShortEquityAndIndexQuoteCategory))->bbo_indicator.get() == 'O' ? sizeof(BestBidAndOfferAppendage) : 0);
            }
            return 0;
        }
        // Underlying Value Category
        if (MessageHeader::parse(entry)->message_category.get() == 'Y') {
            if (available < sizeof(MessageHeader) + sizeof(UnderlyingValueCategory)) {
                return 0;
            }
            // Underlying Value Last Sale Message
            if (UnderlyingValueCategory::parse(entry + sizeof(MessageHeader))->underlying_value_message_type.get() == ' ') {
                return sizeof(MessageHeader) + sizeof(UnderlyingValueCategory) + sizeof(UnderlyingValueLastSaleMessage);
            }
            // Underlying Value Bid And Offer Message
            if (UnderlyingValueCategory::parse(entry + sizeof(MessageHeader))->underlying_value_message_type.get() == 'I') {
                return sizeof(MessageHeader) + sizeof(UnderlyingValueCategory) + sizeof(UnderlyingValueBidAndOfferMessage);
            }
            return 0;
        }
        return 0;
    }

    // next message
    bool next() {

        if (message_index >= messages_in_block) {
            return false;
        }

        const std::size_t size = entry_size(current, static_cast<std::size_t>(end - current));

        // a code the model does not know leaves the rest of the packet unsized
        if (size == 0 || current + size > end) {
            return false;
        }

        message_index++;

        message_header = MessageHeader::parse(current);
        message = current + sizeof(MessageHeader);

        message_category = message_header->message_category.get();

        current += size;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        block_header = nullptr;
        message_header = nullptr;

        message = nullptr;
        messages_in_block = 0;
        message_index = 0;
        message_category = 0;
    }
};
}
