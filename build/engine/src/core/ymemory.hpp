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
		
		END
	};
	inline std::string Stringify(Tag);
	
	void initialize();
	void shutdown();
	
	YAPI void* yallocate(u64, Tag);
	
	YAPI void yfree(void*, u64, Tag);
	
	YAPI void* yzero(void*, u64);
	
	YAPI void* ycopy(void*, const void*, u64);
	
	YAPI void* yset(void*, i32, u64);
	
	YAPI std::string getMemoryUsageString();
}