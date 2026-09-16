#pragma once

#include "structs/PacketHeader.hpp"
#include "structs/MessageHeader.hpp"
#include "structs/TcpPacketHeader.hpp"

#include "messages/SecondsTimestampMessage.hpp"
#include "messages/TradingStatusMessage.hpp"
#include "messages/ExecutionSummaryMessage.hpp"
#include "messages/AddOrderMessage.hpp"
#include "messages/OrderExecutedMessage.hpp"
#include "messages/OrderExecutedWithPriceMessage.hpp"
#include "messages/OrderDeleteMessage.hpp"
#include "messages/ResetMessage.hpp"
#include "messages/CommunicationControlMessage.hpp"
#include "messages/LoginRequestMessage.hpp"
#include "messages/LoginResultMessage.hpp"
#include "messages/MessageResponseMessage.hpp"
#include "messages/EndOfMessageMessage.hpp"

#include "iterators/MessageIterator.hpp"
#include "iterators/TcpPacketIterator.hpp"
