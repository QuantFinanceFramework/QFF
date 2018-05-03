#pragma once
#include <string>
using std::string;

struct BasicTradeInfo final
{
public:
	BasicTradeInfo(string tradeID, string underlying);
	~BasicTradeInfo() = default;

public:
	string m_tradeID;
	string m_underlying;

};

BasicTradeInfo::BasicTradeInfo(string tradeID, string underlying) : m_tradeID(tradeID), m_underlying(underlying) {};
