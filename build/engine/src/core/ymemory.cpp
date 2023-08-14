#include"ymemory.hpp"

#include"logger.hpp"
#include"platform/platform_win32.hpp"
#include"platform/platform_linux.hpp"

namespace Yazh::Core::Memory {
	
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
		std::size_t TotalAllocation;
		std::size_t TaggedAllocation[static_cast<u8>(Tag::MAX)];
	} stats;
	
	inline void initialize() {
		Platform::zeroMemory(&stats, sizeof(Statistics));
	}
	
	inline void shutdown() {
	}
	
	void* allocate(std::size_t size, Tag tag) {
		if (tag == Tag::Unknown)
			Logger::Warn("Yazh::Memory::allocate called using Yazh::Memory::Tag::Unknown. Re-class this allocation.");
		
		stats.TotalAllocation += size;
		stats.TaggedAllocation[(u8)tag] += size;
		
		// TODO: Memory allignement
		void* block = Platform::allocate(size, false);
		Platform::zeroMemory(block, size);
		return block;
	}
	
	void free(void* block, std::size_t size, Tag tag) {
		stats.TotalAllocation -= size;
		stats.TaggedAllocation[(u8)tag] -= size;
		
		// TODO: Memory allignement
		Platform::free(block, size, false);
	}
	
	void* zero(void* block, std::size_t size) {
		return Platform::zeroMemory(block, size);
	}
	
	void* copy(void* dest, const void* source, std::size_t size) {
		return Platform::copyMemory(dest, source, size);
	}
	
	void* set(void* dest, i32 value, std::size_t size) {
		return Platform::setMemory(dest, value, size);
	}
	
	inline std::string getMemoryUsageString() {
		constexpr std::size_t GiB = 1024 * 1024 * 1024;
		constexpr std::size_t MiB = 1024 * 1024;
		constexpr std::size_t KiB = 1024;
		
		std::string output = "System memory use (tagged):\n";
		for (std::size_t t = 0; t < static_cast<u8>(Tag::MAX); ++t) {
			auto tag = static_cast<Tag>(t);
			auto memory = stats.TaggedAllocation[t];
			output += "    " + Stringify(tag) + " : ";
			if (memory >= GiB)
				output += std::to_string((f64)memory / GiB) + " GiB\n";
			else if (memory >= MiB)
				output += std::to_string((f64)memory / MiB) + " MiB\n";
			else if (memory >= KiB)
				output += std::to_string((f64)memory / KiB) + " KiB\n";
			else
				output += std::to_string(memory) + " B\n";
		}

		output += "   ----------------------------------\n";
		
		output += "    " + Stringify(Tag::MAX) + " : ";
		if (stats.TotalAllocation >= GiB)
			output += std::to_string((f64)stats.TotalAllocation / GiB) + " GiB";
		else if (stats.TotalAllocation >= MiB)
			output += std::to_string((f64)stats.TotalAllocation / MiB) + " MiB";
		else if (stats.TotalAllocation >= KiB)
			output += std::to_string((f64)stats.TotalAllocation / KiB) + " KiB";
		else
			output += std::to_string(stats.TotalAllocation) + " B";
		return output;
	}
} // namespace Yazh::Core::Memory
