#pragma once

#include <memory>
#include <utility>

class come_class
{

};

class move_only
{
private:
	std::unique_ptr<come_class> data;
public:
	move_only() {}
	move_only(const move_only &) = delete;
	move_only(move_only && other) : data(std::move(other.data)) {}
	move_only& operator=(const move_only &) = delete;
	move_only& operator=(move_only && other)
	{
		data = std::move(other.data);
		return *this;
	}
};
