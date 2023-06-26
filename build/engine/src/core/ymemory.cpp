#include"ymemory.hpp"

#include"logger.hpp"
#include"platform/platform_win32.hpp"
#include"platform/platform_linux.hpp"

namespace Yazh::Memory {
	
	inline std::string string(Tag tag) {
		switch(tag) {
			case Tag::Unknown          : return "           Unknown";
			case Tag::RingQueue        : return "        Ring Queue";
			case Tag::BST              : return "               BST";
			case Tag::Application      : return "       Application";
			case Tag::Job              : return "               Job";
			case Tag::Texture          : return "           Texture";
			case Tag::MaterialInstance : return " Material Instance";
			case Tag::Renderer         : return "          Renderer";
			case Tag::Game             : return "              Game";
			case Tag::Transform        : return "         Transform";
			case Tag::Entity           : return "            Entity";
			case Tag::EntityNode       : return "       Entity Node";
			case Tag::Scene            : return "             Scene";
			
			default: return "";
		}
	}
	
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
	
	std::string :getMemoryUsageString() {
		const u64 GiB = 1024 * 1024 * 1024;
		const u64 MiB = 1024 * 1024;
		const u64 KiB = 1024;
		
		std::string output = "System memory use (tagged):\n";
		YDEBUG("starting loop");
		for (const auto& [tag, memory] : Statistics.TaggedAllocation) {
			YDEBUG("setting unit and value")
			std::string unit = "B";
			f64 value = memory;
			if (value >= GiB) {
				YDEBUG("Checking GiB");
				unit = "GiB";
				value /= GiB;
			} else if (value >= MiB) {
				YDEBUG("Checking MiB");
				unit = "MiB";
				value /= MiB;
			} else if (value >= KiB) {
				YDEBUG("Checking KiB");
				unit = "KiB";
				value /= KiB;
			} else { YDEBUG("defaulted to B"); }
			YDEBUG("preparing output");
			output += "    " + string(tag) + " : " + std::to_string(value) + " " + unit;
		}
		
		YDEBUG("returning output");
		return output;
	}
}
