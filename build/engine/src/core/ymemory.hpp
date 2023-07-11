#pragma once

#include"defines.hpp"

namespace Yazh::Core::Memory {
	enum class Tag {
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
	inline std::string Stringify(Tag);
	
	YAPI void initialize();
	YAPI void shutdown();
	
	YAPI void* allocate(ysize, Tag);
	
	YAPI void free(void*, ysize, Tag);
	
	YAPI void* zero(void*, ysize);
	
	YAPI void* copy(void*, const void*, ysize);
	
	YAPI void* set(void*, i32, ysize);
	
	YAPI std::string getMemoryUsageString();
} // namespace Yazh::Core::Memory