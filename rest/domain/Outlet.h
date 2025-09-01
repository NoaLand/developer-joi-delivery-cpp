#pragma once

#include <string>
using namespace std;

class Outlet {
public:
	Outlet() {};
	// Getters
	const string& getName() const { return name; }
	const string& getDescription() const { return description; }
	const string& getOutletId() const { return outletId; }

	// Setters
	void setName(const string& name)  { this->name = name; }
	void setDescription(const string& desc) { this->description = desc; }
	void setOutletId(const string& oid) { this->outletId = oid; }

	Outlet(const string& name, const string& desc, const string& oid) {
		this->name = name;
		this->description = desc;
		this->outletId = oid;
	}
private:
    string name;
    string description;
    string outletId;
};
