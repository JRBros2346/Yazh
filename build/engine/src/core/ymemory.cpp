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
			
			default                    : return "            Total";
		}
	}
	
	static struct Statistics {
		ysize TotalAllocation;
		std::map<Tag, ysize> TaggedAllocation;
	} Statistics;
	
	void initialize() {
		Statistics.TotalAllocation = 0;
		for (auto i = 0; i < (int)Tag::Total; i++)
			Statistics.TaggedAllocation[(Tag)i] = 0;
	}
	
	void shutdown() {
	}
	
	void* allocate(ysize size, Tag tag) {
		if (tag == Tag::Unknown)
			YWARN("Yazh::Memory::yallocate called using Yazh::Memory::Tag::Unknown. Re-class this allocation.");
		
		Statistics.TotalAllocation += size;
		Statistics.TaggedAllocation[tag] += size;
		
		// TODO: Memory allignement
		void* block = Platform::allocate(size, false);
		Platform::zeroMemory(block, size);
		return block;
	}
	
	void free(void* block, ysize size, Tag tag) {
		Statistics.TotalAllocation -= size;
		Statistics.TaggedAllocation[tag] -= size;
		
		// TODO: Memory allignement
		Platform::free(block, size, false);
	}
	
	void* zero(void* block, ysize size) {
		return Platform::zeroMemory(block, size);
	}
	
	void* copy(void* dest, const void* source, ysize size) {
		return Platform::copyMemory(dest, source, size);
	}
	
	void* set(void* dest, i32 value, ysize size) {
		return Platform::setMemory(dest, value, size);
	}
	
	std::string getMemoryUsageString() {
		const ysize GiB = 1024 * 1024 * 1024;
		const ysize MiB = 1024 * 1024;
		const ysize KiB = 1024;
		
		std::string output = "System memory use (tagged):\n";
		for (const auto& [tag, memory] : Statistics.TaggedAllocation) {
			output += "    " + Stringify(tag) + " : ";
			if (memory >= GiB)
				output += std::to_string((f64)memory / GiB) + " GiB\n";
			else if (memory >= MiB)
				output += std::to_string((f64)memory / MiB) + " MiB\n";
			else if (memory >= KiB)
				output += std::to_string((f64)memory / KiB) + " KiB\n";
			else
				output += std::to_string((u64)memory) + " B\n";
		}
		output += "   ----------------------------------\n";
		output += "    " + Stringify(Tag::Total) + " : ";
		if (Statistics.TotalAllocation >= GiB) {
			output += std::to_string((f64)Statistics.TotalAllocation / GiB) + " GiB\n";
		} else if (Statistics.TotalAllocation >= MiB) {
			output += std::to_string((f64)Statistics.TotalAllocation / MiB) + " MiB\n";
		} else if (Statistics.TotalAllocation >= KiB) {
			output += std::to_string((f64)Statistics.TotalAllocation / KiB) + " KiB\n";
		} else {
			output += std::to_string(Statistics.TotalAllocation) + " B\n";
		}
		return output;
	}
}
