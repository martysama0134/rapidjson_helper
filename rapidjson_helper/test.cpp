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

int main()
{
	TestLoadData();
	return 0;
}
