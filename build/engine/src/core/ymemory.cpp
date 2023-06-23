#include"ymemory.hpp"

#include"logger.hpp"
#include"platform/platform_win32.hpp"
#include"platform/platform_linux.hpp"

namespace Yazh::Memory {
	static const std::map<Tag, std::string> Stringify {
		{ Tag::Unknown,          "Unknown           " },
		{ Tag::RingQueue,        "Ring Queue        " },
		{ Tag::BST,              "BST               " },
		{ Tag::Application,      "Application       " },
		{ Tag::Job,              "Job               " },
		{ Tag::Texture,          "Texture           " },
		{ Tag::MaterialInstance, "Material Instance " },
		{ Tag::Renderer,         "Renderer          " },
		{ Tag::Game,             "Game              " },
		{ Tag::Transform,        "Transform         " },
		{ Tag::Entity,           "Entity            " },
		{ Tag::EntityNode,       "Entity Node       " },
		{ Tag::Scene,            "Scene             " }
	};
	static struct Statistics {
		u64 TotalAllocation;
		std::map<Tag, u64> TaggedAllocation;
	} Statistics;
	
	void initialize() {
		Platform::zeroMemory(&Statistics, sizeof(Statistics));
	}
	
	void shutdown() {
	}
	
	void* yallocate(u64 size, Tag tag) {
		if (tag == Tag::Unknown)
			YWARN("Yazh::Memory::yallocate called using Yazh::Memory::Tag::Unknown. Re-class this allocation.");
		
		Statistics.TotalAllocation += size;
		Statistics.TaggedAllocation[tag] += size;
		
		/* TODO (#1#): Memory allignement */
		void* block = Platform::allocate(size, false);
		Platform::zeroMemory(block, size);
		return block;
	}
	
	void yfree(void* block, u64 size, Tag tag) {
		if (tag == Tag::Unknown)
			YWARN("Yazh::Memory::yallocate called using Yazh::Memory::Tag::Unknown. Re-class this allocation.");
		
		Statistics.TotalAllocation -= size;
		Statistics.TaggedAllocation[tag] -= size;
		
		/* TODO (#1#): Memory allignement */
		Platform::free(block, false);
	}
	
	void* yzeroMemory(void* block, u64 size) {
		return Platform::zeroMemory(block, size);
	}
	
	void* ycopyMemory(void* dest, const void* source, u64 size) {
		return Platform::copyMemory(dest, source, size);
	}
	
	void* ysetMemory(void* dest, i32 value, u64 size) {
		return Platform::setMemory(dest, value, size);
	}
	
	std::string getMemoryUsageString() {
		const u64 GiB = 1024 * 1024 * 1024;
		const u64 MiB = 1024 * 1024;
		const u64 KiB = 1024;
		
		std::string output = "System memory use (tagged):\n";
		for (Tag t = Tag::Unknown; t < Tag::END; ++t) {
			std::string unit = "B";
			f64 value = Statistics::TaggedAllocation[t];
			if (value >= GiB) {
				unit = "GiB";
				value /= GiB;
			} else if (value >= MiB) {
				unit = "MiB";
				value /= MiB;
			} else if (value >= KiB) {
				unit = "KiB";
				value /= KiB;
			}
			output += "  " + Stringify[t] + ": " + std::string(value) + " " + unit;
		}
		
		return output;
	}
}
