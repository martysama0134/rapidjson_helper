///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2024 IkarusDeveloper. All rights reserved.
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef __INC_IKD_RAPIDJSON_HELPER_H__
#define __INC_IKD_RAPIDJSON_HELPER_H__
#pragma once

#include <rapidjson/document.h> // dependency

#include <optional>
#include <string>

namespace jsonHelper {
	namespace details {
		inline std::optional<int> getInt(rapidjson::Value& value, const std::string& key) {
			// checking member exists
			if (!value.HasMember(key.c_str()))
				return std::nullopt;

			//getting member reference
			rapidjson::Value& member = value[key.c_str()];

			// checking for integer
			if (member.IsInt() == false)
				return std::nullopt;

			// making optional with value
			return std::optional<int>{member.GetInt()};
		}

		inline std::optional<int64_t> getInt64(rapidjson::Value& value, const std::string& key) {
			// checking member exists
			if (!value.HasMember(key.c_str()))
				return std::nullopt;

			//getting member reference
			rapidjson::Value& member = value[key.c_str()];

			// checking for integer
			if (member.IsInt64() == false)
				return std::nullopt;

			// making optional with value
			return std::optional<int64_t>{member.GetInt64()};
		}

		inline std::optional<std::string> getString(rapidjson::Value& value, const std::string& key) {
			// checking member exists
			if (!value.HasMember(key.c_str()))
				return std::nullopt;

			//getting member reference
			rapidjson::Value& member = value[key.c_str()];

			// checking for integer
			if (member.IsString() == false)
				return std::nullopt;

			// making optional with value
			return std::optional<std::string>{member.GetString()};
		}
	}

	template<class T>
	inline std::optional<T> getValue(rapidjson::Value& value, const std::string& key) {
		if constexpr (std::is_same_v<T, int>)
			return details::getInt(value, key);
		else if constexpr (std::is_same_v<T, int64_t>)
			return details::getInt64(value, key);
		else if constexpr (std::is_same_v<T, std::string>)
			return details::getString(value, key);
		else
			return std::nullopt;
	}


	inline void insertValue(rapidjson::Value& value, const std::string& key, const int& insertValue, auto&& allocator) {
		assert(value.IsObject());
		rapidjson::Value keyValue;
		keyValue.SetString(key.c_str(), allocator);
		rapidjson::Value newValue;
		newValue.SetInt(insertValue);
		value.AddMember(keyValue, newValue, allocator);
	}

	inline void insertValue(rapidjson::Value& value, const std::string& key, const int64_t& insertValue, auto&& allocator) {
		assert(value.IsObject());
		rapidjson::Value keyValue;
		keyValue.SetString(key.c_str(), allocator);
		rapidjson::Value newValue;
		newValue.SetInt64(insertValue);
		value.AddMember(keyValue, newValue, allocator);
	}

	inline void insertValue(rapidjson::Value& value, const std::string& key, const std::string& insertValue, auto&& allocator) {
		assert(value.IsObject());
		rapidjson::Value keyValue;
		keyValue.SetString(key.c_str(), allocator);
		rapidjson::Value newValue;
		newValue.SetString(insertValue.c_str(), allocator);
		value.AddMember(keyValue, newValue, allocator);
	}
}

#endif //__INC_IKD_RAPIDJSON_HELPER_H__
