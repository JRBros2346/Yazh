#pragma once

#include"defines.hpp"
#include<map>

namespace Yazh::Memory {
	enum class Tag {
		Unknown,
		RingQueue,
		BST,
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
		
		END,
	};
	inline std::string string(Tag);
	
	void initialize();
	void shutdown();
	
	YAPI void* yallocate(u64, Tag);
	
	YAPI void yfree(void*, u64, Tag);
	
	YAPI void* yzero(void*, u64);
	
	YAPI void* ycopy(void*, const void*, u64);
	
	YAPI void* yset(void*, i32, u64);
	
	YAPI std::string getMemoryUsageString();
}