#include <rapidjson_helper.h>

#include <vector>

struct MyBigThiccData {
	int64_t id{};
	int64_t vnum{};
	int count{};
	std::string name;
	double factor{};
};

bool TestLoadData() {
	std::string filename = "test_load.json";
	rapidjson::Document jsonDoc;
	if (!rapidjsonHelper::parseFromFile(jsonDoc, filename))
		return false;

	// checking for parser errors
	if (jsonDoc.HasParseError()) {
		std::printf("JSON FILE LOAD ERROR %s: [%d] %s\n", filename.c_str(), (int)jsonDoc.GetParseError(), rapidjson::GetParseError_En(jsonDoc.GetParseError()));
		return false;
	}

	// checking if the data is a big array
	if (jsonDoc.IsArray() == false) {
		std::printf("INVALID DATA: document.IsArray() == false\n");
		return false;
	}

	// iterating over array
	std::vector<MyBigThiccData> thiccList;
	for (auto& member : jsonDoc.GetArray()) {
		auto & thiccElem = thiccList.emplace_back();
		thiccElem.id = rapidjsonHelper::getValue<int64_t>(member, "id");
		thiccElem.vnum = rapidjsonHelper::getValue<int64_t>(member, "vnum");
		thiccElem.count = rapidjsonHelper::getValue<int>(member, "count");
		thiccElem.name = rapidjsonHelper::getValue<std::string>(member, "name");
		thiccElem.factor = rapidjsonHelper::getValue<double>(member, "factor");
	}

	// print loaded array
	for (auto& elem : thiccList) {
		std::printf("{");
		std::printf("    id %" PRIi64 ",", elem.id);
		std::printf("    vnum %" PRIi64 ",", elem.vnum);
		std::printf("    count %d,", elem.count);
		std::printf("    name %s,", elem.name.c_str());
		std::printf("    factor %.2f,", elem.factor);
		std::printf("}\n");
	}
	return true;
}

bool TestSaveData() {
	std::string filename = "test_save.json";

	// creating document
	rapidjson::Document jsonDoc;
	jsonDoc.SetArray();

	std::vector<MyBigThiccData> dataList = {
		{1, 169, 11, "Nymph", 11.11},
		{2, 179, 22, "Lion", 22.11},
		{3, 189, 33, "Holo", 33.11},
	};

	// reserving array size
	jsonDoc.GetArray().Reserve((rapidjson::SizeType)dataList.size(), jsonDoc.GetAllocator());

	// populating array
	for (auto& elem : dataList)
	{
		rapidjson::Value member;
		member.SetObject();

		// encoding info
		rapidjsonHelper::insertValue(member, "id", static_cast<int64_t>(elem.id), jsonDoc.GetAllocator());
		rapidjsonHelper::insertValue(member, "vnum", static_cast<int64_t>(elem.vnum), jsonDoc.GetAllocator());
		rapidjsonHelper::insertValue(member, "count", static_cast<int>(elem.count), jsonDoc.GetAllocator());
		rapidjsonHelper::insertValue(member, "name", std::string(elem.name), jsonDoc.GetAllocator());
		rapidjsonHelper::insertValue(member, "factor", static_cast<double>(elem.factor), jsonDoc.GetAllocator());

		// pushing element inside the array
		jsonDoc.PushBack(member, jsonDoc.GetAllocator());
	}

	std::cout << rapidjsonHelper::writeToStream(jsonDoc, true) << std::endl;
	return rapidjsonHelper::writeToFile(jsonDoc, filename);
}

int main()
{
	TestLoadData();
	TestSaveData();
	return 0;
}
