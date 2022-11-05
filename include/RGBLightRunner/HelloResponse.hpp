#pragma once
struct HelloResponse {
	int major;
	int minor;
	MSGPACK_DEFINE_ARRAY(major, minor);
};