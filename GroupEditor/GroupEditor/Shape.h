#pragma once
#include <string>

namespace Shapes
{
	class Shape
	{
	public:
		virtual std::wstring getType() const = 0;
		virtual std::wstring display() const = 0;
		virtual std::pair<int, int> getSize() const = 0;
	};
}
