#pragma once

class no_copies
{
public:
	no_copies() {};
	no_copies(no_copies const &) = delete;
	no_copies & operator=(no_copies const&) = delete;
};
