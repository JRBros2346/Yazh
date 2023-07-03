#include"ymemory.hpp"

#include"logger.hpp"
#include"platform/platform_win32.hpp"
#include"platform/platform_linux.hpp"
#include<map>

namespace Yazh::Memory {
	
	inline std::string Stringify(Tag tag) {
		switch(tag) {
			case Tag::Unknown          : return "          Unknown";
			case Tag::Array            : return "            Array";
			case Tag::Vector           : return "           Vector";
			case Tag::Map              : return "              Map";
			case Tag::RingQueue        : return "       Ring Queue";
			case Tag::BST              : return "              BST";
			case Tag::String           : return "           String";
			case Tag::Application      : return "      Application";
			case Tag::Job              : return "              Job";
			case Tag::Texture          : return "          Texture";
			case Tag::MaterialInstance : return "Material Instance";
			case Tag::Renderer         : return "         Renderer";
			case Tag::Game             : return "             Game";
			case Tag::Transform        : return "        Transform";
			case Tag::Entity           : return "           Entity";
			case Tag::EntityNode       : return "      Entity Node";
			case Tag::Scene            : return "            Scene";
			
			default: return "";
		}
	}
	
	static struct Statistics {
		u64 TotalAllocation;
		std::map<Tag, u64> TaggedAllocation;
	} Statistics;
	
	void initialize() {
		Statistics.TotalAllocation = 0;
		for (auto i = 0; i < (int)Tag::END; i++)
			Statistics.TaggedAllocation[(Tag)i] = 0;
	}
	
	void shutdown() {
	}
	
	void* allocate(u64 size, Tag tag) {
		if (tag == Tag::Unknown)
			YWARN("Yazh::Memory::yallocate called using Yazh::Memory::Tag::Unknown. Re-class this allocation.");
		
		Statistics.TotalAllocation += size;
		Statistics.TaggedAllocation[tag] += size;
		
		/* TODO (#1#): Memory allignement */
		void* block = Platform::allocate(size, false);
		Platform::zeroMemory(block, size);
		return block;
	}
	
	void free(void* block, u64 size, Tag tag) {
		if (tag == Tag::Unknown)
			YWARN("Yazh::Memory::yallocate called using Yazh::Memory::Tag::Unknown. Re-class this allocation.");
		
		Statistics.TotalAllocation -= size;
		Statistics.TaggedAllocation[tag] -= size;
		
		/* TODO (#1#): Memory allignement */
		Platform::free(block, false);
	}
	
	void* zero(void* block, u64 size) {
		return Platform::zeroMemory(block, size);
	}
	
	void* copy(void* dest, const void* source, u64 size) {
		return Platform::copyMemory(dest, source, size);
	}
	
	void* set(void* dest, i32 value, u64 size) {
		return Platform::setMemory(dest, value, size);
	}
	
	std::string getMemoryUsageString() {
		const u64 GiB = 1024 * 1024 * 1024;
		const u64 MiB = 1024 * 1024;
		const u64 KiB = 1024;
		
		std::string output = "System memory use (tagged):\n";
		for (const auto& [tag, memory] : Statistics.TaggedAllocation) {
			std::string unit = "B";
			f64 value = memory;
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
			output += "    " + Stringify(tag) + " : " + std::to_string(value) + " " + unit + "\n";
		}
		
		return output;
	}
}
