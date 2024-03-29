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

#include <cstdio>
#include <optional>
#include <string>

namespace rapidjsonHelper {
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
		
		inline std::optional<unsigned int> getUint(rapidjson::Value& value, const std::string& key) {
			// checking member exists
			if (!value.HasMember(key.c_str()))
				return std::nullopt;

			//getting member reference
			rapidjson::Value& member = value[key.c_str()];

			// checking for integer
			if (member.IsUint() == false)
				return std::nullopt;

			// making optional with value
			return std::optional<unsigned int>{member.GetUint()};
		}

		inline std::optional<uint64_t> getUint64(rapidjson::Value& value, const std::string& key) {
			// checking member exists
			if (!value.HasMember(key.c_str()))
				return std::nullopt;

			//getting member reference
			rapidjson::Value& member = value[key.c_str()];

			// checking for integer
			if (member.IsUint64() == false)
				return std::nullopt;

			// making optional with value
			return std::optional<uint64_t>{member.GetUint64()};
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
			return std::string{member.GetString()};
		}

		inline std::optional<double> getDouble(rapidjson::Value& value, const std::string& key) {
			// checking member exists
			if (!value.HasMember(key.c_str()))
				return std::nullopt;

			//getting member reference
			rapidjson::Value& member = value[key.c_str()];

			// checking for integer
			if (member.IsDouble() == false)
				return std::nullopt;

			// making optional with value
			return member.GetDouble();
		}
		
		inline std::optional<float> getFloat(rapidjson::Value& value, const std::string& key) {
			// checking member exists
			if (!value.HasMember(key.c_str()))
				return std::nullopt;

			//getting member reference
			rapidjson::Value& member = value[key.c_str()];

			// checking for integer
			if (member.IsFloat() == false)
				return std::nullopt;

			// making optional with value
			return member.GetFloat();
		}
		
		inline std::optional<bool> getBool(rapidjson::Value& value, const std::string& key) {
			// checking member exists
			if (!value.HasMember(key.c_str()))
				return std::nullopt;

			//getting member reference
			rapidjson::Value& member = value[key.c_str()];

			// checking for integer
			if (member.IsBool() == false)
				return std::nullopt;

			// making optional with value
			return member.GetBool();
		}

		template<class T>
		inline std::optional<T> getValue(rapidjson::Value& value, const std::string& key) {
			if constexpr (std::is_same_v<T, int>)
				return getInt(value, key);
			else if constexpr (std::is_same_v<T, int64_t>)
				return getInt64(value, key);
			else if constexpr (std::is_same_v<T, unsigned int>)
				return getInt(value, key);
			else if constexpr (std::is_same_v<T, uint64_t>)
				return getInt64(value, key);
			else if constexpr (std::is_same_v<T, std::string>)
				return getString(value, key);
			else if constexpr (std::is_same_v<T, double>)
				return getDouble(value, key);
			else if constexpr (std::is_same_v<T, float>)
				return getFloat(value, key);
			else if constexpr (std::is_same_v<T, bool>)
				return getBool(value, key);
			else
				return std::nullopt;
		}
	}

	template<class T>
	inline T getValue(rapidjson::Value& value, const std::string& key) {
		auto ret = details::getValue<T>(value, key);
		if (!ret)
			std::fprintf(stderr, "RAPIDJSON HELPER: FAILED TO OBTAIN VALUE BY KEY %s\n", key.c_str());
		return ret.value_or(T{});
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
