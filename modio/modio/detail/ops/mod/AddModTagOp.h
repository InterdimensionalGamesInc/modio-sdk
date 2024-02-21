/*
 *  Copyright (C) 2021 mod.io Pty Ltd. <https://mod.io>
 *
 *  This file is part of the mod.io SDK.
 *
 *  Distributed under the MIT License. (See accompanying file LICENSE or
 *   view online at <https://github.com/modio/modio-sdk/blob/main/LICENSE>)
 *
 */

#pragma once

#include "modio/core/ModioBuffer.h"
#include "modio/core/ModioCoreTypes.h"
#include "modio/detail/AsioWrapper.h"
#include "modio/detail/ops/http/PerformRequestAndGetResponseOp.h"
#include "modio/http/ModioHttpParams.h"

#include <asio/yield.hpp>

namespace Modio
{
	namespace Detail
	{
		class AddModTagOp
		{
			asio::coroutine CoroState;
			Modio::GameID GameID;
			Modio::ModID ModID;
			std::string TagName;
			Modio::Detail::DynamicBuffer ResponseBodyBuffer;

		public:
			AddModTagOp(Modio::GameID GameID, Modio::ModID ModID, std::string tagName)
				: GameID(GameID),
				  ModID(ModID),
				  TagName(tagName)
			{}

			template<typename CoroType>
			void operator()(CoroType& Self, Modio::ErrorCode ec = {})
			{
				reenter(CoroState)
				{
					yield Modio::Detail::PerformRequestAndGetResponseAsync(
						ResponseBodyBuffer, Modio::Detail::AddModTagsRequest.SetGameID(GameID).SetModID(ModID).AppendPayloadValue("tags[]", TagName),
						Modio::Detail::CachedResponse::Disallow, std::move(Self));

					if (Modio::ErrorCodeMatches(ec, Modio::ErrorConditionTypes::UserNotAuthenticatedError))
					{
						Modio::Detail::SDKSessionData::InvalidateOAuthToken();
					}
					if (ec)
					{
						Self.complete(ec);
						return;
					}
					Self.complete({});
				}
			}
		};
	} // namespace Detail
} // namespace Modio
#include <asio/unyield.hpp>