#pragma once

#include"defines.hpp"

namespace Yazh::Memory {
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
		
		Total
	};
	inline std::string Stringify(Tag);
	
	void initialize();
	void shutdown();
	
	YAPI void* allocate(ysize, Tag);
	
	YAPI void free(void*, ysize, Tag);
	
	YAPI void* zero(void*, ysize);
	
	YAPI void* copy(void*, const void*, ysize);
	
	YAPI void* set(void*, i32, ysize);
	
	YAPI std::string getMemoryUsageString();
}