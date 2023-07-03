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
	
	YAPI void* allocate(u64, Tag);
	
	YAPI void free(void*, u64, Tag);
	
	YAPI void* zero(void*, u64);
	
	YAPI void* copy(void*, const void*, u64);
	
	YAPI void* set(void*, i32, u64);
	
	YAPI std::string getMemoryUsageString();
}