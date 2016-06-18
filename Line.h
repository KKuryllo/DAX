#pragma once
#include <vector>
#include "Column.h"
namespace dax {
struct Line {
	std::vector<Column> columns;
};
}
