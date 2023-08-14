#pragma once

#include"defines.hpp"

namespace Yazh::Core::Memory {
	enum class Tag : u8 {
		Unknown,
		Array,
		Vector,
		Map,
		RingQueue,
		BST,
		String,
		Application,
		Job,
		Texture,
		MaterialInstance,
		Renderer,
		Game,
		Transform,
		Entity,
		EntityNode,
		Scene,
		
		MAX
	};
	std::string Stringify(Tag);
	
	YAPI void initialize();
	YAPI void shutdown();
	
	YAPI void* allocate(std::size_t, Tag);
	
	YAPI void free(void*, std::size_t, Tag);
	
	YAPI void* zero(void*, std::size_t);
	
	YAPI void* copy(void*, const void*, std::size_t);
	
	YAPI void* set(void*, i32, std::size_t);
	
	YAPI std::string getMemoryUsageString();
} // namespace Yazh::Core::Memory